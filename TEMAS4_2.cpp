#include <iostream>
#include <string>
using namespace std;

enum TipMotor { ELECTRIC = 1, DIESEL = 2, BENZINA = 3 };

class Masina {
private:
    const int id;
    string marca;
    string model;
    float pret;
    TipMotor tipMotor;
    int nrComponente;
    float* greutatiComponente; 
    static int nrMasini;

public:
    
    Masina() : id(++nrMasini) {
        this->marca = "Necunoscuta";
        this->model = "Standard";
        this->pret = 0;
        this->tipMotor = BENZINA;
        this->nrComponente = 0;
        this->greutatiComponente = nullptr;
    }

    
    Masina(string marca, string model, float pret, TipMotor tipMotor, int nrComponente, float* greutati)
        : id(++nrMasini) {
        this->marca = marca;
        this->model = model;
        this->pret = pret;
        this->tipMotor = tipMotor;
        this->nrComponente = nrComponente;

        this->greutatiComponente = new float[this->nrComponente];
        for (int i = 0; i < this->nrComponente; i++) {
            this->greutatiComponente[i] = greutati[i];
        }
        delete[] greutati;
    }

    
    void afisareMasina() {
        cout << endl << id << ". " << marca << " " << model 
             << " costa " << pret << " EUR, are motor ";
        if (tipMotor == ELECTRIC) cout << "ELECTRIC";
        else if (tipMotor == DIESEL) cout << "DIESEL";
        else cout << "BENZINA";

        cout << " si contine " << nrComponente << " componente (greutati in kg): ";
        if (greutatiComponente != nullptr) {
            for (int i = 0; i < nrComponente - 1; i++)
                cout << greutatiComponente[i] << ", ";
            if (nrComponente > 0)
                cout << greutatiComponente[nrComponente - 1] << ".";
        }
    }

    
    int getNrComponente() {
        return nrComponente;
    }

    void setNrComponente(int nrNou) {
        if (nrNou > 0)
            this->nrComponente = nrNou;
        else
            throw "Numar invalid de componente!";
    }

    
    float* getGreutatiComponente() {
        float* copie = new float[this->nrComponente];
        for (int i = 0; i < this->nrComponente; i++)
            copie[i] = this->greutatiComponente[i];
        return copie;
    }

    void setGreutatiComponente(float* greutatiNoi, int nrNou) {
        setNrComponente(nrNou);
        if (this->greutatiComponente != nullptr)
            delete[] this->greutatiComponente;

        this->greutatiComponente = new float[this->nrComponente];
        for (int i = 0; i < this->nrComponente; i++)
            this->greutatiComponente[i] = greutatiNoi[i];

        delete[] greutatiNoi;
    }

  
    ~Masina() {
        if (this->greutatiComponente != nullptr)
            delete[] this->greutatiComponente;
    }
};

int Masina::nrMasini = 0;

void main() {
    Masina m1;
    m1.afisareMasina();

    float* greutati = new float[3]{ 120.5, 80.3, 250.0 };
    Masina* m2 = new Masina("Tesla", "Model S", 89999, ELECTRIC, 3, greutati);
    m2->afisareMasina();

    try {
        m2->setNrComponente(-4);
    }
    catch (const char* mesaj) {
        cout << endl << "Eroare: " << mesaj;
    }

    cout << endl << "Numar componente actual: " << m2->getNrComponente();

    m2->setGreutatiComponente(new float[4]{ 150.2, 95.0, 310.5, 70.0 }, 4);
    float* greutatiActuale = m2->getGreutatiComponente();

    for (int i = 0; i < m2->getNrComponente(); i++) {
        cout << endl << "Componenta " << i + 1 << ": " << greutatiActuale[i] << " kg";
    }

    delete[] greutatiActuale;
    delete m2;

    
}
