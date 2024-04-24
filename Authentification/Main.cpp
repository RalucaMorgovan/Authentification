#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//Ne cream User-ul
class User {

	string nume;
	string parola;
	string raspuns1;
	string raspuns2;
	string raspuns3;
	int numarincercari = 0;

	//constructorul
public:
	User(string n, string p, string r1, string r2, string r3)
	{
		this->nume = n;
		this->parola = p;
		this->raspuns1 = r1;
		this->raspuns2 = r2;
		this->raspuns3 = r3;
	}
	//scriem in fisier
	void ScriereFisier(ofstream& outFile) {
		outFile << nume << " " << parola << " " << raspuns1 << " " << raspuns2 << " " << raspuns3 << "\n";
		cout << endl;
	}


	string getNume()
	{
		return nume;
	}

	string getParola()
	{
		return parola;
	}

};

void CreareUser()
{
	bool gasit = false;
	string nume;
	string parola;
	string r1;
	string r2;
	string r3;
	//verificam numele
	ifstream database("database.txt");
	string existanume;
	string existaparola;
	string nouaparola;
	int numarincercari = 4;
	int i = 0;
	int opt;
	do {
		cout << "0. Iesire din meniu" << endl;
		cout << "1. Autentuficare" << endl;
		cout << "2. Creeaza-ti cont" << endl;
		cout << "3. Reseteaza-ti parola" << endl;
		cout << "Ce doriti sa faceti?" << endl;
		cin >> opt;
		switch (opt)
		{
		case 0: exit(0);
		case 1:
			do {
				cout << "Introduceti numele de utilizator: ";
				cin >> nume;
				cout << "Introduceti parola: ";
				cin >> parola;
				ifstream database("database.txt");

				while (database >> existanume && database >> existaparola) {
					if (nume == existanume && parola == existaparola)
					{
						cout << "V-ati logat cu succes!\n";
						gasit = true;
						break;
					}
				}
				if (!gasit)
				{
					cout << "Eroare! Reintroduceti numele sau parola!\n";
					database.clear();
					database.seekg(0, ios::beg);
					i++;
				}
			} while (!gasit && i < numarincercari);
			if (i >= numarincercari)
			{
				cout << "Ati depasit numarul de incercari! Va rugam sa revenit mai tarziu!";
			}
			break;
		case 2:
		{
			do {

				cout << "Introduceti numele de utilizator: ";
				cin >> nume;

				while (database >> existanume) {
					if (nume == existanume)
					{
						cout << "Deja exista un utilizator cu acest nume! Introduceti alt nume: ";
						database.clear();
						database.seekg(0, ios::beg);
						break;
					}
				}
				i++;
			} while (nume == existanume && i < numarincercari);
			database.close();
			if (i >= numarincercari)
			{
				cout << "Ati depasit numarul de incercari! Va rugam sa revenit mai tarziu!";
				return;
			}
			cout << "Introduceti parola: ";
			cin >> parola;
			cout << "Culoarea preferata este:  ";
			cin >> r1;
			cout << "Mancarea preferata este: ";
			cin >> r2;
			cout << "Sportul preferat este: ";
			cin >> r3;

			//scriere in fisier
			ofstream outFile("database.txt", ios::app);
			if (outFile.is_open())
			{
				User newUser(nume, parola, r1, r2, r3);
				newUser.ScriereFisier(outFile);
				cout << "Contul a fost creat cu succes!\n";
				cout << endl;
				outFile.close();
				break;
			}
			else {
				cout << "Eroare la salvare!\n";

			}
		}
		case 3:
			do {
				cout << "Introduceti numele de utilizator: ";
				cin >> nume;
				while (database >> existanume)
					if (nume == existanume)
					{
						cout << "Introduceti noua parola: ";
						cin >> nouaparola;
						ofstream outFile("database.txt");

						if (outFile.is_open())
						{
							while (database >> existanume >> existaparola >> r1 >> r2 >> r3)
							{
								if (nume == existanume)
									existaparola = nouaparola;
								outFile << existanume << " " << existaparola << " " << r1 << " " << r2 << " " << r3 << "\n";
							}
							outFile.close();
							cout << "Parola a fost resetata cu succes!\n";
							return;
						}
						else {
							cout << "Eroare la salvare!\n";

						}
					}
			} while (nume == existanume);
			database.close();

			break;
		default:
			cout << "Optiunea dumneavostra este gresita! \n";
			break;
		}
	} while (1);
}

int main()
{
	CreareUser();
	return 0;
}
