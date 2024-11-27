#ifndef OBSTACULOS_H
#define OBSTACULOS_H

#include <iostream>
#include <fstream>
#include <map>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPixmap>
#include <QGraphicsView>
#include "niveljuego.h"
using namespace std;

class Obstaculos : public QObject , public QGraphicsPixmapItem{
        Q_OBJECT
    private:
        QGraphicsView *vista;
        string direccionNivel;

        QTimer *timerSpriteCaja;

        QPixmap spritImgCajas;
        QPixmap spritCaja;

        int pos_x_sprite;
        int pos_y_sprite;
        int anchoSprite;
        int contador;

        int cantidadObs;
        int numScena;
        int nivelJuego;

        int arrayDatos[3];

    public:
        Obstaculos(string, int);
        Obstaculos();
        Obstaculos(QGraphicsView *, int);

        map <int,map<int,int>> datosSprites;
        map <int,map<int,int>> datosEnemigo;

        void extraerDatosSprites();
        void extraerDatosEnenim();
        void capturarPosiciones(string, bool);

        void activarObsNivel1_3();
        void cajaNivel1();
        void cajaNivel3();

    signals:

        void nivelSuperado();
};

#endif // OBSTACULOS_H
