#include <QtCore/QCoreApplication>
#include "requesthandler.h"
#include <iostream>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	
	QString fileName = QCoreApplication::applicationDirPath() + "/1.xls";
	if (argc > 3)
	{
		fileName = QString(argv[3]);
	}

	RequestHandler h(fileName);
	if (argc > 1)
	{
		QString strHelp = "/?";
		if (strHelp.compare(argv[1]) == 0)
		{
			std::cout << "The 1st para is Url. Defualt guanan's ali." << std::endl;
			std::cout << "The 2nd para is time. Defualt guanan's 100ms." << std::endl;
			std::cout << "The 3nd para is file. Defualt guanan's 1.xls." << std::endl;
			return 0;
		}
		h.SetUrl(argv[1]);
	}
	if (argc > 2)
	{
		h.SetVal(QString(argv[2]).toInt());
	}
	h.start();

	return a.exec();
}
