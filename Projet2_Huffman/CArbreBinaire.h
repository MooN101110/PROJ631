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
		
		
		bool est_feuille();
		

		void afficher_arbre();
		void afficher_arbre(int indent);
		void creer_arbre(CListeOccurence& lo);


		friend ostream& operator<< (ostream&, const CArbreBinaire&);
		
};


