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

#include "bant.h"

#include "brand.h"
#include "barea.h"
#include "bfield.h"
#include "bhomefield.h"

#include <QString>
#include <QPoint>
#include <QDebug>

class BAntPrivate
{
public:
    int myTurns;
    BAnt* myTryToFollow;
    unsigned short myDirection;
    BArea* myArea;
    BField* myField;
    int myTarget;
};


BAnt::BAnt(BArea *aArea, BField* aField)
    : d ( new BAntPrivate)
{
    d->myTurns = 0;
    d->myTryToFollow = NULL;
    d->myDirection = brand( 7 );
    d->myArea = aArea;
    d->myField = aField;
    d->myTarget = BField::Food;
}

BAnt::~BAnt()
{
    delete d;
}

void BAnt::move()
{
    d->myTurns++;

    QList< QList < BField * > > tList = area()->antView( this );

    if (tList.at(2).at(2)->type() == target())
    {
        targetfound( tList.at(2).at(2) );
    }

    bool bFound = false;
    QPoint tPoint;
    for (int i = 0; i < tList.size(); ++i)
    {
        for (int j = 0; j < tList.first().size(); ++j)
        {
            if (!tList.at(i).at(j)) continue;
            if (tList.at(i).at(j)->type() == target())
            {
                bFound = true;
                tPoint.setX(i);
                tPoint.setY(j);
                break;
            }
        }
        if (bFound) break;
    }

    if (bFound)
    {
        int x = normalize(tPoint.x());
        int y = normalize(tPoint.y());

        if (checkDirection(x,y))
            moveTo( tList[ 2+x ][ 2+y ] );
        setDirection( getDirectionValue( x, y ) );

    } else {
        if (followAnt())
            ;//doit
        else
            tPoint = moveToDirection();
            BField* tField = tList.at(tPoint.x() +2).at(tPoint.y() +2);
            if (!tField)
                updateDirection( 4 );
            else
                moveTo( tField );
    }

    //scan area for food/goal
    //moveto is, if found

    //try to follow fastest, if there is one
    //if not, move anyway
    //TODO need add to the smelly things
}

BArea * BAnt::area()
{
    return d->myArea;
}

BAnt * BAnt::followAnt()
{
    return d->myTryToFollow;
}

void BAnt::moveTo( BField* aField )
{
    aField->addAnt( this );
    field()->takeAnt( this );
    setField( aField );
}

BField * BAnt::field()
{
    return d->myField;
}

void BAnt::setField(BField * aField)
{
    d->myField = aField;
}

int BAnt::normalize(int aValue)
{
    int tVal = aValue;
    if (tVal > 3) --tVal;
    if (tVal < 1) ++tVal;
    return tVal-2;
}

bool BAnt::checkDirection(int aX, int aY)
{
    int x = aX;
    int y = aY;
    int tDirectionDiff = getDirectionValue(aX,aY);

    switch (direction())
    {
        case NN:
            if (y > -1)
            {
                setDirection( tDirectionDiff );
                return false;
            }
            break;

        case NE:
            if (x < 1 && y != -1)
            {
                setDirection( tDirectionDiff );
                return false;
            }
            break;

        case EE:
            if (x < 1)
            {
                setDirection( tDirectionDiff );
                return false;
            }
            break;

        case ES:
            if (x < 1 && y != 1)
            {
                setDirection( tDirectionDiff );
                return false;
            }
            break;

        case SS:
            if (y < 1)
            {
                setDirection( tDirectionDiff );
                return false;
            }
            break;

        case SW:
            if (y < 1 && x != 0)
            {
                setDirection( tDirectionDiff );
                return false;
            }
            break;

        case WW:
            if (x > -1)
            {
                setDirection( tDirectionDiff );
                return false;
            }
            break;

        case WN:
            if (x > -1 && y != -1)
            {
                setDirection( tDirectionDiff );
                return false;
            }
            break;

    }
    return true;
}

int BAnt::direction()
{
    return d->myDirection;
}

int BAnt::target()
{
    return d->myTarget;
}

int BAnt::getDirectionValue(int aX, int aY)
{
    int tSum = aX + aY;
    switch (tSum)
    {
        case -2: return BAnt::WN;
        case -1:
            if (aX == 0)
                return BAnt::NN;
            else
                return BAnt::WW;
        case 0:
            if (aX == 1)
                return BAnt::NE;
            else
                return BAnt::SW;
        case 1:
            if (aX == 1)
                return BAnt::EE;
            else
                return BAnt::SS;
        case 2:
            return BAnt::ES;
        default:
            qWarning() << "aX and aY are NOT normalized, gonna try it again, tSum: " << tSum;
            return getDirectionValue(normalize(aX),normalize(aY));
    }
}

void BAnt::setDirection(int aDirection)
{
    d->myDirection = aDirection;
}

void BAnt::updateDirection(int aValue)
{
    int t = direction() + aValue;
    while (t > 7) t -= 8;
    while (t < 0) t += 8;
    setDirection( t );
}

const QPoint BAnt::moveToDirection()
{
    updateDirection( negbrand(1) );
    switch (direction())
    {
        default:
        case BAnt::NN:
            return QPoint( 0,-1);
        case BAnt::NE:
            return QPoint( 1,-1);
        case BAnt::EE:
            return QPoint( 1, 0);
        case BAnt::ES:
            return QPoint( 1, 1);
        case BAnt::SS:
            return QPoint( 0, 1);
        case BAnt::SW:
            return QPoint(-1, 1);
        case BAnt::WW:
            return QPoint(-1, 0);
        case BAnt::WN:
            return QPoint(-1,-1);
    }
}

void BAnt::setTarget(int aTarget)
{
    d->myTarget = aTarget;
}

void BAnt::targetfound(BField * aField)
{
    updateDirection( 4 );

    if (target() == BField::Food)
        setTarget( BField::Home );
    else
    {
        setTarget( BField::Food );

        BHomeField* tHome = static_cast<BHomeField*>(aField);
        if (!tHome) return;

        tHome->tellResult( turns(), this );
        resetTurns();
        setFollowAnt( tHome->fastAnt() );
    }
}

int BAnt::turns()
{
    return d->myTurns;
}

void BAnt::resetTurns()
{
    d->myTurns = 0;
}

void BAnt::setFollowAnt(BAnt * aAnt)
{
//     d->myTryToFollow = aAnt == this ? aAnt : NULL;
    d->myTryToFollow = NULL;//TODO
}
