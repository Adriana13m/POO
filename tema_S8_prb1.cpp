#include<iostream>
#include<string>

using namespace std;

class ExceptieCustom : public exception
{
public:
	ExceptieCustom(const char* mesaj) :exception(mesaj){}
};

class Angajat {
private:
	const int id;
	string nume;
	float salariu;
public:
	static const float SALARIU_MINIM;
	Angajat() :id(0), nume("Angajat Necunoscut"), salariu(3000) {
	}

	Angajat(int idA, string numeA, float salariuA) :id(idA), nume(numeA), salariu(salariuA) {
		if (salariu < SALARIU_MINIM) {
			throw ExceptieCustom("Salariul este sub minimul legal!");
		}
	}

	virtual void afisare() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Nume: " << this->nume;
		cout << endl << "Salariu: " << this->salariu;
	}

	~Angajat() {
	}

	virtual float getBonus() = 0;

};

const float Angajat::SALARIU_MINIM = 2000;

class AngajatCuBonus : public Angajat{
private: 
	float procentBonus;
public:
	AngajatCuBonus() :Angajat(), procentBonus(15) {}

	AngajatCuBonus(int id, string nume, float salariu, float procentBonus) :Angajat(id, nume, salariu), procentBonus(procentBonus) {}

	void afisare() {
		this->Angajat::afisare();
		cout << endl << "Procent bonus: " << this->procentBonus << "%";
	}

	float getBonus() {
		return this->procentBonus;
	}
};

class CalculatorInterface {
public:
	virtual double calculeazaArie(double latime, double lungime) = 0;
	virtual double calculeazaPerimetru(double latime, double lungime) = 0;
	virtual double calculeazaDiagonala(double latime, double lungime) = 0;
	virtual double calculeazaVolum(double latime, double lungime, double inaltime) = 0;
};

class CalculatorGeometric : public CalculatorInterface{
public:
	double calculeazaArie(double latime, double lungime) {
		return latime * lungime;
	}

	double calculeazaPerimetru(double latime, double lungime) {
		return 2 * (latime + lungime);
	}

	double calculeazaDiagonala(double latime, double lungime) {
		return sqrt(latime * latime + lungime * lungime);

	}

	double calculeazaVolum(double latime, double lungime, double inaltime) {
		if (inaltime > 0) {
			return latime * lungime * inaltime;
		}
		else {
			throw ExceptieCustom("Inaltimea trebuie sa fie pozitiva!");
		}
	}
};

void main() {
	//try {
	//	Angajat muncitor(1, "Ion Popescu", 1500);
	//}
	//catch (ExceptieCustom e) {
	//	cout << endl << e.what();
	//}

	//Angajat manager(1, "Maria Ionescu", 5000);
	//manager.afisare();

	//AngajatCuBonus developer(2, "Andrei Radu", 8000, 20);
	//developer.afisare();

	Angajat* vectorAngajati[3];

	vectorAngajati[0] = new AngajatCuBonus(1, "Ana Popescu", 4000, 15);
	vectorAngajati[1] = new AngajatCuBonus(2, "Mihai Ionescu", 6000, 18);
	vectorAngajati[2] = new AngajatCuBonus(3, "Elena Dumitrescu", 5500, 12);

	for (int i = 0; i < 3; i++) {
		vectorAngajati[i]->afisare();
		delete vectorAngajati[i];
	}

	CalculatorInterface* calculator = new CalculatorGeometric();
	cout << endl << "Aria dreptunghiului: " << calculator->calculeazaArie(5, 10);
	cout << endl << "Perimetrul dreptunghiului: " << calculator->calculeazaPerimetru(5, 10);
	cout << endl << "Diagonala dreptunghiului: " << calculator->calculeazaDiagonala(5, 10);
	
	try {
		cout << endl << "Volumul paralelipipedului: " << calculator->calculeazaVolum(5, 10, 3);
	}
	catch (ExceptieCustom e) {
		cout << endl << e.what();
	}

	delete calculator;
}
