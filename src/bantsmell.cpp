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

#include "bantsmell.h"

class BAntSmellPrivate
{
public:
    BAnt* myOwner;
    double mySmellSence;
};


BAntSmell::BAntSmell(BAnt* aOwner)
    : d ( new BAntSmellPrivate )
{
    d->myOwner = aOwner;
    d->mySmellSence = 100;
}

BAntSmell::~ BAntSmell()
{
    delete d;
}

double BAntSmell::sense() const
{
    return d->mySmellSence;
}

void BAntSmell::sense(double aSmell)
{
    d->mySmellSence = aSmell;
}

void BAntSmell::update()
{
    d->mySmellSence = sense()/100.0f*96.0f;
}
