#include "hades.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Hades w;
	w.show();
	return a.exec();
}
