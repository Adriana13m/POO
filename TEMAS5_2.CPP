#include <iostream>
#include <string>

using namespace std;

enum GenCarte { FICTIUNE = 1, EDUCATIVA = 2, SF = 3 };

class Carte {
private:
    const int id;
    string titlu;
    float pret;
    GenCarte gen;
    int nrCapitole;
    int* nrPagini; 
    static int nrCarti;

public:
    
    Carte() : id(++nrCarti) {
        titlu = "Carte default";
        pret = 0;
        gen = FICTIUNE;
        nrCapitole = 0;
        nrPagini = nullptr;
    }

    
    Carte(string titlu, float pret, GenCarte gen, int nrCapitole, int* paginiPerCapitol) : id(++nrCarti) {
        this->titlu = titlu;
        this->pret = pret;
        this->gen = gen;
        this->nrCapitole = nrCapitole;

        nrPagini = new int[nrCapitole];
        for (int i = 0; i < nrCapitole; i++)
            nrPagini[i] = paginiPerCapitol[i];

        delete[] paginiPerCapitol;
    }

    
    Carte(const Carte& copie) : id(++nrCarti) {
        titlu = copie.titlu;
        pret = copie.pret;
        gen = copie.gen;
        nrCapitole = copie.nrCapitole;

        if (copie.nrPagini != nullptr) {
            nrPagini = new int[nrCapitole];
            for (int i = 0; i < nrCapitole; i++)
                nrPagini[i] = copie.nrPagini[i];
        } else {
            nrPagini = nullptr;
        }
    }

    
    void operator=(const Carte& copie) {
        titlu = copie.titlu;
        pret = copie.pret;
        gen = copie.gen;
        nrCapitole = copie.nrCapitole;

        if (nrPagini != nullptr) delete[] nrPagini;

        if (copie.nrPagini != nullptr) {
            nrPagini = new int[nrCapitole];
            for (int i = 0; i < nrCapitole; i++)
                nrPagini[i] = copie.nrPagini[i];
        } else {
            nrPagini = nullptr;
        }
    }

    void afisare() {
        cout << "\n" << id << ". Carte: " << titlu << ", pret: " << pret << " lei, gen: ";
        if (gen == FICTIUNE) cout << "FICTIUNE";
        if (gen == EDUCATIVA) cout << "EDUCATIVA";
        if (gen == SF) cout << "SF";

        cout << ", nrCapitole: " << nrCapitole;
        if (nrPagini != nullptr) {
            cout << ", pagini per capitol: ";
            for (int i = 0; i < nrCapitole - 1; i++)
                cout << nrPagini[i] << ", ";
            cout << nrPagini[nrCapitole - 1];
        }
    }

    
    int getNrCapitole() { return nrCapitole; }

    void setNrCapitole(int nr) {
        if (nr > 0) nrCapitole = nr;
        else throw "Numar negativ de capitole!";
    }

    int* getNrPagini() {
        int* copie = new int[nrCapitole];
        for (int i = 0; i < nrCapitole; i++)
            copie[i] = nrPagini[i];
        return copie;
    }

    void setNrPagini(int* paginiNoi, int nrNou) {
        setNrCapitole(nrNou);
        if (nrPagini != nullptr) delete[] nrPagini;
        nrPagini = new int[nrCapitole];
        for (int i = 0; i < nrCapitole; i++)
            nrPagini[i] = paginiNoi[i];
        delete[] paginiNoi;
    }

    ~Carte() {
        if (nrPagini != nullptr) delete[] nrPagini;
    }

    void operator+=(float adaosPret) { pret += adaosPret; }
    bool operator>(const Carte& c) { return pret > c.pret; }
};

int Carte::nrCarti = 0;

int main() {
    Carte carte1;
    carte1.afisare();

    int* pagini = new int[3]{20, 30, 25};
    Carte* carte2 = new Carte("Invatam C++", 150, EDUCATIVA, 3, pagini);
    carte2->afisare();

    Carte copieCarte(*carte2);
    copieCarte.afisare();

    carte1 = *carte2;
    carte1.afisare();

    carte1 += 50;
    carte1.afisare();

    if (copieCarte > carte1) cout << "\nCopieCarte este mai scumpa!";
    else cout << "\nCarte1 este mai scumpa!";

    delete carte2;
    return 0;
}
