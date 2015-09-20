//
//  testGraph.h
//  Assignment 5
//
//  Created by Victor Cabrera on 5/12/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.

#ifndef testGraph_h
#define testGraph_h

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Graph.h"
using namespace std;

// Adjacent Graph Tester Class
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// void & OpenFile( std::move( fileName ) ) --> Opens the File entered by the user, or ends program if invalid.
// void CreateGraph( )   --> Creates the graph usng the file now loaded from OpenFile.
// void StartDijkstra ( std::move( startPos ) ) --> Starts up Dijkstra algorithm given the start position, and then asks the user for a position to print out the shortest path to said position.
// ********************************************************


class testGraph{
private:
    int fileNums; //Keeps track of numbers in file that represent node IDs
    float fileCost; //Keeps track of floats that represent the cost of the edges
    int pos; //position of vector currently
    ifstream inStream;
    Graph adjList; //Graph that holds adjacent list
    int vertexNum; //reads the vertex number from the file
    int counter; //counter for edge vector to set new edges in each next part of the vector
public:
    void OpenFile(string && fileName);
    void CreateGraph();
    void StartDijkstra(int && startPos);
};


#endif
