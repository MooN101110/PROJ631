#pragma once
#include "COccurence.h"
#include <iostream>
#include <fstream>
using namespace std;

class CListeOccurence
{
private:
	COccurence* m_pListe;
	int m_nTaille;

public:
	CListeOccurence();
	CListeOccurence(COccurence* occ,int );
	CListeOccurence(const CListeOccurence& l);
	~CListeOccurence();


	friend ostream& operator<< (ostream&, const CListeOccurence&);
	friend ofstream& operator<< (ofstream&, const CListeOccurence&);

	void Ajouter(char c);
	void Ajouter_noeud(char c,int frequence);
	void Trier();
	bool Dedans(COccurence c);

	int Get_size();

	COccurence* get_2_min();

	
};

