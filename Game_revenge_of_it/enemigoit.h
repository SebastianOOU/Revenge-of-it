#ifndef ENEMIGOIT_H
#define ENEMIGOIT_H

#include "enemigo.h"
#include "armas.h"

class EnemigoIT : public Enemigo{

    private:
        QPixmap spriteImg;
        QPixmap sprite;

        float posicionX;
        float posicionY;

        QGraphicsView *vista;

        QTimer *timerMovimiento;
        QTimer *timerArma;

        int estado;
        int contador;

    public:
        EnemigoIT(QGraphicsView *);
        void pausarLanzarBombas();

    public slots:
        void actualizarSprite();
        void mostSprite(int);
        //void aplicarFisica();
        void moverAdelante();
        void moverAtras();
        //void saltar();
        void cambiarEstado(int nuevoEstado);

        void activarArma();
};

#endif // ENEMIGOIT_H
