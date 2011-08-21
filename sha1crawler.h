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

#ifndef Sha1CRAWLER_H
#define Sha1CRAWLER_H

#include <QObject>
#include <QDir>
#include <QStack>

class Sha1Crawler : public QObject
{
    Q_OBJECT
public:
    explicit Sha1Crawler(QString pathToCrawl, QObject *parent = 0);
    void start();

private:
    // members
    QDir dirForCrawling;
    QStack<QString> dirsCrawled;

    // functions
    QString hashFileUsingSha1(QString filePath);
    void crawl();
};

#endif // Sha1CRAWLER_H
