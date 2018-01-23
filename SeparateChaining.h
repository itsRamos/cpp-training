//**********************************************************************************
// Hash Table Dictionary
// The spelling checker accept words from a dictionary or document and then outputs the words in the document that are not in the dictionary. 
// Words in the dictionary are stored in a hash table and program outputs statistics about the hash table’s performance. 
// The dictionary file contains one word per line, and the first line will be the number of words in the file. 
// The document file contains lowercase words separated by spaces or new lines.
// SeparateChaining Hash table class
//
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
#ifndef SEPARATE_CHAINING_H
#define SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;


int nextPrime( int n );

template <typename T>
class HashTable {
    vector<list<T>> theLists;   // The array of Lists
    int  currentSize;

    void rehash( ) {
        vector<list<T>> oldLists = theLists;

        // Create new double-sized, empty table
        theLists.resize( nextPrime( 2 * theLists.size( ) ) );
        for( auto & thisList : theLists )
            thisList.clear( );

        // Copy table over
        currentSize = 0;
        for( auto & thisList : oldLists )
            for( auto & x : thisList )
                insert( std::move( x ) ); // rvalue, no copy
    }

    size_t myhash( const T & x ) const {
        static hash<T> hf;
        return hf( x ) % theLists.size( );
    }
  public:
    explicit HashTable( int size = 101 ) : currentSize{ 0 }
      { theLists.resize( 101 ); }
    int getCapacity() { return theLists.size(); }
    int getCurrentSize() { return currentSize; }
    
    bool contains( const T & x ) const {
        auto & whichList = theLists[ myhash( x ) ];
        return find( begin( whichList ), end( whichList ), x ) != end( whichList );
    }

    void makeEmpty( ) {
        for( auto & thisList : theLists )
            thisList.clear( );
    }
    
    bool insert( const T & x ) {
        auto & whichList = theLists[ myhash( x ) ];
        if( find( begin( whichList ), end( whichList ), x ) != end( whichList) )
            return false;
        whichList.push_back( x );
        if( ++currentSize > theLists.size( ) )
            rehash( );
    }
    bool insert( T && x ) {
        auto & whichList = theLists[ myhash( x ) ];
        if( find( begin( whichList ), end( whichList ), x ) != end( whichList) )
            return false;
        whichList.push_back( x );
        if( ++currentSize > theLists.size( ) )
            rehash( );
    }
    bool remove( const T & x ) {
        auto & whichList = theLists[ myhash( x ) ];
        auto itr = find( begin( whichList ), end( whichList ), x );
        if( itr == end( whichList ) )
            return false;
            
        whichList.erase( itr );
        --currentSize;
        return true;
    }
    
    void getStats( vector<int> & stats ) {
        for( auto & thisList : theLists ) {
            int count = thisList.size();
                if ( count ) stats.push_back( count );
        }
    }
    
    void printStats() {
        vector<int> stats;
        getStats( stats );
        
        int min_id=0, max_id=0;
        double mean, sum=0; 
        for( int i=0; i<stats.size(); i++ ) {
            if( stats[i] < stats[min_id]) min_id = i;
            if( stats[i] > stats[max_id]) max_id = i;
            sum += stats[i];
        }
        mean = sum / double(stats.size());
        
        cout << "\nminimum chain size is " << stats[min_id] 
             << "\nmaximum chain size is " << stats[max_id]
             << "\nThe average collision is " << mean << endl;
    }

};

/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
bool isPrime( int n ) {
    if( n == 2 || n == 3 )
        return true;
    if( n == 1 || n % 2 == 0 )
        return false;
    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;
    return true;
}

// To return a prime number at least as large as n, assumes n > 0.
int nextPrime( int n ) {
    if( n % 2 == 0 ) ++n;
    for( ; !isPrime( n ); n += 2 );
    return n;
}

// A hash routine for string objects.
size_t hash( const string & key ) {
    size_t hashVal = 0;
    for( char ch : key )
        hashVal = 37 * hashVal + ch;
    return hashVal;
}

// A hash routine for ints.
size_t hash( int key ) { return key; }

#endif
