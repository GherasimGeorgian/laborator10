#include "activitate.h"
#include <string>

using std::to_string;

string Activitate::get_titlu() const
{
	return titlu;
}

int Activitate::get_durata() const
{
	return durata;
}

string Activitate::get_tip() const
{
	return tip;
}

string Activitate::get_descriere() const
{
	return descriere;
}

void Activitate::set_titlu(string s)
{
	titlu = s;
}

void Activitate::set_durata(int s)
{
	durata = s;
}

void Activitate::set_tip(string s)
{
	tip = s;
}

void Activitate::set_descriere(string s)
{
	descriere = s;
}

string Activitate::get_str()
{
	string s = "";
	s += "Titlu : " + titlu + "; ";
	string durata_s = std::to_string(durata);
	s += "Durata: " + durata_s + "; ";
	s += "Tip: " + tip + "; ";
	s += "Descriere : " + descriere + " ";

	return s;
}

string Activitate::get_str_CVS()
{
	return titlu + "," + std::to_string(durata) + "," + tip + "," + descriere + "\n";
}

bool operator==(const Activitate& a, const Activitate& b)
{
	return(a.titlu == b.titlu);
}

void Afisator::set_str(string s)
{
	output += s;
}

string Afisator::get_str()
{
	return output;
}

void DTO::increment()
{
	cnt++;
}

void DTO::set_cnt(int x)
{
	cnt = x;
}

void DTO::set_procent(int all)
{
	procent = (cnt * 1.0 / all) * 100;
}

string DTO::get_str()
{
	string output = categorie + " " + to_string(procent) + "%\n";
	return output;
}
