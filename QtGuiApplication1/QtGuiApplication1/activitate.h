#pragma once
#include <string>

using std::string;

class Activitate {

private:

	string titlu, tip, descriere;
	int durata;

public:

	string get_titlu() const;
	int get_durata() const;
	string get_tip() const;
	string get_descriere() const;

	void set_titlu(string s);
	void set_durata(int s);
	void set_tip(string s);
	void set_descriere(string s);

	string get_str();
	string get_str_CVS();

	Activitate() = default;
	Activitate(string titlu, int durata, string tip, string descriere) : titlu{ titlu }, durata{ durata }, tip{ tip }, descriere{ descriere }{};
	Activitate(const Activitate& ot) = default;

	friend bool operator== (const Activitate& a, const Activitate& b);
};

class Afisator {
private:
	string output;
public:
	Afisator() = default;
	~Afisator() = default;
	Afisator(const Afisator& ot) = default;
	void set_str(string s);
	string get_str();
};

class DTO {
private:
	string categorie;
	int cnt;
	double procent;
public:
	DTO() = default;
	DTO(string key) : categorie{ key }, cnt{ 1 }, procent{ 0 }{};
	void increment();
	void set_cnt(int x);
	void set_procent(int all);
	string get_str();
};