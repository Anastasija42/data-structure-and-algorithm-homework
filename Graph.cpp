//
// Created by ra200030d on 12/5/2022.
//

#include "Graph.h"
#define NO_NEXT_NODES 1000;

// kontruktor koji pravi graf od informacija iz tekstualne datoteke
Graph::  Graph(const string& filename){
    ifstream file;
    file.open(filename);
    if (! file.is_open()) {cout<< "Ne postoji takva datoteka!"; return;}
    file >> number_of_nodes;
    file >> number_of_edges;

    Line array_of_lines[number_of_edges];

    vertices = new Node[number_of_nodes];
    edges = new Edge[number_of_edges];

    if ( file.is_open() ) {
    for(int k =0; k<number_of_nodes; k++){
        file>>vertices[k].name;
    }
    insertion_sort(vertices, number_of_nodes);

    int i=0;
    while(file && i<number_of_edges){
        file>>array_of_lines[i].node1>>array_of_lines[i].node2>> array_of_lines[i].w;
        i++;
        }
    }
    file.close();
    insertion_sort_str(array_of_lines, number_of_edges);

    int i=0,j=0;

    while(j<number_of_edges){

        if (strcmp(array_of_lines[j].node1.c_str(), vertices[i].name.c_str()) > 0){
            i++;
            if (strcmp(array_of_lines[j].node1.c_str(), vertices[i].name.c_str()) != 0) {
                vertices[i].index_of_vertice = NO_NEXT_NODES;
                j--;
            }
            else {
                vertices[i].index_of_vertice = j;
            }
        }
        else if (vertices[i].index_of_vertice > j){
            vertices[i].index_of_vertice = j;
        }

        edges[j].name_of_adjacent_node = array_of_lines[j].node2;
        edges[j].weight = array_of_lines[j].w;
        j++;
    }
    vertices[0].index_of_vertice = 0;
    if(vertices[1].index_of_vertice==0) vertices[0].index_of_vertice = NO_NEXT_NODES;
    if(i == number_of_nodes-2){
        vertices[i+1].index_of_vertice = NO_NEXT_NODES;
    }
}

void Graph::copy(const Graph &g) {
    vertices = new Node[number_of_nodes = g.number_of_nodes];
    for (int i = 0; i < number_of_nodes; i++) vertices[i] = g.vertices[i];
    edges = new Edge[number_of_edges = g.number_of_edges];
    for (int i = 0; i < number_of_edges; i++) edges[i] = g.edges[i];
}

void Graph::move(Graph &g) {
    number_of_nodes = g.number_of_nodes;
    number_of_edges = g.number_of_edges;
    vertices = g.vertices;
    edges = g.edges;
    g.vertices = nullptr;
    g.edges = nullptr;
}

void Graph::clear() {
    delete [] vertices;
    vertices = nullptr;
    number_of_nodes = 0;
    delete [] edges;
    edges = nullptr;
    number_of_edges = 0;
}

//ispis reprezentaicije (Vertices: ... Edges: ...)
ostream &operator<<(ostream & os, const Graph &g) {
    os<< "Vertices"<< endl;
    for (int i = 0; i<g.number_of_nodes; i++){
        os<< g.vertices[i].name <<"  "<< g.vertices[i].index_of_vertice <<endl;
    }
    os<<endl;
    os<<"Edges"<<endl;
    for (int i = 0; i<g.number_of_edges; i++){
        os<< g.edges[i].name_of_adjacent_node<< "  "<< g.edges[i].weight <<endl;
    }
    return os;
}

//pomocna funkcija koja nalazi indeks od imena cvora
//binarna pretraga (cvorovi su u leksikografskom redosledu)
int Graph::find_index_of_name(const string& s) {
    int low = 0;
    int high = number_of_nodes;
    if(high == 0) return-1;

    while (low != high){
        if(low>high) break;
        int mid = (low+high)/2;
        if (strcmp(s.c_str(),vertices[mid].name.c_str()) == 0){
            return mid;
        }
        else if (strcmp(s.c_str(), vertices[mid].name.c_str()) > 0){
            low = mid + 1;
        }
        else
            high = mid - 1;
    }
    if(high!=number_of_nodes) {
        if (strcmp(s.c_str(), vertices[low].name.c_str()) == 0) return low;
    }
    return -1;
}

//pomocne funkcije za sortiranje pri pravljenju grafa
void Graph::insertion_sort(Node arr[], int n)
{
    int i, j;
    Node key;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && strcmp(arr[j].name.c_str(), key.name.c_str()) > 0){
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
void Graph::insertion_sort_str(Line arr[], int n)
{
    int i, j;
    Line key;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && strcmp(arr[j].node1.c_str(), key.node1.c_str()) > 0){
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

//dodavanje cvora
void Graph::add_node(const string& s) {
    if(find_index_of_name(s)!=-1) {cout<<"Vec postoji cvor sa datim imenom."; return;}
    //dodavanje na prazni graf
    if(number_of_nodes == 0){
        number_of_nodes = 1;
        Node* new_vertices = new Node[number_of_nodes];
        new_vertices[0].name = s;
        new_vertices[0].index_of_vertice = NO_NEXT_NODES;
        delete [] vertices;
        vertices = new_vertices;
        return;
    }
    number_of_nodes = number_of_nodes + 1;
    Node* new_vertices = new Node[number_of_nodes];
    int i = 0;
    while(strcmp(vertices[i].name.c_str(), s.c_str())<0) {
        new_vertices[i] = vertices[i]; i++;
        if(i==number_of_nodes-1) break;
    }
    new_vertices[i].name = s;
    new_vertices[i].index_of_vertice = NO_NEXT_NODES;
    for(int j = i+1; j<number_of_nodes; j++) {new_vertices[j] = vertices[j-1];}
    delete [] vertices;
    vertices = new_vertices;
}

//uklanjanje cvora
void Graph::remove_node(string s) {
    int index = find_index_of_name(s);
    if(index == -1) {cout<< "Ne postoji cvor sa datim imenom"; return;}
    number_of_nodes = number_of_nodes - 1;
    Node* new_vertices = new Node[number_of_nodes];
    int beg = vertices[index].index_of_vertice;
    if(beg != 1000){
        int last = find_last(index);
        int j = beg;
        for(int i = beg; i < last; i++) this->remove_edge(s, edges[j].name_of_adjacent_node);
    }
    for (int i = 0; i < index; i++) new_vertices[i] = vertices[i];
    for(int i = index; i < number_of_nodes; i++) new_vertices[i] = vertices[i+1];

    delete [] vertices;
    vertices = new_vertices;

    for(int i = 0; i<number_of_nodes-1; i++){
        int beg = vertices[i].index_of_vertice;
        if(beg == 1000){
            continue;
            //if(i != number_of_nodes-1) beg = vertices[i+1].index_of_vertice;
            //else return;
        }
        int last = find_last(i);
        int k = beg;
        for(int j = beg; j<last; j++){
            if(strcmp(edges[k].name_of_adjacent_node.c_str(), s.c_str())==0){
                this->remove_edge(vertices[i].name, s);
                k--;
            }
            k++;
        }
    }
}

//dodavanje grane
void Graph::add_edge(const string& s1, const string& s2, double weight) {
    if(find_index_of_name(s1)==-1) {cout<<"Ne postoji prvi cvor, prvo ga dodajte!"; return;}
    if(find_index_of_name(s2)==-1) {cout<<"Ne postoji drugi cvor, prvo ga dodajte!"; return;}
    int index = find_index_of_name(s1);
    if(index==-1) {return;}
    int last = find_last(index);

    if(vertices[index].index_of_vertice == 1000) vertices[index].index_of_vertice = last;
    number_of_edges++;
    Edge* new_edges = new Edge[number_of_edges];
    for(int i = 0; i<last; i++) new_edges[i] = edges[i];
    new_edges[last].name_of_adjacent_node = s2;
    new_edges[last].weight = weight;

    for(int i = last+1; i<number_of_edges; i++) new_edges[i] = edges[i-1];

    for(int i = index+1; i< number_of_nodes; i++) {
        if (vertices[i].index_of_vertice != 1000) vertices[i].index_of_vertice++;
    }
    delete [] edges;
    edges = new_edges;
}

//uklanjanje grane
void Graph::remove_edge(const string &s1, const string &s2) {
    int index = find_index_of_name(s1);
    if(index ==-1) {cout<< "Ne postoji cvor s1."; return; }
    if (vertices[index].index_of_vertice == 1000) {cout<< "Ne postoji cvor na koji ukazuje."; return;}

    int first = vertices[index].index_of_vertice;
    int last = find_last(index);

    int rem = -1;
    for (int i = first; i < last; i++) {
        if (strcmp(edges[i].name_of_adjacent_node.c_str(), s2.c_str()) == 0) {
            rem = i;
        }
    }
    if (rem == -1) { cout << "Ne postoji data veza."; return;}

    if(last - first == 1){vertices[index].index_of_vertice = NO_NEXT_NODES;}
    number_of_edges--;
    Edge *new_edges = new Edge[number_of_edges];
    for (int i = 0; i < rem; i++) new_edges[i] = edges[i];
    for (int i = rem; i < number_of_edges; i++) new_edges[i] = edges[i + 1];

    for (int i = index + 1; i < number_of_nodes; i++) {
        if (vertices[i].index_of_vertice != 1000) vertices[i].index_of_vertice--;
    }

    delete[] edges;
    edges = new_edges;
}

//Dijkstra algoritam, pronalazi sve najkrace puteve do reci sa najvecom slicnoscu
// Pisemo samo prvih k najslicnijih
void Graph::find_k_most_similar(const string& s, int k) {
    //provere
    int index_s = find_index_of_name(s);
    if(index_s == -1) {cout<< "Data rec se ne nalazi u grafu."; return;}
    if(k<=0) {cout<<"k mora biti pozitivno i vece od nule!"; return;}

    int S[number_of_nodes];
    Edge similarities[number_of_nodes];
    double similarity[number_of_nodes];
    int t[number_of_nodes];
    for (int i = 0; i < number_of_nodes; i++) {similarity[i] = 1;t[i]=0; S[i] = 0; similarities[i].weight = 0; similarities[i].name_of_adjacent_node = "";}

    S[index_s] = 1;

    int first = vertices[index_s].index_of_vertice;
    if(first==1000) return;
    int last = find_last(index_s);

    for (int i = first; i < last; i++) {
        int x = find_index_of_name(edges[i].name_of_adjacent_node);
        t[x] = 1;
        similarity[x] = edges[i].weight;
    }

    for (int k = 1; k < number_of_nodes; k++) {
        double max = 0;
        int index_max = 0;
        bool found = false;
        for(int h = 0; h < number_of_nodes; h++){
            if(S[h] == 0 and similarity[h]!=1)
                if (max<similarity[h]) {max = similarity[h]; index_max = h; found = true;}
        }
        if(!found) continue;
        int i = index_max;
        S[i] = 1;

        for(int j=0; j<number_of_nodes; j++) {
            if (S[j] == 0) {
                double y = similarity[j];
                if (similarity[j] == 1) {
                    y = 0;
                }
                if (weight_of(i, j) != 1) {
                    if (similarity[i] * weight_of(i, j) > y) {
                        similarity[j] = similarity[i] * weight_of(i, j);
                        t[j] = i;
                    }
                }
            }
        }
    }

    int counter = 0;
    for(int i = 0; i<number_of_nodes; i++){
        if(similarity[i]!=1){
            similarities[i].weight = similarity[i];
            similarities[i].name_of_adjacent_node = vertices[i].name;
            counter++;
        }
    }
    for(int j = 0; j<number_of_nodes-1; j++){
        for(int k = j+1; k<number_of_nodes; k++){
            if(similarities[j].weight<similarities[k].weight){
                Edge t;
                t = similarities[j];
                similarities[j] = similarities[k];
                similarities[k] = t;
            }
        }
    }

    if(counter<k){k=counter;}
    cout<< "Najslicnijih "<<k<<" reci za rec "+s+ " su: "<<endl;
    for(int i = 0; i<k; i++){
        cout << similarities[i].name_of_adjacent_node << ": "<<similarities[i].weight<<endl;
    }
}

//Dijkstra algoritam, ispisujemo  putanju
void Graph::shortest_path(const string& s1, const string& s2) {
    int index_s = find_index_of_name(s1);
    if(index_s == -1) {cout<< "Data rec se ne nalazi u grafu."; return;}
    if(find_index_of_name(s2)==-1) {cout<<"Data rec se ne nalazi u grafu."; return;}

    int S[number_of_nodes];
    //Edge similarities[number_of_nodes];
    double similarity[number_of_nodes];
    int t[number_of_nodes];
    for (int i = 0; i < number_of_nodes; i++) {similarity[i] = 1;t[i]=0; S[i] = 0; /*similarities[i].weight = 0; similarities[i].name_of_adjacent_node = "";*/}
    S[index_s] = 1;

    int first = vertices[index_s].index_of_vertice;
    if(first==1000) return;
    int last = find_last(index_s);

    for (int i = first; i < last; i++) {
        int x = find_index_of_name(edges[i].name_of_adjacent_node);
        t[x] = 1;
        similarity[x] = edges[i].weight;
    }

    for (int k = 1; k < number_of_nodes; k++) {
        double max = 0;
        int index_max = 0;
        bool found = false;
        for(int h = 0; h < number_of_nodes; h++){
            if(S[h] == 0 and similarity[h]!=1)
                if (max<similarity[h]) {max = similarity[h]; index_max = h; found = true;}
        }
        if(!found) continue;
        int i = index_max;
        S[i] = 1;

        for(int j=0; j<number_of_nodes; j++) {
            if (S[j] == 0) {
                double y = similarity[j];
                if (similarity[j] == 1) {
                    y = 0;
                }
                if (weight_of(i, j) != 1) {
                    if (similarity[i] * weight_of(i, j) > y) {
                        similarity[j] = similarity[i] * weight_of(i, j);
                        t[j] = i+2;
                    }
                }
            }
        }
    }


    int index_of_s2 = find_index_of_name(s2);
    if(t[index_of_s2]==0) cout<<"Put ne postoji."<<endl;
    else{
        Edge e[number_of_nodes];
        int counter = 0;
        while(t[index_of_s2]!=1){
            e[counter].name_of_adjacent_node =  vertices[index_of_s2].name;
            e[counter].weight = weight_of(t[index_of_s2]-2, index_of_s2);
            index_of_s2 = t[index_of_s2]-2;
            counter++;
        }
        e[counter].name_of_adjacent_node = vertices[index_of_s2].name;
        e[counter].weight = weight_of(index_s, index_of_s2);
        cout<<vertices[index_s].name<<" -> ";
        for(int i = counter; i>-1; i--){
            cout<< e[i].weight<< " -> "<< e[i].name_of_adjacent_node;
            if(i!=0) cout<<" -> ";
        }
        cout<<endl;
    }

}

//pomocna funckija koja vraca tezinu izmedju dva cvora
double Graph::weight_of(int i, int j) {
    int f = vertices[i].index_of_vertice;
    if(f == 1000) return 1;
    int last = find_last(i);
    for (int a = f; a<last; a++){
        if(strcmp(vertices[j].name.c_str(), edges[a].name_of_adjacent_node.c_str())==0){
            return edges[a].weight;
        }
    }
    return 1;
}

//ispisuje sve reci koje su jako povezane sa datom recju
void Graph::strongly_connected_words(const string& s) {
    int index = find_index_of_name(s);
    if(index == -1) {cout<<"Ne postoji takva rec"; return;}
    if(index==1000){cout<<"Nema strogo povezanih komponenti."; return;}

    Graph* t = new Graph();
    t->vertices = new Node[number_of_nodes];
    t->number_of_nodes = number_of_nodes;

    for(int i =0; i<number_of_nodes; i++){
        t->vertices[i].name = vertices[i].name;
        t->vertices[i].index_of_vertice = NO_NEXT_NODES;
    }

    for(int i =0; i<number_of_nodes; i++){
        int beg = vertices[i].index_of_vertice;
        if(beg == 1000){
            if(i != number_of_nodes-1) beg = vertices[i+1].index_of_vertice;
            else continue;
        }
        int last = find_last(i);
        for(int j = beg; j<last; j++){
            t->add_edge(edges[j].name_of_adjacent_node, vertices[i].name, edges[j].weight);
        }
    }

    int S[number_of_nodes];
    int stack[number_of_nodes]; int counter = 0;

    //DFS for original graph
    for(int i = 0; i < number_of_nodes; i++){S[i]=0; stack[i]=0;}
    S[index] = 1;

    int beg = vertices[index].index_of_vertice;
    int last = find_last(index);

    for(int i = beg; i<last; i++){
        stack[counter] = find_index_of_name(edges[i].name_of_adjacent_node);
        counter++;
    }

    while(counter>0){
        int i = stack[counter-1];
        counter--;
        S[i] = 1;

        int beg = vertices[i].index_of_vertice;
        if(beg == 1000) continue;
        int last = find_last(i);

        for(int h = beg; h<last; h++){
            if(S[find_index_of_name(edges[h].name_of_adjacent_node)] == 0) {
                stack[counter] = find_index_of_name(edges[h].name_of_adjacent_node);
                counter++;
            }
        }
    }

    //DFS za transonovanu
    int St[t->number_of_nodes];
    int stackt[t->number_of_nodes]; int countert = 0;


    for(int i = 0; i < t->number_of_nodes; i++){St[i]=0; stackt[i]=0;}
    St[index] = 1;

    beg = t->vertices[index].index_of_vertice;
    last = t->find_last(index);

    for(int i = beg; i<last; i++){
        stackt[countert] = find_index_of_name(t->edges[i].name_of_adjacent_node);
        countert++;
    }

    while(countert>0){
        int i = stackt[countert-1];
        countert--;
        St[i] = 1;

        int beg = t->vertices[i].index_of_vertice;
        if(beg == 1000) continue;

        int last = t->find_last(i);
        for(int h = beg; h<last; h++){
            if(St[find_index_of_name(t->edges[h].name_of_adjacent_node)] == 0) {
                stackt[countert] = find_index_of_name(t->edges[h].name_of_adjacent_node);
                countert++;
            }
        }
    }

    cout<< "Jako povezane reci sa recju "+s+" su: ";
    for(int i = 0; i< number_of_nodes; i++){
        if(S[i]== 1 && St[i] ==1 && i!=index){
            cout<<vertices[i].name<< " ";
        }
    }
    cout<< endl;

}

//pomocna funkcija koja nalazi poslednji indeks do kojeg treba ici
int Graph::find_last(int i) {
    int last = -1;
    if(number_of_edges == 0) last = 0;
    else if(i != number_of_nodes-1){
        int k = i+1;
        last = vertices[k].index_of_vertice;
        while(last == 1000) {
            if(k != number_of_nodes-1) {
                last = vertices[k].index_of_vertice;
                k++;
            }
            else break;
        }
        if(k == number_of_nodes-1 && last==1000) last = number_of_edges;
    }
    else last = number_of_edges;
    return last;
}







