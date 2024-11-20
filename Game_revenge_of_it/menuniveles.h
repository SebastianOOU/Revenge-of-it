 #ifndef MENUNIVELES_H
#define MENUNIVELES_H

#include <QMainWindow>
#include "niveljuego.h"
#include "personaje.h"
#include "enemigo.h"
#include "obstaculos.h"

namespace Ui {
class menuNiveles;
}

class menuNiveles : public QMainWindow{

        Q_OBJECT

    public:
        explicit menuNiveles(QWidget *parent = nullptr);

        void menuBotonesNiveles();


        ~menuNiveles();

    private:

        int _nivelJuego;
        int _numScena;

        Personaje *nuevoPersonaje;
        QGraphicsTextItem *textValorPuntaje;

        Ui::menuNiveles *ui;

    public slots:

        void cambioEscenaDentroNivelJuego();
        void nuevaEscenaNivelJuego();

    private slots:
};

#endif // MENUNIVELES_H
