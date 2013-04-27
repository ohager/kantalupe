#include <QFile>
#include <QTextStream>
#include "MainWindow.h"
#include "global.h"
#include "Application.h"
#include "PluginPool.h"

using namespace k;
using namespace k::global;

QString readStyleSheet(const QString& filename)
{
	QFile fin(filename);

	if(fin.open(QFile::ReadOnly | QFile::Text))
	{
		QTextStream in(&fin);
		return in.readAll();
	}
	else
	{
		WARNING("::","readStyleSheet",
				QApplication::translate("::",
						"Could not open styles sheet '%1'").arg(filename),
				fin.errorString()
			);
	}

	return QString();
}

int main(int argc, char *argv[])
{

	Application a(argc, argv);

	const char * xrsfile = "../resources/kantalupe.xrs";

	if(!initR(xrsfile))
    {
		return -1;
    }

	QString qss( readStyleSheet(
			R.getValue("general","stylesheet")
			)
		);
	a.setStyleSheet( qss );

	k::MainWindow w;
    w.show();

	int result =  a.exec();
	PluginPool::destroy();
	return result;
}
