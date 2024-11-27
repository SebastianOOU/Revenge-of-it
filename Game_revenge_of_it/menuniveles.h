 #ifndef MENUNIVELES_H
#define MENUNIVELES_H

#include <QMainWindow>
#include "niveljuego.h"
#include "personaje.h"
#include "enemigo.h"
#include "enemigoit.h"
#include "obstaculos.h"
#include "juego.h"

namespace Ui {
class menuNiveles;
}

class menuNiveles : public QMainWindow{

        Q_OBJECT

    public:

        explicit menuNiveles(QWidget *parent = nullptr);

        void nuevaEscenaNivelJuego();
        void eliminarGrafico();
        void eliminarObjetosDentroJuego();

        ~menuNiveles();

    private:

        int nivelJuego;
        int numScena;
        bool vida;
        int puntaje = 0;
        string nombreJug;

        Personaje *nuevoPersonaje;
        Personaje *vidaPersonaje;
        QGraphicsTextItem *textValorPun;
        Armas *arma;
        Obstaculos *obsCaja;
        Juego juego;

        QGraphicsScene *escenaNivelJuego;
        QGraphicsTextItem *textValorPuntaje;
        QGraphicsTextItem *textValorBom;

        vector <EnemigoIT *> enemigos;

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

        void actualizarCantBombas();
        void actualizarPunt();

        void nivelSuperadoMost();

    private slots:
};

#endif // MENUNIVELES_H
