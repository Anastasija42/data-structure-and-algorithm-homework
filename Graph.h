
#ifndef ASP_GRAPH_H
#define ASP_GRAPH_H

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// Dva dinamicka niza, jedan (VERTICES) za sva imena cvorova i njihovih pocetnih indeksa u Edges
// i jedan EDGES sa svim granama: imenima cvorova na koji pokazuje i tezina cvorova

struct Node{
    string name;
    int index_of_vertice;
};

struct Edge{
    string name_of_adjacent_node;
    double weight;
};

struct Line{
    string node1, node2;
    double w;
};

class Graph {
private:
    Node *vertices;
    Edge *edges;
    int number_of_nodes, number_of_edges;

    void copy(const Graph &);

    void move(Graph &);

    void clear();

    void insertion_sort(Node arr[], int n);

    void insertion_sort_str(Line arr[], int n);

    int find_last(int index);


public:
    Graph (const string& filename);

    Graph(){
        vertices = nullptr;
        edges = nullptr;
        number_of_nodes = 0; number_of_edges = 0;
    }

    Graph(const Graph &g) { copy(g); }

    Graph(Graph &&g) { move(g); }

    Graph &operator=(const Graph &g) {
        if (this != &g) {
            clear();
            copy(g);
        }
        return *this;
    }

    Graph &operator=(Graph &&g) {
        if (this != &g) {
            clear();
            move(g);
        }
        return *this;
    }

    ~Graph() { clear(); }

    friend ostream &operator<<(ostream &, const Graph &);

    void add_node(const string& s);
    void remove_node(string s); //uklonimo i sve veze sa tim cvorom
    void add_edge(const string& s1, const string& s2, double weight);
    void remove_edge(const string& s1, const string& s2);

    void find_k_most_similar(const string& s, int k);
    void shortest_path(const string& s1, const string& s2);
    void strongly_connected_words(const string& s);

    int find_index_of_name(const string&);
    double weight_of(int i, int j);
};

#endif //ASP_GRAPH_H
