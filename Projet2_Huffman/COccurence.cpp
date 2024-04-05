#include "COccurence.h"

COccurence::COccurence()
	:m_cCaractere(NULL), m_nFrequence(0)
{
}

COccurence::COccurence(char cCaractere, int nFrequence)
	:m_cCaractere(cCaractere), m_nFrequence(nFrequence)
{
}

COccurence::COccurence(const COccurence& copie)
	:m_cCaractere(copie.m_cCaractere), m_nFrequence(copie.m_nFrequence)
{
}

COccurence::~COccurence()
{
}

char COccurence::Get_caractere()
{
	return m_cCaractere;
}

void COccurence::Incrementer()
{
	++m_nFrequence;
}

ostream& operator<<(ostream& os, const COccurence& occurence)
{
	os << occurence.m_cCaractere << " : " << occurence.m_nFrequence << endl;
	return os;
}

ofstream& operator<<(ofstream& of, const COccurence& occurence)
{
	of << occurence.m_cCaractere << " " << occurence.m_nFrequence << endl;
	return of;
}

