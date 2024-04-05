#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class COccurence
{
	private:
		char m_cCaractere;
		int m_nFrequence;

	public:
		COccurence();
		COccurence(char m_cCaractere,int m_nFrequence);
		COccurence(const COccurence&);
		~COccurence();

		char Get_caractere();

		friend ostream& operator<< (ostream&, const COccurence&);
		friend ofstream& operator<< (ofstream&, const COccurence&);

		void Incrementer();
};		

