#include "repo.h"


Repo::Repo(double verr_perc)
{
	err_perc = verr_perc;
	activitatii = {};
}

void Repo::store(const Activitate& d)
{

	for (const Activitate& dc : activitatii) {
		if (dc == d) {
			throw RepoException("Activitate deja introdusa\n");
		}
	}
	activitatii.push_back(d);
	/*
	for (auto it = activitatii.begin(); it != activitatii.end(); it++) {
		auto act = it->second;
		if(act == d)
			throw RepoException("Activitate deja introdusa\n");
	}
	activitatii.insert({ index++, d });*/
}

void Repo::stergere(const Activitate& d)
{

	int i = 0;
	for (const Activitate& dc : activitatii) {
		if (d == dc) {
			activitatii.erase(activitatii.begin() + i);
			return;
		}
		i++;
	}
	throw RepoException("Activitate inexistenta\n");
	/*for (auto it = activitatii.begin(); it != activitatii.end(); it++) {
		auto dc = it->second;
		if (d == dc) {
			activitatii.erase(it);
			return;
		}
	}
	throw RepoException("Activitate inexistenta\n");*/

}

int Repo::cauta(const Activitate& d)
{

	int i = 0;
	for (const Activitate& dc : activitatii) {
		if (d == dc) {
			return i;
		}
		i++;
	}
	throw RepoException("Activitate inexistenta\n");

	/*int i = 0;
	for (auto it = activitatii.begin(); it != activitatii.end(); it++) {
		auto dc = it->second;
		if (d == dc) {
			return i;
		}
		i++;
	}
	throw RepoException("Activitate inexistenta\n");*/
}

void Repo::modify(const Activitate& d1, const Activitate& d)
{
	int idx = this->cauta(d1);
	activitatii[idx] = d;
}


const vector<Activitate> Repo::getAll()
{
	/*vector <std::pair<int, Activitate>> v;
	transform(activitatii.begin(), activitatii.end(), std::back_inserter(v), [](const std::pair<int, Activitate>& p) { return p; });
	vector <Activitate> out;
	for (auto x : v) {
		out.push_back(x.second);
	}*/

	return activitatii;
}

//const unordered_map<int, Activitate> Repo::getAll_map()
//{
//	return activitatii;
//}

int Repo::dimen()
{
	return activitatii.size();
}

Activitate Repo::from_position(int x)
{
	return activitatii[x];
}

int CosActivitatii::goleste()
{
	cos_activitatii.clear();
	return 0;
}

int CosActivitatii::adauga(string d, REPO& r)
{
	auto& activitatii = r.getAll();
	vector<Activitate> out(activitatii.size());
	auto it = copy_if(activitatii.begin(), activitatii.end(), out.begin(), [&](Activitate disc) {return (disc.get_titlu() == d); });
	out.resize(distance(out.begin(), it));
	if (out.size() == 0)
		throw CosException("Activitate inexistenta!\n");
	cos_activitatii.push_back(out[0]);
	return cos_activitatii.size();
}

int CosActivitatii::nr_activitatii()
{
	return cos_activitatii.size();
}

void CosActivitatii::sterge(string d)
{
	int i = 0;
	for (auto& elem : cos_activitatii) {
		if (elem.get_titlu() == d) {
			cos_activitatii.erase(cos_activitatii.begin() + i);
		}
		i++;
	}
}

int CosActivitatii::cos_cauta(Activitate d)
{
	for (auto& dis : cos_activitatii)
		if (dis == d)
			return 1;
	return 0;
}

int CosActivitatii::generare(int numar, REPO& rep)
{
	this->goleste();
	if (numar > rep.dimen())
		throw CosException("Numarul de activitatii e mai mare decat numarul de numarul de activitatii disponibile!\n");
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> dist(0, rep.dimen() - 1);
	int i = 0;
	while (numar--) {
		int rndNr = dist(mt);
		Activitate d = rep.from_position(rndNr);
		while (this->cos_cauta(d) == 1) {
			rndNr = dist(mt);
			Activitate d = rep.from_position(rndNr);
			i++;
			if (i > 50)
				break;
		}
		cos_activitatii.push_back(d);
	}
	return cos_activitatii.size();
}

int CosActivitatii::export_cos(string nume_fisier)
{
	std::ofstream file(nume_fisier);

	file << this->to_string();

	file.close();
	return cos_activitatii.size();
}


string CosActivitatii::to_string()
{
	Afisator out;
	for (auto& dis : cos_activitatii) {
		out.set_str(dis.get_str_CVS());
	}
	return out.get_str();
}

vector<string> parse(string s) {
	vector <string> out;
	string current = "";
	for (auto i = 0; i < s.size(); i++) {
		if (s[i] == ',') {
			out.push_back(current);
			current = "";
		}
		else {
			current += s[i];
		}
	}
	out.push_back(current);
	return out;
}

void FileRepo::load_from_file()
{

	activitatii.clear();
	std::ifstream in(fName);
	if (!in.is_open())
		throw RepoException("Nu am reusit sa deschid fisierul:" + fName);
	while (!in.eof()) {
		string s;
		in >> s;
		if (s.size() == 0)
			break;
		vector <string> vect = parse(s);
		if (vect.size() != 4)
			break;
		Activitate d{ vect[0], stoi(vect[1]), vect[2], vect[3] };
		activitatii.push_back(d);
	}
	in.close();
}


void FileRepo::write_to_file()
{

	std::ofstream out(fName);
	if (!out.is_open())
		throw RepoException("Nu am reusit sa deschid fisierul:" + fName);
	for (auto d : activitatii) {
		out << d.get_str_CVS();
	}
}

void FileRepo::store(const Activitate& d)
{
	load_from_file();
	Repo::store(d);
	write_to_file();
}

void FileRepo::stergere(const Activitate& d)
{
	load_from_file();
	Repo::stergere(d);
	write_to_file();
}

int FileRepo::cauta(const Activitate& d)
{
	load_from_file();
	return Repo::cauta(d);
}

void FileRepo::modify(const Activitate& d1, const Activitate& d)
{
	load_from_file();
	Repo::modify(d1, d);
	write_to_file();
}

const vector<Activitate> FileRepo::getAll()
{
	load_from_file();
	return Repo::getAll();
}
vector<Activitate> CosActivitatii::getAllCos()const {
	return cos_activitatii;
}

int FileRepo::dimen()
{
	load_from_file();
	return Repo::dimen();
}

Activitate FileRepo::from_position(int x)
{
	load_from_file();
	return Repo::from_position(x);
}

void FileRepo::clear_file()
{
	activitatii.clear();
	write_to_file();
}

double REPO::getAll_err_perc()
{
	return err_perc;
}
