#include <iostream>
#include <string>
using namespace std;

#pragma warning(disable:4996)

class Ingredient {
private:
	const int cod;
	char* denumire=nullptr;
	int stoc=0;
	bool esteAlergen="false";
public:
	Ingredient(const int codNou, const char* denumire, int stoc, bool esteAlergen) :cod(codNou) {
		if (denumire != nullptr) {
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
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
		this->stoc = i.stoc;
		this->esteAlergen = i.esteAlergen;
	}

	Ingredient operator=(const Ingredient& i) {
		if (this != &i) {
			if (this->denumire != nullptr) {
				delete[] this->denumire;
			}
			if (i.denumire != nullptr) {
				this->denumire = new char[strlen(i.denumire) + 1];
				strcpy(this->denumire, i.denumire);
			}
			this->stoc = i.stoc;
			this->esteAlergen = i.esteAlergen;

		}
		return *this;
	}


	friend ostream& operator<<(ostream& out, Ingredient& i) {
		out << endl << " Cod: " << i.cod;
		out << " , denumire: ";
		if(i.denumire != nullptr) {
			out << i.denumire;
		}
		out << " ,stoc: " << i.stoc;
		if (i.esteAlergen == true) {
			out << " , este Alergen.";
		}
		else {
			if (i.esteAlergen == false) {
				out << " , nu este Alergen.";
			}
		}
		return out;
	}

	Ingredient operator-(int val) {
		Ingredient copie = *this;
		copie.stoc = this->stoc - val;
		return copie;

	}

	friend Ingredient operator+(int val, const Ingredient& i) {
		Ingredient copie=i;
		copie.stoc = val + i.stoc;
		return copie;

	}

	//Getters necesari pentru clasa Reteta
	const char* getDenumire() const { return this->denumire; }


	~Ingredient() {
		if (this->denumire != nullptr) {
			delete[]this->denumire;
			this->denumire = nullptr;
		}
	}


};




class Reteta {
private:
	Ingredient** listaIngrediente=nullptr;
	int nrIngrediente=0;
public:

	~Reteta() {
		if (this->listaIngrediente != nullptr) {
			for (int i = 0;i < nrIngrediente;i++)
			{
				delete listaIngrediente[i];
			}
			delete[]listaIngrediente;
			this->listaIngrediente = nullptr;
		}
	}

	// Metoda pentru adaugare cu verificare unicitate (dupa nume)
	void adaugaIngredient(const Ingredient& ing) {
		//1.Verificare unicitate
		for (int i = 0;i < nrIngrediente;i++) {
			if (strcmp(listaIngrediente[i]->getDenumire(), ing.getDenumire()) == 0) {
				//ingredientul exista deja
				return;
			}
		}

		// // 2.Adaugare (redimensionare vector)
		Ingredient** temp = new Ingredient * [nrIngrediente + 1];
		for (int i = 0;i < nrIngrediente;i++) {
			temp[i] = listaIngrediente[i];
		}

		//3.adaugam o copie a ingredientului
		temp[nrIngrediente] = new Ingredient(ing);
		if (listaIngrediente != nullptr) {
			delete[]listaIngrediente;
		}
		listaIngrediente = temp;
		nrIngrediente++;
	}

	// Operator != (Reteta != string)
	// Returneaza TRUE daca ingredientul NU se gaseste in reteta
	bool operator!=(const char* numeCautat) {
		for (int i = 0;i < nrIngrediente;i++) {

			// Comparare case-insensitive (optional) sau standard strcmp
		   // Aici folosim _stricmp pentru a gasi "Faina" chiar daca cautam "faina"
		   // Daca nu merge pe Linux/Mac, folositi strcmp sau strcasecmp

			if (_stricmp(listaIngrediente[i]->getDenumire(), numeCautat) == 0) {
				return false;          //// L-am gasit, deci (Reteta != Nume) este Fals
			}
			return true; //Nu l am gasit
		}

	}


	//opretaor[]
	//returneaza denumirea ingredientului de pe poizitia index
	string operator[](int index) {
		if (index >= 0 && index < nrIngrediente) {
			return string(listaIngrediente[index]->getDenumire());
		}
		return"Index invalid";
	}


	friend ostream& operator<<(ostream& out, const Reteta& r) {
		out << "\n--- Reteta ---" << endl;
		if (r.nrIngrediente == 0) {
			out << "reteta e goala"<<endl;
		}
		else {
			for (int i = 0;i < r.nrIngrediente;i++) {
				out << *r.listaIngrediente[i]<<endl;
			}
		}

		return out;
	}



};

int main(){
	Ingredient i1(102, "Faina", 100, true),i2=i1;
	//cout << i1;
	
	i2 = i1 - 10;
	cout << i1;
	cout << i2;

	i1 = 10 + i2;
	cout << i1;

	           // 2. Testare Clasa Reteta

	Reteta r1;

	

	// Populam reteta pentru test
	Ingredient ing1(200, "Zahar", 50, false);
	Ingredient ing2(201, "Oua", 10, true);
	Ingredient ing3(202, "Lapte", 1000, true);

	r1.adaugaIngredient(ing1);
	r1.adaugaIngredient(ing2);
	r1.adaugaIngredient(ing3);

	cout << r1;

	// Verificam conditia din enununt
	// "Faina" nu a fost adaugata in r1, deci conditia va fi adevarata
	if (r1 != "faina")
		cout << "\nIngredientul faina nu se gaseste in reteta curenta";


	// Operator index

	string ingredient = r1[2];    // Ar trebui sa returneze "Lapte" (pozitia 0, 1, 2)
	cout << "Ingredientul de pe pozitia 2 este: " << ingredient << endl;


	return 0;
}
