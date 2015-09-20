//
//  Graph.h
//  Assignment 5
//
//  Created by Victor Cabrera on 5/12/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.
//

#ifndef __Graph__
#define __Graph__

#include "Vertex.h"
#include "PairingHeap.h"
#include <limits.h>

// Adjacent Graph Class
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// void & SetSize( newSize ) --> sets the size of the Vertex Array, finds out how many Vertices are included
// SetID( pos )   --> Set's the ID of the Vertex 
// Vertex SetEdge( vertexPos, edgePos, nextID, newCost )  --> Set's Vertices adjacent to Vertex into Edge Vector, and set's the Cost of the Edge.
// void PrintAdjList( )        --> Prints the Adjacent List out (DEBUG FUNCTION)
// Vertex GetVertex( i )      --> Gets the Vertex at position i of the vector
// void Dijkstra( start )    --> Implements Dijkstra Algorithm at the given start position
// void PrintPath( pos )    --> Prints path from Dijkstra to the given position
// ********************************************************



class Graph{
private:
    vector<Vertex> vertices;
    PairingHeap minHeap;
    int size;
public:
    void SetSize(int newSize);
    int GetSize() { return size; }
    void SetID(const int & pos);
    void SetEdge(const int & vertexPos, const int & edgePos, const int & nextID, const float & newCost);
    void PrintAdjList(); 
    Vertex GetVertex(const int & i); //Retrieves Start Vertex for Dijkstra Algorithm
    void Dijkstra(Vertex start); //Dijkstra Algorithm
    void PrintPath(Vertex pos);
};

#endif /* defined(__Assignment_5__Graph__) */
