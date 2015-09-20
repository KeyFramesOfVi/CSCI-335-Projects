//
//  HashMap.h
//  Assignment 3
//
//  Created by Victor Cabrera on 4/06/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.
//

#ifndef MY_HASH_MAP_H
#define MY_HASH_MAP_H
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
// ******************PRIVATE OPERATIONS*********************
// 
// bool isActive( currentPos ) const		--> Returns true if currentPos is active
// int findPos( key )		--> Hashes and find the position that a key can be placed
// void rehash ( )							--> Will double the size of the HashTable so that Quadratic Probing remains effective
// size_t myhash ( key)     --> Function from textbook, initial hash function that places string in first spot. 
// 
//
//
//
// ******************PUBLIC OPERATIONS*********************
// 
// explicit HashMap ( int size )	 	 --> Constructor, sets initial size of HashMap
// bool contains( key )    				 --> Return true if x is present
// void makeEmpty( )      				 --> Remove all items from hashMap
// bool insert( key, obj )      		 --> Insert hashKey x and hashValue obj into hashMap
// bool insert( move::(key), move::(obj) )--> Moves hashKey x and hashValue obj into hashMap
// bool remove( key )      				 --> Removes one key from hashMap
// HashValue find( const hashKey & key)  --> searches to check if there is a key with it's value and returns the second element if so, much like a Map. 
// HashValue & operator[]( key )		 --> Mimics map bracket overloading. Returns key's hashValue if it's there, else it adds the key and returns empty hashValue.
// HashValue & operator[]( move::(key), move::(obj) ) --> Mimics map bracket overloading. Returns key's hashValue if it's there, else it moves the key and returns empty hashValue.
// int hashCode( string str ) 			 --> Global method to hash strings
// iterator begin(){ return mapArray.begin(); } --> returns the beginning of the mapArray vector via an iterator.
// const_iterator begin() const { return mapArray.begin(); } --> returns a const beginning of the mapArray vector via an iterator.
// iterator end() { return mapArray.end(); } --> returns the empty end of the mapArray vector via an iterator.
// const_iterator end() const { return mapArray.end(); } --> returns the empty end of the mapArray vector via an iterator.


template<typename HashKey, typename HashValue>
class HashMap 
{
	public:
		enum EntryType { ACTIVE, EMPTY, DELETED };
	 private:
		struct HashEntry{
			HashKey		element;
			HashValue	map;
			EntryType	info;

		HashEntry( 	const HashKey & v = HashKey{ }, 
					const HashValue & m = HashValue{ }, 
					EntryType i = EMPTY )
					: element{ v }, map{ m }, info{ i } { }
        
		HashEntry( 	HashKey && v, 
					HashValue && m, 
					EntryType i = EMPTY )
				: element{ std::move( v ) }, map{ std::move( m ) }, info{ i } { }
		};
		vector<HashEntry> mapArray;
		int currentSize;
		bool isActive( int currentPos ) const{ 
			return mapArray[ currentPos ].info == ACTIVE; 
		}
		int findPos( const HashKey & key ) const{
			int offset = 1;
			int currentPos = myhash( key );

			while( mapArray[ currentPos ].info != EMPTY && mapArray[ currentPos ].element != key ){
			currentPos += offset;  // Compute ith probe
			offset += 2;
			if( currentPos >= mapArray.size( ) )
				currentPos -= mapArray.size( );
			if( mapArray[ currentPos ].element == key )
				break;
			}
			return currentPos;
		}
		/*
		  Rehashes the current map to double the size for Quadratic Probing efficiency.
 		*/
		void rehash(){
			vector<HashEntry> oldArray = mapArray;
			// Create new double-sized, empty table
			mapArray.clear();
			mapArray.resize( nextPrime( 2 * oldArray.size( ) ) );
			// Copy table over
			currentSize = 0;
			for( auto & entry : oldArray )
				if( entry.info == ACTIVE )
					insert( std::move( entry.element ), std::move( entry.map ) );
		}
		/*
 		  Retrieves the hash value of a key (Algorithm from textbook)
 		*/
		size_t myhash( const HashKey & key) const{
			static hash<HashKey> hf;
			return hf( key ) % mapArray.size();
	}
    public:
  		explicit HashMap( int size ) : mapArray( nextPrime( size ) ){ makeEmpty(); }
	/*
	  Deletes entire map using Lazy Deletion.
 	*/
	/*
 	   If Active and if part of the map, returns true.
 	*/
		bool contains( const HashKey & key ) const{
		return isActive( findPos( key ) );
	}
		void makeEmpty( ){
		currentSize = 0;
		for( auto & entry : mapArray )
			entry.info = EMPTY;
	}
	/*
 	   Copies the key and object, placing it into the map. 
 	*/
		bool insert( const HashKey & key, const HashValue & obj ){
		// Find key hash value
		int currentPos = findPos( key );

		if( isActive( currentPos ) )
			return false;

		// Insert Items
		mapArray[ currentPos ].element = key;
		mapArray[ currentPos ].map = obj;
		mapArray[ currentPos ].info = ACTIVE;

		if( ++currentSize > mapArray.size( ) / 2 )
			rehash( );

	return true;
	}
	/*
	  Moves a key and object, placing it into the map and then destroying the rvalue. 
	 */
		bool insert( const HashKey && key, const HashValue && obj ){
		// Find key hash value
		int currentPos = findPos( key );
		if( isActive( currentPos ) )
			return false;

		// Move Items in mapArray
		mapArray[ currentPos ].element = std::move( key );
		mapArray[ currentPos ].map = std::move( obj );
		mapArray[ currentPos ].info = ACTIVE;

		if( ++currentSize > mapArray.size( ) / 2 )
			rehash( );

		return true;
	}
	/*
 	  Removes one object from map using lazy deletion
 	*/
		bool remove( const HashKey & key ){
		int currentPos = findPos( key );
		if( !isActive( currentPos ) )
			return false;

		mapArray[ currentPos ].info = DELETED;
		return true;
	}
	
	/*
	   Finds a key if active and if part of the map, and returns the hashvalue. otherwise returns a hashvalue of nothing. 
	 */
		HashValue find( const HashKey & key ) const{
		int currentPos = findPos ( key );
		if( isActive( currentPos ) )
			return mapArray[ currentPos ].map;
		else {
			HashValue empty;
			return empty;
		}
	}
	/*
 	   Overloaded Bracket Operator, acting much in the same way as a Map's Bracket Operator. Retrieves the HashValue of a Key,
 	   Otherwise, it inserts the key into a spot and returns the empty map. 
 	*/
		HashValue & operator[]( const HashKey & key ){	
			int currentPos = findPos( key );
			if( !isActive( currentPos ) ) {
				if(mapArray[ currentPos ].info == DELETED)
					mapArray[ currentPos ].info == ACTIVE;
				else{
					// Insert key as active
					mapArray[ currentPos ].element = key;
					mapArray[ currentPos ].info = ACTIVE;
					if( ++currentSize > mapArray.size( ) / 2 )
						rehash( );
				}
			}
			return mapArray[ currentPos ].map;
		}

	/*
		Overloaded Bracket Operator, acting much in the same way as a Map's Bracket Operator. Retrieves the HashValue of a Key,
 	    Otherwise, it moves the key into a spot and returns the empty map. 
	 */
		HashValue & operator[]( const HashKey && key ){	
			int currentPos = findPos( key );
			if( !isActive( currentPos ) ) {
				if(  mapArray[ currentPos ].info == DELETED )
					mapArray[ currentPos ].info == ACTIVE;
				else{
					// Insert key as active
					mapArray[ currentPos ].element = key;
					mapArray[ currentPos ].info = ACTIVE;
					if( ++currentSize > mapArray.size( ) / 2 )
						rehash( );
				}
			}
			return mapArray[ currentPos ].map;
		}

		typedef typename std::vector<HashEntry>::iterator iterator;
		typedef typename std::vector<HashEntry>::const_iterator const_iterator;
		iterator begin(){ return mapArray.begin(); }
		const_iterator begin() const { return mapArray.begin(); }
		iterator end() { return mapArray.end(); }
		const_iterator end() const { return mapArray.end(); }
};
#endif