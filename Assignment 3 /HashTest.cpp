//
//  HashTest.cpp
//  Assignment 3
//
//  Created by Victor Cabrera on 4/03/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "QuadraticProbing.h"
using namespace std;

int main(){
	HashTable<int> tester;
	double measurement = 0.10;
	int numofElements;
	srand(time(NULL));
	while(numofElements < 1000){
		if(tester.insert(rand() % 10000 + 1)) //Random number from 1 to 10000, just as a sort of measure
			numofElements++;
		if( static_cast<double>(numofElements)/1009 > measurement){
			cout << "At load factor: " << static_cast<double>(numofElements)/1009 << " the number of searches was: " << tester.returnProbe() << endl; //Calculates number of probes
			measurement = measurement + 0.10;
		}
	}
	return 0;
}
