#include <iostream>
#include <string>

#pragma warning(disable:4996);

using namespace std;

class Plantatie {

private:
	const int id;
	char* adresa = nullptr;
	int nrPomi = 0;
	int* varsta = nullptr;
	static int VarstaMinimaRod;



public:

	Plantatie(int _id) : id(_id) {

	}

	Plantatie(int _id,const char* adresa, int nrPomi, int* varsta) :id(_id) {

		this->adresa = new char[strlen(adresa) + 1];
		strcpy(this->adresa, adresa);
		this->nrPomi = nrPomi;
		this->varsta= new int[this->nrPomi];
		for (int i = 0;i < this->nrPomi;i++) {
			this->varsta[i] = varsta[i];
		}

	}



	~Plantatie() {
		if (this->adresa != nullptr) {
			delete[] this->adresa;
			this->adresa = nullptr;
		}
		if (this->varsta != nullptr) {
			delete[] this->varsta;
			this->varsta = nullptr;
		}
	}




	int* getVarsta() {
			int* copie = new int[this->nrPomi];
			for (int i = 0;i < this->nrPomi;i++) {
				copie[i] = varsta[i];
			}
			return copie;
		}

		
	void setNrPomi(int nrPomiNou) {
		if (nrPomiNou > 0) {
			this->nrPomi = nrPomiNou;
		}
	}
	
	Plantatie setVarsta(int* varstaNou, int nrPomiNou) {
		setNrPomi(nrPomiNou);
		if (varstaNou != nullptr) {
			if (this->varsta != nullptr) {
				delete[]this->varsta;
			}
			this->varsta = new int[this->nrPomi];
			for (int i = 0;i < this->nrPomi;i++) {
				this->varsta[i] = varstaNou[i];
			}
		}
		else {
			this->varsta = nullptr;
		}
		delete[] varstaNou;
	}


	char* getAdresa() {
		char* copie = new char[strlen(this->adresa) + 1];
		strcpy(copie, this->adresa);
		return copie;
	}


	Plantatie setAdresa(char* AdresaNou) {
		if (AdresaNou != nullptr && strlen(AdresaNou)>2) {
			if (this->adresa != nullptr) {
				delete[] this->adresa;
			}
			this->adresa = new char[strlen(AdresaNou) + 1];
			strcpy(this->adresa, AdresaNou);
		}
		else {
			this->adresa = nullptr;
		}

		delete[] AdresaNou;
	}


	Plantatie(const Plantatie& p) :id(p.id){

		this->adresa = new char[strlen(p.adresa) + 1];
		strcpy(this->adresa, p.adresa);
		this->nrPomi = p.nrPomi;
		this->varsta = new int[p.nrPomi];
		for (int i = 0;i < this->nrPomi;i++) {
			this->varsta[i] = p.varsta[i];
		}

	}


	Plantatie operator=(const Plantatie& p) {
		if (this != &p) {
			if (this->adresa != nullptr) {
				delete[] this->adresa;
				this->adresa = nullptr;
			}
			this->adresa = new char[strlen(p.adresa) + 1];
			strcpy(this->adresa, p.adresa);
			this->nrPomi = p.nrPomi;
			if (this->varsta != nullptr) {
				delete[] this->varsta;
				this->varsta = nullptr;
			}
			this->varsta = new int[p.nrPomi];
			for (int i = 0;i < this->nrPomi;i++) {
				this->varsta[i] = p.varsta[i];
			}

		}
		return *this;

	}


	friend ostream& operator<<(ostream& out, const Plantatie& p);
	friend istream& operator>>(istream& in,  Plantatie& p);




	explicit operator int() {
		int nr=0;
		if (this->varsta != nullptr && nrPomi>0) {
			for (int i = 0;i < this->nrPomi;i++) {
				if (this->varsta[i] >= Plantatie::VarstaMinimaRod) {
					nr++;
				}
			}
		}

		return nr;
	}


	//Plantatie operator+(int + Plantatie) {
		
		
	
		friend Plantatie operator+(int pomiNoi, Plantatie p) {
			Plantatie temp = p;
			if (pomiNoi > 0) {
				int* vectorNou = new int[temp.nrPomi + pomiNoi];
				for (int i = 0; i < temp.nrPomi; i++) vectorNou[i] = temp.varsta[i];
				for (int i = temp.nrPomi; i < temp.nrPomi + pomiNoi; i++) vectorNou[i] = 0;
				if (temp.varsta != nullptr) delete[] temp.varsta;
				temp.varsta = vectorNou;
				temp.nrPomi += pomiNoi;
			}
			return temp;
		}


	
		//operator ==
		bool operator==(const Plantatie& p) {
			if (this->id != p.id) return false;
			if (this->nrPomi != p.nrPomi) return false;
			if (strcmp(this->adresa, p.adresa) != 0) return false;
			if (this->nrPomi > 0) {
				for (int i = 0; i < this->nrPomi; i++) {
					if (this->varsta[i] != p.varsta[i]) return false;
				}
			}
			return true;
		}

	
	

};
int Plantatie::VarstaMinimaRod = 2;


ostream& operator<<(ostream& out, const Plantatie& p) {
	out << "Id: " << p.id;
	if (p.adresa != nullptr) {
		out << "adresa " << p.adresa;
	}
	out << " nr pomi " << p.nrPomi;
	out << " varsta: ";
	if (p.varsta != nullptr && p.nrPomi > 0) {
		for (int i = 0;i < p.nrPomi;i++) {
			out<<endl << p.varsta[i]<<endl;
		}
	}

	return out;
}




istream& operator>>(istream& in, Plantatie& p) {

	if (p.adresa != nullptr) {
		delete[] p.adresa;
		p.adresa = nullptr;
	}
	cout << "Introduceti adresa: ";
	char buffer[30];
	in >> buffer;
	p.adresa = new char[strlen(buffer) + 1];
	strcpy(p.adresa, buffer);


	cout << "Intr nr pomi: ";
	in >> p.nrPomi;

	if (p.varsta != nullptr) {
		delete[] p.varsta;
		p.varsta = nullptr;
	}
	p.varsta = new int[p.nrPomi];
	for (int i = 0;i < p.nrPomi;i++) {
		cout << endl << "varsta[" << i << "]: ";
		in >> p.varsta[i];
	}


	return in;
}

void main() {

	//apel cosntr cu un param
	Plantatie p1(2);

	//apel cu toti param
	int v[3] = { 4,3,2 };
	Plantatie p2(1, "Bals", 3, v);
	cout << p2;

	//apel operator cast
	int nrPomiFructiferi = (int)p2;
	cout <<"Nr pomi fructiferi(operator cast):" << nrPomiFructiferi;

	//apel operator==
	if (p1 == p2) {
		cout << endl<<"Obiectele sunt egale(operaor ==). "<<endl;
	}
	else {
		cout <<endl<< "Obiectele nu sunt egale(op ==). " << endl;
	}


	//op+
	p2 = 2 + p2;
	cout << endl << "op +"<<endl << p2;



}
