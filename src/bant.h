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

#ifndef BANT_H
#define BANT_H

class BArea;
class BField;
class QPoint;

class BAnt
{
public:

enum MoveDirection {
    NN,
    NE,
    EE,
    ES,
    SS,
    SW,
    WW,
    WN
};

    BAnt(BArea *aArea, BField* aField);
    ~BAnt();

    void move();

private:
    inline BArea* area();
    inline BAnt* followAnt();
    inline void setFollowAnt(BAnt * aAnt);

    inline BField* field();
    inline void setField( BField* aField );
    inline void moveTo( BField* aField );
    inline const QPoint moveToDirection();

    inline int normalize( int aValue );

    inline bool checkDirection( int aX, int aY );
    inline int direction();
    inline void setDirection( int aDirection );
    inline void updateDirection( int aValue );

    inline int target();
    inline void setTarget( int aTarget );
    inline void targetfound( BField* aField );

    inline int getDirectionValue(int aX, int aY);

    inline int turns();
    inline void resetTurns();

    class BAntPrivate * const d;
};

#endif //BANT_H
