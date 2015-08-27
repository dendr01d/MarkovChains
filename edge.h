#ifndef EDGE_H
#define EDGE_H

//maybe one day I'll need more indices than what an int allows
//who knows
typedef int token;

//special tokens that mean stuff like "#BREAK" will probably need to be interpreted by edges
//which means turning this into a class most likely
struct edge {
    edge(token IDin) : ID(IDin), weight(1) {};
    token ID;
    int weight;
};

#endif