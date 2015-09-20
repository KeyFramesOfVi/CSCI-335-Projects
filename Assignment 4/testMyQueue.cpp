//
//  testMyQueue.cpp
//  Priority Queue Hash Table
//
//  Created by Victor Cabrera on 4/22/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.
//

#include <iostream>
#include "testMyQueue.h"

int main(int argc, const char ** argv){
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    testMyQueue tester;
    BinomialQueue<string> testQueue;
    tester.startFile(argv[1]);
    tester.insertWord();
    tester.insertToQueue();
    tester.printEfficiency();
    tester.testDeleteMin();
    tester.testFind();
    tester.testRemove();
    return 0;
}
//Opens File
void testMyQueue::startFile(string && filename){
    inStream.open(filename);
	if(inStream.fail()){
		cout << "Error, file not found." << endl;
		exit(1);
	}
}
//Inserts words into a vector
void testMyQueue::insertWord(){
	while(inStream >> word)
		wordArray.push_back(word);
}
//Inserts words into Queue, and HashTable as well.
void testMyQueue::insertToQueue(){
    for(int i = 0; i < wordArray.size();i++)
        testQueue.insert(wordArray[i]);
    /*
     Debug functions that prove that the HashTable and Queue are one and in the same, in terms
     of having the same elements (Due to the fact that they have the same # of elements.
    */
    testQueue.getSize();
    testQueue.printHash();
   
}
void testMyQueue::printEfficiency(){
    testQueue.printCounters();
}
void testMyQueue::testDeleteMin(){
    cout << "This will print 10 times to test our DeleteMin function." << endl;
    for(int i = 0; i < 10; ++i){
		cout << "Original Min is " << testQueue.findMin() << endl;
		testQueue.deleteMin();
        cout << "New Min is " << testQueue.findMin() << endl;
	}
	cout << testQueue.findMin() << endl;
    //Check to see updated size 
    testQueue.getSize();
    testQueue.printHash();
}
void testMyQueue::testFind(){
    string test;
    char cont;
    cout << "Insert a word, search to see if the word is inside of the HashTable" << endl;
    //Contnues to ask User to find words until content.
    do{
        cin >> test;
        testQueue.testFind(test);
        cout << "Do you want to test another word? Enter 'Y'/'y' if so, any other character if not."
        << endl;
        cin >> cont;
    }while(cont == 'Y' || cont == 'y');
}
void testMyQueue::testRemove(){
    cout << "This is a test remove function. We will ask you to enter 5 \"Valid\" words" << endl;
    int removeCounter = 0;
    string testWord;
    //Tests 5 times SUCCESSFULLY (Will assert that it works by ensuring the user enters valid words that can be found.)
    while(removeCounter < 5){
        cout << "Please enter a word." << endl;
        cin >> testWord;
        while(!testQueue.remove(testWord)){
            cout << "Please enter a \"Valid\" word." << endl;
            cin >> testWord;
        }
        if (!testQueue.remove(testWord))
            cout << "Successfully removed, " << testWord << " can no longer be found" << endl;
        removeCounter++;
    }
    //Check to see updated size 
    testQueue.getSize();
    testQueue.printHash();
}