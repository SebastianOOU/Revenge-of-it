#ifndef NIVELJUEGO_H
#define NIVELJUEGO_H

#include <QObject>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <iostream>
using namespace std;

class NivelJuego{

    private:

        int nivel;
        string direccionFondo;

        bool nivelBlocked;

        int altoImgFondo;
        int anchoImgFondo;

    public:

        NivelJuego(int);

        void verificarNivel(string);
        void extraerDatosJugador();

        void setDireccionFondo(string);
        void setNivelBlocked(bool);

        string getDireccionFondo();
        bool getNivelBlocked();
};

#endif // NIVELJUEGO_H
