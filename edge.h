typedef int token;

struct edge {
    edge(token IDin) : ID(IDin), weight(1) {};
    token ID;
    int weight;
};