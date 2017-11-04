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

#ifndef BFIELD_H
#define BFIELD_H

#include <QList>

class BAnt;
class BAntSmell;

class BField
{
public:

enum FieldType {
	Normal,
	Block,
	Food,
	Home
};

    BField( int aType = BField::Normal );
    ~BField();

    void updateSmell();
    QList< BAntSmell* > smells();

    void addAnt(BAnt* aAnt);
    BAnt* takeAnt(BAnt* aAnt);
    QList<BAnt*> ants();

    bool hasAnt(BAnt *aAnt);

    int type();

private:
    class BFieldPrivate* const d;
};

#endif //BFIELD_H
