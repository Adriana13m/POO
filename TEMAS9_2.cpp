#include<iostream>
using namespace std;

class Preparat {
private:
	float pret = 0;
public:
	Preparat() {
	}

	Preparat(float pret) {
		this->pret = pret;
	}

	float getPret() {
		return this->pret;
	}
};

class Restaurant {
private:
	
	Preparat* preparate;
	int nrPreparate;
	string nume;
public:
	Restaurant(string nume, int nrPreparate, float* preturi) {
		this->nrPreparate = nrPreparate;
		this->nume = nume;
		this->preparate = new Preparat[nrPreparate];
		for (int i = 0; i < nrPreparate; i++) {
			this->preparate[i] = Preparat(preturi[i]);
		}
	}

	Preparat& operator[](int index) {
		if (index >= 0 && index < this->nrPreparate) {
			return this->preparate[index];
		}
		else {
			throw "Index ul este in afara intervalului!";
		}
	}

	string getNume() {
		return this->nume;
	}

	Restaurant(const Restaurant& r) {
		this->nrPreparate = r.nrPreparate;
		this->nume = r.nume;
		if (r.preparate != nullptr) {
			this->preparate = new Preparat[r.nrPreparate];
			for (int i = 0; i < this->nrPreparate; i++) {
				this->preparate[i] = r.preparate[i];
			}
		}
		else {
			this->preparate = nullptr;
		}
	}

	~Restaurant() {
		if (this->preparate != nullptr) {
			delete[] this->preparate;
		}
	}

	
};

void main() {
	Restaurant restaurant("Trattoria Italiana", 3, new float[3] {35.50, 42.00, 28.75});
	cout << endl << "Pretul primului preparat de la " << restaurant.getNume() << " este de " << restaurant[0].getPret() << " lei.";
	
	Restaurant restaurant2 = restaurant;
	cout << endl << "Pretul pentru al doilea preparat de la " << restaurant.getNume() << " este de " << restaurant[1].getPret() << " lei.";
	cout << endl << "Pretul pentru al treilea preparat de la " << restaurant2.getNume() << " este de " << restaurant2[2].getPret() << " lei.";
}
