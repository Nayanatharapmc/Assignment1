#include "BST.h"
#include "RBTree.h" 
#include "SplayTree.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <sstream>
#include <climits>

using namespace std;
using namespace std::chrono;

vector<int> readFile(const string& filename) {
    vector<int> data;
    ifstream infile(filename);
    
    if (!infile.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return data;
    }
    
    string line;
    while (getline(infile, line)) {
        if (line.empty()) continue;
        
        // Replace commas with spaces for easier parsing
        for (char& c : line) {
            if (c == ',') c = ' ';
        }
        
        istringstream iss(line);
        long long value;
        while (iss >> value) {
            data.push_back(static_cast<int>(value % INT_MAX));
        }
    }
    
    cout << "Loaded " << data.size() << " items from " << filename << endl;
    return data;
}

// Alternative method using string tokenization:
vector<int> readFileAlternative(const string& filename) {
    vector<int> data;
    ifstream infile(filename);
    
    if (!infile.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return data;
    }
    
    string line;
    while (getline(infile, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string token;
        
        while (getline(ss, token, ',')) {
            if (!token.empty()) {
                try {
                    long long value = stoll(token);
                    data.push_back(static_cast<int>(value % INT_MAX));
                } catch (const exception& e) {
                    cout << "Warning: Could not parse value: " << token << endl;
                }
            }
        }
    }
    
    cout << "Loaded " << data.size() << " items from " << filename << endl;
    return data;
}

int main() {
    cout << "Tree Performance Analysis" << endl;
    cout << "=========================" << endl;
    
    vector<string> sets = {"set1", "set2"};
    vector<string> dataFiles = {"data_1.txt", "data_2.txt", "data_3.txt"};
    vector<string> descriptions = {"50K items", "100K items", "200K items"};
    
    for (const string& set : sets) {
        cout << "\nTesting " << set << " (" << (set == "set1") << " data):" << endl;
        
        for (size_t fileIndex = 0; fileIndex < dataFiles.size(); fileIndex++) {
            const string& dataFile = dataFiles[fileIndex];
            cout << "\n=== Dataset: " << set << "/" << dataFile << " (" << descriptions[fileIndex] << ") ===" << endl;
            
            vector<int> insertData = readFile("code/data/insert/" + set + "/" + dataFile);
            vector<int> searchData = readFile("code/data/search/" + set + "/" + dataFile);
            vector<int> deleteData = readFile("code/data/delete/" + set + "/" + dataFile);
            
            if (insertData.empty()) continue;
            
            // BST Test
            {
                cout << "\n--- BST Results ---" << endl;
                BST bst;
                
                auto start = high_resolution_clock::now();
                for (int value : insertData) {
                    bst.put(value, value);
                }
                auto end = high_resolution_clock::now();
                auto insertTime = duration_cast<microseconds>(end - start);
                cout << "Insert: " << insertTime.count() << " microseconds" << endl;
                
                if (!searchData.empty()) {
                    start = high_resolution_clock::now();
                    for (int value : searchData) {
                        bst.contains(value);
                    }
                    end = high_resolution_clock::now();
                    auto searchTime = duration_cast<microseconds>(end - start);
                    cout << "Search: " << searchTime.count() << " microseconds" << endl;
                }
                
                if (!deleteData.empty()) {
                    start = high_resolution_clock::now();
                    for (int value : deleteData) {
                        bst.del(value);
                    }
                    end = high_resolution_clock::now();
                    auto deleteTime = duration_cast<microseconds>(end - start);
                    cout << "Delete: " << deleteTime.count() << " microseconds" << endl;
                }
            }
            
            // Splay Tree Test  
            {
                cout << "\n--- Splay Tree Results ---" << endl;
                SplayTree splay;
                
                auto start = high_resolution_clock::now();
                for (int value : insertData) {
                    splay.put(value, value);
                }
                auto end = high_resolution_clock::now();
                auto insertTime = duration_cast<microseconds>(end - start);
                cout << "Insert: " << insertTime.count() << " microseconds" << endl;
                
                if (!searchData.empty()) {
                    start = high_resolution_clock::now();
                    for (int value : searchData) {
                        splay.contains(value);
                    }
                    end = high_resolution_clock::now();
                    auto searchTime = duration_cast<microseconds>(end - start);
                    cout << "Search: " << searchTime.count() << " microseconds" << endl;
                }
                
                if (!deleteData.empty()) {
                    start = high_resolution_clock::now();
                    for (int value : deleteData) {
                        splay.del(value);
                    }
                    end = high_resolution_clock::now();
                    auto deleteTime = duration_cast<microseconds>(end - start);
                    cout << "Delete: " << deleteTime.count() << " microseconds" << endl;
                }
            }
            
            // RB Tree Test
            {
                cout << "\n--- RB Tree Results ---" << endl;
                RBTree rb;
                
                auto start = high_resolution_clock::now();
                for (int value : insertData) {
                    rb.put(value, value);
                }
                auto end = high_resolution_clock::now();
                auto insertTime = duration_cast<microseconds>(end - start);
                cout << "Insert: " << insertTime.count() << " microseconds" << endl;
                
                if (!searchData.empty()) {
                    start = high_resolution_clock::now();
                    for (int value : searchData) {
                        rb.contains(value);
                    }
                    end = high_resolution_clock::now();
                    auto searchTime = duration_cast<microseconds>(end - start);
                    cout << "Search: " << searchTime.count() << " microseconds" << endl;
                }
                
                if (!deleteData.empty()) {
                    start = high_resolution_clock::now();
                    for (int value : deleteData) {
                        rb.del(value);
                    }
                    end = high_resolution_clock::now();
                    auto deleteTime = duration_cast<microseconds>(end - start);
                    cout << "Delete: " << deleteTime.count() << " microseconds" << endl;
                }
            }
        }
    }
    
    cout << "\nAnalysis Complete!" << endl;
    return 0;
}