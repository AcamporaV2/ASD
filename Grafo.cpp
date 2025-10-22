#include <iostream>
#include <vector>
#include <list>

using namespace std;

enum Color { BIANCO, GRIGIO, NERO };

class Graph {
private:
    int V; // numero di vertici
    vector<list<int>> adj; // lista di adiacenza
    vector<Color> color;
    vector<int> padre;
    int cicli;

    void DFS(int u) {
        color[u] = GRIGIO;

        // Esplora tutti i vertici adiacenti
        for (int v : adj[u]) {
            if (color[v] == BIANCO) {
                padre[v] = u;
                DFS(v);
            }
            else if (color[v] == GRIGIO && v != u) {
                // Back-edge trovato e non è un self-loop
                cicli++;
                cout << "Ciclo trovato: back-edge da " << u << " a " << v << endl;
            }
        }

        color[u] = NERO;
    }

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
        color.resize(V);
        padre.resize(V);
        cicli = 0;
    }

    void aggiungiArco(int u, int v) {
        adj[u].push_back(v);
    }

    int contaCicli() {
        // Inizializza
        for (int i = 0; i < V; i++) {
            color[i] = BIANCO;
            padre[i] = -1;
        }
        cicli = 0;

        // Esegui DFS da ogni vertice non visitato
        for (int u = 0; u < V; u++) {
            if (color[u] == BIANCO) {
                DFS(u);
            }
        }

        return cicli;
    }

    void stampaGrafo() {
        cout << "\nGrafo (lista di adiacenza):" << endl;
        for (int i = 0; i < V; i++) {
            cout << i << " -> ";
            for (int v : adj[i]) {
                cout << v << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    cout << "=== TEST 1: Ciclo semplice di lunghezza 3 ===" << endl;
    Graph g1(3);
    g1.aggiungiArco(0, 1);
    g1.aggiungiArco(1, 2);
    g1.aggiungiArco(2, 0);
    g1.stampaGrafo();
    cout << "Numero di cicli: " << g1.contaCicli() << endl;
    cout << "Atteso: 1 ciclo (0->1->2->0)\n" << endl;

    cout << "\n=== TEST 2: Self-loop (NON deve contare) ===" << endl;
    Graph g2(3);
    g2.aggiungiArco(0, 0); // self-loop
    g2.aggiungiArco(0, 1);
    g2.aggiungiArco(1, 2);
    g2.stampaGrafo();
    cout << "Numero di cicli: " << g2.contaCicli() << endl;
    cout << "Atteso: 0 cicli (self-loop escluso)\n" << endl;

    cout << "\n=== TEST 3: Ciclo di lunghezza 2 ===" << endl;
    Graph g3(2);
    g3.aggiungiArco(0, 1);
    g3.aggiungiArco(1, 0);
    g3.stampaGrafo();
    cout << "Numero di cicli: " << g3.contaCicli() << endl;
    cout << "Atteso: 1 ciclo (0->1->0)\n" << endl;

    cout << "\n=== TEST 4: Grafo senza cicli ===" << endl;
    Graph g4(4);
    g4.aggiungiArco(0, 1);
    g4.aggiungiArco(1, 2);
    g4.aggiungiArco(2, 3);
    g4.stampaGrafo();
    cout << "Numero di cicli: " << g4.contaCicli() << endl;
    cout << "Atteso: 0 cicli\n" << endl;

    cout << "\n=== TEST 5: Due cicli separati ===" << endl;
    Graph g5(6);
    // Primo ciclo: 0->1->2->0
    g5.aggiungiArco(0, 1);
    g5.aggiungiArco(1, 2);
    g5.aggiungiArco(2, 0);
    // Secondo ciclo: 3->4->5->3
    g5.aggiungiArco(3, 4);
    g5.aggiungiArco(4, 5);
    g5.aggiungiArco(5, 3);
    g5.stampaGrafo();
    cout << "Numero di cicli: " << g5.contaCicli() << endl;
    cout << "Atteso: 2 cicli\n" << endl;

    cout << "\n=== TEST 6: Ciclo complesso con più back-edge ===" << endl;
    Graph g6(4);
    g6.aggiungiArco(0, 1);
    g6.aggiungiArco(1, 2);
    g6.aggiungiArco(2, 0); // back-edge 1
    g6.aggiungiArco(2, 3);
    g6.aggiungiArco(3, 1); // back-edge 2
    g6.stampaGrafo();
    cout << "Numero di cicli: " << g6.contaCicli() << endl;
    cout << "Atteso: 2 back-edge\n" << endl;

    return 0;
}