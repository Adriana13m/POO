#include<iostream>
#include<string>

using namespace std;
enum TipCombustibil { ELECTRIC = 10, DIESEL = 6, BENZINA = 8 };

class Vehicul {
private:
	const int id;
	float pret;
	string marca;
	TipCombustibil tipCombustibil;
	int nrComponente;
	float* greutati;
	static int nrVehicule;
public:
	//constructor default//fara parametri
	Vehicul() :id(++nrVehicule) {
		this->marca = "Vehicul default";
		this->pret = 0;
		this->nrComponente = 0;
		this->greutati = nullptr;
		this->tipCombustibil = BENZINA;
	}

	Vehicul(string marca, float pret, int nrComponente, float* greutatiComponente, TipCombustibil tipCombustibil) :id(++nrVehicule) {
		this->marca = marca;
		this->pret = pret;
		this->nrComponente = nrComponente;
		this->greutati = new float[this->nrComponente];
		for (int i = 0; i < this->nrComponente; i++) {
			this->greutati[i] = greutatiComponente[i];
		}
		this->tipCombustibil = tipCombustibil;

		delete[] greutatiComponente;
	}

	Vehicul(const Vehicul& copie) :id(++nrVehicule) {
		this->pret = copie.pret;
		this->marca = copie.marca;
		this->tipCombustibil = copie.tipCombustibil;
		this->nrComponente = copie.nrComponente;

		if (copie.greutati != nullptr) {
			this->greutati = new float[copie.nrComponente];
			for (int i = 0; i < copie.nrComponente; i++) {
				this->greutati[i] = copie.greutati[i];
			}
		}
		else {
			this->greutati = nullptr;
		}
	}

	void operator=(const Vehicul& copie) {
		this->marca = copie.marca;
		this->pret = copie.pret;
		this->tipCombustibil = copie.tipCombustibil;
		this->nrComponente = copie.nrComponente;

		if (this->greutati != nullptr) {
			delete[] this->greutati;
			this->greutati = nullptr;
		}

		if (copie.greutati != nullptr) {
			this->greutati = new float[copie.nrComponente];
			for (int i = 0; i < copie.nrComponente; i++) {
				this->greutati[i] = copie.greutati[i];
			}
		}
		else {
			this->greutati = nullptr;
		}

	}

	void afisareVehicul() {
		cout << endl << this->id << ". Vehiculul " << this->marca << " costa " << this->pret << " lei, foloseste combustibil de tip ";
		if (this->tipCombustibil == BENZINA) cout << "BENZINA";
		if (this->tipCombustibil == ELECTRIC) cout << "ELECTRIC";
		if (this->tipCombustibil == DIESEL) cout << "DIESEL";
		cout << " si contine " << this->nrComponente << " componente cu greutati: ";
		if (this->greutati != nullptr) {
			for (int i = 0; i < this->nrComponente - 1; i++) {
				cout << this->greutati[i] << " kg, ";
			}
			cout << this->greutati[this->nrComponente - 1] << " kg.";
		}
	}

	//get si set pentru nrComponente
	int getNrComponente() {
		return this->nrComponente;
	}

	void setNrComponente(int nrComponenteNou) {
		if (nrComponenteNou > 0)
		{
			this->nrComponente = nrComponenteNou;
		}
		else {
			//throw exception();
			//throw 404;
			throw "Valoare negativa";
		}
	}

	//get si set pentru pointeri
	float* getGreutati() {
		//return this->greutati; - asa nu
		float* copieGreutati = new float[this->nrComponente];
		for (int i = 0; i < this->nrComponente; i++) {
			copieGreutati[i] = this->greutati[i];
		}

		return copieGreutati;
	}

	void setGreutati(float* greutatiNoi, int nrComponenteNou) {
		setNrComponente(nrComponenteNou);

		if (this->greutati != nullptr) {
			delete[] this->greutati;
		}
		this->greutati = new float[this->nrComponente];
		for (int i = 0; i < this->nrComponente; i++) {
			this->greutati[i] = greutatiNoi[i];
		}

		delete[] greutatiNoi;
	}

	~Vehicul() {
		if (this->greutati != nullptr) {
			delete[] this->greutati;
		}
	}

	void operator+=(float pretDeAdunat) {
		this->pret += pretDeAdunat;
	}

	bool operator>(const Vehicul& v) {
		return this->pret > v.pret;
	}

	//operatorul negatie
	bool operator!() {
		return this->pret > 0;
	}

	//operatorul functie
	float operator()(float valoareDeAdaugat)
	{
		return this->pret + valoareDeAdaugat;
	}

	//operatorul index
	float& operator[](int index) {
		if (index >= 0 && index < this->nrComponente) {
			return this->greutati[index];
		}
		else{
			throw exception();
		}
	}

	//operator <<  operator de afisare
	friend void operator<<(ostream& out, Vehicul veh) {
		out << endl << "Operator de afisare: ";
		out << endl << "Id: " << veh.id;
		out << endl << "Marca: " << veh.marca;
		out << endl << "Pret: " << veh.pret;
		out << endl << "Tip combustibil: ";
		if (veh.tipCombustibil == BENZINA) out << "BENZINA";
		if (veh.tipCombustibil == ELECTRIC) out << "ELECTRIC";
		if (veh.tipCombustibil == DIESEL) out << "DIESEL";
		out << endl << "Nr componente: " << veh.nrComponente;
		if (veh.greutati != nullptr) {
			out << endl << "Greutati: ";
			for (int i = 0; i < veh.nrComponente - 1; i++) {
				out << veh.greutati[i] << " kg, ";
			}
			out << veh.greutati[veh.nrComponente - 1] << " kg.";
		}			
	}

	friend void operator>>(istream& in, Vehicul& veh);

	//postincrementare
	Vehicul operator++(int) {
		Vehicul copie = *this;
		this->pret++;

		return copie;
	}

	//preincrementare
	Vehicul operator++() {
		this->pret++;
		return *this;
	}
	
	//cast explicit
	explicit operator int() {
		return this->nrComponente;
	}
};

int Vehicul::nrVehicule = 0;

void operator>>(istream& in, Vehicul& veh) { 
	cout << endl << "Pret: ";
	in >> veh.pret;

	cout << endl << "Marca: ";
	in >> veh.marca;

	cout << endl << "Tip combustibil: ";
	int tip;
	in >> tip;

	if (tip == 8) veh.tipCombustibil = BENZINA;
	if (tip == 10) veh.tipCombustibil = ELECTRIC;
	if (tip == 6) veh.tipCombustibil = DIESEL;

	cout << endl << "Nr componente: ";
	in >> veh.nrComponente;

	cout << endl << "Greutati: ";

	if (veh.greutati != nullptr) {
		delete[] veh.greutati;
		veh.greutati = nullptr;
	}

	veh.greutati = new float[veh.nrComponente];
	for (int i = 0; i < veh.nrComponente; i++) {
		cout << endl << "greutati[" << i << "]: ";
		in >> veh.greutati[i];
	}
}

void main() {
	Vehicul masina;
	masina.afisareVehicul();

	float* greutati = new float[3] {250, 150, 300};
	Vehicul* tesla = new Vehicul("Tesla Model S", 50000, 3, greutati, ELECTRIC);
	tesla->afisareVehicul();

	if (!masina) {
		cout << endl << "Pretul este mai mare decat 0!";
	}
	else {
		cout << endl << "Pretul este mai mic sau egal cu 0!";
	}

	cout << endl << masina(5000);

	(*tesla)[0] = 260;

	cout << endl << (*tesla)[0];

	cout << *tesla;

	//cin >> masina;
	//cout << masina;
	//masina are pretul 0;
	Vehicul v1 = masina++;
	//masina are pretul 1;
	Vehicul v2 = ++masina;
	//masina are pretul 2;
	//v1 are pretul 0;
	//v2 are pretul 2;

	cout << v1;
	cout << v2;

	cout << (int)(*tesla);

	delete tesla;
}
