#ifndef NIVEL1_H
#define NIVEL1_H

#include <QMainWindow>
#include "personaje.h"
#include "obstaculos.h"
#include "enemigo.h"
#include "niveljuego.h"

namespace Ui {
class Nivel1;
}

class Nivel1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Nivel1(QWidget *parent = nullptr);
    ~Nivel1();

public slots:
    void nuevaEscena();

private:
    Ui::Nivel1 *ui;
};

#endif // NIVEL1_H
