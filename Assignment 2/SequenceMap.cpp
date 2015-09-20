//
//  SequenceMap.cpp
//  Assignment2
//
//  Created by Victor Cabrera on 3/8/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.
//

#include <vector>
#include "SequenceMap.h"
/*Default Constructor*/
SequenceMap::SequenceMap() {
}  
/*Operator to compare keys alphabetically*/
bool SequenceMap::operator< (const SequenceMap & rhs) const{
	return key < rhs.key;
} 
/*If the Maps both have the same key, this function fuses them together, adding the names
From the new map into the one already in the Tree*/
void SequenceMap::Merge(SequenceMap other) {
	for(int i = 0; i < other.names.size(); i++)
		names.push_back(other.names[i]);
} 
/*Adds name initally grabbed from the database file into the first slot of the Names vector*/
void SequenceMap::setNames(string new_name){
	if(names.size() == 0)
	    names.push_back(new_name);
	else
	    names[0] = new_name;
}
/*Sets key of the SequenceMap*/
void SequenceMap::setKey(string new_key){
        key = new_key;
}
/*Prints out the names from the enzyme*/
ostream& operator<<(ostream& output, const SequenceMap & rhs){
	cout << "The name(s) associated with this recognition sequence is/are" << endl;
    for(int i = 0; i < rhs.names.size();i++)
		output << rhs.names[i] << endl;
    return output;
}
/*Checks to compare string entered by the user to the key in SequenceMap*/
bool SequenceMap::operator<(const string & rhs){
	if(key < rhs)
		return true;
	return false;
}
/*Checks to compare string entered by the user to the key in SequenceMap*/
bool SequenceMap::operator>(const string & rhs){
	if(key > rhs)
		return true;
	return false;
}