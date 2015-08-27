#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <iomanip>
#include <sstream>

#include "edge.h"
#include "Node.h"
#include "Graph.h"

using namespace std;

int main () {
    srand(0);
    
    Graph g; //automatically reads from cin
    
    cout << "[[Read Complete]]" << endl;
    
    g.print();
    
    for (int i = 0; i < 10; ++i) {
        g.talk();
    }
    
    return 0;
}