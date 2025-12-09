#include<iostream>
#include<string>

using namespace std;

class ExceptieCustom : public exception
{
public:
	ExceptieCustom(const char* mesaj) :exception(mesaj){}
};

class Curs {
private:
	const int id;
	string titlu;
	int durata;
public:
	static const int DURATA_MINIMA;
	Curs() :id(0), titlu("Introducere in Programare"), durata(40) {
	}

	Curs(int idC, string titluC, int durataC) :id(idC), titlu(titluC), durata(durataC) {
		if (durata < DURATA_MINIMA) {
			throw ExceptieCustom("Durata cursului este prea mica!");
		}
	}

	virtual void afisare() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Titlu: " << this->titlu;
		cout << endl << "Durata: " << this->durata << " ore";
	}

	~Curs() {
	}

	virtual float getTarifOra() = 0;

};

const int Curs::DURATA_MINIMA = 10;

class CursOnline : public Curs{
private: 
	float tarifOra;
public:
	CursOnline() :Curs(), tarifOra(50) {}

	CursOnline(int id, string titlu, int durata, float tarifOra) :Curs(id, titlu, durata), tarifOra(tarifOra) {}

	void afisare() {
		this->Curs::afisare();
		cout << endl << "Tarif pe ora: " << this->tarifOra << " lei";
	}

	float getTarifOra() {
		return this->tarifOra;
	}
};

class StatisticsInterface {
public:
	virtual float calculeazaMedia(int a, int b, int c) = 0;
	virtual int calculeazaSuma(int a, int b, int c) = 0;
	virtual int calculeazaMaxim(int a, int b, int c) = 0;
	virtual int calculeazaMinim(int a, int b, int c) = 0;
};

class StatisticsOperation : public StatisticsInterface{
public:
	float calculeazaMedia(int a, int b, int c) {
		return (a + b + c) / 3.0;
	}

	int calculeazaSuma(int a, int b, int c) {
		return a + b + c;
	}

	int calculeazaMaxim(int a, int b, int c) {
		int max = a;
		if (b > max) max = b;
		if (c > max) max = c;
		return max;

	}

	int calculeazaMinim(int a, int b, int c) {
		if (a >= 0 && b >= 0 && c >= 0) {
			int min = a;
			if (b < min) min = b;
			if (c < min) min = c;
			return min;
		}
		else {
			throw ExceptieCustom("Valorile trebuie sa fie pozitive!");
		}
	}
};

void main() {
	//try {
	//	Curs workshop(1, "Workshop C++", 5);
	//}
	//catch (ExceptieCustom e) {
	//	cout << endl << e.what();
	//}

	//Curs masterclass(1, "Masterclass OOP", 60);
	//masterclass.afisare();

	//CursOnline pythonCurs(2, "Python pentru Incepatori", 50, 45);
	//pythonCurs.afisare();

	Curs* vectorCursuri[3];

	vectorCursuri[0] = new CursOnline(1, "Java Fundamentals", 80, 60);
	vectorCursuri[1] = new CursOnline(2, "Web Development", 120, 55);
	vectorCursuri[2] = new CursOnline(3, "Data Science", 100, 70);

	for (int i = 0; i < 3; i++) {
		vectorCursuri[i]->afisare();
		delete vectorCursuri[i];
	}

	StatisticsInterface* operation = new StatisticsOperation();
	cout << endl << endl << "Media notelor (8, 9, 7): " << operation->calculeazaMedia(8, 9, 7);
	cout << endl << "Suma notelor: " << operation->calculeazaSuma(8, 9, 7);
	cout << endl << "Nota maxima: " << operation->calculeazaMaxim(8, 9, 7);
	
	try {
		cout << endl << "Nota minima: " << operation->calculeazaMinim(8, 9, 7);
	}
	catch (ExceptieCustom e) {
		cout << endl << e.what();
	}

	delete operation;
}
