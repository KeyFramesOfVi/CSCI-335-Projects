//
//  testMaps.h
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
#include <map>
using namespace std; 
//  Map Tester class for the purpose of searching adjacent words inside of a map
//
//
//
// ******************PUBLIC OPERATIONS*********************
// void startFile( filename )   --> opens file that user entered before starting program
// void insertWord( )      		--> inserts words from file into a vector. 
// void adjacentWordTime( )     --> Calculates time needed to start and finish computeAdjacentWords, also calls the function.
// void computeAdjacentWords( ) --> computes all words only one letter away from each other and puts them into a vector
// void findAdjacentTime( ) 	--> Calculates time needed to start and finish findAdjacentWords, also calls the function.
// void findadjacentWords ( currentword ) --> Searches for word entered by user to see if words one letter off from it are in Map.
// bool oneCharOff(const string & word1, const string& word2) --> Checks if two words are of the same length and have only one character off

class testMaps{
	private:
		ifstream inStream;
		string word;
		vector<string> wordArray;
		map<string, vector<string>> adjacentWords;
	public:
		void startFile(string && filename);
		void insertWord();
		void adjacentWordTime();
		void computeAdjacentWords();
		void findAdjacentTime();
		void findAdjacentWords(string currentWord);
		bool oneCharOff(const string & word1, const string & word2);
};