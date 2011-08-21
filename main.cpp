/*
 *  Copyright (c) 2011 Marc Ransome <marc.ransome@fidgetbox.co.uk>
 *
 *  This file is part of sha1crawler.
 *
 *  sha1crawler is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  sha1crawler is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with sha1crawler.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <QtCore/QCoreApplication>
#include <iostream>

#include "sha1crawler.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if(argc > 1)
    {   // ..an argument was provided

        // instantiate and start crawl using a path argument
        Sha1Crawler m(argv[1]);
        m.start();
    }
    else
    {   // ..no argument was provided

        // output error and exit
        cout << "No path argument specified, exiting.\n";
        exit(1);
    }

    return a.exec();
}
