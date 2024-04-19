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

char CArbreBinaire::get_nom()
{
	return m_cNom;
}

CArbreBinaire CArbreBinaire::get_fils_gauche()
{
	return *this->m_AbrGauche;
}

CArbreBinaire CArbreBinaire::get_fils_droit()
{
	return *this->m_AbrDroit;
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

bool CArbreBinaire::trouve_un_caractere(char c)
{
	if (this->est_feuille() && this->get_nom() == c) {
		//cout << "car trouv� \n";
		return true;
	}
	else {
		if (this->m_AbrGauche != NULL && this->get_fils_gauche().trouve_un_caractere(c)) {
			//cout << "0-";
			return true;
		}
		if (this->m_AbrDroit != NULL && this->get_fils_droit().trouve_un_caractere(c)) {
			//cout << "1-";
			return true;
		}
	}
	return false;
}

const char* CArbreBinaire::codage_un_caractere(char c, char* code, int i)
{
	if (this->est_feuille() && this->get_nom() == c) {
		return code;
	}
	else {
		if (this->m_AbrGauche != NULL && this->get_fils_gauche().trouve_un_caractere(c)) {
			code[i] = '0';
			this->get_fils_gauche().codage_un_caractere(c, code, i+1);
	
		}
		if (this->m_AbrDroit != NULL && this->get_fils_droit().trouve_un_caractere(c)) {
			code[i] = '1';
			this->get_fils_droit().codage_un_caractere(c, code, i+1);

		}
	}
	return code;
}

const char* CArbreBinaire::codage_un_caractere(char c)
{
	char* code = new char[24];

	this->codage_un_caractere(c, code, 0);
	
	//Mise en forme correct du tableau
	int i = 0;
	while (code[i] == '1' || code[i] == '0') {
		++i;
	}

	char* code_compresse = new char[i+1];

	for (int j=0; j < i; j++) {
		code_compresse[j] = code[j];
	}
	code_compresse[i] = '\0';

	delete[] code;

	return code_compresse;
}



ostream& operator<<(ostream& os, const CArbreBinaire& a)
{
	os << a.m_cNom << " (" << a.m_nFrequence << ")" << endl;
	return os;
}




