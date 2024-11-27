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
#include "armas.h"
using namespace  std;

class Personaje : public QObject, public QGraphicsPixmapItem {

        Q_OBJECT
    private:
       // Armas *nuevaArma ;
        QGraphicsView *vista;

        QPixmap spriteImg;
        QPixmap sprite;

        QPixmap spriteImgVida;
        QPixmap spriteVida;

        string nombre;
        //Dimensiones del sprite a mostrar.
        int altoSprite;
        int anchoSprite;
        //Posiciones del sprite en la pantalla.
        float posicionX;
        float posicionY;
        //Posiciones del sprite en la imagen de sprites
        int sprite_x_img;
        int sprite_y_img;
        //Salud del personaje (vidas)
        int salud;
        //Contar la cantidad de sprites que se debe mostrar
        int contador = 0;
        int contadorArmas;

        //QGraphicsRectItem *vidaPersonaje;
        bool a = true;
        bool moverIz, moverDe, moverAr;

        QTimer *choqueEnemigoAma;
        QTimer *timermovimiento;
        bool enElAire;
        int velocidadY;



        vector <QGraphicsRectItem *> itemsPlataformas;


    public:
        Personaje(QGraphicsView *vista,int);
        Personaje();
        vector <QGraphicsPixmapItem *> enemigos;
        void vaciarvector();
        map <int,map<int,int>> posicionPlatafromas;

        void keyPressEvent(QKeyEvent *event);
        void capturarItemsPlataformas(/*QGraphicsRectItem *,*/ int, int, int);
        void capturarEnemigos(QGraphicsPixmapItem *);

        void moverPersonaje(int);
        void camDerecha();
        void camIzquierda();
        void saltar();

        void activarhabilidad();
        void activarArma();
        void redicirSalud();

        void mostSprite(int);
        void mostSpriteVida(int);
        void aplicarFisica();

        void verfColisionPlataforma();
        void verficarSobrePlataforma(int,int &, bool &);

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
        void setSpriteImg(QPixmap);
        void setSprite(QPixmap);

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
        QPixmap getSpriteImg();
        QPixmap getSprite();

    signals:
        void llegarLimiteScena();
        void personajeSinSalud();
        void reducirVida();
        void reducirBombas();
        void actualizarPuntaje();

    public slots:
        void detectarChoqueArma();
};

#endif // PERSONAJE_H
