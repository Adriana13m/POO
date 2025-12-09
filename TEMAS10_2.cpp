#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Hotel {
private:
	string nume = "Necunoscut";
	char* adresa = nullptr;
	int nrCamere = 0;
	bool areRestaurant = true;
public:
	Hotel() {}

	Hotel(string nume, const char* adresa, 
		int nrCamere, bool areRestaurant) {
		this->areRestaurant = areRestaurant;
		this->nrCamere = nrCamere;
		this->nume = nume;
		this->adresa = new char[strlen(adresa) + 1];
		strcpy_s(this->adresa, strlen(adresa) + 1, adresa);
	}

	~Hotel() {
		if (this->adresa != nullptr) {
			delete[] this->adresa;
		}
	}

	Hotel(const Hotel& copie) {
		this->areRestaurant = copie.areRestaurant;
		this->nume = copie.nume;
		this->nrCamere = copie.nrCamere;
		if (copie.adresa != nullptr) {
			this->adresa = new char[strlen(copie.adresa) + 1];
			memcpy(this->adresa, copie.adresa, strlen(copie.adresa) + 1);
		}
		else {
			this->adresa = nullptr;
		}
	}

	friend void operator<<(ostream& out, Hotel h) {
		out << endl << "Nr camere: " << h.nrCamere;
		out << endl << "Nume: " << h.nume;
		out << endl << (h.areRestaurant ? "Are restaurant" : "Nu are restaurant");
		out << endl << (h.adresa != nullptr ? "Adresa: " + string(h.adresa) : "Adresa default");
	}

	friend void operator<<(fstream& outFile, Hotel h) {
		outFile << h.nrCamere << endl;
		outFile << h.nume << endl;
		outFile << h.areRestaurant << endl;
		outFile << h.adresa << endl;
	}

	friend void operator>>(ifstream& inFile, Hotel& h) {
		inFile >> h.nrCamere;
		inFile >> h.nume;
		inFile >> h.areRestaurant;
		if (h.adresa != nullptr) {
			delete[] h.adresa;
			h.adresa = nullptr;
		}
		char buffer[100];
		inFile >> buffer;
		h.adresa = new char[strlen(buffer) + 1];
		strcpy_s(h.adresa, strlen(buffer) + 1, buffer);
	}
};

void main() {
	Hotel hilton("Hilton", "BulevarduliuManiu", 250, true);
	
	fstream fileStream("Hotel.txt", ios::out);
	fileStream << hilton;
	fileStream.close();

	Hotel hiltonCopie;
	cout << hiltonCopie;

	ifstream inputFileStream("Hotel.txt", ios::in);
	inputFileStream >> hiltonCopie;
	inputFileStream.close();

	cout << hiltonCopie;
	
}
