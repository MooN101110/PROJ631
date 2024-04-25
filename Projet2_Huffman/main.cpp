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
	cout << "\x1b[38;5;9mEntrez le nom du fichier que vous souhaitez compresser : \033[0m" << endl;
	cin >> filename;

	CListeOccurence lo;

	ifstream is("data/"+filename+".txt");
	if (!is) {
		cerr << "\n\n\x1b[41mERREUR - Fichier introuvable\033[0m" << endl;
	}
	else {
		string buffer;
		cout << "\n\033[38;5;10m\033[1mApercu du fichier :\033[0m" << endl;
		while (getline(is, buffer)) {
			const char* str = buffer.data();
			cout << buffer << endl;
			for (int i = 0; i < strlen(str); i++) {
				lo.Ajouter(buffer[i]);
			}
		}
		is.close();
		cout << endl << "\n\033[38;5;10m\033[1mFrequence des characteres :\033[0m" << endl;
		cout << lo << endl;
		lo.Trier();
		cout << "\n\033[38;5;10m\033[1mFrequence triee des characteres :\033[0m" << endl;
		cout << lo << endl;

		//Enregistrement de la fréquence dans un fichier
		ofstream fichier_freq("data/" + filename + "_freq.txt");
		fichier_freq << lo;

		//Création de l'arbre
		cout << "\n\033[38;5;10m\033[1mArbre Binaire :\033[0m" << endl;
		CArbreBinaire arbre;
		arbre.creer_arbre(lo);

		//Enregistrement dans fichier binaire
		arbre.ecrire_binaire(filename);


		//Vérification de la compression
		double taille_origine = taille_fichier("data/" + filename + ".txt");
		double taille_compresse = taille_fichier("data/" + filename + "_comp.bin");
		double taille_frequence = taille_fichier("data/" + filename + "_freq.txt");

		cout << endl << "\x1b[38;5;85mTaille du fichier d'origine : \033[0m" << taille_origine << " \x1b[38;5;85moctets\033[0m" << endl;
		cout << "\x1b[38;5;85mTaille du fichier compresse: \033[0m" << taille_compresse << "\x1b[38;5;85m octets\033[0m" << endl;

		//Taux de compression
		double taux_comp = 1 - ((taille_compresse + taille_frequence) / taille_origine);
		cout << endl << "\x1b[38;5;72mTaux de compression : \033[0m" << taux_comp * 100 << " \x1b[38;5;72m%\033[0m" << endl;

		//Nombre moyen de bits par caractère
		double nb_moyen_bits = arbre.nb_moyen_bits(filename);
		cout << "\x1b[38;5;36mNombre moyen de bits par caractère : \033[0m" << nb_moyen_bits << " \x1b[38;5;36mbits\033[0m" << endl;
	}


	cout << "\n\n\x1b[38;5;9mAppuyez sur une touche pour quitter\033[0m" << endl;
	cin.ignore();
	cin.ignore();
}