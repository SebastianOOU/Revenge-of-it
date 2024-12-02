#ifndef ARMAS_H
#define ARMAS_H

#include <QTimer>
#include <QObject>
#include <QPixmap>
#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <map>
#include <iostream>
#include "personaje.h"
using namespace std;

class Armas : public QObject, public QGraphicsPixmapItem {
        Q_OBJECT
    private:

        QPixmap spriteImgArma, spriteArma, spriteExplosion, explosion;
        QTimer *timerExplosion, *timerArma;
        QGraphicsView *vista;

        bool personORenemin;

        int spriteX, spriteY, posicion, contador;

        bool derecha, izquierda;

        //Angulo de lanzamiento
        float tiempoArma, gravedad;

        float nuevaXArma, nuevaYArma, xArma, yArma;

        float velocidadInicialArma, anguloArma;

        map <int,int> posicionesPlataforma;

    public:
        Armas(QGraphicsView *, bool, bool, bool);
        Armas();
        void lanzarArma(float,float);
        void captDatosPosicionPlat(int,int);

        void mostAnimExplosion();

        void verificarColision();

    public slots:

        void moverArma();
        void actiAnimExplocion();

    signals:
        void aumentarPuntaje();

};

#endif // ARMAS_H
