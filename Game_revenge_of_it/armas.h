#ifndef ARMAS_H
#define ARMAS_H

#include <QTimer>
#include <QObject>
#include <QPixmap>
#include <QGraphicsEllipseItem>
#include <QGraphicsView>

class Armas : public QObject, public QGraphicsPixmapItem {
        Q_OBJECT
    private:

        QPixmap spriteExplosion;
        QPixmap explosion;
        QTimer *timerExplosion;

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

    public:
        Armas(QGraphicsView *, bool, bool);

        void lanzarArma(qreal,qreal);
        void moverArma();

        void actiAnimExplocion();
        void mostAnimExplosion();

        void detectarChoque();
        void mostrarSpritExplosion();

};

#endif // ARMAS_H
