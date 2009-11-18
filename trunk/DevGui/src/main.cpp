/*
    This file is part of QTwitlib.

    QTwitlib is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    QTwitlib is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QTwitlib.  If not, see <http://www.gnu.org/licenses/>.
	
	Original Author: Bradley Lackey
*/

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


