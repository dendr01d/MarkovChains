#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <iomanip>
#include <sstream>

#include "edge.h"

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
    
    void addEdge(token word) {
        ++totalWeight; //happens no matter what
        for (edge &e : edges) { //add weight to edge if it exists
            if (e.ID == word) {
                e.weight += 1;
                return;
            }
        }
        //otherwise make a new one
        edges.push_back(edge(word));
    }
    
    token getEdge(int rnum) {
        rnum %= totalWeight;
        for (edge e : edges) {
            rnum -= e.weight;
            if (rnum < 0) {
                return e.ID;
            }
        }
        //shouldn't happen but
        cout << "getEdge Error!\n";
        return 0;
    }
    
    void print(vector<string> &dictionary) {
        cout << setw(8) << dictionary[name] << ' ' << setw(2) << totalWeight << " : ";
        for (edge e : edges) {
            cout << setw(8) << dictionary[e.ID] << ' ' << setw(2) << e.weight << ' ';
        }
    }
    
};

bool compareNodes(Node a, Node b) {
    return (a.getName() < b.getName());
}

void readIn(vector<Node> &nodes, token word1, token word2) {
    for (auto i = nodes.begin(); i != nodes.end(); ++i) {
        if (i->getName() == word1) {
            i->addEdge(word2);
            return;
        }
    }
    nodes.push_back(Node(word1, word2));
}

token find(vector<Node> &nodes, token word, int r) {
    for (Node n : nodes) {
        if (n.getName() == word) {
            return (n.getEdge(r));
        }
    }
    cout << "find Error!/n";
    return 0;
}

/*
bool charMatch(char ch, string str) {
    for (char c : str) {
        if (ch == c) {
            return true;
        }
    }
    return false;
}
*/

static h_findInDict(vector<string> &dictionary, string target, int lb, int rb) {
    int look = lb + (rb - lb) / 2;
    if (dictionary[look] == target) {
        return look;
    } else if (target < dictionary[look]) {
        return h_findInDict(dictionary, target, lb, look);
    } else {
        return h_findInDict(dictionary, target, look, rb);
    }
}

token findInDict(vector<string> &dictionary, string target) {
    return lower_bound(dictionary.begin(), dictionary.end(), target) - dictionary.begin();
}

int main () {
    srand(0);
    
    vector<string> text;
    text.push_back("#BREAK");
    string input, word;
    
    while (getline(cin, input)) {
        stringstream ss(input);
        while (ss >> word) {
            //when I worry about cleaning input it'll happen here
            text.push_back(word);
            //also when I want to start inserting #BREAKS after sentence-ending punctuation
        }
        if (text.back() != "#BREAK") {
            text.push_back("#BREAK"); //for now we'll just break the text after line breaks
        }
    }
    
    for (string str : text) {
        cout << str << ' ';
        if (str == "#BREAK") {
            cout << endl;
        }
    }
    
    vector<string> dictionary(text);
    sort(dictionary.begin(), dictionary.end()); 
    
    //UGLY UGLY UGLY find a better way to do this
    dictionary.resize(unique(dictionary.begin(), dictionary.end()) - dictionary.begin());
    
    //consider this immutable now
    //tokens will refer to indices within this dictionary
    //should save space on string-storage but'll add quite a bit of processing time
    
    for (string str : dictionary) {
        cout << str << ' ';
    }
    cout << endl;
    
    
    vector<Node> nodes;
    token ta = findInDict(dictionary, text[0]);
    token tb;
    
    for (unsigned i = 1; i < text.size(); ++i) {
        tb = findInDict(dictionary, text[i]);
        readIn(nodes, ta, tb);
        
        ta = tb;
    }
    
    
    cout << "[[Read Complete]]\n";
    sort(nodes.begin(), nodes.end(), compareNodes);
    for (Node n : nodes) {
        n.print(dictionary);
        cout << '\n';
    }
    
    //reusing ta and tb here
    
    for (int i = 0; i < 10; ++i) {
        
        ta = findInDict(dictionary, "#BREAK"); //and this is why special tokens will be helpful
        //I could have just said "oh well the token for break is -1" and used that
        tb = find(nodes, ta, rand());
        
        while (dictionary[tb] != "#BREAK") {
            cout << dictionary[tb] << ' ';
            ta = tb;
            tb = find(nodes, ta, rand());
        }
        cout << '\n';
    }
    
    return 0;
}