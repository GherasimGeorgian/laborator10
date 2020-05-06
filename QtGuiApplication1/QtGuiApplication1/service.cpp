#pragma once
#include "service.h"
#include <map>
#include <algorithm>

using std::copy_if;
using std::distance;
using std::map;
using std::unordered_map;
using std::find;
using std::count_if;

void Service::adauga(string titlu, int durata, string tip, string descriere)
{
	double probabilitate = (rand() % 100) * 1.0 / 100;
	if (probabilitate < repo.getAll_err_perc())
		throw RepoException("Repo a picat!");
	Activitate d{ titlu, durata, tip, descriere };
	validator.valideaza(d);
	repo.store(d);
	undoActions.push_back(std::make_unique<UndoAdauga>(repo, d));
}



void Service::stergere(string titlu, int durata, string tip, string descriere)
{
	double probabilitate = (rand() % 100) * 1.0 / 100;
	if (probabilitate < repo.getAll_err_perc())
		throw RepoException("Repo a picat!");
	Activitate d{ titlu, durata, tip, descriere };
	validator.valideaza(d);

	repo.stergere(d);
	undoActions.push_back(std::make_unique<UndoStergere>(repo, d));
}

void Service::modificare(string titlu, int durata, string tip, string descriere)
{
	double probabilitate = (rand() % 100) * 1.0 / 100;
	if (probabilitate < repo.getAll_err_perc())
		throw RepoException("Repo a picat!");

	
	Activitate act1{ titlu, durata, tip, descriere };
	validator.valideaza(act1);
	Activitate d2{ "", -1, "", "" };
	for (auto activitate : repo.getAll())
		if (activitate.get_titlu() == act1.get_titlu())
		{
			d2.set_titlu(titlu);
			d2.set_durata(durata);
			d2.set_tip(tip);
			d2.set_descriere(descriere);
			validator.valideaza(d2);
			repo.modify(act1, d2);
			undoActions.push_back(std::make_unique<UndoMod>(repo, d2, act1));
		}


}

int Service::cautare(string titlu, int durata, string tip, string descriere)
{
	Activitate d{ titlu, durata, tip, descriere };
	validator.valideaza(d);
	return repo.cauta(d);
}

int Service::dimen_repo()
{
	return repo.dimen();
}

string Service::filtrare_durata(const int durata)
{
	auto& discipline = repo.getAll();
	int ind = 1;
	Afisator output;
	vector<Activitate> out(discipline.size());
	auto it = copy_if(discipline.begin(), discipline.end(), out.begin(), [&](Activitate d) {return (d.get_durata() == durata); });
	out.resize(distance(out.begin(), it));
	for (auto& disciplina : out) {
		output.set_str(std::to_string(ind) + ". " + disciplina.get_str() + "\n");
		ind++;
	}
	return output.get_str();
}

string Service::filtrare_descriere(string descriere)
{
	auto& discipline = repo.getAll();
	int ind = 1;
	Afisator output;
	vector<Activitate> out(discipline.size());
	auto it = copy_if(discipline.begin(), discipline.end(), out.begin(), [&](Activitate d) {return (d.get_descriere() == descriere); });
	out.resize(distance(out.begin(), it));
	for (auto& disciplina : out) {
		output.set_str(std::to_string(ind) + ". " + disciplina.get_str() + "\n");
		ind++;
	}
	return output.get_str();
}

string Service::sortare_titlu()
{
	auto discipline = repo.getAll();
	sort(discipline.begin(), discipline.end(), [](const Activitate& a, const Activitate& b) {
		return a.get_titlu() < b.get_titlu();
		});
	int ind = 1;
	Afisator output;
	for (auto disciplina : discipline) {
		output.set_str(std::to_string(ind) + ". " + disciplina.get_str() + "\n");
		ind++;
	}
	return output.get_str();
}

string Service::sortare_durata()
{
	auto discipline = repo.getAll();
	sort(discipline.begin(), discipline.end(), [](const Activitate& a, const Activitate& b) {
		return a.get_durata() < b.get_durata();
		});
	int ind = 1;
	Afisator output;
	for (auto disciplina : discipline) {
		output.set_str(std::to_string(ind) + ". " + disciplina.get_str() + "\n");
		ind++;
	}
	return output.get_str();
}

string Service::sortare_descriere_tip()
{
	auto discipline = repo.getAll();
	sort(discipline.begin(), discipline.end(), [](const Activitate& a, const Activitate& b) {
		if (a.get_descriere() == b.get_descriere())
			return a.get_tip() < b.get_tip();
		return a.get_descriere() < b.get_descriere();
		});
	int ind = 1;
	Afisator output;
	for (auto disciplina : discipline) {
		output.set_str(std::to_string(ind) + ". " + disciplina.get_str() + "\n");
		ind++;
	}
	return output.get_str();
}


vector<Activitate> Service::afisare()
{
	auto activitati = repo.getAll();
	return activitati;
}
vector<Activitate> Service::afisare_cos()
{
	auto cos_act = cos.getAllCos();
	return cos_act;
}

string Service::adauga_cos(string titlu)
{
	cos.adauga(titlu, repo);
	undoActions.push_back(std::make_unique<UndoAddCos>(cos, titlu));
	return "Adaugare cu succes";
}

void Service::golire_cos()
{
	cos.goleste();
}

void Service::generare_cos(int nr)
{
	cos.generare(nr, repo);
}

void Service::export_cos(string nf)
{
	nf += ".txt";
	cos.export_cos(nf);
}

vector<DTO> Service::statistica()
{
	auto activitati = repo.getAll();


	int numar_activitati = repo.dimen();


	map<string, DTO> statistica;

	for (auto activitate : activitati) {
		if (statistica.find(activitate.get_titlu()) == statistica.end()) {
			DTO nou{ activitate.get_titlu() };
			statistica.insert({ activitate.get_titlu(), nou });
		}
		else {
			DTO aux = statistica[activitate.get_titlu()];
			aux.increment();
			statistica[activitate.get_titlu()] = aux;
		}

	}


	map<string, DTO>::iterator it = statistica.begin();

	vector <DTO> output;

	while (it != statistica.end()) {
		it->second.set_procent(numar_activitati);
		output.push_back(it->second);
		it++;
	}

	return output;
}

void Service::undo()
{
	if (undoActions.empty()) {
		throw RepoException("Nu mai exista operatii");
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}
