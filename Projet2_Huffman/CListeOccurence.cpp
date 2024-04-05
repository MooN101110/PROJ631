#include "CListeOccurence.h"

CListeOccurence::CListeOccurence()
	:m_pListe(NULL), m_nTaille(0)
{
}

CListeOccurence::CListeOccurence(COccurence* pl)
	:m_pListe(pl), m_nTaille(0)
{
}

CListeOccurence::CListeOccurence(const CListeOccurence& l)
	:m_pListe(l.m_pListe), m_nTaille(l.m_nTaille)
{
}

CListeOccurence::~CListeOccurence()
{
	if (m_pListe != NULL) {
		delete[] m_pListe;
	}
}

void CListeOccurence::Ajouter(char c)
{
	bool occ_ok = false;
	for (int i = 0; i < m_nTaille; i++) {
		if (m_pListe[i].Get_caractere() == c) {
			m_pListe[i].Incrementer();
			occ_ok = true;
		}
	}
	if (!occ_ok) {
		COccurence o(c, 1);
		COccurence* new_tab = new COccurence[m_nTaille + 1];
		for (int i = 0; i < m_nTaille; i++) {
			new_tab[i] = m_pListe[i];
		}
		new_tab[m_nTaille] = o;
		++m_nTaille;
		delete[] m_pListe;
		m_pListe = new_tab;
	}
}

ostream& operator<<(ostream& os, const CListeOccurence& l)
{
	for (int i = 0; i < l.m_nTaille; i++) {
		os << l.m_pListe[i] << endl;
	}
	return os;
}

ofstream& operator<<(ofstream& fs, const CListeOccurence& l)
{
	for (int i = 0; i < l.m_nTaille; i++) {
		fs << l.m_pListe[i] << endl;
	}
	return fs;
}
