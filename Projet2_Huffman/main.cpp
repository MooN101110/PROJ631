#include <iostream>
#include <fstream>
#include "CListeOccurence.h"
#include <string>

using namespace std;

int main()
{
	const char* filename;
	filename = "data/test.txt";

	ofstream fichier(filename);
	fichier << "marche s'il te plaît";

	fichier.close();

	CListeOccurence lo;

	ifstream is(filename);
	string buffer; 
	while (getline(is, buffer)) {
		const char* str = buffer.data();
		cout << buffer << endl;
		for (int i = 0; i < strlen(str); i++) {
			lo.Ajouter(buffer[i]);
		}
	}
	cout << lo;

}