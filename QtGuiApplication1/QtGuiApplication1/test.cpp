#include "test.h"
#include "activitate.h"
#include "valid.h"
#include "repo.h"
#include "service.h"
#include <cassert>

void teste_entitate() {

	Activitate act1{ "Nunta",  2000 ,"obligatoriu","descriere nunta"};
	Activitate act2("Absolvire",100, "optional", "descriere absolvire");

	assert(act1.get_titlu() == "Nunta");
	assert(act1.get_durata() == 2000);
	assert(act1.get_tip() == "obligatoriu");
	assert(act1.get_descriere() == "descriere nunta");
	assert(act1.get_str().size() > 0);

}

void teste_validare() {
	Activitate act1{ "Nunta",  2000 ,"obligatoriu","descriere nunta" };
	Activitate act_titlu( "",  2000 ,"obligatoriu","descriere nunta" );
	Activitate act_durata("Nunta", -1, "obligatoriu", "descriere nunta" );
	Activitate act_tip("Nunta", 2000, "", "descriere nunta");
	Activitate act_descriere("Nunta", 2000, "obligatoriu", "");
	Validator valid;
	valid.valideaza(act1);
	try {
		valid.valideaza(act_titlu);
		assert(false);
	}
	catch (ValidException& e) {
		assert(e.getMessage().size() > 0);
	}
	try {
		valid.valideaza(act_durata);
		assert(false);
	}
	catch (ValidException& e) {
		assert(e.getMessage().size() > 0);
	}
	try {
		valid.valideaza(act_tip);
		assert(false);
	}
	catch (ValidException& e) {
		assert(e.getMessage().size() > 0);
	}
	try {
		valid.valideaza(act_descriere);
		assert(false);
	}
	catch (ValidException& e) {
		assert(e.getMessage().size() > 0);
	}


}

void teste_repo_store() {
	Activitate act1{ "Nunta",  2000 ,"obligatoriu","descriere nunta" };
	Repo r;
	assert(r.dimen() == 0);
	r.store(act1);
	try {
		r.store(act1);
		assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMessage().size() > 0);
	}
	assert(r.dimen() == 1);

}

void teste_repo_modify() {
	Activitate act1{ "Nunta",  2000 ,"obligatoriu","descriere nunta" };
	Activitate act2("Absolvire", 100, "optional", "descriere absolvire");
	Repo r;
	r.store(act1);
	r.modify(act1, act2);
	try {
		r.modify(act1, act2);
		assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMessage().size() > 0);
	}
}

void teste_repo_delete() {
	Activitate act1{ "Nunta",  2000 ,"obligatoriu","descriere nunta" };
	Activitate act2("Absolvire", 100, "optional", "descriere absolvire");
	Repo r;
	r.store(act1);
	r.store(act2);
	r.stergere(act2);
	assert(r.dimen() == 1);
	try {
		r.stergere(act2);
		assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMessage().size() > 0);
	}
}

void teste_repo_cautare() {
	Activitate act1{ "Nunta",  2000 ,"obligatoriu","descriere nunta" };
	Activitate act2("Absolvire", 100, "optional", "descriere absolvire");
	Repo r;
	r.store(act1);
	assert(r.cauta(act1) == 0);
	try {
		int poz = r.cauta(act2);
		assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMessage().size() > 0);
	}
}

void teste_srv_adaugare() {
	Repo r;
	Validator v;
	CosActivitatii c;
	Service s{ r, v, c };
	
	s.adauga("Nunta", 2000, "obligatoriu", "descriere nunta");
	s.adauga("Absolvire", 100, "optional", "descriere absolvire");
	try {
		s.adauga("Nunta", 2000, "obligatoriu", "descriere nunta");
		assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMessage().size() > 0);
	}
}

void teste_srv_stergere() {
	Repo repo(0);
	Validator val;
	CosActivitatii cos;
	Service serv{ repo, val, cos };
	Activitate act1{ "Nunta",  2000 ,"obligatoriu","descriere nunta" };
	Activitate act2("Absolvire", 100, "optional", "descriere absolvire");

	serv.adauga("Nunta", 2000, "obligatoriu", "descriere nunta");
	serv.adauga("Absolvire", 100, "optional", "descriere absolvire");
	serv.stergere("Nunta", 2000, "obligatoriu", "descriere nunta");
	try {
		serv.stergere("Nunta", 2000, "obligatoriu", "descriere nunta");
		assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMessage().size() > 0);
	}
}

void teste_srv_modificare() {
	Repo r(0);
	Validator v;
	CosActivitatii c;
	Service s{ r, v, c };
	s.adauga("Nunta", 2000, "obligatoriu", "descriere nunta");
	s.modificare("Nunta", 1999, "obligatoriu", "descriere nunta");
	auto act = r.getAll();
	assert(act[0].get_titlu() == "Nunta");
	assert(act[0].get_durata() == 1999);

	try {
		s.modificare("", 2000, "obligatoriu", "descriere nunta");
		assert(false);
	}
	catch (ValidException& e) {
		assert(e.getMessage().size() > 0);
	}
}

void teste_srv_afisare() {
	Repo r(0);
	Validator v;
	CosActivitatii c;
	Service s{ r, v, c };
	s.adauga("Nunta", 2000, "obligatoriu", "descriere nunta");
	s.adauga("Absolvire", 100, "optional", "descriere absolvire");
	auto out = s.afisare();
	assert(out.size() == 2);
}

void teste_srv_cautare() {
	Repo r(0);
	Validator v;
	CosActivitatii c;
	Service s{ r, v, c };
	s.adauga("Nunta", 2000, "obligatoriu", "descriere nunta");
	s.cautare("Nunta", 2000, "obligatoriu", "descriere nunta");
	try {
		s.cautare("Nimic", 15, "obligatoriu", "descriere nunta");
		assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMessage().size() > 0);
	}
}

void teste_srv_filtrare_durata() {
	Repo r(0);
	Validator v;
	CosActivitatii c;
	Service s{ r, v, c };
	s.adauga("Nunta", 2000, "obligatoriu", "descriere nunta");
	s.adauga("Absolvire", 100, "optional", "descriere absolvire");
	string out = s.filtrare_durata(2000);
	assert(out.size() > 0);
}

void teste_srv_filtrare_descriere() {
	Repo r(0);
	Validator v;
	CosActivitatii c;
	Service s{ r, v, c };
	s.adauga("Nunta", 2000, "obligatoriu", "descriere nunta");
	s.adauga("Absolvire", 100, "optional", "descriere absolvire");
	string out = s.filtrare_descriere("descriere absolvire");
	assert(out.size() > 0);
}

void teste_srv_statistica() {
	Repo r(0);
	Validator v;
	CosActivitatii c;
	Service s{ r, v, c };
	s.adauga("Nunta", 2000, "obligatoriu", "descriere nunta");
	s.adauga("Absolvire", 100, "optional", "descriere absolvire");
	s.adauga("Nunta2", 2000, "obligatoriu", "descriere nunta");
	s.adauga("Absolvire2", 100, "optional", "descriere absolvire");

	auto test = s.statistica();
	assert(test.size() == 4);
	for (auto s : test) {
		string x = s.get_str();
		assert(x.size() > 0);
	}
}

void teste_cos() {
	CosActivitatii cos;
	Activitate act1{ "Nunta", 1500, "obligatoriu", "descriere nunta" };
	Activitate act2{ "Absolvire", 1200, "facultativ", "descriere absolvire" };
	Activitate act3{ "Practica", 1000, "facultativ", "descriere practica" };
	string titlu1 = "Nunta";
	string titlu2 = "Absolvire";
	string titlu3 = "Practica";
	Repo r(0);
	r.store(act2);
	r.store(act1);
	assert(cos.goleste() == 0);
	assert(cos.adauga(titlu1, r) == 1);
	assert(cos.adauga(titlu2, r) == 2);
	assert(cos.cos_cauta(act1) == 1);
	assert(cos.cos_cauta(act3) == 0);
	assert(cos.goleste() == 0);

	try {
		cos.generare(5, r);
		assert(false);
	}
	catch (CosException& e) {
		assert(e.getMessage().size() > 0);
	}
	cos.goleste();
	assert(cos.generare(2, r) == 2);

	string x = "haha";
	try {
		cos.adauga(x, r);
		assert(false);
	}
	catch (CosException& e) {
		assert(e.getMessage().size() > 0);
	}

	Activitate ac1{ "Nunta22", 15, "obligatoriu", "descriere nunta" };
	Activitate ac2{ "Absolvire22", 12, "facultativ", "am ctrecut" };
	Activitate ac3{ "Practica22", 10, "facultativ", "naspac" };
	Activitate ac4{ "Fotbal22", 10, "facultativ", "campionat european" };
	Activitate ac5{ "Sesiune22", 10, "facultativ", "nu cred ca vrei sa stii" };
	r.store(ac1);
	r.store(ac2);
	r.store(ac3);
	r.store(ac4);
	r.store(ac5);
	cos.generare(3, r);
	assert(cos.export_cos("teste.txt") == 3);
}

void test_store_f() {
	FileRepo r("fisier_test.txt", 0);
	r.clear_file();
	Activitate act{ "Nunta22", 15, "obligatoriu", "descriere nunta" };
	r.store(act);
	try
	{
	r.store(act);
		assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMessage().size() > 0);
	}
	assert(r.dimen() == 1);
}
void teste_repo_modify_f() {
	Activitate act1{ "Nunta", 1500, "obligatoriu", "descriere nunta" };
	Activitate act2{ "Absolvire", 1200, "facultativ", "descriere absolvire" };

	FileRepo r("fileteste.txt", 0);
	r.clear_file();
	r.store(act1);
	r.modify(act1, act2);
	try {
		r.modify(act1, act2);
		assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMessage().size() > 0);
	}
}

void teste_repo_delete_f() {
	Activitate act1{ "Nunta", 1500, "obligatoriu", "descriere nunta" };
	Activitate act2{ "Absolvire", 1200, "facultativ", "descriere absolvire" };

	FileRepo r("fileteste.txt", 0);
	r.clear_file();
	r.store(act1);
	r.store(act2);
	r.stergere(act2);
	assert(r.dimen() == 1);
	try {
		r.stergere(act2);
		assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMessage().size() > 0);
	}
}

void teste_repo_cautare_f() {
	Activitate act1{ "Nunta", 1500, "obligatoriu", "descriere nunta" };
	Activitate act2{ "Absolvire", 1200, "facultativ", "descriere absolvire" };

	FileRepo r("fileteste.txt", 0);
	r.clear_file();
	r.store(act1);
	assert(r.cauta(act1) == 0);
	try {
		int poz = r.cauta(act2);
		assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMessage().size() > 0);
	}
}

void teste_fisier() {
	test_store_f();
	teste_repo_cautare_f();
	teste_repo_delete_f();
	teste_repo_modify_f();

}

void teste_undo_add() {
	Repo r(0);
	CosActivitatii c;
	Validator v;
	Service s{ r, v, c };
	
	s.adauga("Nunta", 1500, "obligatoriu", "descriere nunta");
	s.adauga("Absolvire", 1200, "facultativ", "descriere absolvire");
	assert(s.dimen_repo() == 2);
	s.undo();
	assert(s.dimen_repo() == 1);
	s.undo();
	assert(s.dimen_repo() == 0);

	try {
		s.undo();
		assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMessage().size() > 0);
	}


}
void teste_undo_stergere() {
	Repo r(0);
	CosActivitatii c;
	Validator v;
	Service s{ r, v, c };
	s.adauga("Nunta", 1500, "obligatoriu", "descriere nunta");
	s.adauga("Absolvire", 1200, "facultativ", "descriere absolvire");
	assert(s.dimen_repo() == 2);
	s.stergere("Absolvire", 1200, "facultativ", "descriere absolvire");
	assert(s.dimen_repo() == 1);
	s.undo();
	assert(s.dimen_repo() == 2);
}

void teste_undo_modificare() {
	Repo r(0);
	CosActivitatii c;
	Validator v;
	Service s{ r, v, c };
	s.adauga("Nunta", 1500, "obligatoriu", "descriere nunta");

	s.modificare("plimbare", 1400, "optional", "afara");

	s.undo();

	try {
		s.modificare("nimic", 14, "optional", "afara");
	}
	catch (RepoException& e) {
		assert(e.getMessage().size() > 0);
	}

}

void teste_undo_adaugare_cos() {
	Repo r(0);
	CosActivitatii c;
	Validator v;
	Service s{ r, v, c };
	s.adauga("plimbare", 15, "obligatoriu", "natura");
	s.adauga("aer", 12, "facultativ", "frumos afara");
	string ss = "plimbare";
	s.adauga_cos(ss);
	ss = "aer";
	s.adauga_cos(ss);
	assert(c.nr_activitatii() == 2);
	s.undo();
	assert(c.nr_activitatii() == 1);


}


void teste_undo() {
	teste_undo_add();
	teste_undo_stergere();
	teste_undo_modificare();
	teste_undo_adaugare_cos();
}
string printstring(int n)
{
	char letters[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q',
	'r','s','t','u','v','w','x',
	'y','z' };
	string ran = "";
	for (int i = 0; i < n; i++)
		ran = ran + letters[rand() % 26];
	return ran;
}
void teste_error_repo() {
	std::ofstream out("rezultate_error.txt");
	FileRepo r("repo_test2.txt", 0.5);
	r.clear_file();
	CosActivitatii c;
	Validator v;
	Service s{ r, v, c };

	for (int i = 0; i < 20; i++) {
		try {
			int durata = rand();
			string titlu = printstring(150);
			string tip = "facultativ";
			string descriere = printstring(20);
			s.adauga(titlu, durata, tip, descriere);
			out << "Succes\n";
		}
		catch (RepoException& e) {
			assert(e.getMessage().size() > 0);
			out << "FAIL\n";
		}
	}
	out.close();

}

void Teste::teste_run() {
	teste_entitate();
	teste_validare();
	teste_repo_store();
	teste_repo_modify();
	teste_repo_delete();
	teste_repo_cautare();
	teste_srv_adaugare();
	teste_srv_stergere();
	teste_srv_modificare();
	teste_srv_afisare();
	teste_srv_cautare();
	teste_srv_filtrare_durata();
	teste_srv_filtrare_descriere();
	teste_srv_statistica();
	teste_cos();
	teste_fisier();
	teste_undo();
	teste_error_repo();
}