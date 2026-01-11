#include<iostream>
#include<string>

using namespace std;
#pragma warning(disable:4996)

class RezervareBilet {
private:
	int cod=0;
	float pretBilet=0;
	int rand=0;
	char loc;


public:
	RezervareBilet(int cod, float pretBilet, int rand, const char loc) {
		this->cod = cod;
		this->pretBilet = pretBilet;
		this->rand = rand;
		this->loc = loc;
	}

	RezervareBilet(const RezervareBilet& r) {
		this->cod = r.cod;
		this->pretBilet = r.pretBilet;
		this->rand = r.rand;
		this->loc = r.loc;


	}

	RezervareBilet& operator=(const RezervareBilet& r) {
		if (this != &r) {
			this->cod = r.cod;
			this->pretBilet = r.pretBilet;
			this->rand = r.rand;
			this->loc = r.loc;
		}
		return *this;

	}
	
	friend ostream& operator<<(ostream& out, RezervareBilet& r) {
		out << endl << " Cod: " << r.cod;
		out << " ,pret Bilet: " << r.pretBilet;
		out << " , rand: " << r.rand;
		out << " loc: " << r.loc;

		return out;
	}


	bool operator!=(const RezervareBilet& r) const {
		return (this->cod != r.cod &&
			this->pretBilet != r.pretBilet &&
			this->rand != r.rand &&
			this->loc != r.loc);
	}


	RezervareBilet operator++(int) {
		RezervareBilet copie = *this;
		this->pretBilet++;
		return copie;



	}

	int getCod() const { return this->cod; }
	float getPret() const { return pretBilet; }

};

enum TipZbor{INTERN, INTERNATIONAL};


class Zbor {
private:
	char* destinatie=nullptr;
	TipZbor tip=INTERN;
	RezervareBilet** listaRezervareBilet=nullptr;
	int nrRezervari=0;


public:
	Zbor(const char* destinatie) {
		this->destinatie = new char[strlen(destinatie) + 1];
		if (this->destinatie != nullptr) {
			strcpy(this->destinatie,destinatie);
		}
		else {
			this->destinatie = nullptr;
		}


	}



	~Zbor(){
		if (this->destinatie != nullptr) {
			delete[]this->destinatie;
			this->destinatie = nullptr;
		}

		if (this->listaRezervareBilet != nullptr) {
			for (int i = 0;i < nrRezervari;i++) {
				delete[]this->listaRezervareBilet[i];
			}
			delete[]listaRezervareBilet;
			this->listaRezervareBilet = nullptr;
		}
	}


	void adaugaRezervare(const RezervareBilet& r) {
		for (int i = 0;i < nrRezervari;i++) {
			if (listaRezervareBilet[i]->getCod() == r.getCod()) return;
		}

		RezervareBilet** temp = new RezervareBilet * [nrRezervari + 1];
		for (int i = 0;i < nrRezervari;i++) {
			temp[i] = listaRezervareBilet[i];
		}
		temp[nrRezervari] = new RezervareBilet(r);

		delete[] listaRezervareBilet;
		listaRezervareBilet = temp;
		nrRezervari++;


	}


	friend ostream& operator<<(ostream& out, const Zbor& z) {
		out << "\nZbor destinatie: ";
		if(z.destinatie!=nullptr){
			out << z.destinatie;
		}
		  
		out<< " | Rezervari: " << z.nrRezervari;
		return out;
	}

	bool operator>(const Zbor& z) const {
		if (this->nrRezervari > z.nrRezervari) {
			return true;
		}
		else{
			return false;
		 }
	}

	// 1. Copy Constructor pentru Zbor (esențial pentru operatorul +)
	Zbor(const Zbor& altul){
		this->nrRezervari = altul.nrRezervari;
		this->tip = altul.tip;

		if (altul.destinatie != nullptr) {
        this->destinatie = new char[strlen(altul.destinatie) + 1];
        strcpy(this->destinatie, altul.destinatie);
		  } 
		else {
        this->destinatie = nullptr;
    }

		if (altul.listaRezervareBilet != nullptr && altul.nrRezervari > 0) {
			// CORECT: Alocăm un vector de POINTERI (RezervareBilet*), nu de obiecte
			this->listaRezervareBilet = new RezervareBilet * [this->nrRezervari];

			for (int i = 0; i < this->nrRezervari; i++) {
				// CORECT: Alocăm fiecare obiect individual folosind Constructorul de Copiere al RezervareBilet
				this->listaRezervareBilet[i] = new RezervareBilet(*altul.listaRezervareBilet[i]);
			}
		}

	}

	Zbor operator+(const RezervareBilet& r) {
		Zbor copie = *this;
		copie.adaugaRezervare(r);
		return copie;
	}


};




int main() {
	cout << "-------Testare clasa RezervareBilet:------";
	RezervareBilet r1(102, 105.4, 12, 'B'), r2(r1);
	cout<<r1<<r2;
	if (r1 != r2)
		cout << "\nRezervarile au toate campurile diferite";
	
	r1++;
	cout << r1;
	



	cout << "-------Testare clasa Zbor:------";

	Zbor z1("Bucuresti-Malaga"), z2("Bucuresti-Lampedusa");
	
	z1.adaugaRezervare(r1);
	z2.adaugaRezervare(r1);
	cout << z1 << z2;

	if(z1 > z2) {
		cout << "\nZborul z1 are mai multe rezervari decat z2";
	}
	else {
		cout << "\nZborul z1 NU are mai multe rezervari decat z2, ci z2 are mai multe decat z1";
	}
	

	if (z1 + r1 > z2) {
		cout << "\nZborul z1 cu noua rezervare adaugata are mai multe bilete decat z2";
	}
	else {
		cout << "\nZborul z1 cu noua rezervare adaugata NU ARE mai multe";
	}

	return 0;
}
