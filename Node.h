#ifndef NODE_H
#define NODE_H

#include "edge.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

class Node {
private:
    token name;
    vector<edge> edges;
    int totalWeight;
    
public:
    Node(token in1, token in2) : name(in1), totalWeight(0) {
        addEdge(in2);
    }
    
    token getName() { return name; }
    
    //so nodes can be sorted and junk? This'll need to be modified in a particular way if
    //  I increase the number of names a node can have
    bool operator<(Node &rhs);
    
    //so I can search for nodes in containers just using their names
    //bound to confusing. May need to change how this works once I add multiple names
    bool operator<(const int &rhs);
    
    //adds an edge with the particular token to the list of edges
    //if an edge with that token already exists, increments its weight
    void addEdge(token word);
    
    //given a random number, rnum, uses weighted probabilities
    //  to select an edge and return its token
    token getEdge(int rnum);
    
    //prints out the name of the node and its total weight
    //also prints out every edge within the node along with its weighted probability
    //for debugging purposes mainly
    void print(vector<string> &dictionary);
};

#endif