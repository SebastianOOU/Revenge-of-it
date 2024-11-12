#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "personaje.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *escena = new QGraphicsScene(this);
    escena->setSceneRect(0,0,1280,720);
    ui->graphicsView->setScene(escena);

    NivelJuego *nivelJuego = new NivelJuego();
    escena->addItem(nivelJuego);
    nivelJuego->setPos(0,0);

    Personaje *personajeJugador = new Personaje(ui->graphicsView);
    escena->addItem(personajeJugador);
    personajeJugador->setPos(30,565);
    personajeJugador->setFocus();

    Personaje *vida = new Personaje();
    escena->addItem(vida);
    vida->setPos(30,10);

    Enemigo *enemigo = new Enemigo();
    enemigo->setPos(800,565);

    escena->addItem(enemigo);

    Obstaculos obstaculos;
    obstaculos.extraerDatosSprites(1,1);

    /*for(auto& posiciones : obstaculos.datosSprites){

        QGraphicsPixmapItem *obstaculo = new QGraphicsPixmapItem(QPixmap(":/spritesIMG/fondoImgLevel 1.png"));
        obstaculo->setPos(posiciones.first, posiciones.second);
        escena->addItem(obstaculo);
    }*/

    QGraphicsPixmapItem *obstaculo1 = new QGraphicsPixmapItem(QPixmap(":/spritesIMG/obstaculo_bloques.png"));
    obstaculo1->setPos(540, 500);
    escena->addItem(obstaculo1);

    QGraphicsPixmapItem *obstaculo2 = new QGraphicsPixmapItem(QPixmap(":/spritesIMG/obstaculo_bloques.png"));
    obstaculo2->setPos(900, 450);
    escena->addItem(obstaculo2);

    QGraphicsPixmapItem *obstaculo3 = new QGraphicsPixmapItem(QPixmap(":/spritesIMG/obstaculo_bloques.png"));
    obstaculo3->setPos(180, 450);
    escena->addItem(obstaculo3);

    /*QGraphicsRectItem *rectangu1o1 = new QGraphicsRectItem(540, 500, 200,50);
    rectangu1o1->setBrush(Qt::gray);
    escena->addItem(rectangu1o1);

    QGraphicsRectItem *rectangu1o2 = new QGraphicsRectItem(900, 450, 200,50);
    rectangu1o2->setBrush(Qt::gray);
    escena->addItem(rectangu1o2);

    QGraphicsRectItem *rectangu1o3 = new QGraphicsRectItem(180, 450, 200,50);
    rectangu1o3->setBrush(Qt::gray);
    escena->addItem(rectangu1o3);*/


    connect(personajeJugador, &Personaje::llegarLimiteScena,this,&MainWindow::nuevaEscena);
}

void MainWindow::nuevaEscena(){

    for(QGraphicsItem *item : this->ui->graphicsView->scene()->items()){
        if(QGraphicsPixmapItem *bstaculos = dynamic_cast<QGraphicsPixmapItem*>(item)){
            this->ui->graphicsView->scene()->removeItem(bstaculos);
        }
    }

    QGraphicsScene *escena = new QGraphicsScene(this);
    escena->setSceneRect(0,0,1280,720);
    ui->graphicsView->setScene(escena);

    NivelJuego *nivelJuego = new NivelJuego();
    escena->addItem(nivelJuego);
    nivelJuego->setPos(0,0);

    Personaje *personajeJugador = new Personaje(ui->graphicsView);
    escena->addItem(personajeJugador);
    personajeJugador->setPos(30,600);
    personajeJugador->setFocus();

    Personaje *vida = new Personaje();
    escena->addItem(vida);
    vida->setPos(30,10);

    Enemigo *enemigo = new Enemigo();
    enemigo->setPos(800,565);

    escena->addItem(enemigo);

    QGraphicsPixmapItem *bstaculos = new QGraphicsPixmapItem(QPixmap(":/spritesIMG/obstaculo_bloques.png"));
    bstaculos->setPos(540,450);
    escena->addItem(bstaculos);

    QGraphicsPixmapItem *bstaculos2 = new QGraphicsPixmapItem(QPixmap(":/spritesIMG/obstaculo_bloques.png"));
    bstaculos2->setPos(900,400);
    escena->addItem(bstaculos2);

    QGraphicsPixmapItem *bstaculos3 = new QGraphicsPixmapItem(QPixmap(":/spritesIMG/obstaculo_bloques.png"));
    bstaculos3->setPos(180,500);
    escena->addItem(bstaculos3);

}
MainWindow::~MainWindow()
{
    delete ui;
}


