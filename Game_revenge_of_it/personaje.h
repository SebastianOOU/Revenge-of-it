#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsRectItem>
using namespace  std;

class Personaje : public QObject, public QGraphicsPixmapItem {

    Q_OBJECT
private:
    QPixmap spriteImg;
    QPixmap sprite;

    QPixmap spriteImgVida;
    QPixmap spriteVida;
    string nombre;
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
    int contador = 0;

    QGraphicsView *vista;

    QTimer *timermovimiento;
    bool enElAire;
    int velocidadY;

public slots:

public:
    Personaje(QGraphicsView *vista);
    Personaje();
    bool flechaDe,flechaIz,flechaAr,espacio;
    void keyPressEvent(QKeyEvent *event);
    void moverPersonaje(int);
    void activarhabilidad();
    void camDerecha();
    void camIzquierda();
    void saltar();
    void redicirSalud();
    void mostSprite(int);
    void aplicarFisica();

signals:
    void llegarLimiteScena();

};

#endif // PERSONAJE_H
