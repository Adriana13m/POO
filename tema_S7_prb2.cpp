#include<iostream>
#include<string>

using namespace std;
enum Gen { FICTIUNE = 4, STIINTA = 9, ISTORIE = 6 };

class Carte {
private:
	const int id;
	float pret;
	string titlu;
	Gen gen;
	int nrCapitole;
	int* pagini;
	static int nrCarti;
public:
	//constructor fara parametri
	Carte() :id(++nrCarti) {
		this->titlu = "Carte default";
		this->pret = 0;
		this->nrCapitole = 0;
		this->pagini = nullptr;
		this->gen = FICTIUNE;
	}

	Carte(string titlu, float pret, int nrCapitole, int* paginiCapitole, Gen gen) :id(++nrCarti) {
		this->titlu = titlu;
		this->pret = pret;
		this->nrCapitole = nrCapitole;
		this->pagini = new int[this->nrCapitole];
		for (int i = 0; i < this->nrCapitole; i++) {
			this->pagini[i] = paginiCapitole[i];
		}
		this->gen = gen;

		delete[] paginiCapitole;
	}

	Carte(const Carte& copie) :id(++nrCarti) {
		this->pret = copie.pret;
		this->titlu = copie.titlu;
		this->gen = copie.gen;
		this->nrCapitole = copie.nrCapitole;

		if (copie.pagini != nullptr) {
			this->pagini = new int[copie.nrCapitole];
			for (int i = 0; i < copie.nrCapitole; i++) {
				this->pagini[i] = copie.pagini[i];
			}
		}
		else {
			this->pagini = nullptr;
		}
	}

	void operator=(const Carte& copie) {
		this->titlu = copie.titlu;
		this->pret = copie.pret;
		this->gen = copie.gen;
		this->nrCapitole = copie.nrCapitole;

		if (this->pagini != nullptr) {
			delete[] this->pagini;
			this->pagini = nullptr;
		}

		if (copie.pagini != nullptr) {
			this->pagini = new int[copie.nrCapitole];
			for (int i = 0; i < copie.nrCapitole; i++) {
				this->pagini[i] = copie.pagini[i];
			}
		}
		else {
			this->pagini = nullptr;
		}
		
	}

	void afisareCarte() {
		cout << endl << this->id << ". Cartea \"" << this->titlu << "\" costa " << this->pret << " lei, apartine genului ";
		if (this->gen == FICTIUNE) cout << "FICTIUNE";
		if (this->gen == STIINTA) cout << "STIINTA";
		if (this->gen == ISTORIE) cout << "ISTORIE";
		cout << " si contine " << this->nrCapitole << " capitole cu paginile: ";
		if (this->pagini != nullptr) {
			for (int i = 0; i < this->nrCapitole - 1; i++) {
				cout << this->pagini[i] << " pagini, ";
			}
			cout << this->pagini[this->nrCapitole - 1] << " pagini.";
		}
	}

	//get si set pentru nrCapitole
	int getNrCapitole() {
		return this->nrCapitole;
	}

	void setNrCapitole(int nrCapitoleNou) {
		if (nrCapitoleNou > 0)
		{
			this->nrCapitole = nrCapitoleNou;
		}
		else {
			//throw exception();
			//throw 404;
			throw "Valoare negativa";
		}
	}

	//get si set pentru pointeri
	int* getPagini() {
		//return this->pagini; - asa nu
		int* copiePagini = new int[this->nrCapitole];
		for (int i = 0; i < this->nrCapitole; i++) {
			copiePagini[i] = this->pagini[i];
		}

		return copiePagini;
	}

	void setPagini(int* paginiNoi, int nrCapitoleNou) {
		setNrCapitole(nrCapitoleNou);

		if (this->pagini != nullptr) {
			delete[] this->pagini;
		}
		this->pagini = new int[this->nrCapitole];
		for (int i = 0; i < this->nrCapitole; i++) {
			this->pagini[i] = paginiNoi[i];
		}

		delete[] paginiNoi;
	}

	~Carte() {
		if (this->pagini != nullptr) {
			delete[] this->pagini;
		}
	}

	void operator+=(float pretDeAdunat) {
		this->pret += pretDeAdunat;
	}

	bool operator>(const Carte& c) {
		return this->pret > c.pret;
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
	int& operator[](int index) {
		if (index >= 0 && index < this->nrCapitole) {
			return this->pagini[index];
		}
		else{
			throw exception();
		}
	}

	//operator << / operator de afisare
	friend void operator<<(ostream& out, Carte carte) {
		out << endl << "Operator de afisare: ";
		out << endl << "Id: " << carte.id;
		out << endl << "Titlu: " << carte.titlu;
		out << endl << "Pret: " << carte.pret;
		out << endl << "Gen: ";
		if (carte.gen == FICTIUNE) out << "FICTIUNE";
		if (carte.gen == STIINTA) out << "STIINTA";
		if (carte.gen == ISTORIE) out << "ISTORIE";
		out << endl << "Nr capitole: " << carte.nrCapitole;
		if (carte.pagini != nullptr) {
			out << endl << "Pagini per capitol: ";
			for (int i = 0; i < carte.nrCapitole - 1; i++) {
				out << carte.pagini[i] << " pagini, ";
			}
			out << carte.pagini[carte.nrCapitole - 1] << " pagini.";
		}			
	}

	friend void operator>>(istream& in, Carte& carte);

	//postincrementare
	Carte operator++(int) {
		Carte copie = *this;
		this->pret++;

		return copie;
	}

	//preincrementare
	Carte operator++() {
		this->pret++;
		return *this;
	}
	
	//cast explicit
	explicit operator int() {
		return this->nrCapitole;
	}
};

int Carte::nrCarti = 0;

void operator>>(istream& in, Carte& carte) { 
	cout << endl << "Pret: ";
	in >> carte.pret;

	cout << endl << "Titlu: ";
	in.ignore();
	getline(in, carte.titlu);

	cout << endl << "Gen: ";
	int gen;
	in >> gen;

	if (gen == 4) carte.gen = FICTIUNE;
	if (gen == 9) carte.gen = STIINTA;
	if (gen == 6) carte.gen = ISTORIE;

	cout << endl << "Nr capitole: ";
	in >> carte.nrCapitole;

	cout << endl << "Pagini per capitol: ";

	if (carte.pagini != nullptr) {
		delete[] carte.pagini;
		carte.pagini = nullptr;
	}

	carte.pagini = new int[carte.nrCapitole];
	for (int i = 0; i < carte.nrCapitole; i++) {
		cout << endl << "pagini[" << i << "]: ";
		in >> carte.pagini[i];
	}
}

void main() {
	Carte carteVida;
	carteVida.afisareCarte();

	int* pagini = new int[5] {25, 30, 42, 18, 35};
	Carte* sapiens = new Carte("Sapiens: Scurta istorie a omenirii", 45, 5, pagini, ISTORIE);
	sapiens->afisareCarte();

	if (!carteVida) {
		cout << endl << "Pretul este mai mare decat 0!";
	}
	else {
		cout << endl << "Pretul este mai mic sau egal cu 0!";
	}

	cout << endl << carteVida(15.5);

	(*sapiens)[0] = 28;

	cout << endl << (*sapiens)[0];

	cout << *sapiens;

	//cin >> carteVida;
	//cout << carteVida;
	//carteVida are pretul 0;
	Carte c1 = carteVida++;
	//carteVida are pretul 1;
	Carte c2 = ++carteVida;
	//carteVida are pretul 2;
	//c1 are pretul 0;
	//c2 are pretul 2;

	cout << c1;
	cout << c2;

	cout << (int)(*sapiens);

	delete sapiens;
}
