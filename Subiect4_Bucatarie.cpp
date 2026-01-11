#include<iostream>
#include<string>
using namespace std;
#pragma warning(disable:4996)


class Ingredient {
private:
	const int cod;
	char* denumire=nullptr;
	int stoc=0;
	bool esteAlergen = false;
public:
	Ingredient(const int codNou,  const char* denumire, int stoc,bool esteAlergen) :cod(codNou) {
		if (denumire != nullptr) {
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire,denumire);
		}
		else {
			this->denumire = nullptr;
		}
		this->stoc = stoc;
		this->esteAlergen = esteAlergen;



	}


	Ingredient(const Ingredient& i):cod(i.cod) {
		if (i.denumire != nullptr) {
			this->denumire = new char[strlen(i.denumire) + 1];
			strcpy(this->denumire, i.denumire);
		}
		else {
			this->denumire = nullptr;
		}
		this->stoc = i.stoc;
		this->esteAlergen = i.esteAlergen;
	}

	Ingredient& operator=(const Ingredient& i) {
		if (this != &i) {
			if (this->denumire != nullptr) {
				delete[] this->denumire;
			}
			if (i.denumire != nullptr) {
				this->denumire = new char[strlen(i.denumire) + 1];
				strcpy(this->denumire, i.denumire);
			}
			else {
				this->denumire = nullptr;
			}
			this->stoc = i.stoc;
			this->esteAlergen = i.esteAlergen;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, Ingredient& i) {
		out << endl << "Cod: " << i.cod;
		out << " , denumire: ";
		if (i.denumire != nullptr) {
			out << i.denumire;
		}
		out << " , stoc: " << i.stoc;
		out << " , este Alergen : " << i.esteAlergen;
		return out;

	}


	Ingredient& operator++() {
		
		this->stoc++;
		return *this;
	}


	friend Ingredient operator+(int val, Ingredient& i) {
		Ingredient copie = i;
		copie.stoc += val;
		return copie;

	}

	const char* getDenumire() const { return denumire; }
	int getCod() const { return cod; }
	bool getEsteAlergen() const { return esteAlergen; }
	void setStoc(int stocNou) { this->stoc = stocNou; }
	int getStoc() const { return stoc; }

	~Ingredient() {
		if (this->denumire != nullptr) {
			delete[]this->denumire;
			this->denumire=nullptr;
		}
	}

};


class Prajitura {
private:
	char* denumire=nullptr;
	Ingredient** listaIngrediente = nullptr;
	int nrIngrediente=0;

public: 
	Prajitura(const char* denumire) {
		if (denumire != nullptr) {
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
		}
	}


	Prajitura(const Prajitura& p) {
		if (p.denumire != nullptr) {
			this->denumire = new char[strlen(p.denumire) + 1];
			strcpy(this->denumire, p.denumire);
		}
		else { this->denumire = nullptr; }
		this->nrIngrediente = p.nrIngrediente;
		if (p.nrIngrediente > 0) {
			this->listaIngrediente = new Ingredient * [this->nrIngrediente];
			for (int i = 0;i < this->nrIngrediente;i++) {
				this->listaIngrediente[i] = new Ingredient(*(p.listaIngrediente[i]));
			}

		}
		else {
			this->listaIngrediente = nullptr;
		}
		
	}

	Prajitura& operator=(const Prajitura& p) {
		if (this != &p) {
			if (this->denumire != nullptr) {
				delete[]this->denumire;
			}
			if (p.denumire != nullptr) {
				this->denumire = new char[strlen(p.denumire) + 1];
				strcpy(this->denumire, p.denumire);
			}
			else { this->denumire = nullptr; }
			this->nrIngrediente = p.nrIngrediente;
			if (p.nrIngrediente > 0) {
				this->listaIngrediente = new Ingredient * [this->nrIngrediente];
				for (int i = 0;i < this->nrIngrediente;i++) {
					this->listaIngrediente[i] = new Ingredient(*(p.listaIngrediente[i]));
				}

			}
			else {
				this->listaIngrediente = nullptr;
			}
		}
		return* this;
	}

	friend ostream& operator<<(ostream& out, Prajitura& p) {
		out << endl << " DENUMIRE: ";
		if (p.denumire != nullptr) {
			out << p.denumire;
		}
		out << " , are nr ingrediente= " << p.nrIngrediente;
		out << ", are LISTA ingrediente: ";
		if (p.listaIngrediente != nullptr) {
			for (int i = 0;i < p.nrIngrediente;i++) {
				out << *(p.listaIngrediente[i]);
			}
		}
		
		return out;
	}


	// Metoda pentru adaugare cu verificarea unicitatii (nume si cod)
	void adaugaIngredient(const Ingredient& ing) {
		// Verificam daca ingredientul exista deja
		for (int i = 0;i<this->nrIngrediente;i++) {
			if (listaIngrediente[i]->getCod() == ing.getCod() && strcmp(listaIngrediente[i]->getDenumire(), ing.getDenumire()) == 0) {
				return; // Exista deja, nu il mai adaugam
			}
		}

		// Realocare memorie
		Ingredient** temp = new Ingredient * [nrIngrediente + 1];
		for (int i = 0;i < nrIngrediente;i++) {
			temp[i] = listaIngrediente[i];
		}
		temp[nrIngrediente] = new Ingredient(ing); // Folosim copy constructor

		delete[] listaIngrediente;
		listaIngrediente = temp;
		nrIngrediente++;


	}


	// 1. Operator ! (Verifică dacă NU are alergeni)
	bool operator!() {
		for (int i = 0;i < nrIngrediente;i++) {
			if (listaIngrediente[i]->getEsteAlergen()) {
				return false;// Dacă găsește UNUL, !Prajitura este false
			}
		}
		return true;
	}


	//2.operator--post
	Prajitura operator--(int) {
		Prajitura copie = *this;
		for (int i = 0;i < nrIngrediente;i++) {
			int stocVechi = listaIngrediente[i]->getStoc();
			if (stocVechi > 0) {
				listaIngrediente[i]->setStoc(stocVechi - 1);
			}
		}
		return copie;
	}







	~Prajitura() {
		if (this->denumire != nullptr) {
			delete[]this->denumire;
			this->denumire = nullptr;
		}

		if (this->listaIngrediente != nullptr) {
			for (int i = 0;i < nrIngrediente;i++) {
				delete this->listaIngrediente[i];
				
			}
			delete[]this->listaIngrediente;

		}
	}



};



int main(){ 
	cout << "----Testare clasa Ingredient----";
	Ingredient i1(102, "Faina", 100, true),i2(i1);
	cout << i1;
	i2 = ++i1;
	cout << i2;
	
	i1 = 10 + i2;
	cout << i1;



	cout << endl<<"----Testare clasa Prajitura----";

	Prajitura p1("tiramisu");

	//apel modalitate populare cu ingrediente
	p1.adaugaIngredient(i1);
	cout << p1;

	//operator1
	if (!p1) {
		cout << "\nPrajitura nu are are ingrediente alergen in componenta";
	}
	else {
		cout << "\nPrajitura CONTINE Alergeni!";
	}
	
	//operator2 
	cout << p1;
	p1--; //scadem stocul
	cout << "\nDupa utilizare (stoc scazut):" << p1;


	return 0;
}
