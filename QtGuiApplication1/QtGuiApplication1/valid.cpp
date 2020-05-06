#pragma once
#include "valid.h"
#include <string>

string ValidException::getMessage()
{
	return msg;
}

void Validator::valideaza(Activitate d)
{
	string err = "";
	if (d.get_descriere() == "")
		err += "Descriere este vida!\n";
	if (d.get_titlu() == "")
		err += "Titlul este vid!\n";
	if (d.get_durata() < 1)
		err += "Durata invalida!\n";
	string type = d.get_tip();
	if (type != "optional" && type != "obligatoriu" && type != "facultativ")
		err += "Tip activitate invalid!\n";
	if (err.size() > 0)
		throw(ValidException(err));
	return;
}
