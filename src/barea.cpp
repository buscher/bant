/***************************************************************************
 *   Copyright (C) 2007 by Bernd Buschinski   *
 *   b.buschinski@web.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "barea.h"

#include <QList>
// #include <QTimer>
#include <QTime>

#include "bfield.h"
#include "bhomefield.h"
#include "bfoodfield.h"
#include "bant.h"
#include "bdebug.h"

class BAreaPrivate
{
public:
    //X , Y
    QList< QList< BField* > > myMap;
    QList< BAnt* > myAntList;
//     QTimer myTimer; //TODO not stupid, let it work itself, that we dont have to care
    unsigned int myAreaSize;
    int myHomeX;
    int myHomeY;
};

BArea::BArea()
    : d ( new BAreaPrivate )
{
    d->myAreaSize = 50;
    d->myHomeX = -1;
    d->myHomeY = -1;

    for (uint i = 0; i < size(); i++)
    {
        QList< BField* > tList;
        for (uint j = 0; j < size(); j++ )
        {
            tList.append( new BField );
        }
        d->myMap.append( tList );
    }
}

BArea::~ BArea()
{
    while (!d->myMap.isEmpty())
    {
        while (!d->myMap.first().isEmpty())
        {
            delete d->myMap.first().takeFirst();
        }
        d->myMap.takeFirst();
    }

    delete d;
}

/**
 * -----
 * -----
 * --A--
 * -----
 * -----
 *
 * The Ant can see a 5x5 big field
 * @param aAnt The Ant
 * @return an Array of the visible fields
 */
QList< QList < BField * > > BArea::antView(BAnt * aAnt)
{
    QPoint tPoint = findAnt(aAnt);
    QList< QList < BField * > > tFieldList;

    if (tPoint.x() < 0) return tFieldList; //error, do something

    for (int x = tPoint.x()-2; x < tPoint.x()+3; ++x)
    {
        QList<BField*> tList;
        for (int y = tPoint.y()-2; y < tPoint.y()+3; ++y)
            tList.append( at(x,y));

        tFieldList.append( tList );
    }

    return tFieldList;
}

BField * BArea::at(int x, int y)
{
    if (x >= d->myMap.size())
        return NULL;
    if (x < 0)
        return NULL;

    if (y >= d->myMap.first().size())
        return NULL;
    if (y < 0)
        return NULL;

    return d->myMap.at(x).at(y);
}

QPoint BArea::findAnt(BAnt * aAnt) const
{
    for (int i = 0; i < d->myMap.size(); i++)
    {
        QList< BField* > tList;
        for (int j = 0; j < d->myMap.first().size(); j++ )
        {
            if (d->myMap.at(i).at(j)->hasAnt( aAnt))
                return QPoint(i,j);
        }
    }
    bDebug("This shouldn't happen");
    return QPoint(-1,-1);
}

unsigned int BArea::size()
{
    return d->myAreaSize;
}

void BArea::update()
{
    QTime tTime;
    tTime.start();
    for (int i = 0; i < d->myMap.size(); i++)
    {
        for (int j = 0; j < d->myMap.first().size(); j++ )
        {
            d->myMap.at(i).at(j)->updateSmell();
        }
    }
    bDebug("Smell time: " + QString::number( tTime.elapsed() ) );
    tTime.start();


    for ( int i = 0; i < d->myAntList.size(); ++i)
    {
        d->myAntList.at(i)->move();
    }
    bDebug("Ant time: " + QString::number( tTime.elapsed() ) );
}

bool BArea::addAnt()
{
    if (d->myHomeX > -1)
        return addAnt( d->myHomeX, d->myHomeY );
    else
        return addAnt( 25,25);
}

bool BArea::addAnt(int aX, int aY)
{
    //TODO range checking
    BAnt *tAnt = new BAnt(this, at( aX, aY));
    d->myAntList.append( tAnt );
    at( aX, aY)->addAnt( tAnt );

    return true;
}

bool BArea::addHome(int aX, int aY)
{
    //TODO range check
    delete d->myMap.at(aX).at(aY);
    d->myMap[aX][aY] = new BHomeField();

    d->myHomeX = aX;
    d->myHomeY = aY;

    return true;
}

bool BArea::addFood(int aX, int aY)
{
    //TODO range check
    delete d->myMap.at(aX).at(aY);
    d->myMap[aX][aY] = new BFoodField();

    return true;
}

QList< BAnt * > BArea::ants()
{
    return d->myAntList;
}
