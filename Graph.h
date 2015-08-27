#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator> //why can't I just use auto?

using namespace std;

class Graph {
private:
    //int degree; //how many words a node's "name" consists of
    vector<Node> nodes;
    vector<string> dictionary; //might want to make this its own thing?
    
public:
    //for now it just always takes input from cin
    Graph();
    
    //prints a full "sentence"
    void talk();
    
    //prints out the graph and everything you need to know about it
    //install some options later so this can be used for saving/loading them
    void print();
};

#endif