//
//  Chain.h
//  The Big Five
//
//  Created by Victor Cabrera on 2/10/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.
//  Purpose: To create a vector like class called a Chain, a class that is modifiable through operators
//  much like a vector, rather than having to call class functions to modify it.

#ifndef __The_Big_Five__Chain__
#define __The_Big_Five__Chain__

#include <iostream>
#include <cstdlib>
using namespace std;

class Chain{
private:
    int size; //The current size of the dynamic array
    int capacity; //The amount the array can hold
    int *arr; //The int * that will become a dynamic array and hold the values given to us

    /*@param ostream& output will obtain sequence of characters and other data, outputting them when it is returned, 
      @param const Chain& rhs will be the object of type Chain being outputted in this case.
      Pre-Condition: When a object of type Chain is outputted "cout << ChainType;", it will take in the class and label it as a const Chain called rhs and use this function to output.
      Post-Condition: Every element in the dynamic array inside of the Chain will be outputted, in the format [1 2 3 4 5 etc].
    */
    friend ostream& operator<<(ostream& output, const Chain & rhs);
    /*@param istream& input will read and interpret a sequence of characters and other data, inputting them when it is returned,
      @param const Chain& rhs will be the object of type Chain being outputted in this case.
      Pre-Condition: When a object of type Chain is inputted "cin >> ChainType;", it will take in the class and label it as a const Chain called rhs and input into this function.
      Post-Condition: The object will take in as many elements as the user desires, in the format [1 2 3 4 5 etc].
    */
    friend istream& operator>>(istream& input, Chain & rhs);
    /*@param const Chain& lhs will be the first of two objects of type Chain being added together.
      @param const Chain& rhs will be the second of two objects of type Chain being added together.
      Pre-Condition: When two objects of type Chain are added together, this function will be called to create a temporary object of type Chain that will be the concatenation of the two dynamic arrays inside of the class.
      Post-Condition: The sum of the two objects, now in a third object of type Chain, will be returned to represent the concatenation of the two dynamic arrays inside of the class.*/
    friend Chain operator+(const Chain& lhs, const Chain& rhs);\
    /*@param const Chain& lhs will be the object of type Chain that is part of the addition operation
      @param int newValue will be the number that will be concatenated into the Chain.
      Pre-Condition: When an object of type chain is added to an int, this function will be called to create a new object of type Chain
      Post-Condition: A new object of type Chain will be returned that concatenates the array with the integer it was added to.
    */
    friend Chain operator+(const Chain& lhs, int newValue);
    /*Pre-Condition: the function GetChain is called, otherwise no other requirements are needed for this function to perform.
      Post-Condition: the function returns a Chain with a random number of integers, randomly chosen. 
    */
    friend Chain GetChain();
public:
    /*Pre-Condition: An object of type Chain, with no parameters, is evoked.
      Post-Condition: An object of type Chain, with size 0, capacity 100, and no elements is returned.
    */ 
    Chain(); //Default Constructor
    /*@param initialElement is the element that is called along with the object of type Chain.
      Pre-Condition: An object of type Chain, with one int parameter, is evoked.
      Post-Condition: An object of type Chain, with size 1, capacity 100, and an element is returned. 
    */
    Chain(int initialElement); //One Element Constructor
    /*@param const Chain& rhs is the Chain called along with the object of type Chain.
      Pre-Condition: An object of type Chain, called along with another object of type Chain.
      Post-Condition: An object of type Chain, now equal to the other object of type Chain, is returned.
    */
    Chain(const Chain& rhs); //Copy Constructor
    /*@param const Chain&& rhs is the temporary Chain called along with the object of type Chain.
      Pre-Condition: An object of type Chain, called along with an object of type Chain that is rvalue referenced. (std::move, &&)
      Post-Condition: An object of type Chain, is now equal to the temporary object of type Chain, which moved it's values to the initalized Chain and then emptied itself. 
    */
    Chain(Chain&& rhs); //Move Constructor
    /*@param const Chain& rhs is the Chain that the left hand Chain is going to equal, or effectively become.
      Pre-Condition: When the equal sign is evoked for two objects of type Chain, effectively making the left hand Chain the same as the right hand chain, this assignment function is called.
      Post-Condition: The Chain on the left hand side of the equal sign will now effectively be a copy of the Chain on the right hand side of the equal sign.
    */
    Chain & operator= (const Chain & rhs); //Copy Assignment
    /*@param const Chain&& rhs is the temporary Chain that will moved into the left hand Chain.
      Pre-Condition: When the equal sign is evoked for an object of type Chain and an rvalue reference of type Chain, this assignment function is called.
      Post-Condition: The Chain on the left hand side of the equal sign will now have the values of the temporary Chain on the right hand side of the equal sign.
    */
    Chain & operator= (Chain && rhs); //Move Assignment
    /*@param const int position is the position that we will access inside of the Chain.
      Pre-Condition: When a specific element of the Chain (Chain[1]), is evoked, this subscript operator will be called.
      Post-Condition: the specific element in the dynamic array inside of the member of type Chain will be returned.
    */
    int & operator[](const int position);
    /*Pre-Condition: Called when an Chain is to be deleted.
      Post-Condition: The dynamic array is deleted and the Chain is effectively emptied.
    */
    ~Chain(); //Destructor
    /*Pre-Condition: the function is called with an object of type Chain (Chain.Length()) 
      Post-Condition: The current size of the Chain is returned.
    */
    int Length(); //Returns the current number of elements held by the array (the current size)
    /*@param: const Chain& rhs is the object of type Chain that is going to be copied.
     Pre-Condition: the function is called with an object of type Chain, specifically called during other functions in the class.
     Post-Condition: The Chain that called it now has all of the arr values of Chain& rhs.
     */
    void CopyValues(const Chain& rhs);
};

#endif /* defined(__The_Big_Five__Chain__) */

