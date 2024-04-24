#include <iostream>
#include <fstream>
#include "CListeOccurence.h"
#include <string>
#include "CArbreBinaire.h"



using namespace std;

double taille_fichier(const string file) 
{
	ifstream fichier(file, ios::binary | ios::ate);
	return fichier.tellg();
}

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
	cout << endl << "Frequence des characteres :" << endl;
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
	
	//Enregistrement dans fichier binaire
	arbre.ecrire_binaire(filename);
	

	//Vérification de la compression
	double taille_origine = taille_fichier("data/" + filename + ".txt");
	double taille_compresse = taille_fichier("data/" + filename + "_comp.bin");
	double taille_frequence = taille_fichier("data/" + filename + "_freq.txt");

	cout << endl << "Taille du fichier d'origine : " << taille_origine << " octets" << endl;
	cout << "Taille du fichier compresse: " << taille_compresse << " octets" << endl;

	//Taux de compression
	double taux_comp = 1 - ((taille_compresse + taille_frequence) / taille_origine);
	cout << endl << "Taux de compression : " << taux_comp * 100 << " %" << endl;

	//Nombre moyen de bits par caractère
	double nb_moyen_bits = arbre.nb_moyen_bits(filename);
	cout << "Nombre moyen de bits par caractère : " << nb_moyen_bits << " bits" << endl;

}