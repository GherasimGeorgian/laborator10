#pragma once
#include <vector>
#include <string>
#include "activitate.h"
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <cstdlib>

using std::to_string;
using std::string;
using std::vector;
using std::string;
using std::unordered_map;
using std::transform;

class RepoException {
	string msg;
public:
	RepoException(string s) : msg{ s } {};
	string getMessage() {
		return msg;
	}
};
class CosException {
	string msg;
public:
	CosException(string s) : msg{ s } {};
	string getMessage() {
		return msg;
	}
};

class REPO {
protected:
	double err_perc;
public:
	virtual void store(const Activitate& d) = 0;
	virtual void stergere(const Activitate& d) = 0;
	virtual void modify(const Activitate& d1, const Activitate& d) = 0;
	virtual const vector<Activitate> getAll() = 0;
	virtual int cauta(const Activitate& d) = 0;
	virtual int dimen() = 0;
	virtual Activitate from_position(int x) = 0;

	virtual double getAll_err_perc();
};

class Repo : public REPO {
protected:
	//unordered_map<int, Activitate> activitatii;
	//int index;

	vector<Activitate> activitatii;
public:
	Repo() = default;
	Repo(double verr_perc);
	virtual void store(const Activitate& d);
	virtual void stergere(const Activitate& d);
	virtual int cauta(const Activitate& d);
	virtual void modify(const Activitate& d1, const Activitate& d);
	virtual const vector<Activitate> getAll();
	//const unordered_map<int, Activitate> getAll_map();
	virtual int dimen();
	virtual Activitate from_position(int x);
};

class FileRepo :public Repo {
private:
	string fName;
	void load_from_file();
	void write_to_file();
public:
	FileRepo(string fname, double err_perc) : Repo(err_perc), fName{ fname } {}
	~FileRepo() = default;
	void store(const Activitate& d) override;
	void stergere(const Activitate& d) override;
	int cauta(const Activitate& d) override;
	void modify(const Activitate& d1, const Activitate& d) override;
	const vector<Activitate> getAll() override;
	int dimen() override;
	Activitate from_position(int x) override;
	void clear_file();

};

class CosActivitatii {
private:
	vector<Activitate> cos_activitatii;
public:
	CosActivitatii() = default;
	CosActivitatii(const CosActivitatii& ot) = default;
	~CosActivitatii() = default;
	int goleste();
	int adauga(string d, REPO& r);
	int nr_activitatii();
	void sterge(string d);
	vector<Activitate> getAllCos() const;
	int cos_cauta(Activitate d);
	int generare(int numar, REPO& rep);
	int export_cos(string nume_fisier);
	string to_string();

};

