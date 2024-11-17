#include "nivel1.h"
#include "ui_nivel1.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QImage>
#include <QBrush>

Nivel1::Nivel1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Nivel1)
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

    QBrush brush(QImage(":/spritesIMG/obstaculo_bloques.png"));

    QPen pen(Qt::gray, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    for(auto& posiciones : obstaculos.datosSprites){

        QGraphicsRectItem *obstaculo = new QGraphicsRectItem(posiciones.first,posiciones.second,200,40);
        obstaculo->setBrush(brush);
        obstaculo->setPen(pen);
        personajeJugador->capturarItemsPlataformas(obstaculo, posiciones.first, posiciones.second);

        escena->addItem(obstaculo);
    }

    connect(personajeJugador, &Personaje::llegarLimiteScena,this,&Nivel1::nuevaEscena);

}

void Nivel1::nuevaEscena(){

    for(QGraphicsItem *item : this->ui->graphicsView->scene()->items()){
        if(QGraphicsRectItem *bstaculos = dynamic_cast<QGraphicsRectItem*>(item)){
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
    personajeJugador->setPos(30,565);
    personajeJugador->setFocus();

    Personaje *vida = new Personaje();
    escena->addItem(vida);
    vida->setPos(30,10);

    Enemigo *enemigo = new Enemigo();
    enemigo->setPos(800,565);

    escena->addItem(enemigo);

    Obstaculos obstaculos;
    obstaculos.extraerDatosSprites(1,2);

    QBrush brush(QImage(":/spritesIMG/obstaculo_bloques.png"));

    QPen pen(Qt::gray, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    for(auto& posiciones : obstaculos.datosSprites){

        QGraphicsRectItem *obstaculo = new QGraphicsRectItem(posiciones.first,posiciones.second,200,40);
        obstaculo->setBrush(brush);
        obstaculo->setPen(pen);
        personajeJugador->capturarItemsPlataformas(obstaculo, posiciones.first, posiciones.second);

        escena->addItem(obstaculo);
    }
}
Nivel1::~Nivel1()
{
    delete ui;
}
