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

#include "bfield.h"

#include "bantsmell.h"
#include "bant.h"

class BFieldPrivate
{
public:
    QList<BAnt*> myAntList;
    QList<BAntSmell*> mySmellList;
    unsigned int myType;
};


BField::BField( int aType )
    : d ( new BFieldPrivate )
{
	d->myType = aType;
}

/**
 * WARNING! it deletes all Ants on the Field!
 * Remove the ants before if you don't want them to be deleted.
 */
BField::~ BField()
{
    while (!d->myAntList.isEmpty())
        delete d->myAntList.takeFirst();

    while (!d->mySmellList.isEmpty())
        delete d->mySmellList.takeFirst();

    delete d;
}

void BField::updateSmell()
{
    for (int i = 0; i < d->mySmellList.size(); i++)
    {
        d->mySmellList.at( i )->update();
        if (d->mySmellList.at( i )->sense() < 0.5f )
            delete d->mySmellList.takeAt( i );
    }
}

BAnt * BField::takeAnt(BAnt * aAnt)
{
    for (int i = 0; i < d->myAntList.size(); i++)
    {
        if (aAnt == d->myAntList.at( i ))
        {
            return d->myAntList.takeAt( i );
        }
    }
    return 0;
}

bool BField::hasAnt(BAnt * aAnt)
{
    for (int i = 0; i < d->myAntList.size(); ++i)
        if (aAnt == d->myAntList.at( i ))
            return true;
    return false;
}

int BField::type()
{
    return d->myType;
}

void BField::addAnt(BAnt * aAnt)
{
    d->myAntList.append( aAnt );
    d->mySmellList.append( new BAntSmell( aAnt ));
}

QList< BAnt * > BField::ants()
{
    return d->myAntList;
}

QList< BAntSmell * > BField::smells()
{
    return d->mySmellList;
}
