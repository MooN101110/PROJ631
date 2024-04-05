#include <iostream>
#include <fstream>
#include "CListeOccurence.h"
#include <string>

using namespace std;

int main()
{
	string filename;
	filename = "test1";

	ofstream fichier("data/"+filename +".txt");
	fichier << "Bonjour   !";

	fichier.close();

	CListeOccurence lo;

	ifstream is("data/"+filename+".txt");
	string buffer; 
	while (getline(is, buffer)) {
		const char* str = buffer.data();
		cout << buffer << endl;
		for (int i = 0; i < strlen(str); i++) {
			lo.Ajouter(buffer[i]);
		}
	}
	is.close();
	cout << lo<<endl;
	lo.Trier();
	cout << lo;

	//Enregistrement de la fréquence dans un fichier
	ofstream fichier_freq("data/"+filename+"_freq.txt");
	fichier_freq << lo;


}