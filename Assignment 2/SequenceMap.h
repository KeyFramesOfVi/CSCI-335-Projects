//
//  SequenceMap.h
//  TreeTest
//
//  Created by Victor Cabrera on 3/10/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.
//

#ifndef __TreeTest__SequenceMap__
#define __TreeTest__SequenceMap__

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "BinarySearchTree.h"
#include "AvlTree.h"
#include "AvlLazy.h"
using namespace std;
class SequenceMap{
public:
	/*PreCondition: SequenceMap is called
	  PostCondition: a Default Constructor SequenceMap with initial empty values is given back to the user
	*/
	SequenceMap(); 
	/*@param string & rhs is a string being compared to the SequenceMap via the > symbol. 
	  PreCondition: a member of type SequenceMap is being compared to a String with the > symbol.
	  PostCondition: The true or false value of this comparison via the Sequence Map's key is given back.*/
	bool operator>(const string & rhs);
	/*@param string & rhs is a string being compared to the SequenceMap via the < symbol. 
	  PreCondition: a member of type SequenceMap is being compared to a String with the < symbol.
	  PostCondition: The true or false value of this comparison via the Sequence Map's key is given back.*/
	bool operator<(const string & rhs);
	/*@param string new_name is a string with a Name of an enzyme via Acronym
	  PreCondition: a SequenceMap calls this function with a string.
	  PostCondition: The SequenceMap now has an enzyme acronym placed inside of it's vector
	*/
    void setNames(string new_name);
    /*@param string new_key is a string with a new key/recognition sequence that will be placed in the SequenceMap
      PreCondition: a SequenceMap calls this function with a string.
      PostCondition: The SequenceMap now has an enzyme key placed as it's string.
    */
	void setKey(string new_key);
	/*@param SequenceMap & rhs is a SequenceMap being compared to another Sequence Map through <
	  PreCondition: A SequenceMap is compared to another SequenceMap via <
	  PostCondition: Whether the lhs SequenceMap's key is alphabetically smaller than the other is given back via true or false
	*/
	bool operator< (const SequenceMap & rhs) const; /*Less than operator*/
	/*@param the Tree found a Node with a duplicate key
	  PreCondition: A Duplicate of the node attempting to be inserted was found.
	  PostCondition: The Node we are trying to insert is merged with the Node already there, adding all of the names into it*/
	void Merge(SequenceMap other); /*Merge Function*/
private:
	string key; //The Key/Recognition Sequence
    vector<string> names; //The Acronym Names of the enzymes
    /*@param ostream output is what will be printed, SequenceMap & rhs is the SequenceMap that we will print from
      PreCondition: We are trying to print a SequenceMap's Names based on the key entered by the user.
      PostCondition: the list of names in a SequenceMap is printed, showing all of the Names associated with said key.
    */
	friend ostream& operator<<(ostream& output, const SequenceMap & rhs);
};

#endif
