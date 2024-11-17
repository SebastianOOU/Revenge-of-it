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

        bool moverIz, moverDe, moverAr;

        QGraphicsView *vista;

        QTimer *timermovimiento;
        bool enElAire;
        int velocidadY;

        vector <QGraphicsRectItem *> itemsPlataformas;
        map <int,int> posicionPlatafromas;

    public slots:

    public:
        Personaje(QGraphicsView *vista);
        Personaje();

        void keyPressEvent(QKeyEvent *event);
        void capturarItemsPlataformas(QGraphicsRectItem *, int, int);

        void moverPersonaje(int);
        void camDerecha();
        void camIzquierda();
        void saltar();

        void activarhabilidad();
        void redicirSalud();

        void mostSprite(int);
        void aplicarFisica();

        void verfColisionPlataforma();
        void verficarSobrePlataforma(int,int &, bool &);


    signals:
        void llegarLimiteScena();

};

#endif // PERSONAJE_H
