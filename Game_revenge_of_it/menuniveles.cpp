#include "menuniveles.h"
#include "ui_menuniveles.h"
#include <QGraphicsView>

menuNiveles::menuNiveles(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::menuNiveles)
{
    ui->setupUi(this);
}

menuNiveles::~menuNiveles()
{
    delete ui;
}

void menuNiveles::on_pushButton_clicked(){

    Nivel1 *nivel1 = new Nivel1(this);
    nivel1->setWindowTitle("Revenge of it/Nivel 1");
    nivel1->show();

}

