#include <iostream>
#include <vector>
#include <string>

using namespace std;

class TrotinetaElectrica {
private:
    const int id;
    float nivelBaterie;             // 0 - 100
    float consumPerKm;              // unități de energie
    float* kmPerSesiuneInchiriere;  // vector alocat dinamic
    int nrSesiuniInchiriere;        // dimensiunea vectorului
    static int pretperkm;
    // [CERINȚA 1] Aici vei adăuga atributele statice și constante

public:
    // Constructor Implicit
    TrotinetaElectrica(int _id) :id(_id){
        this->nivelBaterie = 100;
        this->consumPerKm = 5;
        this->kmPerSesiuneInchiriere = nullptr;
        this->nrSesiuniInchiriere = 0;
        // Incrementare static (dacă e cazul)
    }

    // Constructor cu Parametri
    TrotinetaElectrica(const int _id,float nivel, float consum, int nrSesiuni, float* istoricKm) :id(_id) {
        this->nivelBaterie = nivel;
        this->consumPerKm = consum;
        this->nrSesiuniInchiriere = nrSesiuni;
        if (nrSesiuni > 0 && istoricKm != nullptr) {
            this->kmPerSesiuneInchiriere = new float[nrSesiuni];
            for (int i = 0; i < nrSesiuni; i++) {
                this->kmPerSesiuneInchiriere[i] = istoricKm[i];
            }
        }
        else {
            this->kmPerSesiuneInchiriere = nullptr;
            this->nrSesiuniInchiriere = 0;
        }
        // Incrementare static + Inițializare constant (dacă e cazul)
    }

    // Constructor de Copiere 
    TrotinetaElectrica(const TrotinetaElectrica& t):id(t.id) {
        this->nivelBaterie = t.nivelBaterie;
        this->consumPerKm = t.consumPerKm;
        this->nrSesiuniInchiriere = t.nrSesiuniInchiriere;
        if (t.kmPerSesiuneInchiriere != nullptr && t.nrSesiuniInchiriere > 0) {
            this->kmPerSesiuneInchiriere = new float[t.nrSesiuniInchiriere];
            for (int i = 0; i < t.nrSesiuniInchiriere; i++) {
                this->kmPerSesiuneInchiriere[i] = t.kmPerSesiuneInchiriere[i];
            }
        }
        else {
            this->kmPerSesiuneInchiriere = nullptr;
        }
    }

    // Operator= 
    TrotinetaElectrica operator=(const TrotinetaElectrica& t) {
        if (this != &t) {
            this->nivelBaterie = t.nivelBaterie;
            this->consumPerKm = t.consumPerKm;
            this->nrSesiuniInchiriere = t.nrSesiuniInchiriere;
            if (this->kmPerSesiuneInchiriere != nullptr) {
                delete[] this->kmPerSesiuneInchiriere;
                this->kmPerSesiuneInchiriere = nullptr;
            }
            if (t.kmPerSesiuneInchiriere != nullptr && t.nrSesiuniInchiriere > 0) {
                this->kmPerSesiuneInchiriere = new float[t.nrSesiuniInchiriere];
                for (int i = 0; i < t.nrSesiuniInchiriere; i++) {
                    this->kmPerSesiuneInchiriere[i] = t.kmPerSesiuneInchiriere[i];
                }
            }
            else {
                this->kmPerSesiuneInchiriere = nullptr;
            }
        }
        return *this;
    }




    // Destructor
    ~TrotinetaElectrica() {
        if (this->kmPerSesiuneInchiriere != nullptr) {
            delete[] this->kmPerSesiuneInchiriere;
        }
        // Decrementare static (dacă e cazul)
    }

    // Metode de afisare (ajutatoare)
    void afisare() {
        cout << "Baterie: " << nivelBaterie << "%, Consum: " << consumPerKm << ", Sesiuni: " << nrSesiuniInchiriere << endl;
        if (nrSesiuniInchiriere > 0) {
            cout << "Istoric km: ";
            for (int i = 0; i < nrSesiuniInchiriere; i++) cout << kmPerSesiuneInchiriere[i] << " ";
            cout << endl;
        }
    }



    //get pt kmPerSesiuneInchiriere
    float* getKmPerSesiuneInchiriere() {
        float* copie = new float[this->nrSesiuniInchiriere];
        if (this->kmPerSesiuneInchiriere != nullptr) {
            for (int i = 0;i < this->nrSesiuniInchiriere;i++) {
                copie[i] = this->kmPerSesiuneInchiriere[i];
            }
        }
        else {
            copie = nullptr;
        }


        return copie;
    }




    //set pt kmPerSesiuneInchiriere
    //void setNrSesiuniInchiriere(int nrSesiuniInchiriereNou) {
      //  if (nrSesiuniInchiriereNou > 0) {
        //    this->nrSesiuniInchiriere = nrSesiuniInchiriereNou;
        //}
        //else {
          //  throw exception("Valoare negativa");
        //}

    //}


    void setKmPerSesiuneInchiriere(float* kmPerSesiuneNou, int nrSesiuniInchiriereNou) {
       // setNrSesiuniInchiriere(nrSesiuniInchiriereNou);

        this->nrSesiuniInchiriere = nrSesiuniInchiriereNou;
        if (kmPerSesiuneNou != nullptr) {
            delete[] this->kmPerSesiuneInchiriere;
            this->kmPerSesiuneInchiriere;
        }

            this->kmPerSesiuneInchiriere = new float[this->nrSesiuniInchiriere];
            if (kmPerSesiuneNou != nullptr){
                for (int i = 0;i < this->nrSesiuniInchiriere;i++) {
                    this->kmPerSesiuneInchiriere[i] = kmPerSesiuneNou[i];
                }
            }
            else {
                this->kmPerSesiuneInchiriere = nullptr;
            }

            //delete[] kmPerSesiuneNou;


    }


    //operator + la NivelBaterie
 
    TrotinetaElectrica operator+(float val) {

        if (val > 0) {
            TrotinetaElectrica copie(*this);
            if (this->nivelBaterie + val > 100)
                copie.nivelBaterie = 100;
            else copie.nivelBaterie += val;
            return copie;

        }
        throw exception("val negativa");



    }

    //operator >   Supraîncarcă operatorul > care compară două trotinete pe baza numărului total de kilometri parcurși (suma elementelor din vectorul kmPerSesiuneInchiriere).
    bool operator>(TrotinetaElectrica& t) {
        float kmtotal=0;
        if (this->kmPerSesiuneInchiriere != nullptr) {
            for (int i = 0;i < this->nrSesiuniInchiriere;i++) {
                kmtotal += this->kmPerSesiuneInchiriere[i];
            }
        }
        float kmtotal1 = 0;
        if (t.kmPerSesiuneInchiriere != nullptr) {
            for (int i = 0;i < t.nrSesiuniInchiriere;i++) {
                kmtotal += t.kmPerSesiuneInchiriere[i];
            }
        }
        return kmtotal > kmtotal1;

        }


    //4. Operator cast la float:

    //Supraîncarcă operatorul de cast explicit la float.
    //Acesta trebuie să returneze autonomia estimată(câți km mai poate merge trotineta cu bateria curentă).
    //Formula: nivelBaterie / consumPerKm.

    explicit operator float() {
        return this->nivelBaterie / this->consumPerKm;

}

    //5. Excepții (try-catch) în setNivelBaterie:

    //Implementează metoda void setNivelBaterie(float nivel) care să modifice atributul nivelBaterie.
    //Dacă valoarea primită este negativă(ex: -5), aruncă o excepție de tip float sau string.


    void setNivelBaterie(float nivelBaterieNou) {
        if (nivelBaterieNou > 0) {
            this->nivelBaterie = nivelBaterieNou;
        }
        else {
            throw exception("nivel baterie negativ");
        }

}


    friend ostream& operator<<(ostream& out, const TrotinetaElectrica& t) {
        out << endl << "Id: " << t.id;
        out << " , nivelBaterie " << t.nivelBaterie;
        out << ", consumPerKm " << t.consumPerKm;
        out << ", nrSesiuniInchiriere " << t.nrSesiuniInchiriere;
        if (t.kmPerSesiuneInchiriere != nullptr) {
            for (int i = 0;i < t.nrSesiuniInchiriere;i++)
                out <<endl<< t.kmPerSesiuneInchiriere[i]<<endl;
        }

        return out;
 }

    friend istream& operator>>(istream& in, TrotinetaElectrica& t) {
        
        cout << endl << "Da nivelBaterie ";
        in >> t.nivelBaterie;
        cout << endl << "Da consum per km ";
        in >> t.consumPerKm;
        cout << endl << "Da nrSesiuniInchiriere: ";
        in >> t.nrSesiuniInchiriere;
        if (t.kmPerSesiuneInchiriere != nullptr) {
            delete[]t.kmPerSesiuneInchiriere;
            t.kmPerSesiuneInchiriere = nullptr;
        }
        t.kmPerSesiuneInchiriere = new float[t.nrSesiuniInchiriere];
        //sau cout << endl << "Da nrSesiuniInchiriere";
        
        for (int i = 0;i < t.nrSesiuniInchiriere;i++) {
                cout << "sesiunea[ " << i << "]: ";
                in >> t.kmPerSesiuneInchiriere[i];
            }
        
        return in;
    }




};
int TrotinetaElectrica::pretperkm = 5;


void main() {

    TrotinetaElectrica t1(1);
    cout << t1 << "Constr cu un param ";


    //CONSTR CU TOTI PARAM
    float v[3] = { 10,20,30 };
    TrotinetaElectrica t2(2, 90, 4, 3, v);
    cout<<endl<<"Constr cu toti param"<<t2;

    //apel istream si ostream
   // cin >> t1;
    //cout << t1;

    //operator + la NivelBaterie
    try {
        t2 = t2 + (-5);
        cout << "modificare NivelBaterie opertor+ " << t2;
    }
    catch(exception ex){
            cout << endl << ex.what();
    }

    //op >
    float v2[3] = { 10,20,35 };
    TrotinetaElectrica t3(2, 90, 4, 3, v2);
    if (t2 > t3) {
        cout << "t2 are kmperses mai mare(op >)";
    }
    else{
        cout << "t3 are kmperses mai mare(op>)";
    }


    //4. Operator cast la float:
    float autonomie=0;
    autonomie = (float)t2;
    cout <<endl<<"op cast"<<autonomie;

    //set
    float v3[4] = { 10,20,30,40 };
    t2.setKmPerSesiuneInchiriere(v3, 4);
    cout << endl<<"t2set  "<<t2;

    //get
    float* copie= t2.getKmPerSesiuneInchiriere();
    for (int i = 0; i < 4; i++) {     // t2 are 4 sesiuni după set
        cout << copie[i] << " ";
    }

    delete[] copie;
    

}
