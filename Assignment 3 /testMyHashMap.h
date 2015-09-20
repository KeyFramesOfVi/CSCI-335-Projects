//
//  testHashMap.h
//  Assignment 3
//
//  Created by Victor Cabrera on 4/03/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <chrono> 
#include "HashMap.h"
//  Map Tester class for the purpose of searching adjacent words inside of a map
//
//
//
// ******************PUBLIC OPERATIONS*********************
// void startFile( filename )       						  --> opens file that user entered before starting program
// void insertWord( )      									  --> inserts words from file into a vector. 
// HashMap<string,vector<string>> adjacentWordTime( size )  --> Calculates time needed to start and finish computeAdjacentWords, also calls the function. 
//																  Also returns the HashMap created.
// HashMap<string,vector<string>> computeAdjacentWords( size )  --> computes all words only one letter away from each other and puts them into a vector inside of the HashMap.
// void findAdjacentTime( adjacentWords )					  --> Calculates time needed to start and finish findAdjacentWords, also calls the function.
// void findadjacentWords ( adjacentWords ) 				  --> Searches for word entered by user to see if words one letter off from it are in HashMap.
// bool oneCharOff(const string & word1, const string& word2) --> Checks if two words are of the same length and have only one character off.
// void display ( adjacentWords)							  --> Displays the entire HashMap as it is to the user.

class testHashMap{
	private:
		ifstream inStream;
		string word;
		vector<string> wordArray;
	public:
		void startFile(string && filename);
		void insertWord();
		HashMap<string,vector<string>> adjacentWordTime(const int size);
		HashMap<string,vector<string>> computeAdjacentWords(const int size);
		void findAdjacentTime(const HashMap<string, vector<string>> & adjacentWords);
		void findAdjacentWords(string currentWord, const HashMap<string, vector<string>> & adjacentWords);
		bool oneCharOff(const string & word1, const string & word2);
		void display(HashMap<string,vector<string>> adjacentWords);
};