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

        QPixmap spriteImgArma;
        QPixmap spriteArma;

        QPixmap spriteExplosion;
        QPixmap explosion;
        QTimer *timerExplosion;

        bool personORenemin;

        int spriteX;
        int spriteY;
        int posicion;
        int contador = 0;

        bool derecha; bool izquierda;

        QTimer *timerArma;
        QGraphicsEllipseItem *arma;

        QGraphicsView *vista;
        float nuevaXArma;
        float nuevaYArma;
        //Posicion de la bomba
        float xArma;
        float yArma;

        float velocidadInicialArma;
        float anguloArma;
        //Angulo de lanzamiento
        float tiempoArma;

        float gravedad;

        map <int,int> posicionesPlataforma;

    public:
        Armas(QGraphicsView *, bool, bool, bool);
        Armas();
        void lanzarArma(float,float);
        void moverArma();
        void captDatosPosicionPlat(int,int);
        //void choqueDetectadoPer();

        void mostAnimExplosion();

        void detectarChoque();
        void mostrarSpritExplosion();

        void verificarColision();
        void pararMovimiento();

    public slots:
        void actiAnimExplocion();

    signals:
        void aumentarPuntaje();

};

#endif // ARMAS_H
