#include <iostream>
#include <string>
#include<cstring>
#pragma warning(disable:4996);


using namespace std;

class Laptop {
private:
   
    char* producator;           // char* (nume brand)
    int ram;                    // GB
    float* istoricTemperaturi;  // vector dinamic
    int nrMasuratori;

    static int nrLaptopuriUnice;

public:
    // 1. Constructor Implicit
    Laptop() {
        this->producator = new char[strlen("Necunoscut") + 1];
        strcpy(this->producator, "Necunoscut");

        this->ram = 4;
        this->istoricTemperaturi = nullptr;
        this->nrMasuratori = 0;
        nrLaptopuriUnice++;
    }

    // 2. Constructor cu Parametri
    Laptop(const char* _producator, int _ram, float* _istoric, int _nr) {
        // Alocare si copiere char*
        if (_producator != nullptr) {
            this->producator = new char[strlen(_producator) + 1];
            strcpy(this->producator, _producator);
        }
        else {
            this->producator = new char[strlen("N/A") + 1];
            strcpy(this->producator, "N/A");
        }

        this->ram = _ram;
        this->nrMasuratori = _nr;

        // Alocare si copiere vector float
        if (_nr > 0 && _istoric != nullptr) {
            this->istoricTemperaturi = new float[_nr];
            for (int i = 0; i < _nr; i++) {
                this->istoricTemperaturi[i] = _istoric[i];
            }
        }
        else {
            this->istoricTemperaturi = nullptr;
            this->nrMasuratori = 0;
        }
        nrLaptopuriUnice++;
    }

    // --- ZONA TA DE LUCRU ---

    // CERINTA 1: Constructor de Copiere (atentie la char*)
    Laptop(const Laptop& l) {
        if (l.producator != nullptr) {
            this->producator = new char[strlen(l.producator) + 1];
            strcpy(this->producator, l.producator);
        }
        else {
            this->producator = new char[strlen("N/A") + 1];
            strcpy(this->producator, "N/A");
        }

        this->ram = l.ram;
        this->nrMasuratori = l.nrMasuratori;

        // Alocare si copiere vector float
        if (l.nrMasuratori > 0 && l.istoricTemperaturi != nullptr) {
            this->istoricTemperaturi = new float[l.nrMasuratori];
            for (int i = 0; i < l.nrMasuratori; i++) {
                this->istoricTemperaturi[i] = l.istoricTemperaturi[i];
            }
        }
        else {
            this->istoricTemperaturi = nullptr;
            this->nrMasuratori = 0;
        }
        nrLaptopuriUnice++;



     }

    // CERINTA 1: Destructor
    ~Laptop() {
        if (this->producator != nullptr) {
            delete[] this->producator;
            this->producator = nullptr;
        }
        if (this->istoricTemperaturi != nullptr) {
            delete[] this->istoricTemperaturi;
            this->istoricTemperaturi = nullptr;
        }

    }

    // CERINTA 1: Operator= 
    // Laptop& operator=(const Laptop& l) ...
    Laptop operator=(const Laptop& l) {
        if (this != &l) {
            if (this->producator != nullptr) {
                delete[] this->producator;
            }
            if (l.producator != nullptr) {
                this->producator = new char[strlen(l.producator) + 1];
                strcpy(this->producator, l.producator);
            }
            else {
                this->producator = new char[strlen("N/A") + 1];
                strcpy(this->producator, "N/A");
            }

            this->ram = l.ram;
            this->nrMasuratori = l.nrMasuratori;

            // Alocare si copiere vector float
            if (this->istoricTemperaturi != nullptr) {
                delete[] this->istoricTemperaturi;
            }
            if (l.nrMasuratori > 0 && l.istoricTemperaturi != nullptr) {
                this->istoricTemperaturi = new float[l.nrMasuratori];
                for (int i = 0; i < l.nrMasuratori; i++) {
                    this->istoricTemperaturi[i] = l.istoricTemperaturi[i];
                }
            }
            else {
                this->istoricTemperaturi = nullptr;
                this->nrMasuratori = 0;
            }
            nrLaptopuriUnice++;



        }


        return *this;
    }





    // CERINTA 2: Setter pentru producator (sterge vechiul, pune noul)
    void setProducator(const char* numeNou) {
        if (this->producator != nullptr) {
            delete[] this->producator;
            this->producator = nullptr;
        }
        this->producator = new char[strlen(numeNou) + 1];
        if (numeNou != nullptr) {
            if (strlen(numeNou) > 2) {
                strcpy(this->producator, numeNou);
            }
        }
        else {
            this->producator = nullptr;
        }

        delete[] numeNou;

    }






    // CERINTA 3: Operator < (compara RAM)
    bool operator<(int RAM) {
        return this->ram < RAM;
    
    }




    // CERINTA 4: Operator cast la string (returneaza producatorul)
    explicit operator string() {
        return string(this->producator);
    }



    // explicit operator string() ...

    // CERINTA 5: Operator << pentru afisare
    friend ostream& operator<<(ostream& out, Laptop& l) {
        if (l.producator != nullptr) {
            out << l.producator;
        }
        out << l.ram;
        out << l.nrMasuratori;
        if (l.istoricTemperaturi != nullptr) {
            for (int i = 0;i < l.nrMasuratori;i++) {
                out << l.nrMasuratori;
            }
        }

        
        return out;
    }





    static int getNrLaptopuri() { return nrLaptopuriUnice; }
};

int Laptop::nrLaptopuriUnice = 0;

int main() {
    float temp[] = { 45.5, 60.2, 85.0 };

    Laptop l1("Lenovo", 16, temp, 3);
    Laptop l2("Dell", 8, nullptr, 0);

    // Testare Rule of Three
    Laptop l3 = l1; // Copy Const
    l2 = l1;        // Op =

    // Testare Setter char*
    l2.setProducator("Asus"); // Aici trebuie sa nu crape memoria

    // Testare operatori
   //if (l2 < l1) cout << "l2 e mai slab ca l1" << endl;

    // Testare cast
    // string nume = (string)l1;
    // cout << "Brand l1: " << nume << endl;

    // Testare afisare
    // cout << l1;

    return 0;
}
