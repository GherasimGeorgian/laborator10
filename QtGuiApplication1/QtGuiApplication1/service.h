#pragma once
#include "repo.h"
#include "valid.h"
#include "activitate.h"
#include "undo.h"
#include <string>
#include <vector>
#include <algorithm>
using std::sort;
using std::vector;
using std::unique_ptr;
using std::string;

class Service {
private:
	REPO& repo;
	Validator& validator;
	CosActivitatii& cos;
	vector<unique_ptr<ActiuneUndo>> undoActions;
public:
	Service(REPO& r, Validator& v, CosActivitatii& c) : repo{ r }, validator{ v }, cos{ c }{};
	~Service() = default;
	void adauga(string titlu, int durata, string tip, string descriere);
	void stergere(string titlu, int durata, string tip, string descriere);
	void modificare(string titlu, int durata, string tip, string descriere);
	int cautare(string titlu, int durata, string tip, string descriere);
	int dimen_repo();


	string filtrare_durata(const int durata);
	string filtrare_descriere(string descriere);
	string sortare_titlu();
	string sortare_durata();
	string sortare_descriere_tip();
	string adauga_cos(string titlu);

	vector<Activitate> afisare();
	vector<Activitate> afisare_cos();

	void golire_cos();
	void generare_cos(int nr);
	void export_cos(string nf);
	vector<DTO> statistica();
	void undo();
};