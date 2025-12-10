#include<iostream>
#include<string>

using namespace std;
enum Categorie { PRO = 10, PRO_MAX = 15, NORMAL = 5 };

class Telefon {
private:
	const int id;
	float pret;
	string model;
	Categorie categorie;
	int nrAplicatii;
	float* spatiiOcupate;
	static int nrTelefoane;
public:
	//constructor fara parametri
	Telefon() :id(++nrTelefoane) {
		this->model = "Telefon default";
		this->pret = 0;
		this->nrAplicatii = 0;
		this->spatiiOcupate = nullptr;
		this->categorie = NORMAL;
	}

	Telefon(string model, float pret, int nrAplicatii, float* spatiiAplicatii, Categorie categorie) :id(++nrTelefoane) {
		this->model = model;
		this->pret = pret;
		this->nrAplicatii = nrAplicatii;
		this->spatiiOcupate = new float[this->nrAplicatii];
		for (int i = 0; i < this->nrAplicatii; i++) {
			this->spatiiOcupate[i] = spatiiAplicatii[i];
		}
		this->categorie = categorie;

		delete[] spatiiAplicatii;
	}

	Telefon(const Telefon& copie) :id(++nrTelefoane){
		this->pret = copie.pret;
		this->model = copie.model;
		this->categorie = copie.categorie;
		this->nrAplicatii = copie.nrAplicatii;

		if (copie.spatiiOcupate != nullptr) {
			this->spatiiOcupate = new float[copie.nrAplicatii];
			for (int i = 0; i < copie.nrAplicatii; i++) {
				this->spatiiOcupate[i] = copie.spatiiOcupate[i];
			}
		}
		else {
			this->spatiiOcupate = nullptr;
		}
	}

	void operator=(const Telefon& copie){
		this->model = copie.model;
		this->pret = copie.pret;
		this->categorie = copie.categorie;
		this->nrAplicatii = copie.nrAplicatii;

		if (this->spatiiOcupate != nullptr) {
			delete[] this->spatiiOcupate;
			this->spatiiOcupate = nullptr;
		}

		if (copie.spatiiOcupate != nullptr) {
			this->spatiiOcupate = new float[copie.nrAplicatii];
			for (int i = 0; i < copie.nrAplicatii; i++) {
				this->spatiiOcupate[i] = copie.spatiiOcupate[i];
			}
		}
		else {
			this->spatiiOcupate = nullptr;
		}
		
	}

	void afisareTelefon() {
		cout << endl << this->id << ". Telefonul " << this->model << " costa " << this->pret << " lei, este din categoria ";
		if (this->categorie == NORMAL) cout << "NORMAL";
		if (this->categorie == PRO) cout << "PRO";
		if (this->categorie == PRO_MAX) cout << "PRO_MAX";
		cout << " si are instalate " << this->nrAplicatii << " aplicatii care ocupa: ";
		if (this->spatiiOcupate != nullptr) {
			for (int i = 0; i < this->nrAplicatii - 1; i++) {
				cout << this->spatiiOcupate[i] << " MB, ";
			}
			cout << this->spatiiOcupate[this->nrAplicatii - 1] << " MB.";
		}
	}

	//get si set pentru nrAplicatii
	int getNrAplicatii() {
		return this->nrAplicatii;
	}

	void setNrAplicatii(int nrAplicatiiNou) {
		if (nrAplicatiiNou > 0)
		{
			this->nrAplicatii = nrAplicatiiNou;
		}
		else {
			
			throw "Valoare negativa";
		}
	}

	//get si set pentru pointeri
	float* getSpatiiOcupate() {
		//return this->spatiiOcupate; - asa nu
		float* copieSpatii = new float[this->nrAplicatii];
		for (int i = 0; i < this->nrAplicatii; i++) {
			copieSpatii[i] = this->spatiiOcupate[i];
		}

		return copieSpatii;
	}

	void setSpatiiOcupate(float* spatiiNoi, int nrAplicatiiNou) {
		setNrAplicatii(nrAplicatiiNou);

		if (this->spatiiOcupate != nullptr) {
			delete[] this->spatiiOcupate;
		}
		this->spatiiOcupate = new float[this->nrAplicatii];
		for (int i = 0; i < this->nrAplicatii; i++) {
			this->spatiiOcupate[i] = spatiiNoi[i];
		}

		delete[] spatiiNoi;
	}

	~Telefon() {
		if (this->spatiiOcupate != nullptr) {
			delete[] this->spatiiOcupate;
		}
	}

	void operator+=(float pretDeAdunat) {
		this->pret += pretDeAdunat;
	}

	bool operator>(const Telefon& t) {
		return this->pret > t.pret;
	}
};

int Telefon::nrTelefoane = 0;

void main() {
	Telefon samsung;
	//samsung.pret = 2000;

	samsung.afisareTelefon();
	float* spatii = new float[4] {150.5, 320.8, 89.2, 450.0};
	Telefon* iphone = new Telefon("iPhone 15 Pro", 5500, 4, spatii, PRO);

	iphone->afisareTelefon();

	//Telefon telefon = *iphone;
	Telefon telefon(*iphone);
	telefon.afisareTelefon();

	samsung = *iphone;
	samsung.afisareTelefon();

	samsung += 500;

	samsung.afisareTelefon();

	if (telefon > samsung) {
		cout << endl << " Telefonul iPhone are pretul mai mare!";
	}
	else {
		cout << endl << " Telefonul Samsung are pretul mai mare!";
	}

	delete iphone;
}
