//
//  testHashMap.cpp
//  Assignment 3
//
//  Created by Victor Cabrera on 4/03/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.
//
#include "testMyHashMap.h"
using namespace std;

int main( int argc, char **argv ) {
	if (argc != 3) {
		cout << "Usage: " << argv[0] << " <filename>" << "<size of hash table>" << endl;
		return 1;
	}
	int size = atoi(argv[2]); //sets the size that the user enters
	char choice; //choice to print out the HashMap
	testHashMap tester;
	tester.startFile(argv[1]); //opens file that the user enters
	tester.insertWord();
	HashMap<string, vector<string>> adjacentWords = tester.adjacentWordTime(size);
	tester.findAdjacentTime(adjacentWords);
	cout << "Enter 'Y' if you want to display the hashmap, enter anything else if you don't." << endl;
	cin >> choice;
	if(choice == 'Y')
		tester.display(adjacentWords);
	return 0;
}
void testHashMap::startFile(string && filename){
	inStream.open((filename));
	if(inStream.fail()){
		cout << "Error, file not found." << endl;
		exit(1);
	}
}
void testHashMap::insertWord(){
	while(inStream >> word)
		wordArray.push_back(word);
}
HashMap<string,vector<string>> testHashMap::adjacentWordTime(const int size){
	cout << "Going to compute how much time it takes to compute adjacent words now." << endl;
	const auto begin = chrono::high_resolution_clock::now();
	HashMap<string,vector<string>> adjacentWords = computeAdjacentWords(size);
	const auto end = chrono::high_resolution_clock::now();
	cout << "The time to compute the adjacent words is: " << endl;
  	cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
 	cout << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "ms." << endl;
 	return adjacentWords;
}
HashMap<string,vector<string>> testHashMap::computeAdjacentWords(const int size){
	HashMap<string,vector<string>> adjacentWords(size);
	HashMap<int, vector<string>> wordsByLength(100000);

	// Group the words by their length
	for( auto & thisWord : wordArray )
		wordsByLength[ thisWord.length( ) ].push_back( thisWord );

	// Work on each group separately
	for( auto entry = wordsByLength.begin(); entry != wordsByLength.end(); ++entry ) {
		const vector<string> & groupsWords = entry->map;
   // Start putting adjacent words into vectors 
		for( int i = 0; i < groupsWords.size( ); ++i )
			for( int j = i + 1; j < groupsWords.size( ); ++j )
				if( oneCharOff( groupsWords[ i ], groupsWords[ j ] ) ) {
					adjacentWords[ groupsWords[ i ] ].push_back( groupsWords[ j ] ); //These emulate how maps work by using overloaded operators, check HashMap.h
					adjacentWords[ groupsWords[ j ] ].push_back( groupsWords[ i ] );
				}
	}
	return adjacentWords;
}
void testHashMap::findAdjacentTime(const HashMap<string, vector<string>> & adjacentWords){
	string currentWord;
	cout << "Enter a word to look for other words only one character off from this one." << endl;
	cin >> currentWord;

	cout << "Calculating time it takes to find words adjacent to " << currentWord << "." << endl;
	const auto begin = chrono::high_resolution_clock::now();
	findAdjacentWords(currentWord,adjacentWords);
	const auto end = chrono::high_resolution_clock::now();
	cout << "The time it took to attempt to find words adjacent to " << currentWord << " is: " << endl;
  	cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
 	cout << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "ms." << endl;
}
void testHashMap::findAdjacentWords(string currentWord, const HashMap<string, vector<string>> & adjacentWords){
	if( adjacentWords.contains( currentWord ) ) {
		// Gets a vector of the user inputted key
		auto adjacentVector = adjacentWords.find( currentWord );
		
		cout << "Word found, now outputting all adjacent words." << endl;
		cout << currentWord << " ";
		for(auto & itr : adjacentVector) // For Loop that will write every adjacent word using iterators
			cout << itr << " ";
		cout << "" << endl;
	}

	else
		cout << "Could not find word." << endl;
}
// Returns true if word1 and word2 are the same length
// and differ in only one character.
bool testHashMap::oneCharOff(const string & word1, const string & word2){
 	if( word1.length( ) != word2.length( ) ) //Checks to see if it has the same length
 		return false;

	int diffs = 0;

 	for( int i = 0; i < word1.length( ); ++i )
 		if( word1[ i ] != word2[ i ] )
 			if( ++diffs > 1 )
 				return false;

 	return diffs == 1;
}

void testHashMap::display(HashMap<string,vector<string>> adjacentWords){

		//Uses iterators to print out every word placed into the HashMap
	for( auto itr = adjacentWords.begin(); itr != adjacentWords.end(); ++itr ) {
		if( itr->map.size() != 0 ){ 
			cout << itr->element << " ";
			for( auto & itr2 : itr->map )
				cout << itr2 << " ";
		}
		if( itr->map.size() != 0 )
			cout << "\n";
	}
}