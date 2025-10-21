#include <iostream>
#include <string>
using namespace std;

// Classe base Impiegato
class Impiegato {
protected:
    string nome;
    double salario;
public:
    Impiegato(const string& n, double s) : nome(n), salario(s) {}
    virtual ~Impiegato() {}
    virtual void stampa() const {
        cout << "Impiegato: " << nome << ", Salario: " << salario << endl;
    }
    virtual double getSalario() const {
        return salario;
    }
};

// Classe derivata Manager
class Manager : public Impiegato {
    double bonus;
public:
    Manager(const string& n, double s, double b) : Impiegato(n, s), bonus(b) {}
    void stampa() const override {
        cout << "Manager: " << nome << ", Salario: " << salario << ", Bonus: " << bonus << endl;
    }
    double getSalario() const override {
        return salario + bonus;
    }
};

// Nodo della lista
struct Nodo {
    Impiegato* imp;
    Nodo* next;
    Nodo(Impiegato* i) : imp(i), next(nullptr) {}
};

// Lista collegata di impiegati
class ListaImpiegati {
    Nodo* head;
public:
    ListaImpiegati() : head(nullptr) {}
    ~ListaImpiegati() {
        Nodo* curr = head;
        while (curr) {
            delete curr->imp;
            Nodo* tmp = curr;
            curr = curr->next;
            delete tmp;
        }
    }
    void aggiungi(Impiegato* imp) {
        Nodo* nuovo = new Nodo(imp);
        nuovo->next = head;
        head = nuovo;
    }
    void stampa() const {
        Nodo* curr = head;
        while (curr) {
            curr->imp->stampa();
            curr = curr->next;
        }
    }
    // Overload operatore + per sommare i salari di tutti gli impiegati
    double operator+ (const ListaImpiegati& l) const {
        double totale = 0;
        Nodo* curr = head;
        while (curr) {
            totale += curr->imp->getSalario();
            curr = curr->next;
        }
        curr = l.head;
        while (curr) {
            totale += curr->imp->getSalario();
            curr = curr->next;
        }
        return totale;
    }
    // Somma salari della lista stessa
    double sommaSalari() const {
        double totale = 0;
        Nodo* curr = head;
        while (curr) {
            totale += curr->imp->getSalario();
            curr = curr->next;
        }
        return totale;
    }
};

int main() {
    ListaImpiegati lista;
    lista.aggiungi(new Impiegato("Mario Rossi", 2000));
    lista.aggiungi(new Manager("Anna Bianchi", 2500, 500));
    lista.aggiungi(new Impiegato("Luca Verdi", 1800));

    cout << "Lista impiegati:" << endl;
    lista.stampa();

    cout << "Somma salari: " << lista.sommaSalari() << endl;

    // Esempio di overload +
    ListaImpiegati altraLista;
    altraLista.aggiungi(new Manager("Giulia Neri", 3000, 700));
    double totale = lista + altraLista;
    cout << "Somma salari di entrambe le liste: " << totale << endl;

    return 0;
}