//
//  Vertex.h
//  Assignment 5
//
//  Created by Victor Cabrera on 5/12/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.
//

#ifndef Assignment_5_Vertex_h
#define Assignment_5_Vertex_h
#include <iostream>
#include <vector>
using namespace std;

// Vertex Class
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// void & SetID( x ) --> Sets the ID of the Vertex
// int GetID( )   --> Returns the ID of the Vertex
// size_t GetEdgeCount( ) --> returns the size of the edge vector
// void SetEdge ( pos, otherID ) --> Sets the ID of the Vector to int to of the edge vector at that position.
// int GetEdgeTo( pos ) --> returns the edge at that given position
// void ResizeEdgeVector( ) --> Resizes the edge vector to become one size bigger.
// void SetEdgeCost( pos, newCost ) --> Sets the cost of the edge at the given position
// const float GetEdgeCost( pos )    --> Retrieves the cost of the edge at the given position
// int GetTo( pos ) --> Returns the ID of the vector adjacent at the given position
// void SetDist( newDist ) --> sets the distance of the vector to a new distance
// float GetDist() const --> returns the distance of the vector from start point
// void SetKnown( isKnown ) --> Sets the bool known
// bool GetKnown( ) --> Retrieves known boolean value
// void SetPath( v ) --> Sets the path to the ID value of the vertex it travels to
// int GetPath( ) --> Returns the ID of the vector path, fused with vector or vertices to grab the vector
// ********************************************************



class Vertex{
private:
    struct Edge{
        int to; //The ID of a node that the edge can travel through
        float cost; //The cost to travel to that edge
        Edge(){
            to = cost = 0;
        }
    };
    vector<Edge> edges; //List of nodes that the vertex is adjacent to
    int id; //id of the Vertex retrieved from the file, uses this to emulate pointing
    float dist;
    bool known;
    int path;
public:
    Vertex() {
        edges.resize( 0 );
        id = dist = known = 0;
        path = -1; //Keeps the path at -1. The start vector should always have this at -1 to signify the end of the path.
    }
    void SetID(const int & x){ id = x; }
    int GetID(){ return id; }
    size_t GetEdgeCount(){ return edges.size(); }
    void SetEdge(const int & pos, const float & otherID){ edges[pos].to = otherID; }
    int GetEdgeTo(const int & pos){ return edges[pos].to; }
    void ResizeEdgeVector(){ edges.resize( edges.size() + 1 ); }
    void SetEdgeCost(const int & pos, const float & newCost){ edges[pos].cost = newCost; }
    const float GetEdgeCost( const int & pos){ return edges[pos].cost; }
    int GetTo(int pos){ return edges[pos].to; }
    void SetDist(float newDist){ dist = newDist; }
    const float GetDist() const { return dist; }
    void SetKnown(bool isKnown){ known = isKnown; }
    bool GetKnown(){ return known; }
    void SetPath(Vertex v) { path = v.GetID(); }
    int GetPath() { return path; }
};

#endif