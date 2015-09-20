//
//  main.cpp
//  TreeTest
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

using namespace std;
int main(int argc, const char * argv[])
{	
    if (argc != 3) {
    cout << "Usage: " << argv[0] << " <file_name> <tree-type>" << endl;
    return 0;
    }
    string file_name(argv[1]);
    string param_tree(argv[2]);
    parser tester;
    string recognition;
    SequenceMap recog;
    cout << "Input file_name is " << file_name << endl;
    /*Checks to see whether the flag dictates it should check BST, AVL, or LazyAVL Tree functions
    It then parses the database file into the Tree, putting every single recognition sequence and 
    enzyme key into the tree as a SequenceMap*/
    if (param_tree == "BST") {
    	cout << "I will run the BST code" << endl;
    	BinarySearchTree<SequenceMap> tree;
    	tester.parseBST(tree,file_name);
    	/*Menu that allows the user to enter sequences that are then queried. Ends when the user presses "F" for finished*/
    	cout << "This is a queryTree. Please write a recognition string so that we can check to see if it is there\n"
    	     << "This will produce all of the enzyme names, or nothing, depending on if it can be found.\n"
    	     << "If you want to finish, please just type \"F\".\n";
    	while(recognition != "F"){
    		cin >> recognition;
    		if(recognition != "F"){
    	    	tree.query(recognition);
    	    	cout << "Please write another recognition string. If you want to finish, please just type \"F\"" << endl;
    		}
    	}	
    }	
  	/*Same as BST but with AVL*/
  	else if (param_tree == "AVL") {
    	cout << "I will run the AVL code" << endl;
    	AvlTree<SequenceMap> tree;
    	tester.parseAVL(tree,file_name);
    	cout << "This is a queryTree. Please write a recognition string so that we can check to see if it is there\n"
    	     << "This will produce all of the enzyme names, or nothing, depending on if it can be found.\n"
    	     << "If you want to finish, please just type \"F\".\n";
    	    while(recognition != "F"){
    			cin >> recognition;
    			if(recognition != "F"){
    		    	tree.query(recognition);
    		    	cout << "Please write another recognition string. If you want to finish, please just type \"F\"" << endl;
    			}
   	    	}
  	} 
  	/*Same as BST but with LazyAVL*/
  	else if (param_tree == "LazyAVL") {
    	cout << "I will run the Lazy AVL code" << endl;
	AvlLazy<SequenceMap> tree;
	tester.parseLazy(tree,file_name);
	cout << "This is a queryTree. Please write a recognition string so that we can check to see if it is there\n"
    	     << "This will produce all of the enzyme names, or nothing, depending on if it can be found.\n"
    	     << "If you want to finish, please just type \"F\".\n";
            while(recognition != "F"){
    		    cin >> recognition;
    			if(recognition != "F"){
    		    	tree.query(recognition);
    		        cout << "Please write another recognition string. If you want to finish, please just type \"F\"" << endl;
    			}
    		}
   		}
  	/*Error, none wrong flag was written in the command*/ 
  	else {
   		cout << "Unknown tree type " << param_tree << " (User should provide BST, AVL, or LazyAVL)" << endl;
  	}
    return 0;
}

