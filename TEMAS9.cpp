#include<iostream>
using namespace std;

class Carte {
private:
	float pret = 0;
public:
	Carte() {
	}

	Carte(float pret) {
		this->pret = pret;
	}

	float getPret() {
		return this->pret;
	}
};

class Biblioteca {
private:
	//1:1
	//Carte carte;
	//1:m
	Carte* carti;
	int nrCarti;
	string nume;
public:
	Biblioteca(string nume, int nrCarti, float* preturi) {
		this->nrCarti = nrCarti;
		this->nume = nume;
		this->carti = new Carte[nrCarti];
		for (int i = 0; i < nrCarti; i++) {
			this->carti[i] = Carte(preturi[i]);
		}
	}

	Carte& operator[](int index) {
		if (index >= 0 && index < this->nrCarti) {
			return this->carti[index];
		}
		else {
			throw "Index ul este in afara intervalului!";
		}
	}

	string getNume() {
		return this->nume;
	}

	Biblioteca(const Biblioteca& b) {
		this->nrCarti = b.nrCarti;
		this->nume = b.nume;
		if (b.carti != nullptr) {
			this->carti = new Carte[b.nrCarti];
			for (int i = 0; i < this->nrCarti; i++) {
				this->carti[i] = b.carti[i];
			}
		}
		else {
			this->carti = nullptr;
		}
	}

	~Biblioteca() {
		if (this->carti != nullptr) {
			delete[] this->carti;
		}
	}

	//Biblioteca(int nrCarti, float pret) {
	//	this->nrCarti = nrCarti;
	//	this->carte = Carte(pret);
	//}
};

void main() {
	Biblioteca biblioteca("Biblioteca Centrala", 2, new float[2] {45.50, 78.90});
	cout << endl << "Pretul primei carti din " << biblioteca.getNume() << " este de " << biblioteca[0].getPret() << " lei.";
	
	Biblioteca biblioteca2 = biblioteca;
	cout << endl << "Pretul pentru a doua carte din " << biblioteca.getNume() << " este de " << biblioteca[1].getPret() << " lei.";
}
