#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// Restituisce true se esiste almeno un ciclo di due archi
bool twoEdgeCycle(int V, const vector<vector<int>>& adj) {
    // Creiamo una rappresentazione con set per ricerche O(1)
    vector<unordered_set<int>> adjSet(V);
    for (int u = 0; u < V; ++u) {
        for (int v : adj[u]) {
            adjSet[u].insert(v);
        }
    }

    // Controlliamo se esistono archi reciproci
    for (int u = 0; u < V; ++u) {
        for (int v : adj[u]) {
            if (adjSet[v].count(u)) {
                return true; // trovato (u,v) e (v,u)
            }
        }
    }

    return false; // nessun ciclo di due archi trovato
}

int main() {
    int V, E;
    cout << "Inserisci numero di vertici e archi: ";
    cin >> V >> E;

    vector<vector<int>> adj(V);

    cout << "Inserisci " << E << " archi orientati (u v):\n";
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v); // arco diretto da u a v
    }

    if (twoEdgeCycle(V, adj))
        cout << "TRUE: Esiste un ciclo di due archi.\n";
    else
        cout << "FALSE: Nessun ciclo di due archi.\n";

    return 0;
}
