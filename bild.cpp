/* bild.cpp */

#include "bild.h"

/* Konstruktor */
Bild::Bild(QString bilddatei, QWidget* elternobjekt) : QLabel(elternobjekt)
{
    reload(bilddatei);
}

/* Destruktor */
Bild::~Bild()
{
}

void Bild::reload(QString bilddatei)
{
    bild.load( bilddatei );
    this->setGeometry( 0, 0, bild.width(), bild.height() );
    this->setPixmap( bild );
}
