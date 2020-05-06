#include "ActivitatiGUI.h"
#include "test.h"
//#define _CRTDBG_MAP_ALLOC
int main(int argc, char* argv[])
{
//{
	Teste teste;
	teste.teste_run();
	//Repo repo;	
	FileRepo repo("fileRepo.txt", 0);
	Validator valid;
	CosActivitatii contract;
	Service serv{ repo, valid, contract };
	QApplication a(argc, argv);
	ActivitatiGUI gui{ serv };
	gui.show();
	return a.exec();
	//_CrtDumpMemoryLeaks();
//}


}
