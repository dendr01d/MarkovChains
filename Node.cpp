#include "Node.h"

bool Node::operator<(Node &rhs) {
    return (name < rhs.name);
}

bool Node::operator<(const int &rhs) {
    return (name < rhs);
}

void Node::addEdge(token word) {
    ++totalWeight; //happens no matter what
    for (edge &e : edges) { //add weight to edge if it exists
        if (e.ID == word) {
            ++e.weight;
            return;
        }
    }
    //otherwise make a new one
    edges.push_back(edge(word));
}

token Node::getEdge(int rnum) {
    rnum %= totalWeight;
    for (edge e : edges) {
        rnum -= e.weight;
        if (rnum <= 0) {
            return e.ID;
        }
    }
    //shouldn't happen but
    cout << "getEdge Error!\n";
    return 0;
}

void Node::print(vector<string> &dictionary) {
    cout << setw(10) << dictionary[name] << "  " << setw(3) << totalWeight << " : ";
    
    for (edge e : edges) {
        cout << setw(10) << dictionary[e.ID] << ' ' << setw(2) << e.weight << " | ";
    }
    cout << '\n';
}