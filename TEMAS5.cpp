#include <iostream>
#include <string>

using namespace std;

enum TipElectronic { PORTABIL = 1, FIX = 2, PREMIUM = 3 };

class ProdusElectronic {
private:
    const int id;
    float pret;
    string denumire;
    TipElectronic tip;
    int nrComponente;
    float* greutati;
    static int nrProduseElectronice;

public:
    
    ProdusElectronic() : id(++nrProduseElectronice) {
        denumire = "Produs electronic default";
        pret = 0;
        nrComponente = 0;
        greutati = nullptr;
        tip = PORTABIL;
    }

    
    ProdusElectronic(string denumire, float pret, int nrComponente, float* greutatiComponente, TipElectronic tip) : id(++nrProduseElectronice) {
        this->denumire = denumire;
        this->pret = pret;
        this->nrComponente = nrComponente;
        this->tip = tip;

        this->greutati = new float[nrComponente];
        for (int i = 0; i < nrComponente; i++) {
            this->greutati[i] = greutatiComponente[i];
        }

        delete[] greutatiComponente;
    }

    
    ProdusElectronic(const ProdusElectronic& copie) : id(++nrProduseElectronice) {
        pret = copie.pret;
        denumire = copie.denumire;
        tip = copie.tip;
        nrComponente = copie.nrComponente;

        if (copie.greutati != nullptr) {
            greutati = new float[nrComponente];
            for (int i = 0; i < nrComponente; i++) {
                greutati[i] = copie.greutati[i];
            }
        } else {
            greutati = nullptr;
        }
    }

    void operator=(const ProdusElectronic& copie) {
        denumire = copie.denumire;
        pret = copie.pret;
        tip = copie.tip;
        nrComponente = copie.nrComponente;

        if (greutati != nullptr) {
            delete[] greutati;
            greutati = nullptr;
        }

        if (copie.greutati != nullptr) {
            greutati = new float[nrComponente];
            for (int i = 0; i < nrComponente; i++) {
                greutati[i] = copie.greutati[i];
            }
        }
    }

    void afisare() {
        cout << "\n" << id << ". Produsul electronic " << denumire << " costa " << pret << " lei, este de tipul ";
        if (tip == PORTABIL) cout << "PORTABIL";
        if (tip == FIX) cout << "FIX";
        if (tip == PREMIUM) cout << "PREMIUM";

        cout << " si contine " << nrComponente << " componente: ";
        if (greutati != nullptr) {
            for (int i = 0; i < nrComponente - 1; i++)
                cout << greutati[i] << " grame, ";
            cout << greutati[nrComponente - 1] << " grame.";
        }
    }

    
    int getNrComponente() { return nrComponente; }

    void setNrComponente(int nrNou) {
        if (nrNou > 0) nrComponente = nrNou;
        else throw "Valoare negativa pentru nrComponente";
    }

    
    float* getGreutati() {
        float* copie = new float[nrComponente];
        for (int i = 0; i < nrComponente; i++)
            copie[i] = greutati[i];
        return copie;
    }

    void setGreutati(float* greutatiNoi, int nrNou) {
        setNrComponente(nrNou);

        if (greutati != nullptr) delete[] greutati;

        greutati = new float[nrComponente];
        for (int i = 0; i < nrComponente; i++)
            greutati[i] = greutatiNoi[i];

        delete[] greutatiNoi;
    }

    ~ProdusElectronic() {
        if (greutati != nullptr) delete[] greutati;
    }

    void operator+=(float pretDeAdunat) { pret += pretDeAdunat; }
    bool operator>(const ProdusElectronic& p) { return pret > p.pret; }
};

int ProdusElectronic::nrProduseElectronice = 0;

int main() {
    ProdusElectronic laptop;
    laptop.afisare();

    float* greutati = new float[2]{1500, 500};
    ProdusElectronic* telefon = new ProdusElectronic("Telefon", 3000, 2, greutati, PORTABIL);
    telefon->afisare();

    ProdusElectronic tablet(*telefon);
    tablet.afisare();

    laptop = *telefon;
    laptop.afisare();

    laptop += 500;
    laptop.afisare();

    if (tablet > laptop) cout << "\nTablet-ul are pretul mai mare!";
    else cout << "\nLaptop-ul are pretul mai mare!";

    delete telefon;
    return 0;
}
