#pragma once
#include "activitate.h"
#include "repo.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	Activitate d_adaugata;
	REPO& repo;
public:
	UndoAdauga(REPO& rep, const Activitate d) : repo{ rep }, d_adaugata{ d } {}
	void doUndo() override;
};

class UndoStergere : public ActiuneUndo {
	Activitate d_stearsa;
	REPO& repo;
public:

	UndoStergere(REPO& rep, const Activitate d) : repo{ rep }, d_stearsa{ d } {}
	void doUndo() override;
};

class UndoMod : public ActiuneUndo {
	Activitate d1, d2;
	REPO& repo;
public:

	UndoMod(REPO& rep, const Activitate d1, const Activitate d2) : repo{ rep }, d1{ d1 }, d2{ d2 } {}
	void doUndo() override;
};

class UndoAddCos : public ActiuneUndo {
	string nume;
	CosActivitatii& cont;
public:

	UndoAddCos(CosActivitatii& cont, string nume) : cont{ cont }, nume{ nume } {}
	void doUndo() override;
};
