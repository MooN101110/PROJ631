#include "CArbreBinaire.h"
#include <iostream>


CArbreBinaire::CArbreBinaire()
	:m_cNom(NULL),m_nFrequence(0),m_AbrDroit(NULL),m_AbrGauche(NULL)
{
}

CArbreBinaire::CArbreBinaire(char cNom, int nFrequence)
	:m_cNom(cNom),m_nFrequence(nFrequence), m_AbrDroit(NULL), m_AbrGauche(NULL)
{
}

CArbreBinaire::CArbreBinaire(char cNom, int nFrequence, CArbreBinaire& AG, CArbreBinaire& AD)
	:m_cNom(cNom), m_nFrequence(nFrequence), m_AbrDroit(&AD), m_AbrGauche(&AG)
{
}

CArbreBinaire::CArbreBinaire(const CArbreBinaire& copie)
	:m_cNom(copie.m_cNom),m_nFrequence(copie.m_nFrequence),m_AbrDroit(copie.m_AbrDroit), m_AbrGauche(copie.m_AbrGauche)
{
}

CArbreBinaire::~CArbreBinaire()
{
}


void CArbreBinaire::set_fils(CArbreBinaire& AG, CArbreBinaire& AD)
{
	this->m_AbrDroit = &AD;
	this->m_AbrGauche = &AG;
}

void CArbreBinaire::set_fils_gauche(CArbreBinaire& AG)
{
	this->m_AbrGauche = &AG;
}

void CArbreBinaire::set_fils_droit(CArbreBinaire& AD)
{
	this->m_AbrDroit = &AD;
}

void CArbreBinaire::set_Nom(char c)
{
	this->m_cNom = c;
}

void CArbreBinaire::set_Freq(int f)
{
	this->m_nFrequence = f;
}

int CArbreBinaire::Get_freq()
{
	return m_nFrequence;
}

bool CArbreBinaire::est_feuille()
{
	return this->m_AbrDroit == NULL && this->m_AbrGauche == NULL;
}

void CArbreBinaire::afficher_arbre()
{
	this->afficher_arbre(0);
}

void CArbreBinaire::afficher_arbre(int indent)
{
	for (int i = 0; i < indent; i++) {
		cout << "  ";
	}
	cout << *this;

	if (this->est_feuille()) {
		return;
	}
	else {
		if (this->m_AbrGauche != NULL) {
			this->m_AbrGauche->afficher_arbre(indent + 1);
		}
		if (this->m_AbrDroit != NULL) {
			this->m_AbrDroit->afficher_arbre(indent + 1);
		}
	}
}

void CArbreBinaire::creer_arbre(CListeOccurence& lo)
{
	CArbreBinaire* listeArbre= new CArbreBinaire[lo.Get_size()];
	this->creer_arbre(lo,listeArbre, 0);
}

void CArbreBinaire::creer_arbre(CListeOccurence& lo, CArbreBinaire* listeArbre, int i)
{
	while (lo.Get_size() > 1) {
		COccurence* listeMin = new COccurence[2];
		listeMin = lo.get_2_min();
		int frequence = listeMin[0].Get_frequence() + listeMin[1].Get_frequence();
		char car = listeMin[0].Get_caractere() + listeMin[1].Get_caractere();

		//Cr�ation arbre 
		CArbreBinaire *gauche = new CArbreBinaire(listeMin[0].Get_caractere(), listeMin[0].Get_frequence());
		CArbreBinaire *droit = new CArbreBinaire(listeMin[1].Get_caractere(), listeMin[1].Get_frequence());

		this->set_Freq(frequence);
		this->set_Nom(NULL);
		this->set_fils(*gauche, *droit);

		//this->afficher_arbre();

		for (int a = 0; a < i; a++) {
			if (gauche->Get_freq() == listeArbre[a].Get_freq()) {
				this->set_fils_gauche(listeArbre[a]);
			}
			else if (droit->Get_freq() == listeArbre[a].Get_freq()) {
				this->set_fils_droit(listeArbre[a]);
			}
		}

		listeArbre[i] = *this;

		//Mise � jour de la liste
		lo.Ajouter_noeud(car, frequence);

		++i;

	}
	//Lier les arbres
	this->afficher_arbre();
}


ostream& operator<<(ostream& os, const CArbreBinaire& a)
{
	os << a.m_cNom << " (" << a.m_nFrequence << ")" << endl;
	return os;
}




