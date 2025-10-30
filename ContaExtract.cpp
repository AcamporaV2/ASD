#include <iostream>
#include <vector>
#include <stdexcept> // Per std::runtime_error
#include <algorithm> // Per std::swap
#include <string>

using namespace std;

// Indice del figlio sinistro per un heap 1-based
int left(int i) {
    return 2 * i;
}

// Indice del figlio destro per un heap 1-based
int right(int i) {
    return 2 * i + 1;
}

int minHeapifyCount(vector<int>& A, int i, int heap_size) {
    int l = left(i);
    int r = right(i);
    int smallest = i;

    // Confronta con il figlio sinistro
    if (l <= heap_size && A[l] < A[i]) {
        smallest = l;
    }
    // Confronta con il figlio destro (che potrebbe essere il più piccolo di tutti)
    if (r <= heap_size && A[r] < A[smallest]) {
        smallest = r;
    }
    
    if (smallest != i) {
        swap(A[i], A[smallest]); // conta come 1 scambio
        // Aggiunge 1 (scambio corrente) al conteggio degli scambi nelle chiamate ricorsive
        return 1 + minHeapifyCount(A, smallest, heap_size);
    }
    return 0; // Nessuno scambio
}

int extractMinCount(vector<int>& A) {
    if (A.size() <= 1) { // Se c'è solo l'elemento fittizio o è vuoto
        throw runtime_error("heap underflow");
    }
    
    int heap_size = A.size() - 1;
    
    // Sposta l'ultimo elemento alla radice (non conta come scambio secondo la traccia)
    A[1] = A[heap_size];
    
    // Rimuove l'ultimo elemento dal vettore per ridimensionare l'heap
    A.pop_back();
    
    // La nuova dimensione dell'heap è A.size() - 1
    int new_heap_size = A.size() - 1;
    
    // Ripristina la proprietà di min-heap a partire dalla radice e conta gli scambi
    if (new_heap_size > 0) {
        return minHeapifyCount(A, 1, new_heap_size);
    }
    
    return 0;
}

void printHeap(const vector<int>& A, const string& label) {
    cout << label;
    // Stampa gli elementi dell'heap (da indice 1)
    for (size_t i = 1; i < A.size(); ++i) {
        cout << A[i] << " ";
    }
    cout << endl;
}

int main() {
    // Heap di esempio: [0, 1, 5, 3, 10, 7, 6] (A[0] non usato)
    //        1
    //      /   \
    //     5     3
    //    / \   /
    //   10  7 6
    vector<int> A = {0, 1, 5, 3, 10, 7, 6};
    
    printHeap(A, "Heap prima di extract-min:  ");
    
    int scambi = extractMinCount(A);
    
    cout << "Numero di scambi: " << scambi << endl;
    
    printHeap(A, "Heap dopo extract-min:   ");
    
    return 0;
}