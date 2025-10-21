#include <iostream>      // Per input/output su console
#include <fstream>       // Per la gestione dei file
#include <vector>        // Per usare il tipo vector
#include <string>        // Per usare il tipo string
#include <sstream>       // Per la conversione da stringa a stream
#include <unordered_set> // Per usare set non ordinati (verifica duplicati)

using namespace std;     // Evita di scrivere std:: davanti ai tipi standard

// Classe che gestisce la verifica delle soluzioni del gioco "Rispetta i versi"
class RispettaVersi {
public:
    // Metodo che legge i file di problema e soluzione, verifica e scrive l'esito
    void verifica(const string& problemaFile, const string& soluzioneFile, const string& esitoFile) {
        ifstream probIn(problemaFile);    // Apertura file problema in lettura
        ifstream solIn(soluzioneFile);    // Apertura file soluzione in lettura
        ofstream esitoOut(esitoFile);     // Apertura file esito in scrittura

        string probLine, solLine;
        // Ciclo su ogni riga dei file (una istanza per riga)
        while (getline(probIn, probLine) && getline(solIn, solLine)) {
            bool esito = verificaIstanza(probLine, solLine); // Verifica la soluzione
            esitoOut << (esito ? "CORRETTA" : "ERRATA") << endl; // Scrive l'esito
        }
    }

private:
    // Metodo che verifica una singola istanza del problema
    bool verificaIstanza(const string& probLine, const string& solLine) {
        vector<char> segni; // Vettore per i simboli di disuguaglianza
        istringstream probStream(probLine); // Stream per leggere la riga del problema
        string token;
        // Estrae i simboli '<' e '>' dalla riga del problema
        while (probStream >> token) {
            if (token == "<" || token == ">") segni.push_back(token[0]);
        }

        vector<int> numeri; // Vettore per i numeri della soluzione
        istringstream solStream(solLine); // Stream per leggere la riga della soluzione
        int n;
        // Estrae i numeri dalla riga della soluzione
        while (solStream >> n) numeri.push_back(n);

        int N = numeri.size(); // Numero di caselle
        unordered_set<int> visti; // Set per controllare duplicati
        // Verifica che i numeri siano da 1 a N e non ripetuti
        for (int x : numeri) {
            if (x < 1 || x > N || visti.count(x)) return false;
            visti.insert(x);
        }

        // Verifica che le disuguaglianze siano rispettate
        for (int i = 0; i < segni.size(); ++i) {
            if (segni[i] == '<' && !(numeri[i] < numeri[i+1])) return false;
            if (segni[i] == '>' && !(numeri[i] > numeri[i+1])) return false;
        }
        return true; // Se tutte le verifiche sono passate, la soluzione è corretta
    }
};

// Funzione principale
int main() {
    RispettaVersi rv; // Istanzia la classe
    rv.verifica("Problema.txt", "Soluzione.txt", "Esito.txt"); // Avvia la verifica
    cout << "Verifica completata. Controlla Esito.txt." << endl; // Messaggio finale
    return 0;
}