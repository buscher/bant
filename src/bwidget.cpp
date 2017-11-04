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

#include "bwidget.h"

#include "barea.h"
#include "bfield.h"
#include "bantsmell.h"
#include "bdebug.h"

#include <QTimer>
#include <QTime>
#include <QLabel>
#include <QGLWidget>
#include <QPainter>
#include <QPushButton>
#include <QCheckBox>
#include <QString>

class BWidgetPrivate
{
public:
    QTimer *myTimer;
    QPainter myPainter;
    BArea myArea;
    bool myAntialiasing;
};

BWidget::BWidget()
    : QWidget(), d ( new BWidgetPrivate )
{
    setupUi(this);

    connect ( myAntAddButton, SIGNAL(clicked()), this, SLOT(addAntClicked()));
    d->myAntialiasing = false;
    connect ( myAntialiasingCheck, SIGNAL(stateChanged ( int )), this, SLOT( renderHints( int ) ));

    area()->addHome( 5, 5);
    area()->addFood( area()->size() - 4, area()->size() - 4);

    addAntClicked();

    d->myTimer = new QTimer();
    connect ( d->myTimer, SIGNAL(timeout()), this, SLOT(updateAnts()));
    d->myTimer->start( 250 );
}

BWidget::~ BWidget()
{
    d->myTimer->stop();
    delete d->myTimer;
    delete d;
}

void BWidget::updateAnts( bool aNoUpdate )
{
    if (!aNoUpdate)
        area()->update();

    painter()->begin( myGLWidget );
    painter()->setRenderHint( QPainter::HighQualityAntialiasing, d->myAntialiasing );
    painter()->setPen( Qt::black );
    painter()->fillRect(0, 0, pixWidth(), pixHeight(), Qt::white );

    BField* tField;
    BAntSmell *tSmell;
    bool bPaint;

    QTime tTime;
    tTime.start();
    for (uint x = 0; x < area()->size(); ++x)
    {
        for (uint y = 0; y < area()->size(); ++y)
        {
            tField = area()->at(x,y);
            if (!tField) continue;
            bPaint = false;

            switch (tField->type())
            {
            case BField::Home:
                if (myGoalCheck->checkState() == Qt::Checked)
                {
                    painter()->setPen( Qt::blue );
                    painter()->setBrush( Qt::blue );
                    bPaint = true;
                }
                break;
            case BField::Food:
                if (myGoalCheck->checkState() == Qt::Checked)
                {
                    painter()->setPen( Qt::darkYellow );
                    painter()->setBrush( Qt::darkYellow );
                    bPaint = true;
                }
                break;
            default:
                if (mySmellCheck->checkState() == Qt::Checked)
                {
                    tSmell = highestSmell( tField->smells() );
                    if (!tSmell) continue;
                    painter()->setBrush( QColor(255,0,0, 255/100*tSmell->sense() ) );
                    painter()->setPen( QColor(255,0,0, 255/100*tSmell->sense() ) );
                    bPaint = true;
                }
                break;
            }
            if (bPaint)
                    painter()->drawRect(x*pixWidth()/area()->size(),
                                        y*pixHeight()/area()->size(),
                                        pixWidth()/area()->size(),
                                        pixHeight()/area()->size() );


            if (myAntCheck->checkState() == Qt::Checked && tField->ants().size() > 0)
            {
                painter()->setBrush( Qt::black );
                painter()->setPen( Qt::black );
                painter()->drawEllipse( x*pixWidth()/area()->size(),
                                        y*pixHeight()/area()->size(),
                                        pixWidth()/area()->size(),
                                        pixHeight()/area()->size() );
            }
        }
    }

    painter()->setBrush( Qt::white );
    painter()->setPen( Qt::black );
    int tVal = 0;
    for (uint i = 0; i < area()->size()+1; ++i)
    {
        //horiz
        tVal = qMax(i*pixHeight()/area()->size(), (uint)1);
        painter()->drawLine(0, tVal, pixWidth(), tVal);

        //vert
        tVal = qMin(i*pixWidth()/area()->size(),pixWidth()-1);
        painter()->drawLine(tVal, 0, tVal, pixHeight());
    }

    painter()->end();
    bDebug("Paint time: " + QString::number( tTime.elapsed() ) );
}

QPainter * BWidget::painter()
{
    return &d->myPainter;
}

BArea * BWidget::area()
{
    return &d->myArea;
}

void BWidget::resizeEvent(QResizeEvent * aEvent)
{
    updateAnts( true );
    QWidget::resizeEvent( aEvent );
}

void BWidget::showEvent(QShowEvent * aEvent)
{
    updateAnts( true );
    QWidget::showEvent( aEvent );
}

BAntSmell * BWidget::highestSmell(QList< BAntSmell * > aList)
{
    if (aList.size() == 0) return NULL;

    int tHigh = 0;
    for (int i = 0; i < aList.size(); ++i)
    {
        if (aList.at(i)->sense() > aList.at( tHigh)->sense())
            tHigh = i;
    }
    return aList.at( tHigh );
}

void BWidget::addAntClicked()
{
    area()->addAnt();
    myAntCountLabel->setText( QString::number( area()->ants().size() ) );
}

uint BWidget::pixHeight()
{
    return myGLWidget->height();
}

uint BWidget::pixWidth()
{
    return myGLWidget->width();
}

void BWidget::renderHints(int aState)
{
    d->myAntialiasing = aState == Qt::Checked ? true : false;
}
