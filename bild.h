/* bild.h */

#ifndef BILD_H
#define BILD_H

#include <qlabel.h>
#include <qpixmap.h>

class Bild : public QLabel
{
   Q_OBJECT

public:
   Bild(QString bilddatei=0, QWidget *elternobjekt = 0);   /* Konstruktor */
  ~Bild();                                                 /* Destruktor  */

private:
   QPixmap bild;

public slots:
   void reload(QString);
};

#endif
