//
//  HashMap.cpp
//  Assignment 3
//
//  Created by Victor Cabrera on 4/03/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.
//


#include "HashMap.h"
#include <iostream>
using namespace std;
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}

/**
 *  If a number is not Prime, get next Prime
 */

int nextPrime( int n ) 
{
    if( n % 2 == 0 )
        ++n;

    for( ; !isPrime( n ); n += 2 )
        ;
    return n;
}