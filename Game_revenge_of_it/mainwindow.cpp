#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "personaje.h"
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *escena = new QGraphicsScene(this);
    escena->setSceneRect(0,0,1280,720);
    ui->graphicsView->setScene(escena);

    escena->addItem(personajeJugador);
    personajeJugador->setPos(30,600);//

    personajeJugador->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

