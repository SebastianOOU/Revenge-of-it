#ifndef NIVELJUEGO_H
#define NIVELJUEGO_H

#include <QObject>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <vector>
#include <QTimer>
#include <ctime>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <cstdlib>
#include <iostream>
using namespace std;

class NivelJuego{

    private:

        string nombreJugador;

        int nivel;
        int numScena;

        string direccionFondo;
        string direccFondoRects;

        bool nivelBlocked;

    public:

        NivelJuego(int,int);

        void verificarNivel(string);
        void extraerDatosJugador();
        void direccFondoImg();
        string rutaNivel();

        void setDireccionFondo(string);
        void setDireccFonsoRects(string);
        void setNivelBlocked(bool);

        string getDireccionFondo();
        string getDireccFondoRects();
        string getNombreJugador();
        bool getNivelBlocked();

};

#endif // NIVELJUEGO_H
