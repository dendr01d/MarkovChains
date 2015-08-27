#include "Graph.h"

static bool charMatch(char ch, string str) {
    for (char c : str) {
        if (ch == c) {
            return true;
        }
    }
    return false;
}

static void readIn(vector<Node> &nodes, token word1, token word2) {
    auto target = lower_bound(nodes.begin(), nodes.end(), word1);
    if (target != nodes.end() && target->getName() == word1) {
        target->addEdge(word2);
    }
    else {
        nodes.push_back(Node(word1, word2));
        sort(nodes.begin(), nodes.end());
    }
}

static token find(vector<Node> &nodes, token word, int r) {
    auto target = lower_bound(nodes.begin(), nodes.end(), word);
    if (target != nodes.end()) {
        return (target->getEdge(r));
    }
    else {
        cout << "find Error!/n";
        return 0;
    }
}

static token findInDict(vector<string> &dictionary, string target) {
    return lower_bound(dictionary.begin(), dictionary.end(), target) - dictionary.begin();
}

Graph::Graph() {
    srand(0);
    vector<string> text;
    text.push_back("#BREAK");
    string input, word;
    
    while (getline(cin, input)) {
        stringstream ss(input);
        while (ss >> word) {
            //when I worry about cleaning input it'll happen here
            text.push_back(word);
            if (charMatch(text.back().back(), ".?!")) { //insert breaks after sentence-ending punctuation
                text.push_back("#BREAK");
            }
        }
        if (text.back() != "#BREAK") {
            text.push_back("#BREAK"); //break the text after line breaks
        }
    }
    
    cout << endl;
    for (string str : text) {
        cout << str << ' ';
        if (str == "#BREAK") {
            cout << endl;
        }
    }
    cout << endl;
    
    dictionary = text;
    sort(dictionary.begin(), dictionary.end()); 
    //UGLY UGLY UGLY find a better way to do this
    dictionary.resize(unique(dictionary.begin(), dictionary.end()) - dictionary.begin());
    
    token prev = findInDict(dictionary, "#BREAK");
    token curr;
    
    for (unsigned i = 1; i < text.size(); ++i) {
        curr = findInDict(dictionary, text[i]);
        /////
        //cout << dictionary[prev] << " (" << prev << ") ";
        //cout << dictionary[curr] << " (" << curr << ")\n";
        /////
        readIn(nodes, prev, curr);
        prev = curr;
    }
    
    sort(nodes.begin(), nodes.end());
}

void Graph::talk() {
    token prev, curr;
    
    prev = findInDict(dictionary, "#BREAK"); //and this is why special tokens will be helpful
    //I could have just said "oh well the token for break is -1" and used that
    curr = find(nodes, prev, rand());
    
    while (dictionary[curr] != "#BREAK") {
        cout << dictionary[curr] << ' ';
        prev = curr;
        curr = find(nodes, prev, rand());
    }
    cout << '\n';
}

void Graph::print() {
    for (string str : dictionary) {
        cout << str << ' ';
    }
    cout << endl;
    for (Node n : nodes) {
        n.print(dictionary);
    }
    cout << '\n';
}