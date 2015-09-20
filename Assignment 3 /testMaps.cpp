#include <iostream>
//
//  testMaps.cpp
//  Assignment 3
//
//  Created by Victor Cabrera on 4/03/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.
//

#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <chrono> 
#include "testMaps.h"
using namespace std;
int main(int argc, char **argv){
	if (argc != 2) {
    	cout << "Usage: " << argv[0] << " <filename>" << endl;
    	return 0;
  	}
  	testMaps tester;
  	tester.startFile(argv[1]); //opens file
  	tester.insertWord();
  	tester.adjacentWordTime();
  	tester.findAdjacentTime();
  	return 0;
}
void testMaps::startFile(string && filename){
	inStream.open((filename));
	if(inStream.fail()){
		cout << "Error, file not found." << endl;
		exit(1);
	}
}
void testMaps::insertWord(){
	int count;
	while(inStream >> word) {
 		wordArray.push_back(word);
 		count++;
 	}
}
void testMaps::adjacentWordTime(){
	cout << "Going to compute how much time it takes to compute adjacent words now." << endl;
	const auto begin = chrono::high_resolution_clock::now();
	computeAdjacentWords();
	const auto end = chrono::high_resolution_clock::now();
	cout << "The time to compute the adjacent words is: " << endl;
  	cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
 	cout << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "ms." << endl;
}
void testMaps::computeAdjacentWords(){
	map<int,vector<string>> wordsByLength;

	// Group the words by their length
 	for( auto & thisWord : wordArray )
 		wordsByLength[ thisWord.length( ) ].push_back( thisWord );

 	// Now work on each group separately
 	for( auto & entry : wordsByLength ) {
 		const vector<string> & groupsWords = entry.second;
 	// Stuffs adjacentWords into vectors to store with each other 
 		for( int i = 0; i < groupsWords.size( ); ++i )
 			for( int j = i + 1; j < groupsWords.size( ); ++j )
 				if( oneCharOff( groupsWords[ i ], groupsWords[ j ] ) ) {
 					adjacentWords[ groupsWords[ i ] ].push_back( groupsWords[ j ] );
 					adjacentWords[ groupsWords[ j ] ].push_back( groupsWords[ i ] );
 				}
 	}
}
void testMaps::findAdjacentTime(){
	string currentWord;
	cout << "Enter a word to look for other words only one character off from this one." << endl;
	cin >> currentWord;

	cout << "Calculating time it takes to find words adjacent to " << currentWord << "." << endl;
	const auto begin = chrono::high_resolution_clock::now();
	findAdjacentWords(currentWord);
	const auto end = chrono::high_resolution_clock::now();
	cout << "The time it took to attempt to find words adjacent to " << currentWord << " is: " << endl;
  	cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
 	cout << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "ms." << endl;
}
void testMaps::findAdjacentWords(string currentWord){
	map<string, vector<string>>::const_iterator itr;
	itr = adjacentWords.find(currentWord);

 	if (itr == adjacentWords.end())
 		cout << "Was unable to find word.";
 	// Uses iterators to traverse through vector and print out all words adjacent to word entered.
 	else {
 		cout << "Word was found, will now output all adjacent words to this one." << endl;
 		for(auto itrtemp = itr->second.begin(); itrtemp != itr->second.end(); ++itrtemp) 
			cout << *itrtemp << " ";
		cout << "" << endl;
	}
}
// Returns true if word1 and word2 are the same length
// and differ in only one character.
bool testMaps::oneCharOff(const string & word1, const string & word2){
 	if( word1.length( ) != word2.length( ) )
 		return false;

	int diffs = 0;

 	for( int i = 0; i < word1.length( ); ++i )
 		if( word1[ i ] != word2[ i ] )
 			if( ++diffs > 1 )
 				return false;

 	return diffs == 1;
}