//
//  main2.cpp
//  TestTree
//
//  Created by Victor Cabrera on 3/10/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.
//


#include <iostream>
#include <fstream>
#include "SequenceMap.h"
#include "BinarySearchTree.h"
#include "AvlTree.h"
#include "AvlLazy.h"
#include "parser.h"
#include <math.h>
using namespace std;
int main(int argc, const char * argv[])
{	
    if (argc != 4) {
    cout << "Usage: " << argv[0] << " <filename> <queryfilename> <tree-type>" << endl;
    return 0;
  }
  string filename(argv[1]);
  string query_filename(argv[2]);
  string param_tree(argv[3]);
  parser tester;
  cout << "Input file is " << filename << ", and query file is " << query_filename << endl;
   /*Checks to see whether the flag dictates it should check BST, AVL, or LazyAVL Tree functions
     It then completes these 5 steps:
     1. Prints the number of recursive calls to Insert.
     2. Prints the # of Nodes, Average Depth, and Average Depth / log2(n). 
     3. Checks the query file, checking to see which sequences in the file are also in the tree,
     while printing out the number of contain recursive calls & successful contains.
     4. Removes all of the sequences in the file from the tree.
     5. Recomputes the statistics and checks to make sure none of the sequences from the query 
     file are inside of the tree.
   */
    if (param_tree == "BST") {
    	cout << "I will run the BST code " << endl;
    	BinarySearchTree<SequenceMap> tree;
    	cout << "Parsing database file and inserting enzymes into Tree." << endl;
   		tester.parseBST(tree, filename); //parses File
    	cout << "The number of recursive calls to insert was: " << tree.returnRecursiveInsert() << endl; //Counts Number of Inserts
    	cout << "Calculating Number of Nodes, Average Depth, and average depth divided by log10 of # of Nodes." << endl;
    	tree.statistics(); //Retrieves Average Depth, NumofNodes, and avgDepth/log of NoN. 
    	cout << "Checking query file to see what recognition sequences are contained in our tree." << endl;
    	tester.sequenceContainBST(tree, query_filename); //Checks every recognition sequence in query file in the tree
    	cout << "The number of recursive calls to contains was: " << tree.returnRecursiveContains() << endl; 
    	cout << "The number of times our contain function was successful was: " << tree.returnSuccessfulContains() << endl;
    	cout << "Checking query file to remove recognition sequences that are contained in our tree." << endl;
    	tester.removeSequenceBST(tree, query_filename); //Removes every recognition sequence in query file in the tree
    	cout << "The number of recursive calls to remove was: " << tree.returnRecursiveRemove() << endl;
    	cout << "The number of times our remove function was successful was: " << tree.returnSuccessfulRemoves() << endl;
    	cout << "Calculating Number of Nodes, Average Depth, and average depth divided by log10 of # of Nodes." << endl;
    	tree.statistics(); //Checks for Average Depth, Num of Nodes, and avgDepth/log of NoN after remoal.
    	tree.resetCounts(); //Resets counts for recursive calls/successful calls back to 0 
    	cout << "Checking query file to see what recognition sequences are contained in our tree." << endl;
    	tester.sequenceContainBST(tree, query_filename); //Now checks number of recursive contains and successful contains after removal
    	cout << "The number of recursive calls to contains was: " << tree.returnRecursiveContains() << endl; 
    	cout << "The number of times our contain function was successful was: " << tree.returnSuccessfulContains() << endl;
    } 
    /*Same as BST but with AVL*/
    else if (param_tree == "AVL") {
    	cout << "I will run the AVL code " << endl;
    	AvlTree<SequenceMap> tree;
    	cout << "Parsing database file and inserting enzymes into Tree." << endl;
    	tester.parseAVL(tree, filename);
    	cout << "The number of recursive calls to insert was: " << tree.returnRecursiveInsert() << endl; //Counts Number of Inserts
    	cout << "Calculating Number of Nodes, Average Depth, and average depth divided by log10 of # of Nodes." << endl;
    	tree.statistics(); //Retrieves Average Depth, NumofNodes, and avgDepth/log of NoN. 
    	cout << "Checking query file to see what recognition sequences are contained in our tree." << endl;
    	tester.sequenceContainAVL(tree, query_filename); //Checks every recognition sequence in query file in the tree
    	cout << "The number of recursive calls to contains was: " << tree.returnRecursiveContains() << endl; 
    	cout << "The number of times our contain function was successful was: " << tree.returnSuccessfulContains() << endl;
    	cout << "Checking query file to remove recognition sequences that are contained in our tree." << endl;
    	tester.removeSequenceAVL(tree, query_filename); //Removes every recognition sequence in query file in the tree
    	cout << "The number of recursive calls to remove was: " << tree.returnRecursiveRemove() << endl;
    	cout << "The number of times our remove function was successful was: " << tree.returnSuccessfulRemoves() << endl;
    	cout << "Calculating Number of Nodes, Average Depth, and average depth divided by log10 of # of Nodes." << endl;
    	tree.statistics(); //Checks for Average Depth, Num of Nodes, and avgDepth/log of NoN after remoal.
    	tree.resetCounts(); //Resets counts for recursive calls/successful calls back to 0 
    	cout << "Checking query file to see what recognition sequences are contained in our tree." << endl;
    	tester.sequenceContainAVL(tree, query_filename); //Now checks number of recursive contains and successful contains after removal
    	cout << "The number of recursive calls to contains was: " << tree.returnRecursiveContains() << endl; 
    	cout << "The number of times our contain function was successful was: " << tree.returnSuccessfulContains() << endl;
  	}  
    /*Same as BST but with LazyAVL*/
    else if (param_tree == "LazyAVL") {
   		cout << "I will run the Lazy AVL code " << endl;
    	AvlLazy<SequenceMap> tree;
    	cout << "Parsing database file and inserting enzymes into Tree." << endl;
    	tester.parseLazy(tree, filename);
    	cout << "The number of recursive calls to insert was: " << tree.returnRecursiveInsert() << endl; //Counts Number of Inserts
    	cout << "Calculating Number of Nodes, Average Depth, and average depth divided by log10 of # of Nodes." << endl;
    	tree.statistics(); //Retrieves Average Depth, NumofNodes, and avgDepth/log of NoN. 
    	cout << "Checking query file to see what recognition sequences are contained in our tree." << endl;
    	tester.sequenceContainLazy(tree, query_filename); //Checks every recognition sequence in query file in the tree
    	cout << "The number of recursive calls to contains was: " << tree.returnRecursiveContains() << endl; 
    	cout << "The number of times our contain function was successful was: " << tree.returnSuccessfulContains() << endl;
    	cout << "Checking query file to remove recognition sequences that are contained in our tree." << endl;
    	tester.removeSequenceLazy(tree, query_filename); //Removes every recognition sequence in query file in the tree
    	cout << "The number of recursive calls to remove was: " << tree.returnRecursiveRemove() << endl;
    	cout << "The number of times our remove function was successful was: " << tree.returnSuccessfulRemoves() << endl;
    	cout << "Calculating Number of Nodes, Average Depth, and average depth divided by log10 of # of Nodes." << endl;
    	tree.statistics(); //Checks for Average Depth, Num of Nodes, and avgDepth/log of NoN after remoal.
    	tree.resetCounts(); //Resets counts for recursive calls/successful calls back to 0 
    	cout << "Checking query file to see what recognition sequences are contained in our tree." << endl;
    	tester.sequenceContainLazy(tree, query_filename); //Now checks number of recursive contains and successful contains after removal
    	cout << "The number of recursive calls to contains was: " << tree.returnRecursiveContains() << endl; 
    	cout << "The number of times our contain function was successful was: " << tree.returnSuccessfulContains() << endl;
    	
    }	 
  else {
    	cout << "Unknown tree type " << param_tree << " (User should provide BST, AVL, or LazyAVL)" << endl;
  	}
  return 0;
}
