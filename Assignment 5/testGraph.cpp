//
//  testGraph.cpp
//  Assignment 5
//
//  Created by Victor Cabrera on 5/12/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.
//

#include "testGraph.h"

int main(int argc, const char * argv[]){
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <filename>" << " <starting vertex #>" << std::endl;
        return 1;
    }
    testGraph tester;
    tester.OpenFile(argv[1]);
    tester.CreateGraph();
    tester.StartDijkstra(atoi(argv[2]));
    return 0;
}
void testGraph::OpenFile( string && fileName){
    inStream.open(fileName);
    if(inStream.fail()){
        cout << "Error. This file could not open." << endl;
        exit(1);
    }
}
void testGraph::CreateGraph(){
    inStream >> fileNums;
    adjList.SetSize(fileNums); //First graphs the size of the vector array and then sets it
    while(inStream >> fileNums){
        pos = fileNums;
        adjList.SetID(pos); //The Vertex that we will be adding adjacent edges to
        counter = 0;
        while(inStream.peek() != -1){
            inStream >> fileNums;
            if(fileNums == -1) //If either fileNums or fileCost grabs -1, break and move to the next line
                break;
            inStream >> fileCost;
            if(fileCost == -1)
                break;
            adjList.SetEdge(pos,counter,fileNums,fileCost); //Sets the edge using the parameters received
            counter++;
        }
    }
    adjList.PrintAdjList();
}
void testGraph::StartDijkstra(int && startPos){
    if(startPos < 0 || startPos >= adjList.GetSize()){
        cout << "This is not a valid startPos in the Vertex" << endl;
        exit(1);
    }
    cout << "Starting position is " << startPos << endl;
    adjList.Dijkstra(adjList.GetVertex(startPos));
    char choice;
    int vertexNum;
    do{
        cout << "Enter a valid Vertex number. This will print the shortest path to that Vertex." << endl;
        cin >> vertexNum;
        /* Checks to see whether user enters a number in a valid range so that program doesn't break */
        while (vertexNum < 0 || vertexNum >= adjList.GetSize()){
            cout << "Invalid Number, try again." << endl;
            cin >> vertexNum;
        }
        /* If the Distance is still INT_MAX, that means there was no path from it to anywhere else */
        if(adjList.GetVertex(vertexNum).GetDist() == INT_MAX){
            cout << "Getting to the position written is impossible." << endl;
        }
        else{
            cout << "The total cost to " << adjList.GetVertex(vertexNum).GetID() << " is " << adjList.GetVertex(vertexNum).GetDist() << endl;
            cout << "The Path is: " << endl;
            adjList.PrintPath(adjList.GetVertex(vertexNum));
            cout << endl;
        }
        cout << "Would you like to try another Vertex? If so, enter \'Y\' or \'y\'. Otherwise, enter anything else." << endl;
        cin >> choice;
    } while(choice == 'Y' || choice == 'y');
}
