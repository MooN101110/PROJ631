#pragma once
#include <string>
#include "CListeOccurence.h"

using namespace std;

class CArbreBinaire
{
	private:
		char m_cNom;
		int m_nFrequence;
		CArbreBinaire *m_AbrGauche;
		CArbreBinaire *m_AbrDroit;


	public:
		CArbreBinaire();
		CArbreBinaire(char cNom, int nFrequence);
		CArbreBinaire(char cNom, int nFrequence, CArbreBinaire& AG, CArbreBinaire& AD);
		CArbreBinaire(const CArbreBinaire& copie);
		~CArbreBinaire();

		void set_fils(CArbreBinaire& AG, CArbreBinaire& AD);
		void set_fils_gauche(CArbreBinaire& AG);
		void set_fils_droit(CArbreBinaire& AD);
		void set_Nom(char c);
		void set_Freq(int f);
		int Get_freq();
		char get_nom();
		CArbreBinaire get_fils_gauche();
		CArbreBinaire get_fils_droit();
		
		
		bool est_feuille();
		

		void afficher_arbre();
		void afficher_arbre(int indent);
		void creer_arbre(CListeOccurence& lo);
		void creer_arbre2(CListeOccurence& lo, CArbreBinaire* listeArbre, int i);

		bool trouve_un_caractere(char c);
		const char* codage_un_caractere(char c);
		const char* codage_un_caractere(char c, char* code, int i);

		void encodage_binaire(string filename, string buffer);
		void ecrire_binaire(string filename);

		double nb_moyen_bits(string filename);

		friend ostream& operator<< (ostream&, const CArbreBinaire&);
		
};


