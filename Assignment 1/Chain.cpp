
//
//  Chain.cpp
//  The Big Five
//
//  Created by Victor Cabrera on 2/10/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.
//  Purpose: To create a vector like class called a Chain, a class that is modifiable through operators
//  much like a vector, rather than having to call class functions to modify it.

#include "Chain.h"

//Default Constructor, given initial values.
Chain::Chain(): size(0), capacity(100), arr(new int[capacity]){}
//One Parameter Constructor, with the initial element placed in the first position of the array, and the size
//adjusted to meet that fact.
Chain::Chain(int initialElement) : size(1), capacity(100), arr(new int[capacity]){
    arr[0] = initialElement; //arr with one element currently
}
//Destructor
Chain::~Chain(){
    cout << "This is the destructor." << endl;
    delete [] arr; //Deletes the arr once it is done with it.
    size = 0; //Sets all values to 0 
    capacity = 0; //Sets all values to 0
}
//Copy Constructor
Chain::Chain(const Chain & rhs): size(rhs.size), capacity(rhs.capacity), arr(new int{rhs.capacity}){
    cout << "This is the copy constructor." << endl;
    //copies from Chain rhs from it's first element to it's last, and then places each result into arr.
    copy(rhs.arr, rhs.arr + rhs.size, arr);
}
//Copy Assignment
Chain & Chain::operator= (const Chain & rhs){
    cout << "This is the copy assignment." << endl;
    //If they are not already the same Chain, rhs will have all values copied to the Chain that called this assignment.
    if(this != &rhs){
        size = rhs.size;
        arr = new int[rhs.size];
        CopyValues(rhs); 
    }
    return *this;
}
//Move Constructor
Chain::Chain(Chain && rhs): size(rhs.size), capacity(rhs.capacity), arr(rhs.arr){
    cout << "This is the move constructor." << endl;
    rhs.arr = nullptr; //sets to nullptr, making this not a direct copy and giving ownership to lhs.
    rhs.size = 0;
}
//Move Assignment
Chain & Chain::operator= (Chain && rhs){
    cout << "This is the move assignment." << endl; 
    if (this != &rhs){
        /*delete[] arr;
        arr = rhs.arr;
        size = rhs.size;
        rhs.arr = nullptr;
        rhs.size = 0;*/
        std::swap(arr, rhs.arr); //Swaps, giving ownership to the lhs
        size = rhs.size;
    }
    return *this;
}
ostream& operator<<(ostream& output, const Chain& rhs){
    /*This prints out every number from the Chain's dynamic array in a format that allows 
      it to print in an array style [1 2 3]. The if statement makes it so that the last number 
      of the array doesn't space, making the end array subscript bracket neater.*/
    output << "["; 
    for(int i = 0;i < rhs.size; i++){
        output << rhs.arr[i]; 
    if(i+1 < rhs.size)
        output << " "; 
    }
    output << "]\n";
    return output;
}
istream& operator>>(istream& input, Chain& rhs){
    string s; //This string allows us to grab the entire line that the user inputs 
    Chain temp;
    temp.arr = new int[100];
    temp.size = 0;
    getline(input,s); //We use getline to extract all of the input that the user entered
    /*For every char inside of string s that is a digit, we use the function stoi to turn that 
      specific character in the string into an integer, and then put the integer into the array,
      increasing the total size for each integer. temp.size serves as the way of adding to each section 
      of the array incrementally, while i goes through the string incrementally.*/
    for(unsigned int i = 0; i< s.size();i++){
        if(isdigit(s[i])){
            temp.arr[temp.size] = stoi(s.substr(i,i));
            temp.size++;
        }
    }
    rhs = std::move(temp); //move the contents of temp into the array we want to input to.
    return input;
}
Chain operator+ (const Chain& lhs, const Chain& rhs){
    Chain temp;
    temp.arr = new int[lhs.capacity]; //creates a temp that will hold the values of both Chains 
    temp.size = 0;
    /*The first for loop goes through the entirety of the first Chain, getting every value from it and 
      incrementing it's size. The second for loop uses lhs.size, which is the same size as the temp when it begins,
      in order to continue incrementing from the first slot of the array after lhs, until rhs ends. It is now an array
      concatenated with all the integers of both arrays. This does not use the CopyValues function since it requires
      all three arrays in order for the algorithm to work.*/
    for(int i = 0;i<lhs.size;i++){
        temp.arr[i] = lhs.arr[i];
        temp.size++;
    }
    for(int j = 0;j<rhs.size;j++){
        temp.arr[lhs.size+j] = rhs.arr[j];
        temp.size++;
    }
    return temp;
}
Chain operator+ (const Chain& lhs, int newValue){
    Chain temp;
    temp.arr = new int[lhs.size+1]; //Creates a new array with 1 extra slot for the new value being added 
    temp.size = lhs.size+1;
    temp.CopyValues(lhs);
    temp.arr[temp.size-1] = newValue;
    return temp;
}
int & Chain::operator[](const int position){
    return arr[position]; //returns the position from the array.
}
int Chain::Length(){
    return size; //returns size
}
void Chain::CopyValues(const Chain& rhs){
    /*Since a few functions use the same algorithm to retrieve every value from one array to another, this function 
      serves as a way of making the code a beat neater when doing so. This is for when you cannot directly copy or 
      move one Chain to another, due to adding extra values or for other concerns.*/
    for(int i = 0; i < rhs.size;i++)
	arr[i] = rhs.arr[i];
}
/*This function is technically pseudorandom, however it does effectively create it's own random Chain and output it 
  correctly regardless*/
Chain GetChain(){
    cout << "This is the GetChain function. It will create a random Chain of random size and random ints." << endl; 
    Chain temp;
    temp.size = rand()% 20 + 1;
    for(int i = 0;i < temp.size;i++)
	temp.arr[i] = rand()% 9 + 1;
    return temp;
}


