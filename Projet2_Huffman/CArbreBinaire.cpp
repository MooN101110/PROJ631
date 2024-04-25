#include "CArbreBinaire.h"
#include <iostream>

using namespace std;


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

bool CArbreBinaire::est_dans_liste(int* liste, int n, int t)
{
	for (int i = 0; i < t; ++i) {
		if (n == liste[i]) {
			return true;
		}
	}
	return false;
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
	this->creer_arbre2(lo,listeArbre, 0);
}

void CArbreBinaire::creer_arbre2(CListeOccurence& lo, CArbreBinaire* listeArbre, int i)
{
	int* indice_place = new int[lo.Get_size()*2];
	int j = 0;

	while (lo.Get_size() > 1) {
		COccurence* listeMin = new COccurence[2];
		listeMin = lo.get_2_min();
		int frequence = listeMin[0].Get_frequence() + listeMin[1].Get_frequence();

		//Création arbre 
		CArbreBinaire *gauche = new CArbreBinaire(listeMin[0].Get_caractere(), listeMin[0].Get_frequence());
		CArbreBinaire *droit = new CArbreBinaire(listeMin[1].Get_caractere(), listeMin[1].Get_frequence());

		this->set_Freq(frequence);
		this->set_Nom(NULL);
		this->set_fils(*gauche, *droit);

		//this->afficher_arbre();

		bool ok_gauche = false;
		bool ok_droit = false;


		for (int a = 0; a < i; a++) {

			if (gauche->Get_freq() == listeArbre[a].Get_freq() && (gauche->get_nom()==NULL) && (est_dans_liste(indice_place, a, j) == false) && (ok_gauche == false)) {
				this->set_fils_gauche(listeArbre[a]);
				indice_place[j] = a;
				++j;
				ok_gauche = true;
			}
			else if (droit->Get_freq() == listeArbre[a].Get_freq() && (droit->get_nom() == NULL) && !(est_dans_liste(indice_place, a, j)) && (!ok_droit)) {
				this->set_fils_droit(listeArbre[a]);
				indice_place[j] = a;
				++j;
				ok_droit = true;
			}
		}
		listeArbre[i] = *this;
		++i;


		//Mise à jour de la liste
		lo.Ajouter_noeud(NULL, frequence);

	}
	this->afficher_arbre();
}


bool CArbreBinaire::trouve_un_caractere(char c)
{
	if (this->est_feuille() && this->get_nom() == c) {
		//cout << "car trouvé \n";
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

const char* CArbreBinaire::codage_un_caractere(char c)
{
	char* code = new char[24];

	this->codage_un_caractere(c, code, 0);

	//Mise en forme correct du tableau
	int i = 0;
	while (code[i] == '1' || code[i] == '0') {
		++i;
	}

	char* code_compresse = new char[i + 1];

	for (int j = 0; j < i; j++) {
		code_compresse[j] = code[j];
	}
	code_compresse[i] = '\0';

	delete[] code;

	return code_compresse;
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


void CArbreBinaire::encodage_binaire(string filename,string buffer)
{
	ofstream fichier("data/" + filename + "_comp.bin", ios::out | ios::binary);

	int taille_buffer = buffer.length();

	//travail octet par octet
	for (int i = 0; i < taille_buffer; i += 8) {
		string binaire8 = "";

		if (i < taille_buffer - 8) {
			binaire8 = buffer.substr(i, i + 8);
		}
		else {
			binaire8 = buffer.substr(i, taille_buffer);
		}
	

		//Utilisation des booléens pour écrire en binaire
		unsigned char octet = 0;

		for (int j = 0; j < 8; ++j) {
			bool resultat = true;
			if (j < binaire8.length()) {
				resultat = (binaire8[j] & 1);
				octet +=resultat;
			}
		}

		fichier.put(octet);
		taille_buffer = buffer.length();
	}
	fichier.close();

	cout << endl << "\n\x1b[38;5;104mFichier binaire cree avec succes\033[0m" << endl;
}

void CArbreBinaire::ecrire_binaire(string filename)
{
	ifstream fichier("data/" + filename + ".txt");
	string buffer;
	string line;

	if (!fichier) {
		cerr << "Erreur lors de l'ouverture du fichier" << endl;
	}
	else {
		while (getline(fichier, line)) {
			for (int i = 0; i < line.length(); i++) {
				buffer += this->codage_un_caractere(line[i]);
			}
		}
		fichier.close();
		encodage_binaire(filename, buffer);
	}

}

double CArbreBinaire::nb_moyen_bits(string filename)
{
	double nb_moyen = 0.0;
	int nb_char = 0;

	ifstream is("data/" + filename + "_freq.txt");
	string buffer;

	while (getline(is, buffer)) {
		const char* str = buffer.data();
		float pourcentage = stof(buffer.substr(1, strlen(str)));
		int nb_bits = strlen(codage_un_caractere(buffer[0]));
		nb_moyen += nb_bits * pourcentage;
		nb_char += pourcentage;
	}
	is.close();
	return nb_moyen/nb_char;
}


ostream& operator<<(ostream& os, const CArbreBinaire& a)
{
	os << a.m_cNom << " (" << a.m_nFrequence << ")" << endl;
	return os;
}




