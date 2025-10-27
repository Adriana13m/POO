#include <iostream>
#include <string>
using namespace std;

enum Gen { FICTIUNE = 1, NON_FICTIUNE = 2, EDUCATIE = 3 };

class Carte {
private:
    const int id;
    string titlu;
    string autor;
    float pret;
    Gen gen;
    int nrCapitole;
    int* paginiPeCapitol;
    static int nrCarti;

public:
    
    Carte() : id(++nrCarti) {
        this->titlu = "Carte necunoscuta";
        this->autor = "Anonim";
        this->pret = 0;
        this->gen = FICTIUNE;
        this->nrCapitole = 0;
        this->paginiPeCapitol = nullptr;
    }

    
    Carte(string titlu, string autor, float pret, Gen gen, int nrCapitole, int* pagini)
        : id(++nrCarti) {
        this->titlu = titlu;
        this->autor = autor;
        this->pret = pret;
        this->gen = gen;
        this->nrCapitole = nrCapitole;

        this->paginiPeCapitol = new int[this->nrCapitole];
        for (int i = 0; i < this->nrCapitole; i++)
            this->paginiPeCapitol[i] = pagini[i];

        delete[] pagini;
    }

    
    void afisareCarte() {
        cout << endl << id << ". \"" << titlu << "\" de " << autor
             << " costa " << pret << " lei. Gen: ";
        if (gen == FICTIUNE) cout << "FICTIUNE";
        else if (gen == NON_FICTIUNE) cout << "NON_FICTIUNE";
        else cout << "EDUCATIE";

        cout << " si are " << nrCapitole << " capitole: ";
        if (paginiPeCapitol != nullptr) {
            for (int i = 0; i < nrCapitole - 1; i++)
                cout << paginiPeCapitol[i] << " pagini, ";
            if (nrCapitole > 0)
                cout << paginiPeCapitol[nrCapitole - 1] << " pagini.";
        }
    }

    
    int getNrCapitole() {
        return nrCapitole;
    }

    void setNrCapitole(int nrNou) {
        if (nrNou > 0)
            nrCapitole = nrNou;
        else
            throw "Numar invalid de capitole!";
    }

    
    int* getPagini() {
        int* copie = new int[nrCapitole];
        for (int i = 0; i < nrCapitole; i++)
            copie[i] = paginiPeCapitol[i];
        return copie;
    }

    void setPagini(int* paginiNoi, int nrNou) {
        setNrCapitole(nrNou);
        if (paginiPeCapitol != nullptr)
            delete[] paginiPeCapitol;

        paginiPeCapitol = new int[nrCapitole];
        for (int i = 0; i < nrCapitole; i++)
            paginiPeCapitol[i] = paginiNoi[i];

        delete[] paginiNoi;
    }

    
    ~Carte() {
        if (paginiPeCapitol != nullptr)
            delete[] paginiPeCapitol;
    }
};

int Carte::nrCarti = 0;


int main() {
    Carte carte1;
    carte1.afisareCarte();

    int* pagini = new int[3]{ 10, 25, 30 };
    Carte* carte2 = new Carte("Povestea coderului", "Ion Popescu", 59.9, FICTIUNE, 3, pagini);
    carte2->afisareCarte();

    try {
        carte2->setNrCapitole(-2);
    }
    catch (const char* mesaj) {
        cout << endl << "Eroare: " << mesaj;
    }

    cout << endl << "Numar capitole actual: " << carte2->getNrCapitole();

    carte2->setPagini(new int[4]{ 12, 18, 20, 22 }, 4);
    int* paginiActuale = carte2->getPagini();

    for (int i = 0; i < carte2->getNrCapitole(); i++) {
        cout << endl << "Capitolul " << i + 1 << ": " << paginiActuale[i] << " pagini";
    }

    delete[] paginiActuale;
    delete carte2;

    return 0;
}
