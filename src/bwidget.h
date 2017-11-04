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

#ifndef BWIDGET_H
#define BWIDGET_H

#include "ui_bantviewwidget.h"

#include <QWidget>

class BArea;
class BAntSmell;

class BWidget : public QWidget, public Ui::BAntViewWidget
{
Q_OBJECT

public:
    BWidget();
    ~BWidget();

protected:
    virtual void resizeEvent ( QResizeEvent * aEvent );
    virtual void showEvent ( QShowEvent * aEvent );

private slots:
    void updateAnts( bool aNoUpdate = false );
    void addAntClicked();
    void renderHints( int aState );

private:
    inline uint pixHeight();
    inline uint pixWidth();

    inline BAntSmell* highestSmell( QList< BAntSmell* > aList);

    inline QPainter* painter();
    inline BArea* area();

    class BWidgetPrivate* const d;
};

#endif //BWIDGET_H
