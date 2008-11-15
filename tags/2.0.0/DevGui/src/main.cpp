#include <iostream>
#include "example.h"


int main(int argc, char** argv)
{
	QApplication a(argc, argv);
    Example w;
    w.show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
	int result = a.exec();

	return result;
}


