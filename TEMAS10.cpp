#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Universitate {
private:
	string denumire = "Necunoscut";
	char* oras = nullptr;
	int nrStudenti = 0;
	bool estePublica = true;
public:
	Universitate() {}

	Universitate(string denumire, const char* oras, 
		int nrStudenti, bool estePublica) {
		this->estePublica = estePublica;
		this->nrStudenti = nrStudenti;
		this->denumire = denumire;
		this->oras = new char[strlen(oras) + 1];
		strcpy_s(this->oras, strlen(oras) + 1, oras);
	}

	~Universitate() {
		if (this->oras != nullptr) {
			delete[] this->oras;
		}
	}

	Universitate(const Universitate& copie) {
		this->estePublica = copie.estePublica;
		this->denumire = copie.denumire;
		this->nrStudenti = copie.nrStudenti;
		if (copie.oras != nullptr) {
			this->oras = new char[strlen(copie.oras) + 1];
			memcpy(this->oras, copie.oras, strlen(copie.oras) + 1);
		}
		else {
			this->oras = nullptr;
		}
	}

	friend void operator<<(ostream& out, Universitate u) {
		out << endl << "Nr studenti: " << u.nrStudenti;
		out << endl << "Denumire: " << u.denumire;
		out << endl << (u.estePublica ? "Este publica" : "Este privata");
		out << endl << (u.oras != nullptr ? "Oras: " + string(u.oras) : "Oras default");
	}

	friend void operator<<(fstream& outFile, Universitate u) {
		outFile << u.nrStudenti << endl;
		outFile << u.denumire << endl;
		outFile << u.estePublica << endl;
		outFile << u.oras << endl;
	}

	friend void operator>>(ifstream& inFile, Universitate& u) {
		inFile >> u.nrStudenti;
		inFile >> u.denumire;
		inFile >> u.estePublica;
		if (u.oras != nullptr) {
			delete[] u.oras;
			u.oras = nullptr;
		}
		char buffer[50];
		inFile >> buffer;
		u.oras = new char[strlen(buffer) + 1];
		strcpy_s(u.oras, strlen(buffer) + 1, buffer);
	}
};

void main() {
	Universitate politehnica("Politehnica", "Bucuresti", 12000, true);
	
	fstream fileStream("Universitate.txt", ios::out);
	fileStream << politehnica;
	fileStream.close();

	Universitate politehnicaCopie;
	cout << politehnicaCopie;

	ifstream inputFileStream("Universitate.txt", ios::in);
	inputFileStream >> politehnicaCopie;
	inputFileStream.close();

	cout << politehnicaCopie;
	
}
