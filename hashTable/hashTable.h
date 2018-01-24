//**********************************************************************************
// CONSTRUCTION: an approximate initial size or default of 101
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// int getCapacity( )     --> Return theLists.size()
// int getCurrentSize( )  --> Return currentSize;
// void makeEmpty( )      --> Remove all items
// Author: Erick Ramos
// Date: December 11, 2017
//***********************************************************************************
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

int nextPrime(int n);

template <typename T>
class HashTable {
    vector<list<T>> lists;
    int currentSize;
    
    void rehash(){
        vector<list<T>> oldLists = lists;
        
        lists.resize(nextPrime(2 * lists.size()));
        for(auto & currentList:lists) currentList.clear();
        
        currentSize = 0;
        for(auto & currentList : oldLists)
            for(auto & x:currentList) insert(std::move(x));
    }
    
    size_t myhash(const T & x) const{
        static hash<T> hf;
        return hf(x) % lists.size();
    }
    
    public:
    
    explicit HashTable(int size = 101):currentSize{0}{
        lists.resize(101);
    }
    
    int getCapacity() {
        return lists.size();
    }
    
    int getCurrentSize(){
        return currentSize;
    }
    
    bool contains(const T & x) const{
        auto & whichList = lists[myhash(x)];
        return find(begin(whichList), end(whichList), x) != end(whichList);
    }
    
    void makeEmpty(){
        for(auto & currentList:lists) currentList.clear();
    }
    
    bool insert(const T & x){
        auto & whichList = lists[myhash(x)];
        
        if(find(begin(whichList), end(whichList), x) != end(whichList)){
            return false;
        }
        
        whichList.push_back(x);
        
        if(++currentSize > lists.size()){
            rehash();
        }
    }
    
    bool insert(T && x){
        auto & whichList = lists[myhash(x)];
        
        if(find(begin(whichList), end(whichList), x) != end(whichList)){
            return false;
        }
        
        whichList.push_back(x);
        
        if(++currentSize > lists.size()){
            rehash();
        }
    }
    
    bool remove(const T & x){
        auto & whichList = lists[myhash(x)];
        
        auto itr = find(begin(whichList), end(whichList), x);
        
        if(itr == end(whichList)){
            return false;
        }
        
        whichList.erase(itr);
        --currentSize;
        return true;
    }
    
    void getStats(vector<int> & stats){
        for(auto & currentList:lists){
            int count = currentList.size();
            
            if(count) stats.push_back(count);
        }
    }
    
    void printStats(){
        vector<int> stats;
        getStats(stats);
        
        int min_id = 0, max_id = 0;
        double mean, sum = 0;
        
        for(int i = 0; i < stats.size(); i++){
            if(stats[i] < stats[min_id]) { 
                min_id = i;
            }
            
            if(stats[i] > stats[max_id]) {
                max_id = i;
            }
            
            sum += stats[i];
        }
        
        mean = sum / double(stats.size());
        
        cout << "\nMinimum Hash Table size: " << stats[min_id]
            << "\nMaximum Hash Table size: " << stats[max_id]
            << "\nAverage collision: " << mean << endl;
    }
};

bool isPrime(int n){
    if(n == 2 || n == 3){
        return true;
    }
    
    if(n == 1 || n % 2 == 0){
        return false;
    }
    
    for(int i = 3; i * i <= n; i += 2) {
        if(n % i == 0){
            return false;
        }
    }
    
    return true;
}

int nextPrime(int n) {
    if(n % 2 == 0) ++n;
    
    for( ; !isPrime(n); n += 2);
    return n;
}

size_t hash(const string & key) {
    size_t hashVal = 0;
    
    for(char ch:key){
        hashVal = 37 * hashVal + ch;
    }
    return hashVal;
}

size_t hash(int key) {
    return key;
}

#endif
