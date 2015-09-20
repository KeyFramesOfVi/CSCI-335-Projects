//
//  BinarySearchTree.h
//  TreeTest
//
//  Created by Victor Cabrera on 3/10/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.
//

#ifndef TreeTest_BinarySearchTree_h
#define TreeTest_BinarySearchTree_h

#include <algorithm>
#include "dsexceptions.h"
using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree( ) : root{ nullptr }, insert_count_{0}, remove_count_{0}, contains_count_{0}, successful_removes_{0}, successful_contains_{0}
    {
    }
    
    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }
    
    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }
    
    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
    
    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );
        return *this;
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
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            //throw UnderflowException{ };
            return findMin( root )->element;
    }
    
    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            //throw UnderflowException{ };
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
    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }
    
    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }
    
    /**
     * Insert x into the tree; duplicates are merged.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
    
    /**
     * Insert x into the tree; duplicates are merg
ed.
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
    
private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        
        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
        : element{ theElement }, left{ lt }, right{ rt } { }
        
        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
        : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };
    
    BinaryNode *root;
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
    void insert( const Comparable & x, BinaryNode * & t )
    {
        insert_count_++;
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            t->element.Merge(x);  // Duplicate; merge
    
    }
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, BinaryNode * & t )
    {
        insert_count_++;
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            t->element.Merge(x);  // Duplicate; merge
    }
    
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, BinaryNode * & t )
    {
        remove_count_++;
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
            successful_removes_++;
        }
    }
    void query( const string & x, BinaryNode * & t )
    {
        if( t == nullptr )
            return; // Item not found; do nothing
        else if( t->element > x )
            query( x, t->left );
        else if( t->element < x )
            query( x, t->right );
        else
            cout << t->element << endl;  //element found, print out all enzyme acronyms associated with that Map.
    }
    void statistics(BinaryNode *t, int &num_of_nodes, int current_depth, int & sum_of_depth, int & max_depth){
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
    BinaryNode * findMin( BinaryNode *t ) const
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
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }
    
    
    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        contains_count_++;
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else{
            successful_contains_++;
            return true;    // Match
        }
    }
    /****** NONRECURSIVE VERSION*************************
     bool contains( const Comparable & x, BinaryNode *t ) const
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
    void makeEmpty( BinaryNode * & t )
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
    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
    }
    
    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }
};
#endif
