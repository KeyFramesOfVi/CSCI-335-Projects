//
//  main.cpp
//  The Big Five
//
//  Created by Victor Cabrera on 2/10/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.
//  Purpose: To test and see if my Chain function works.

#include "Chain.h"
Chain GetChain();

int main(int argc, const char * argv[]) {
    Chain a, b, c; //Three empty chains are created
    Chain d{10}; //A chain containing just one element: 10
    cout << d; // Output is [ 10 ]
    cout << a.Length() << endl; //yields 0
    cout << "Please write integers in the format [1 2 3 4 etc]. Press enter when finished." << endl;
    cin >> a; // User types [2 3 7]
    cout << a; // Output is [2 3 7]
    cout << "Please write integers in the format [1 2 3 4 etc]. Press enter when finished." << endl;
    cin >> b; // User types [8 4 2 1]
    cout << b; // Output is [8 4 2 1]
    c = a; // Copy assignment
    cout << c; // Output should be [2 3 7]
    
    
     cout << a + b << endl; // Output is [2 3 7 8 4 2 1]
     cout << a + 5; // Output is [2 3 7 5]
     Chain e{c}; //Copy Constructor
     cout << e;  //Output should be [2 3 7]
     cout << a[1] << endl; //Should printout 3
     c[1] = 100; //Should change c[1]
     cout << c;  //Should print [2 100 7]
     cout << e;  //Should print [2 3 7]
     Chain f = GetChain(); //GetChain() should be a function that returns by value a Chain of some elements.
     //Write this simple functioin.
     cout << f; //Should print whatever GetChain() returned.
     
    return 0;
}

