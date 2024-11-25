 #ifndef MENUNIVELES_H
#define MENUNIVELES_H

#include <QMainWindow>
#include "niveljuego.h"
#include "personaje.h"
#include "enemigo.h"
#include "enemigoit.h"
#include "obstaculos.h"

namespace Ui {
class menuNiveles;
}

class menuNiveles : public QMainWindow{

        Q_OBJECT

    public:

        explicit menuNiveles(QWidget *parent = nullptr);

        void nuevaEscenaNivelJuego();



        ~menuNiveles();

    private:

        int _nivelJuego;
        int _numScena;
        bool vida;

        Personaje *nuevoPersonaje;
        Personaje *vidaPersonaje;

        QGraphicsScene *escenaNivelJuego;
        QGraphicsTextItem *textValorPuntaje;

        vector <QGraphicsPixmapItem *> enemigos;

        Ui::menuNiveles *ui;

    public slots:

        void menuBotonesNiveles();

        void cambioNivel1();
        void eliminarObjetos();
        void cambioNivel2();
        void cambioNivel3();

        void cambioEscenaDentroNivelJuego();
        void reducirVidas();
        void mostGameOver();

    private slots:
};

#endif // MENUNIVELES_H
