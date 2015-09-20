//
//  QuadraticProbing.h
//  Priority Queue Hash Table
//
//  Created by Victor Cabrera on 4/22/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.
//

#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;

int nextPrime( int n );

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x, p )       --> Insert x and p
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// voud updatePointer ( key, newValue ) --> changes pointers of keys whenever necessary 
// void makeEmpty( )      --> Remove all items
// int hashCode( string str ) --> Global method to hash strings
// HashedValue find ( key ) --> returns the HashedValue of a given HashedObj, returns nullptr otherwise
// void updatePointer( key, newValue ) -->updates a pointer with new value, made to update along with the percolateup
template <typename HashedObj, typename HashedValue>
class HashTable
{
public:
    explicit HashTable( int size = 101 ) : array( nextPrime( size ) )
    { makeEmpty( ); }
    
    bool contains( const HashedObj & x ) const
    {
        return isActive( findPos( x ) );
    }
    
    void makeEmpty( )
    {
        currentSize = 0;
        for( auto & entry : array )
            entry.info = EMPTY;
    }
    HashedValue find ( const HashedObj & key ) const
    {
        int currentPos = findPos ( key );
		if( isActive( currentPos ) )
			return array[ currentPos ].pointer; //Returns pointer if can be found
		else {
			HashedValue empty = nullptr;
			return empty; //returns empty (nullptr) if it can't be found
        }
    }
    void updatePointer( const HashedObj & key, const HashedValue & newValue ){
        //Finds position of key
        int currentPos = findPos( key );
        //Switches key with new key, to match change in Queue.
        array[ currentPos ].pointer = newValue;
    }

    bool insert( const HashedObj & x, const HashedValue & p )
    {
        // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;
        
        if( array[ currentPos ].info != DELETED )
            ++currentSize;
        
        array[ currentPos ].element = x;
        array[ currentPos ].pointer = p;
        array[ currentPos ].info = ACTIVE;
        
        // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );
        
        return true;
    }
    
    bool insert( HashedObj && x, const HashedValue & p )
    {
        // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;
        
        if( array[ currentPos ].info != DELETED )
            ++currentSize;
        
        array[ currentPos ].element = std::move( x );
        array[ currentPos ].pointer = p;
        array[ currentPos ].info = ACTIVE;
        
        // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );
        
        return true;
    }
    
    /*Debug function*/
    void printSize()
    {
        cout << "There are " << currentSize << " elements in HashTable." << endl;
    }

    bool remove( const HashedObj & x )
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;
        
        array[ currentPos ].pointer = nullptr; //represents pointer for assignment 4
        array[ currentPos ].info = DELETED;
        currentSize--; //This is here only for this function to emulate Queue size. This would normally go against the design for a QuadraticProbe but since we are not inserting anything else after the insert for this assignment, I am merely leaving this here to show that the HashTable removes when the Queue removes.
        return true;
    }
    
    enum EntryType { ACTIVE, EMPTY, DELETED };
       
private:
    struct HashEntry
    {
        HashedObj element;
        HashedValue pointer;
        EntryType info;
        
        HashEntry( const HashedObj & e = HashedObj{ }, const HashedValue & p = HashedValue{ }, EntryType i = EMPTY )
        : element{ e }, pointer{ p }, info{ i } { }
        
        HashEntry( HashedObj && e, HashedValue && p, EntryType i = EMPTY )
        : element{ std::move( e ) }, pointer{ std::move( p ) }, info{ i } { }
    };
    
    vector<HashEntry> array;
    int currentSize;
    
    bool isActive( int currentPos ) const
    { return array[ currentPos ].info == ACTIVE; }
    
    int findPos( const HashedObj & x ) const
    {
        int offset = 1;
        int currentPos = myhash( x );
        
        while( array[ currentPos ].info != EMPTY &&
              array[ currentPos ].element != x )
        {
            currentPos += offset;  // Compute ith probe
            offset += 2;
            if( currentPos >= array.size( ) )
                currentPos -= array.size( );
        }
        
        return currentPos;
    }
    void rehash( )
    {
        vector<HashEntry> oldArray = array;
        
        // Create new double-sized, empty table
        array.resize( nextPrime( 2 * oldArray.size( ) ) );
        for( auto & entry : array )
            entry.info = EMPTY;
        
        // Copy table over
        currentSize = 0;
        for( auto & entry : oldArray ){
            if( entry.info == ACTIVE )
                insert( std::move( entry.element ), std::move( entry.pointer ) );
        }
    }
    size_t myhash( const HashedObj & x ) const
    {
        static hash<HashedObj> hf;
        return hf( x ) % array.size( );
    }
};

#endif
