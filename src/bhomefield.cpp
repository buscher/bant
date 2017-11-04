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

#include "bhomefield.h"

class BHomeFieldPrivate
{
public:
    BAnt* myFastAnt; //former brainbug save
    unsigned int myTurns;
};


BHomeField::BHomeField()
    : BField ( BField::Home ), d ( new BHomeFieldPrivate )
{
    d->myTurns = 65536;
    d->myFastAnt = NULL;
}

BHomeField::~ BHomeField()
{
    delete d;
}

void BHomeField::tellResult(uint aTurns, BAnt * aAnt)
{
    if (aTurns < d->myTurns)
    {
        d->myTurns = aTurns;
        d->myFastAnt = aAnt;
    }
}

BAnt * BHomeField::fastAnt()
{
    return d->myFastAnt;
}

unsigned int BHomeField::turns()
{
    return d->myTurns;
}
