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
       int altoSprite;
       int anchoSprite;
       int posicionX;
       int posicionY;
       int sprite_x_img;
       int sprite_y_img;
       int contador;
       int totalSuelo;
       int posicionIncial;
       bool _a,_c;
       int movDerecha;
       int movIzquierda;
       QGraphicsView *vista;
       QPixmap spriteImg;
       QPixmap sprite;
       QTimer *timerMovimiento;
       QTimer *timerArma;
       int estado;
       float velocidadY;
       const float gravedad = 0.5f;
       bool enElAire;
    public:
        Enemigo();
        Enemigo(QGraphicsView *,int,int,int,int x = 1000, int = 565, int ancho = 45, int alto = 60);
        void dimensionarSprite(int, int);
    public slots:
        void actualizarSprite();
        void mostSprite(int);
        //void aplicarFisica();
        void moverAdelante();
        void moverAtras();
        //void saltar();
        void cambiarEstado(int nuevoEstado);

};

#endif // ENEMIGO_H
