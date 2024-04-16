#include <iostream>
#include <fstream>
#include "CListeOccurence.h"
#include <string>
#include "CArbreBinaire.h"

using namespace std;

int main()
{
	string filename;
	filename = "test";

	CListeOccurence lo;

	ifstream is("data/"+filename+".txt");
	string buffer; 
	cout << "Apercu du fichier :" << endl;
	while (getline(is, buffer)) {
		const char* str = buffer.data();
		cout << buffer << endl;
		for (int i = 0; i < strlen(str); i++) {
			lo.Ajouter(buffer[i]);
		}
	}
	is.close();
	cout << "Frequence des characteres :" << endl;
	cout << lo << endl;
	lo.Trier();
	cout << "Frequence triee des characteres :" << endl;
	cout << lo << endl;

	//Enregistrement de la fréquence dans un fichier
	ofstream fichier_freq("data/"+filename+"_freq.txt");
	fichier_freq << lo;
	
	//Création de l'arbre
	cout << "Arbre Binaire :" << endl;
	CArbreBinaire arbre;
	arbre.creer_arbre(lo);
	

	//CArbreBinaire filsD('a', 7);
	//CArbreBinaire filsD1('q', 3);
	//CArbreBinaire filsG('b', 4);
	//CArbreBinaire arbre('C', 1, filsG, filsD);
	//filsG.set_fils_droit(filsD1);
	//arbre.afficher_arbre();
}