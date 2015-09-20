//
//  testMyBinaryHeap.h
//  Priority Queue Hash Table
//
//  Created by Victor Cabrera on 4/22/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.
//

//  Queue Tester class for the purpose of using a Hash Table implementation inside of the Queue to optimize operations
//
//
//
// ******************PUBLIC OPERATIONS*********************
// void startFile( filename )       						  --> opens file that user entered before starting program
// void insertWord( )      									  --> inserts words from file into a vector.
// void insertToQueue( )                                      --> inserts words from vector into the file, and therefore into the HashTable as well. Then prints size of both to prove they are one and the same.
// void printEfficiency( )                                    --> prints the number of comparisons and assignments done throughout the insert.
// void testDeleteMin( )                                      --> Calls DeleteMin 10 times, printing out the new min each time it does. 
// void testFind( )                                           --> Asks the user to enter a word, and tests it by searching for the word, and returning the result. Can be done any number of times.
// void testRemove( )                                         --> Asks the user to enter 10 valid words to remove from the Queue, and tries to remove again, returning false if it can no longer remove to prove that the word is no longer part of the Queue.

#ifndef testMyQueue_h
#define testMyQueue_h
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include "BinomialQueue.h"
using namespace std;
class testMyQueue{
private:
    ifstream inStream;
    string word;
    vector<string> wordArray;
    BinomialQueue<string> testQueue;
public:
    void startFile(string && filename);
    void insertWord();
    void insertToQueue();
    void printEfficiency();
    void testDeleteMin();
    void testFind();
    void testRemove();
    
    };
#endif
