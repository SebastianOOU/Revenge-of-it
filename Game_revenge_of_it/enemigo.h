#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "personaje.h"
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>

class Enemigo : public QObject, public QGraphicsPixmapItem{
       Q_OBJECT
    private:
       int altoSprite;
       int anchoSprite;
       int posicionX;
       int posicionY;
       int sprite_x_img;
       int sprite_y_img;
       int contador;
       QPixmap spriteImg;
       QPixmap sprite;
       QTimer *timerMovimiento;
       int estado;
       float velocidadY;
       const float gravedad = 0.5f;
       bool enElAire;
    public:
        Enemigo(int x = 1000, int = 565, int ancho = 70, int alto = 100);
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
