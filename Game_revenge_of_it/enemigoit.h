#ifndef ENEMIGOIT_H
#define ENEMIGOIT_H

#include "enemigo.h"
#include "armas.h"

class EnemigoIT : public Enemigo{
        Q_OBJECT
    private:

        QGraphicsView *vista;
        QTimer *timerMovimiento, *timerArma;

        int estado, nivel;

    public:
        EnemigoIT(QGraphicsView *, int);

        void pausarLanzarBombas();
        void verificarChoqueArma();

        void mostSprite(int);

        void moverAdelante();
        void moverAtras();

        void cambiarEstado(int nuevoEstado);
        void reducirVidaEne();

    public slots:

        void actualizarSprite();
        void activarArma();

    signals:

        void eneminItdead();
        void actuVidaIT();
};

#endif // ENEMIGOIT_H
