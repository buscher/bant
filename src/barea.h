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

#ifndef BAREA_H
#define BAREA_H

#include <QList>
#include <QPoint>

class BField;
class BAnt;

class BArea
{
public:
    BArea();
    ~BArea();

    QList< QList< BField* > > antView(BAnt* aAnt);
    QList< BAnt* > ants();

    BField* at( int x, int y);
    QPoint findAnt(BAnt* aAnt) const;

    void update();
    bool addAnt(int aX, int aY);
    bool addAnt();

    bool addHome( int aX, int aY);

    bool addFood( int aX, int aY);

    unsigned int size();

private:
    class BAreaPrivate *const d;
};

#endif //BAREA_H
