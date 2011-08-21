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

#include "sha1crawler.h"

#include <iostream>
#include <QCryptographicHash>

using namespace std;

Sha1Crawler::Sha1Crawler(QString pathToCrawl, QObject *parent) :
    QObject(parent)
{
    // test for existence of path
    if(QDir(pathToCrawl).exists())
    {   // ..path exists

        // set initial path to crawl
        dirForCrawling.setPath(pathToCrawl);
    }
    else
    {   // ..path does not exist

        // output error and exit
        cout << "Path \"" << pathToCrawl.toLocal8Bit().constData() << "\" does not exist." << endl;
        exit(1);
    }
}

void Sha1Crawler::start()
{
    cout << "\nSha1 crawler starting..\n";

    // call recursive crawler function
    crawl();

    cout << "Success.\n\n";

    exit(0);
}

void Sha1Crawler::crawl()
{
    // test for existence of Sha1 file and remove
    if(QFile::exists(dirForCrawling.absolutePath() + QDir::separator() + "sha1"))
    {
        // remove existing Sha1 file
        cout << "  - deleting sha1 from " << dirForCrawling.absolutePath().toLocal8Bit().constData() << endl;


        // attempt to delete file
        if(!QFile::remove(dirForCrawling.absolutePath() + QDir::separator() + "sha1"))
        {   // ..file deletion failed

            // output error and exit
            cout << "  - unable to delete sha1 from" << dirForCrawling.absolutePath().toLocal8Bit().constData() << endl;
            cout << "Exiting (error)\n";
            exit(1);
        }
    }

    // loop for each subdir
    Q_FOREACH(QFileInfo info, dirForCrawling.entryInfoList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsLast))
    {   // ..loop starts here

        // test for dir
        if (info.isDir())
        {   // ..found a dir

            // cd to subdir
            if(!dirForCrawling.cd(info.absoluteFilePath()))
            {
                // output error and exit
                cout << "  - cd to subdir failed " << info.absoluteFilePath().toLocal8Bit().constData() << endl;
                cout << "Exiting (error)\n";
                exit(1);
            }

            // output
            cout << "  > crawling subdir "<< dirForCrawling.absolutePath().toLocal8Bit().constData() << endl;

            // recurse for subdir by calling self function
            crawl();

            // attempt to move up a dir
            if(!dirForCrawling.cdUp())
            {
                // output error and exit
                cout << "  - cd to parent dir failed from " << dirForCrawling.absolutePath().toLocal8Bit().constData() << endl;
                cout << "Exiting (error)\n";
                exit(1);
            }

            cout << "  < moving up a dir " << dirForCrawling.absolutePath().toLocal8Bit().constData() << endl;
        }
        else if (info.isFile())
        {   // ..found a file

            // file object for reading/writing sha1 file
            QFile Sha1File(dirForCrawling.absolutePath() + QDir::separator() + "sha1");

            // attempt to open file for appending
            if (!Sha1File.open(QIODevice::Append))
            {   // ..file could not be opened

                // output error and exit
                cout << "  - file could not be opened\n";
                cout << "Exiting (error)\n";
                exit(1);
            }

            // generate file hash
            QString fileHash = hashFileUsingSha1(dirForCrawling.absolutePath() + QDir::separator() + info.fileName());

            // write filename and hash to sha1 file
            Sha1File.write(QString(info.fileName() + ":" + fileHash + "\n").toAscii());

            // close file object
            Sha1File.close();
        }
    }
}

QString Sha1Crawler::hashFileUsingSha1(QString filePath)
{
        // update output
        cout << "  + adding hash for " << filePath.toLocal8Bit().constData() << endl;

        // create file reference from the filename passed to function
        QFile currentFile(filePath);

        // attempt to open file for reading
        if(currentFile.open(QIODevice::ReadOnly))
        {   // ..success

            // create byte array from file contents
            QByteArray bytes = currentFile.readAll();

            // close file
            currentFile.close();

            // return hashed value of byte array
            return QString(QCryptographicHash::hash((bytes),QCryptographicHash::Sha1).toHex());
        }
        else
        {   // ..failure, could not open file

            // could not open file for hashing
            cout << "  - file could not be opened " << filePath.toLocal8Bit().constData() << endl;
            cout << "Exiting (error)" << endl;
            exit(1);
        }
}
