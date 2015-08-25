#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <iomanip>
#include <sstream>

using namespace std;

struct edge {
    edge(string str) : name(str), weight(1) {};
    string name;
    int weight;
};

class Node {
private:
    string name;
    vector<edge> edges;
    int totalWeight;
    
public:
    Node(string in1, string in2) : name(in1), totalWeight(0) {
        addEdge(in2);
    }
    
    string getName() { return name; }
    
    void addEdge(string str) {
        ++totalWeight; //happens no matter what
        for (edge &e : edges) { //add weight to edge if it exists
            if (e.name == str) {
                e.weight += 1;
                return;
            }
        }
        //otherwise make a new one
        edges.push_back(edge(str));
    }
    
    string getEdge(int num) {
        num %= totalWeight;
        for (edge e : edges) {
            num -= e.weight;
            if (num < 0) {
                return e.name;
            }
        }
        //shouldn't happen but
        return "Error";
    }
    
    void print() {
        cout << setw(8) << name << ' ' << setw(2) << totalWeight << " : ";
        for (edge e : edges) {
            cout << setw(8) << e.name << ' ' << setw(2) << e.weight << ' ';
        }
    }
    
};

bool compareNodes(Node a, Node b) {
    return (a.getName() < b.getName());
}

void readIn(vector<Node> &nodes, string word1, string word2) {
    for (auto i = nodes.begin(); i != nodes.end(); ++i) {
        if (i->getName() == word1) {
            i->addEdge(word2);
            return;
        }
    }
    nodes.push_back(Node(word1, word2));
}

string find(vector<Node> &nodes, string word, int r) {
    for (Node n : nodes) {
        if (n.getName() == word) {
            return (n.getEdge(r));
        }
    }
    return "Error!";
}

bool charMatch(char ch, string str) {
    for (char c : str) {
        if (ch == c) {
            return true;
        }
    }
    return false;
}

int main () {
    srand(0);
    
    vector<Node> nodes;
    
    string input;
    string prevword, word;
    
    while (getline(cin, input)) {
        stringstream ss(input);
        prevword = "#BREAK";
        while (ss >> word) {
            readIn(nodes, prevword, word);
            prevword = word;
        }
        if (prevword != "#BREAK") {
            readIn(nodes, prevword, "#BREAK");
        }
    }
    
    cout << "[[Read Complete]]\n";
    sort(nodes.begin(), nodes.end(), compareNodes);
    for (Node n : nodes) {
        n.print();
        cout << '\n';
    }
    
    //repurposing prevword and word here
    
    for (int i = 0; i < 10; ++i) {
        
        prevword = "#BREAK";
        word = find(nodes, prevword, rand());
        
        while (word != "#BREAK") {
            cout << word << ' ';
            prevword = word;
            word = find(nodes, prevword, rand());
        }
        cout << '\n';
    }
    
    return 0;
}