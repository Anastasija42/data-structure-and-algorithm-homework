
//Domaci iz ASP-a, Anastasija Rakic 2020/0030

#include "Graph.h"

int main() {
/*
     Graph g("graf1.txt");
     g.remove_edge("skola", "ETF");
     g.add_edge("skola", "ETF", 0.1);
    //g.strongly_connected_words("berza");
    //g.add_node("smrt");
    //g.remove_node("skola");
    //g.add_edge("ETF", "smrt", 0.69);
    //g.remove_edge("tekst", "knjiga");

    //g.find_k_most_similar("likvidnost", 20);
    //g.find_k_most_similar("skola", 10);
    g.shortest_path("skola", "algoritam");
    cout<<g;
*/

    string OUT = "\n2. Dodavanje cvora u graf i uklanjanje cvora iz grafa.\n" \
"3.  Dodavanje i uklanjanje grane izmedju dva cvora u grafu.\n" \
"4. Ispis reprezentacije grafa.\n"\
"5. Brisanje grafa iz memorije\n"\
"6. Nalazenje k (unosi korisnik) semanticki najslicnijih reci zadatoj reci\n"\
"7. Ispis svih reci na najkracem putu od zadate jedne reci do druge zadate reci.\n"\
"8. Nalazenje svih reci koje su jako povezane sa zadatom recju.\n"\
"9. Zelite da zavrsite program?\n";

    cout<< "DOBRODOSLI, izaberite opciju koju zelite!"<<endl;
    cout<<"1. Ucitavanje grafa iz fajla"<<endl;
    cout<< "9. Zelite da zavrsite program?"<<endl;
    int n;
    cin>>n;
    bool not_end = true;
    bool not_read = true;
    Graph *g = new Graph;

    while(not_read) {
        if (n == 1) {
            string s;
            bool f = true;
            while(f) {
                cout << "Unesite ime fajla: ";
                cin >> s;
                ifstream file;
                file.open(s);
                if (!file.is_open()) { cout << "Nema takve datoteke, probajte ponovo!"; }
                else {f = false; file.close();}
            }
            Graph graph(s);
            *g = graph;
            not_read = false;
            cout << OUT;
            cin >> n;
        } else if (n == 9) {not_end = false; not_read = false;}
        else {
            cout << "Niste uneli broj koji predstavlja opciju,, probajte ponovo!" << endl;
            cin >> n;
        }
    }
    while(not_end) {
        switch (n) {
            case 2: {
                int m;
                string s;
                cout << "\n1. Dodavanje\n 2. Izbacivanje\n Izaberite pa upisite ime\n";
                cin >> m;
                cin >> s;
                if (m == 1) g->add_node(s);
                else if (m == 2) g->remove_node(s);
                else {cout<< "Niste izabrali dobru opciju!"; break;}
                cout << OUT;
                cin >> n;
                break;
            }
            case 3: {
                int m;
                string s1, s2;
                cout << "\n1. Dodavanje\n 2. Izbacivanje\n Izaberite pa upisite imena cvorova\n";
                cin >> m >> s1 >> s2;
                if (m == 1) {
                    //provera da li veza postoji
                    double w = g->weight_of(g->find_index_of_name(s1), g->find_index_of_name(s2));
                    if(w!=1){
                        cout<< "Vec postoji veza: "<<w<<endl;
                    }
                    else{
                    cout << "Unesite tezinu izmedju cvorova: ";
                    cin >> w;
                    g->add_edge(s1, s2, w);
                    }
                }
                else if (m == 2) {
                    g->remove_edge(s1, s2);
                }
                else cout << "Niste izabrali dobru opciju!";
                cout << OUT;
                cin>>n;
                break;
            }
            case 4:{
                cout << *g;
                cout << OUT;
                cin >> n;
                break;
            }
            case 5: {
                not_read = true;

                cout<<"1. Ucitavanje grafa iz fajla"<<endl;
                cout<< "9. Zelite da zavrsite program?"<<endl;
                cin>>n;
                while(not_read) {
                    if (n == 1) {
                        string s;
                        bool f = true;
                        while(f) {
                            cout << "Unesite ime fajla: ";
                            cin >> s;
                            ifstream file;
                            file.open(s);
                            if (!file.is_open()) { cout << "Nema takve datoteke, probajte ponovo!"; }
                            else {f = false; file.close();}
                        }
                        Graph graph(s);
                        *g = graph;
                        not_read = false;
                        cout << OUT;
                        cin >> n;
                    } else if (n == 9) {not_end = false; not_read = false;}
                    else {
                        cout << "Niste uneli broj koji predstavlja opciju,, probajte ponovo!" << endl;
                        cin >> n;
                    }
                }
                break;
            }
            case 6: {
                int k;
                string s;
                cout << "Unesite rec i broj k: ";
                cin >> s >> k;
                g->find_k_most_similar(s, k);

                cout << OUT;
                cin >> n;
                break;
            }
            case 7:{
                string s1, s2;
                cout<<"Unesite dve reci: ";
                cin >> s1 >> s2;
                g->shortest_path(s1,s2);
                cout << OUT;
                cin>>n;
                break;
            }
            case 8: {
                string s;
                cout<<"Upisite rec: ";
                cin>> s;
                g->strongly_connected_words(s);
                cout << OUT;
                cin >> n;
                break;
            }
            case 9:{
                not_end = false;
                cout
                        << "Hvala sto ste koristili program sa \"Sekvencijalnom reprezentacijom koriscenjem linearizovanih lista susednosti.\"";
                break;
            }
            default:
            {cout<< "Niste uneli broj koji predstavlja opciju,, probajte ponovo!"<<endl; cin>>n; break;}

        }
    }

}
