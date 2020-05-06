#pragma once
#include "Service.h"
#include <QtWidgets/qwidget.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qspinbox.h>
#include <QtWidgets/qgridlayout.h>
#include <qdebug.h>
#include <qmessagebox.h>

class ActivitatiGUI: public QWidget {
public:
	ActivitatiGUI(Service& s) : srv{ s } {
		initGUI();
		loadData();
		initConnect();
	}
private:
	Service& srv;
	QPushButton* btn_exit = new QPushButton{ "&Exit" };
	QPushButton* btn_add = new QPushButton{ "&Adauga" };
	QPushButton* btn_del = new QPushButton{ "&Sterge" };
	QPushButton* btn_mod = new QPushButton{ "&Modifica" };
	QPushButton* btn_undo = new QPushButton{ "&Undo" };
	QPushButton* btn_genereaza = new QPushButton{ "&Genereaza" };
	QPushButton* btn_adauga_cos = new QPushButton{ "&AdaugaCos" };

	QLineEdit* txt_titlu = new QLineEdit{};
	QLineEdit* txt_durata = new QLineEdit{};
	QLineEdit* txt_tip = new QLineEdit{};
	QLineEdit* txt_descriere = new QLineEdit{};
	QListWidget* list = new QListWidget;
	QListWidget* cos_list = new QListWidget;

	QSpinBox* spn_box = new QSpinBox{};
	
	void initConnect() {
		QObject::connect(btn_exit, &QPushButton::clicked, [&]() {
			qDebug() << "Aplicatia se inchide!";
			//QMessageBox::information(nullptr,"INFO","Mersi pentru utilizare!");
			close();
			});
		QObject::connect(btn_add, &QPushButton::clicked, [&]() {
			auto titlu = txt_titlu->text();
			auto tip = txt_tip->text();
			auto durata = txt_durata->text();
			auto descriere = txt_descriere->text();
			try {
				srv.adauga(titlu.toStdString().c_str(), durata.toUInt(), tip.toStdString().c_str(), descriere.toStdString().c_str());
			}
			catch (ValidException& e) {
				QMessageBox::information(nullptr, " Eroare la validare:", e.getMessage().c_str());
			}
			catch (RepoException& e) {
				QMessageBox::information(nullptr, " EEroare la repository:", e.getMessage().c_str());
			}
			loadData();
			});
		QObject::connect(btn_del, &QPushButton::clicked, [&]() {
			auto titlu = txt_titlu->text();
			auto tip = txt_tip->text();
			auto durata = txt_durata->text();
			auto descriere = txt_descriere->text();
			try {
				srv.stergere(titlu.toStdString().c_str(), durata.toUInt(), tip.toStdString().c_str(), descriere.toStdString().c_str());
			}
			catch (ValidException& e) {
				QMessageBox::information(nullptr, " Eroare la validare:", e.getMessage().c_str());
			}
			catch (RepoException& e) {
				QMessageBox::information(nullptr, " EEroare la repository:", e.getMessage().c_str());
			}
			loadData();
			});
		QObject::connect(btn_mod, &QPushButton::clicked, [&]() {
			auto titlu = txt_titlu->text();
			auto tip = txt_tip->text();
			auto durata = txt_durata->text();
			auto descriere = txt_descriere->text();
			try {
				srv.modificare(titlu.toStdString().c_str(), durata.toUInt(), tip.toStdString().c_str(), descriere.toStdString().c_str());
				loadData();
			}
			catch (ValidException& e) {
				QMessageBox::information(nullptr, " Eroare la validare:", e.getMessage().c_str());
			}
			catch (RepoException& e) {
				QMessageBox::information(nullptr, " EEroare la repository:", e.getMessage().c_str());
			}
			});
		QObject::connect(btn_undo, &QPushButton::clicked, [&]() {
			try {
				srv.undo();
				loadData();
				loadDataCos();
			}
			catch (RepoException& e) {
				QMessageBox::information(nullptr, " EEroare la repository:", e.getMessage().c_str());
			}

			});
		QObject::connect(btn_genereaza, &QPushButton::clicked, [&]() {
			try {
				srv.generare_cos(spn_box->value());
				loadDataCos();
				
			}
			catch (CosException& e) {
				QMessageBox::information(nullptr, " EEroare la repository:", e.getMessage().c_str());
			}

			});

		QObject::connect(btn_adauga_cos, &QPushButton::clicked, [&]() {
			auto titlu = txt_titlu->text();
			auto tip = txt_tip->text();
			auto durata = txt_durata->text();
			auto descriere = txt_descriere->text();
			try {
				srv.adauga_cos(titlu.toStdString().c_str());
				loadDataCos();
			}
			catch (CosException& e) {
				QMessageBox::information(nullptr, " EEroare la repository:", e.getMessage().c_str());
			}

			});


	}

	void loadData() {
		list->clear();
		auto activitati =srv.afisare();
		for (auto act : activitati) {
			list->addItem( QString::fromStdString(act.get_str()));
		}
		
	}
	void loadDataCos() {
		cos_list->clear();
		auto cos_activitatii = srv.afisare_cos();
		for (auto act : cos_activitatii) {
			cos_list->addItem(QString::fromStdString(act.get_str()));
		}
	}
	void initGUI() {

		spn_box->setValue(0);
		QGridLayout* layout = new QGridLayout{};

		QHBoxLayout* vert_ly = new QHBoxLayout{};

		//list->addItem("cercel");
		//list->addItem(new QListWidgetItem{ "cercel2" });

		vert_ly->addWidget(list);
		vert_ly->addWidget(cos_list);

		auto stanga_ly = new QVBoxLayout;

		auto form_ly = new QFormLayout;
		form_ly->addRow("Titlu", txt_titlu);
		form_ly->addRow("Durata", txt_durata);
		form_ly->addRow("Tip", txt_tip);
		form_ly->addRow("Descriere", txt_descriere);
		stanga_ly->addLayout(form_ly);




		setLayout(vert_ly);

		

		auto but_ly = new QHBoxLayout{};
		but_ly->addWidget(btn_add);
		but_ly->addWidget(btn_del);
		but_ly->addWidget(btn_mod);
		but_ly->addWidget(btn_exit);
		but_ly->addWidget(btn_undo);
		but_ly->addWidget(btn_genereaza);

		stanga_ly->addLayout(but_ly);
		stanga_ly->addWidget(spn_box, 0, 0);

		vert_ly->addLayout(stanga_ly);
		
		vert_ly->addLayout(layout);
		
		layout->addWidget(btn_add, 0, 0);
		layout->addWidget(btn_del, 0, 1);
		layout->addWidget(btn_undo, 1, 0, 1, 2);
		layout->addWidget(btn_genereaza, 2, 0);
		layout->addWidget(btn_mod, 2, 1);
		layout->addWidget(btn_exit, 3, 1);
		layout->addWidget(btn_adauga_cos, 3, 0);
		
	}

};