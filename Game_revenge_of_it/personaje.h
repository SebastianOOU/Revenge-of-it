#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsRectItem>
#include <vector>
#include <map>
#include <QMediaPlayer>
#include <QUrl>
#include <QAudioOutput>
#include "armas.h"
using namespace  std;

class Personaje : public QObject, public QGraphicsPixmapItem {

        Q_OBJECT
    private:
        QMediaPlayer *musicaGolpeArma;
        QAudioOutput *volumen;
        QGraphicsView *vista;

        QPixmap spriteImgVida, spriteVida;

        int puntaje;
        //Dimensiones del sprite a mostrar.
        int altoSprite;
        int anchoSprite;
        //Posiciones del sprite en la pantalla.
        qreal posicionX;
        qreal posicionY;
        //Posiciones del sprite en la imagen de sprites
        int sprite_x_img;
        int sprite_y_img;
        //Salud del personaje (vidas)
        int salud;
        //Contar la cantidad de sprites que se debe mostrar
        int contador;
        int contadorArmas;

        bool moverIz, moverDe, moverAr;

        QTimer *choqueEnemigoAma;
        QTimer *timermovimiento;
        QTimer *timerMoverPersonaje;
        QTimer *timerDetectarColItems;

        bool enElAire;
        int velocidadY;

    public:
        Personaje();
        Personaje(QGraphicsView *vista,int);

        vector <QGraphicsRectItem *> itemsPlataformas;
        map <int,map<int,int>> posicionPlataformas;

        QPixmap spriteImg, sprite;

        void keyPressEvent(QKeyEvent *event);
        void keyReleaseEvent(QKeyEvent *event);
        void capturarItemsPlataformas(QGraphicsRectItem *, int, int, int);

        void camDerecha();
        void camIzquierda();
        void saltar();

        void activarhabilidad();
        void activarArma();
        void redicirSalud();

        void mostSprite(int);
        void mostSpriteVida(int);

        void verfColisionPlataforma();
        void verficarSobrePlataforma(bool &, int &);
        void stopTimers();

        void setAltoSprite(int);
        void setAnchoSprite(int);
        void setPosicionX(qreal);
        void setPosicionY(qreal);
        void setSprite_x_img(int);
        void setSprite_y_img(int);
        void setSalud(int);
        void setContador(int);
        void setMoverIz(bool);
        void setMoverDe(bool);
        void setBombas(int);
        void setEnElAire(bool);
        void setPuntaje(int);

        int getAltoSprite();
        int getAnchoSprite();
        qreal getPosicionX();
        qreal getPosicionY();
        int getSprite_x_img();
        int getSprite_y_img();
        int getSalud();
        int getContador();
        bool getMoverIz();
        bool getMoverDe();
        int getBombas();
        bool getEnElAire();
        int getPuntaje();

    public slots:

        void aplicarFisica();
        void detectarColisionItemsScena();
        void moverPersonaje();
        void actualizarPunt();
        void detectarColisionArma();

    signals:

        void llegarLimiteScena();
        void personajeSinSalud();
        void reducirVida();
        void actuPuntInter();
        void actualizarNumBombas();
};

#endif // PERSONAJE_H
