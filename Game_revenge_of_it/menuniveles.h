 #ifndef MENUNIVELES_H
#define MENUNIVELES_H

#include <QMainWindow>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QUrl>
#include <QAudioOutput>
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
        void closeEvent(QCloseEvent *event);

        ~menuNiveles();

    private:

        QMediaPlayer *musicaFondo;
        QAudioOutput *volumen;

        int nivelJuego;
        int numScena;
        int puntaje;
        string nombreJug;

        QTimer *timer;

        Personaje *nuevoPersonaje;
        Personaje *vidaPersonaje;
        EnemigoIT *nuevoEnemigo;
        QGraphicsTextItem *textValorPun;
        Obstaculos *obsCaja;
        Juego juego;

        QGraphicsScene *escenaNivelJuego;
        QGraphicsTextItem *textValorPuntaje;
        QGraphicsTextItem *textValorBom;
        QGraphicsTextItem *textVidaIt;

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

        void actualNumBombas();
        void actualizarPunt();

        void nivelSuperadoMost();
        void createAndMoveEllipse();

        void actuVidaEneIT();
        void nuevoMenu();

    private slots:
};

#endif // MENUNIVELES_H
