//
//  dsexceptions.h
//  Priority Queue Hash Table
//
//  Created by Victor Cabrera on 4/22/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.
//

#ifndef BINOMIAL_QUEUE_H
#define BINOMIAL_QUEUE_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include "dsexceptions.h"
#include "QuadraticProbing.h"
using namespace std;

// Binomial queue class with a Hashtable inside of it.
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x, and therefore inserts into HashTable as well
// deleteMin( )           --> Return and remove smallest item from Queue and HashTable
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// bool remove( x )       --> return true if successful removal of x from Queue, using percolateUp 
// void makeEmpty( )      --> Remove all items
// void merge( rhs )      --> Absorb rhs into this heap
// void testFind ( x ) --> returns the node that contains x, or nullptr if nothing (uses private find function to do so)
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinomialQueue
{
public:
    BinomialQueue( ) : theTrees( DEFAULT_TREES )
    {
        for( auto & root : theTrees )
            root = nullptr;
        currentSize = 0;
    }
    
    BinomialQueue( const Comparable & item ) : theTrees( 1 ), currentSize{ 1 }
    {
        theTrees[ 0 ] = new BinomialNode{ item, nullptr, nullptr, nullptr };
        assignmentCounter += 4;
    }
    
    BinomialQueue( const BinomialQueue & rhs )
    : theTrees( rhs.theTrees.size( ) ),currentSize{ rhs.currentSize }
    {
        for( int i = 0; i < rhs.theTrees.size( ); ++i )
        {
            theTrees[ i ] = clone( rhs.theTrees[ i ] );
            assignmentCounter++;
        }
    }
    
    BinomialQueue( BinomialQueue && rhs )
    : theTrees{ std::move( rhs.theTrees ) }, currentSize{ rhs.currentSize }
    {
    }
    
    ~BinomialQueue( )
    { makeEmpty( ); }
    
    
    /**
     * Deep copy.
     */
    BinomialQueue & operator=( const BinomialQueue & rhs )
    {
        BinomialQueue copy = rhs;
        assignmentCounter++;
        std::swap( *this, copy );
        return *this;
    }
    
    /**
     * Move.
     */
    BinomialQueue & operator=( BinomialQueue && rhs )
    {
        std::swap( currentSize, rhs.currentSize );
        std::swap( theTrees, rhs.theTrees );
        
        return *this;
    }
    
    /**
     * Return true if empty; false otherwise.
     */
    bool isEmpty( ) const
    { return currentSize == 0; }
    
    /**
     * Returns minimum item.
     * Throws UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        
        return theTrees[ findMinIndex( ) ]->element;
    }
    
    /**
     * Insert item x into the priority queue; allows duplicates.
     */
    void insert( const Comparable & x )
    {
        BinomialQueue oneItem{ x };
        h.insert(x, oneItem.theTrees[0]); //inserts element and pointer in hash
        comparisonCounter += 3; //comparisons in hash insert
        assignmentCounter += 5; //assignments in hash insert 
        merge( oneItem );
    }
    
    /**
     * Insert item x into the priority queue; allows duplicates.
     */
    void insert( Comparable && x )
    {
        BinomialQueue oneItem{ std::move( x ) };
        h.insert(std::move( x ), oneItem.TheTrees[0]); //inserts element and pointer in hash
        comparisonCounter += 3; //comparisons in hash insert
        assignmentCounter += 5; //assignments in hash insert
        merge( oneItem );
    }
    
    /**
     * Remove the smallest item from the priority queue.
     * Throws UnderflowException if empty.
     */
    void deleteMin( )
    {
        Comparable x;
        deleteMin( x );
    }
    
    /**
     * Remove the minimum item and place it in minItem.
     * Throws UnderflowException if empty.
     */
    void deleteMin( Comparable & minItem )
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        
        int minIndex = findMinIndex( );
        minItem = theTrees[ minIndex ]->element;
        BinomialNode *oldRoot = theTrees[ minIndex ];
        BinomialNode *deletedTree = oldRoot->leftChild;
        delete oldRoot;
        
        h.remove( minItem ); //Removes from hashTable afterwards

        
        // Construct H''
        BinomialQueue deletedQueue;
        deletedQueue.theTrees.resize( minIndex );
        deletedQueue.currentSize = ( 1 << minIndex ) - 1;
        for( int j = minIndex - 1; j >= 0; --j )
        {
            deletedQueue.theTrees[ j ] = deletedTree;
            deletedTree = deletedTree->nextSibling;
            deletedQueue.theTrees[ j ]->nextSibling = nullptr;
        }
        
        // Construct H'
        theTrees[ minIndex ] = nullptr;
        currentSize -= deletedQueue.currentSize + 1;
        
        merge( deletedQueue );
    }
    
    bool remove( const Comparable & item )
    {
        if ( !h.contains( item ) )
            return false;
        
        BinomialNode *temp = h.find(item);
        int index = findIndex( temp );
        
        // Moves the selected item to the top of the tree
        BinomialNode *deletedTree = percolateUp( temp );
        
        
        
        BinomialNode *oldRoot = deletedTree;
        deletedTree = deletedTree->leftChild;
        oldRoot = nullptr;
        delete oldRoot;
        h.remove( item ); //removes item from hashTable
        
        /*At this point, this function emulates deleteMin, and therefore uses the exact same ideas and names as deleteMin*/
        // Construct H''
        BinomialQueue deletedQueue;
        deletedQueue.theTrees.resize( index );
        deletedQueue.currentSize = ( 1 << index ) - 1;
        
        for( int j = index - 1; j >= 0; --j )
        {
            deletedQueue.theTrees[ j ] = deletedTree;
            deletedTree = deletedTree->nextSibling;
            deletedQueue.theTrees[ j ]->nextSibling = nullptr;
        }
        
        // Construct H'
        theTrees[ index ] = nullptr;
        currentSize -= deletedQueue.currentSize + 1;
        
        merge( deletedQueue );
        
        return true;
    }
    
    /**
     * Make the priority queue logically empty.
     */
    void makeEmpty( )
    {
        currentSize = 0;
        for( auto & root : theTrees )
            makeEmpty( root );
        h.makeEmpty();
    }
    
    /**
     * Merge rhs into the priority queue.
     * rhs becomes empty. rhs must be different from this.
     * Exercise 6.35 needed to make this operation more efficient.
     */
    void merge( BinomialQueue & rhs )
    {
        if( this == &rhs ){ // Avoid aliasing problems
            comparisonCounter++;
            return;
        }
        currentSize += rhs.currentSize;
        assignmentCounter++;
        if( currentSize > capacity( ) )
        {
            comparisonCounter++;
            int oldNumTrees = theTrees.size( );
            int newNumTrees = max( theTrees.size( ), rhs.theTrees.size( ) ) + 1;
            assignmentCounter += 2;
            theTrees.resize( newNumTrees );
            assignmentCounter++; //Because of i in for loop when initialized 
            for( int i = oldNumTrees; i < newNumTrees; ++i ){
                comparisonCounter++; //for each comparison in for loop
                theTrees[ i ] = nullptr;
                assignmentCounter+= 2; //for ++i and theTrees[ i ] = nullptr
            }
        }
        BinomialNode *carry = nullptr;
        assignmentCounter += 2; //for nullptr and i in for loop 
        for( int i = 0, j = 1; j <= currentSize; ++i, j *= 2 )
        {
            comparisonCounter++; //each comparison for the for loop
            BinomialNode *t1 = theTrees[ i ];
            BinomialNode *t2 = i < rhs.theTrees.size( ) ? rhs.theTrees[ i ] : nullptr;
            
            int whichCase = t1 == nullptr ? 0 : 1;
            whichCase += t2 == nullptr ? 0 : 2;
            whichCase += carry == nullptr ? 0 : 4;
            assignmentCounter += 5; //All assignments before switch is activated
            switch( whichCase )
            {
                case 0: /* No trees */
                case 1: /* Only this */
                    break;
                case 2: /* Only rhs */
                    theTrees[ i ] = t2;
                    rhs.theTrees[ i ] = nullptr;
                    assignmentCounter += 2;
                    break;
                case 4: /* Only carry */
                    theTrees[ i ] = carry;
                    carry = nullptr;
                    assignmentCounter += 2;
                    break;
                case 3: /* this and rhs */
                    carry = combineTrees( t1, t2 );
                    theTrees[ i ] = rhs.theTrees[ i ] = nullptr;
                    assignmentCounter += 2;
                    break;
                case 5: /* this and carry */
                    carry = combineTrees( t1, carry );
                    theTrees[ i ] = nullptr;
                    assignmentCounter += 2;
                    break;
                case 6: /* rhs and carry */
                    carry = combineTrees( t2, carry );
                    rhs.theTrees[ i ] = nullptr;
                    assignmentCounter += 2;
                    break;
                case 7: /* All three */
                    theTrees[ i ] = carry;
                    carry = combineTrees( t1, t2 );
                    rhs.theTrees[ i ] = nullptr;
                    assignmentCounter += 3;
                    break;
            }
        }
        assignmentCounter++; //for initalization of root
        //Ensures that each root's parent is nullptr so that the program doesn't crash
        for( auto & root: theTrees ){
            comparisonCounter++; //for loop
            assignmentCounter++; //for loop
            if(root != nullptr){
                assignmentCounter++; //assignment to root's parent
                root->parent = nullptr;
            }
            comparisonCounter++; //comparison through if statement
        }

        for( auto & root : rhs.theTrees ){
            root = nullptr;
            assignmentCounter += 2; //accounts for for loop format adds to increment i, also loop
            comparisonCounter++; //accounts to comparison for each increment
        }
        rhs.currentSize = 0;
        assignmentCounter++;
    }
    /* 
     DEBUG FUNCTION: Prints amount of elements & trees
    */
    void getSize()
    {
        cout << "There are " << currentSize << " elements in the priority queue" << endl;
        cout << "There are " << theTrees.size() << "Trees in the priority queue" << endl;
    }
    /*
     DEBUG FUNCTION: Prints out number of assignments and comparisons during insert
    */
    
    void printCounters(){
        cout << "There were " << assignmentCounter << " number of assignments" << endl;
        cout << "There were " << comparisonCounter << " number of comparisons" << endl; 
    }
    
    /*
     DEBUG FUNCTION: prints amount of elements in Hash, used to compare to Queue
    */
    void printHash()
    {
        h.printSize(); 
    }
    
    /*
     DEBUG FUNCTION/Function for assignment: Used to test private find function
    */
    void testFind(const Comparable & test)
    {
        BinomialNode* tester = find(test);
        if(tester != nullptr)
            cout << "Find was successful." << endl;
        else
            cout << "Find returned \"nullptr\" and failed." << endl;
    }
private:
    struct BinomialNode
    {
        Comparable    element;
        BinomialNode *parent; //Added parent pointer to include percolating up.
        BinomialNode *leftChild;
        BinomialNode *nextSibling;
        
        
        BinomialNode( const Comparable & e, BinomialNode *p, BinomialNode *lt, BinomialNode *rt )
        : element{ e }, parent{ p }, leftChild{ lt }, nextSibling{ rt } { }
        
        BinomialNode( Comparable && e, BinomialNode *p, BinomialNode *lt, BinomialNode *rt )
        : element{ std::move( e ) }, parent{ p }, leftChild{ lt }, nextSibling{ rt } { }
    };
    
    const static int DEFAULT_TREES = 1;
    HashTable<string,BinomialNode*> h;
    vector<BinomialNode *> theTrees;  // An array of tree roots
    int currentSize;                  // Number of items in the priority queue
    //Counters for assignment and comparisons throughout the insertion of words into Queue
    mutable int assignmentCounter = 0;
    mutable int comparisonCounter = 0;

    /**
     * Find index of tree containing the smallest item in the priority queue.
     * The priority queue must not be empty.
     * Return the index of tree containing the smallest item.
     */
    
    int findMinIndex( ) const
    {
        int i;
        int minIndex;
        
        for( i = 0; theTrees[ i ] == nullptr; ++i )
            ;
        
        for( minIndex = i; i < theTrees.size( ); ++i )
            if( theTrees[ i ] != nullptr &&
               theTrees[ i ]->element < theTrees[ minIndex ]->element )
                minIndex = i;
        
        return minIndex;
    }
    
    
    /**
     * Find index of tree containing the item in the priority queue we percolated up.
     * The priority queue must not be empty.
     * Return the index of tree containing this specific item. Emulates a lot of the
     * ideas in findMinIndex except that it looks for the node we are specifically
     * trying to delete, and returns that index. Therefore, it uses the same names as
     * findMinIndex to reflect that
     */
    
    int findIndex( BinomialNode * &t ) const
    {
        int index;
        BinomialNode *top = t;
        while( top->parent != nullptr ){
            top = top->parent;
        }
        for( int i = 0; i < theTrees.size(); ++i )
            if( theTrees[ i ] != nullptr)
                if( theTrees[ i ] == top )
                    index = i;
        
        return index;
    }
    

    /**
     * Return the capacity.
     */
    
    int capacity( ) const
    { return ( 1 << theTrees.size( ) ) - 1; }
    
    /**
     * Return the result of merging equal-sized t1 and t2.
     */
    
    BinomialNode * combineTrees( BinomialNode *t1, BinomialNode *t2 )
    {
        if( t2->element < t1->element ){
            comparisonCounter++;
            return combineTrees( t2, t1 );
        }
        t2->nextSibling = t1->leftChild;
        t1->leftChild = t2;
        t2->parent = t1;
        assignmentCounter += 3;
        return t1;
    }
    
    /**
     * Make a binomial tree logically empty, and free memory.
     */
    
    void makeEmpty( BinomialNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->leftChild );
            makeEmpty( t->nextSibling );
            delete t;
            t = nullptr;
        }
    }
    
    /**
     * Internal method to clone subtree.
     */
    BinomialNode * clone( BinomialNode * t ) const
    {
        if( t == nullptr ){
            comparisonCounter++;
            return nullptr;
        }
        else
            return new BinomialNode{ t->element, clone( t->leftChild ), clone( t->nextSibling ),clone( t->parent ) };
        
    }
    
    /**
       Percolates to the top of the tree by changing elements rather than pointers.
     */
    BinomialNode * percolateUp( BinomialNode * & t )
    {
        if(t->parent == nullptr){
            return t;
        }
        Comparable oldElement = t->element;
        h.updatePointer(t->element,t->parent);
        h.updatePointer(t->parent->element,t);
        t->element = t->parent->element;
        t->parent->element = oldElement;
        
        return percolateUp( t->parent );
    }
    /**
      Uses hash table to find the node that contains e, otherwise returns nullptr if fail
    */
    
    BinomialNode * find(const Comparable & e)
    {
        return h.find(e);
    }
    
};

#endif
