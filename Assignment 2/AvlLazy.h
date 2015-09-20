//
//  AvlLazy.h
//  TreeTest
//
//  Created by Victor Cabrera on 3/10/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.
//

#ifndef TreeTest_AvlLazy_h
#define TreeTest_AvlLazy_h

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
using namespace std;

// AvlLazy class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlLazy
{
public:
    AvlLazy( ) : root{ nullptr }, insert_count_{0}, remove_count_{0}, contains_count_{0}, successful_removes_{0}, successful_contains_{0}
    { }
    
    AvlLazy( const AvlLazy & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }
    
    AvlLazy( AvlLazy && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    ~AvlLazy( )
    {
        makeEmpty( );
    }
    
    /**
     * Deep copy.
     */
    AvlLazy & operator=( const AvlLazy & rhs )
    {
        AvlLazy copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
    
    /**
     * Move.
     */
    AvlLazy & operator=( AvlLazy && rhs )
    {
        std::swap( root, rhs.root );
        
        return *this;
    }
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }
    
    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }
    
    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }
    
    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }
    
    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }
    
    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }
    
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
    
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }
    /**
     *Searches to see if string x is a recognition sequence in the string and
     *Then prints out alll of the names associated with it. Nothing is done if x is not found.
     */
    void query( const string & x)
    {
        query ( x, root );
    }
    /**
    * Computes the average Depth and number of Nodes of the tree. Nothing is done if the tree is NULL.
    */
    void statistics(){
        double avg_depth;
        int num_of_nodes = 0;
        num_of_nodes = 0;
        int sum_of_depth = 0;
        int max_depth = -1;
        statistics(root,num_of_nodes,0,sum_of_depth,max_depth);
        if (num_of_nodes > 0)
            avg_depth = static_cast<double>(sum_of_depth) / num_of_nodes;
        else
            avg_depth = 0.0;
        printStatistics(avg_depth,num_of_nodes);
    }
    /**
    * Prints out the statistics received from the Statistics function
    */
    void printStatistics(double avg_depth, int num_of_nodes){
        cout << "Number of Nodes: " << num_of_nodes << endl;
        cout << "The average Depth: " << avg_depth << endl;
        cout << "log2 ratio of the Number of Nodes: " << log2(num_of_nodes) << endl;
        cout << "Average Depth divided by log2 ratio of the Number of Nodes: " << avg_depth/log2(num_of_nodes) << endl;
    }
    int returnRecursiveInsert(){
        return insert_count_; 
    }
    int returnRecursiveRemove(){
        return remove_count_;
    }
    int returnRecursiveContains(){
        return contains_count_;
    }
    int returnSuccessfulContains(){
        return successful_contains_;
    }
    int returnSuccessfulRemoves(){
        return successful_removes_;
    }
    void resetCounts(){
        insert_count_ = remove_count_ = contains_count_ = successful_contains_ = successful_removes_ = 0;
    }
private:
    struct AvlNode
    {
        Comparable element;
        AvlNode   *left;
        AvlNode   *right;
        int       height;
        bool flag; //true if deleted
        
        AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0, bool start = false )
        : element{ ele }, left{ lt }, right{ rt }, height{ h }, flag{ start} { }
        
        AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0, bool start = false )
        : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h }, flag{ start} { }
    };
    
    AvlNode *root;
    mutable int insert_count_;
    mutable int contains_count_;
    mutable int remove_count_;
    mutable int successful_contains_;
    mutable int successful_removes_;
   
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, AvlNode * & t )
    {
        insert_count_++;
        if( t == nullptr )
            t = new AvlNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            t->element.Merge(x);
        
        balance( t );
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, AvlNode * & t )
    {
        insert_count_++;
        if( t == nullptr )
            t = new AvlNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            t->element.Merge(x); //duplicate
        balance( t );
    }
    
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, AvlNode * & t )
    {
        remove_count_++;
        if( t == nullptr )
            return;   // Item not found; do nothing
        
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else{
            t->flag = true;
	    successful_removes_++;
        }
        balance( t );
    }
    
    static const int ALLOWED_IMBALANCE = 1;
    
    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t )
    {
        if( t == nullptr )
            return;
        
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
            else
                if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
                    if( height( t->right->right ) >= height( t->right->left ) )
                        rotateWithRightChild( t );
                    else
                        doubleWithRightChild( t );
        
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }
    void query( const string & x, AvlNode * & t )
    {
        if( t == nullptr )
            return; // Item not found; do nothing
        else if( t->element > x )
            query( x, t->left );
        else if( t->element < x )
            query( x, t->right );
        else
            cout << t->element << endl; //element found, print out all enzyme acronyms associated with that Map.
    }
    void statistics(AvlNode *t, int &num_of_nodes, int current_depth, int & sum_of_depth, int & max_depth){
        if (t == nullptr)
            return; //at the last leaf of this side of the tree, so return.
        num_of_nodes++; //add 1 for every node traversed 
        sum_of_depth = sum_of_depth + current_depth; //everytime depth increases, add to sum
        if (current_depth > max_depth )
            max_depth = current_depth; //If currentDepth is larger, make that the new maxDepth. 
        statistics(t->left, num_of_nodes, current_depth+1, sum_of_depth, max_depth); //go left, increment currentDepth by 1.
        statistics(t->right, num_of_nodes, current_depth+1, sum_of_depth, max_depth); //go right, increment currentDepth by 1.
    }
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }
    
    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }
    
    
    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        contains_count_++;
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else if( t->flag )
            return nullptr;
        else{
	    successful_contains_++;
            return true;    // Match
	}
    }
    /****** NONRECURSIVE VERSION*************************
     bool contains( const Comparable & x, AvlNode *t ) const
     {
     while( t != nullptr )
     if( x < t->element )
     t = t->left;
     else if( t->element < x )
     t = t->right;
     else
     return true;    // Match
     
     return false;   // No match
     }
     *****************************************************/
    
    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }
    
    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( AvlNode *t ) const
    {
        if( t != nullptr && !t->flag )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }
    
    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
    }
    // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height( AvlNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }
    
    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }
    
    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }
    
    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }
    
    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }
    
    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }
};

#endif
