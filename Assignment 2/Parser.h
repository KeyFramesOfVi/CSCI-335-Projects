#include <iostream>
#include <fstream>
#include <cstdlib>
#include "BinarySearchTree.h"
#include "AvlTree.h"
#include "AvlLazy.h"
#include "SequenceMap.h"
#include "dsexceptions.h"

class parser{
private:
	ifstream inStream;
public:
	/*@param BinarySearchTree currentTree is the tree that is being included inside of our program, fileName is
	  the name of the file that we want to read given to us in the command line. 
	  PreCondition: BinarySearchTree was what was chosen on the command line
	  PostCondition: We will use this parser to add every enzyme into the BST.
	*/
	void parseBST(BinarySearchTree<SequenceMap> & current_tree, string filename);
	/*@param ABLTree currentTree is the tree that is being included inside of our program, fileName is
	  the name of the file that we want to read given to us in the command line. 
	  PreCondition: AVLTree was what was chosen on the command line
	  PostCondition: We will use this parser to add every enzyme into the AVLTree.
	*/
	void parseAVL(AvlTree<SequenceMap> & current_tree, string filename);
	/*@param AvlLazy currentTree is the tree that is being included inside of our program, fileName is
	  the name of the file that we want to read given to us in the command line. 
	  PreCondition: AVlLazy was what was chosen on the command line
	  PostCondition: We will use this parser to add every enzyme into the AVLLazy Tree.
	*/
	/*
	  *@param AvlLazy currentTree is the tree that is being included inside of our program, fileName is
	  the name of the file that we want to read given to us in the command line. 
	  PreCondition: AVlLazy was what was chosen on the command line
	  PostCondition: We will use this parser to add every enzyme into the AVLLazy Tree.
	*/
	void parseLazy(AvlLazy<SequenceMap> & current_tree, string filename);
	/*@param string filename is the string that holds the name of the file from the command line
	  PreCondition: a file has to be opened for the Parser.
	  PostCondition: the file has been opened and is now available to read through.
	*/
	void openFile(string fileName);
	/*
	  @param BinarySearchTree currentTree is the tree that is being included inside of our program, fileName is
	  the name of the file that we want to read given to us in the command line. 
	  PreCondition: A tree with the database file already inserted has called this function.
	  PostCondition: We will check to see how many nodes contain the enzyme names in the query file. 
	*/
	void sequenceContainBST(BinarySearchTree<SequenceMap> & current_tree, string fileName);
	/*
	  @param BinarySearchTree currentTree is the tree that is being included inside of our program, fileName is
	  the name of the file that we want to read given to us in the command line. 
	  PreCondition: A tree with the database file already inserted has called this function.
	  PostCondition: We will remove the nodes that contain the enzyme names in the query file. 
	*/
	void removeSequenceBST(BinarySearchTree<SequenceMap> & current_tree, string fileName);
	/*
	  @param AvlTree currentTree is the tree that is being included inside of our program, fileName is
	  the name of the file that we want to read given to us in the command line. 
	  PreCondition: A tree with the database file already inserted has called this function.
	  PostCondition: We will check to see how many nodes contain the enzyme names in the query file. 
	*/
	void sequenceContainAVL(AvlTree<SequenceMap> & current_tree, string fileName);
	/*
	  @param AvlTree currentTree is the tree that is being included inside of our program, fileName is
	  the name of the file that we want to read given to us in the command line. 
	  PreCondition: A tree with the database file already inserted has called this function.
	   PostCondition: We will remove the nodes that contain the enzyme names in the query file. 
	*/
	void removeSequenceAVL(AvlTree<SequenceMap> & current_tree, string fileName);
	/*
	  @param AvlLazy currentTree is the tree that is being included inside of our program, fileName is
	  the name of the file that we want to read given to us in the command line. 
	  PreCondition: A tree with the database file already inserted has called this function.
	  PostCondition: We will check to see how many nodes contain the enzyme names in the query file. 
	*/
	void sequenceContainLazy(AvlLazy<SequenceMap> & current_tree, string fileName);
	/*
	  @param AvlLazy currentTree is the tree that is being included inside of our program, fileName is
	  the name of the file that we want to read given to us in the command line. 
	  PreCondition: A tree with the database file already inserted has called this function.
	  PostCondition: We will check to see how many nodes contain the enzyme names in the query file. 
	*/
	void removeSequenceLazy(AvlLazy<SequenceMap> & current_tree, string fileName);
	/*PreCondition: The file has finished being read.
	  PostCondition: The file is now closed
	*/
	void closeFile();
};
