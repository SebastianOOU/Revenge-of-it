#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "personaje.h"
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>
#include <QGraphicsView>
#include "armas.h"

class Enemigo : public Personaje{
       Q_OBJECT
    private:

       QGraphicsView *vista;

        int totalSuelo; int posicionIncial;

    public:

        Enemigo();
        Enemigo(QGraphicsView *,int,int,int,int);

        QTimer *timerMovimiento;

        void mostSprite(int);
        void moverAdelante();
        void moverAtras();

    public slots:
        void actualizarSprite();      
};

#endif // ENEMIGO_H
