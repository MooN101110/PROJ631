#include "CListeOccurence.h"

CListeOccurence::CListeOccurence()
	:m_pListe(NULL), m_nTaille(0)
{
}

CListeOccurence::CListeOccurence(COccurence* pl,int nTaille)
	:m_pListe(pl), m_nTaille(nTaille)
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

void CListeOccurence::Ajouter_noeud(char c,int frequence)
{
	COccurence noeud(c, frequence);
	COccurence* new_tab = new COccurence[m_nTaille-1];
	for (int i = 2; i < m_nTaille; i++) {
		new_tab[i-2] = m_pListe[i];
	}
	new_tab[m_nTaille-2] = noeud;
	--m_nTaille;
	delete[] m_pListe;
	m_pListe = new_tab;

	//Trie du tableau
	this->Trier();
}

void CListeOccurence::Trier()
{
	COccurence* tab_trie = new COccurence[m_nTaille];
	CListeOccurence liste_trie(tab_trie,m_nTaille);

	for (int i = 0; i < m_nTaille; i++) {
		COccurence min_elt;
		for (int j = 0; j < m_nTaille; j++) {
			if (!liste_trie.Dedans(m_pListe[j])) {
				if (((m_pListe[j].Get_frequence() < min_elt.Get_frequence())
					||(((m_pListe[j].Get_frequence() == min_elt.Get_frequence()))
					&& ((int)m_pListe[j].Get_caractere() < (int)min_elt.Get_caractere())))
					|| min_elt.Get_frequence() == 0) {
						min_elt = m_pListe[j];
				}
			}
		}

		tab_trie[i] = min_elt;
	}
	if (this != &liste_trie) {
		for (int i = 0; i < m_nTaille; i++) {
			m_pListe[i] = liste_trie.m_pListe[i];
		}
	}
}

bool CListeOccurence::Dedans(COccurence c)
{
	bool res = false;
	for (int i = 0; i < m_nTaille; i++) {
		if (m_pListe[i].Get_caractere() == c.Get_caractere()) {
			res = true;
		}
	}
	return res;
}

int CListeOccurence::Get_size()
{
	return m_nTaille;
}


COccurence* CListeOccurence::get_2_min()
{
	COccurence* listeMin = new COccurence[2];
	listeMin[0] = m_pListe[0];
	listeMin[1] = m_pListe[1];
	return listeMin;
}


ostream& operator<<(ostream& os, const CListeOccurence& l)
{
	for (int i = 0; i < l.m_nTaille; i++) {
		os << l.m_pListe[i];
	}
	return os;
}

ofstream& operator<<(ofstream& fs, const CListeOccurence& l)
{
	for (int i = 0; i < l.m_nTaille; i++) {
		fs << l.m_pListe[i];
	}
	return fs;
}
