#include "menuniveles.h"
#include "ui_menuniveles.h"
#include <QGraphicsView>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QGraphicsPixmapItem>

menuNiveles::menuNiveles(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::menuNiveles)
{
    ui->setupUi(this);

    menuBotonesNiveles();

}

void menuNiveles::nuevaEscenaNivelJuego(/*int _nivelJuego, int _numScena*/){

    bool nivelBlocked; QString direccionImgFondo;

    NivelJuego nuevoNivel(_nivelJuego);
    nuevoNivel.extraerDatosJugador();

    nivelBlocked = nuevoNivel.getNivelBlocked();
    direccionImgFondo = QString::fromStdString(nuevoNivel.getDireccionFondo());

    if(nivelBlocked){
        //FALTA PARA MOSTRAR UN MENSAJE POR PANTALLA E INFORMARLE AL USUARIO
        return;
    }

    QGraphicsScene *escenaNivelJuego = new QGraphicsScene();
    escenaNivelJuego->setSceneRect(0,0,1280,720);
    ui->graphicsView->setScene(escenaNivelJuego);

    QPixmap imagenFondo(direccionImgFondo);

    QGraphicsPixmapItem *imagenFondoJuego = new QGraphicsPixmapItem(imagenFondo);
    escenaNivelJuego->addItem(imagenFondoJuego);

    nuevoPersonaje = new Personaje(ui->graphicsView);
    escenaNivelJuego->addItem(nuevoPersonaje);
    nuevoPersonaje->setPos(60,75);
    nuevoPersonaje->setFocus();

    Enemigo *nuevoEnemigo = new Enemigo(ui->graphicsView);
    nuevoEnemigo->setPos(800,550);
    escenaNivelJuego->addItem(nuevoEnemigo);

    Obstaculos nuevoObstaculo;
    nuevoObstaculo.extraerDatosSprites(_nivelJuego,_numScena);

    QBrush brushObstaculo(QImage(":/spritesIMG/obstaculo_bloques.png"));

    QPen pen(Qt::gray, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    for(auto& posiciones : nuevoObstaculo.datosSprites){

        QGraphicsRectItem *plataformaObs = new QGraphicsRectItem(posiciones.first,posiciones.second,200,40);

        plataformaObs->setBrush(brushObstaculo);
        plataformaObs->setPen(pen);
        escenaNivelJuego->addItem(plataformaObs);

        nuevoPersonaje->capturarItemsPlataformas(plataformaObs, posiciones.first, posiciones.second);
    }

    connect(nuevoPersonaje, &Personaje::llegarLimiteScena,this,&menuNiveles::cambioEscenaDentroNivelJuego);
}

void menuNiveles::cambioEscenaDentroNivelJuego(){

    _numScena = 2;

    for(QGraphicsItem *item : this->ui->graphicsView->scene()->items()){
        if(QGraphicsPixmapItem *bstaculos = dynamic_cast<QGraphicsPixmapItem*>(item)){
            this->ui->graphicsView->scene()->removeItem(bstaculos);
        }
    }

    nuevaEscenaNivelJuego();
}

menuNiveles::~menuNiveles()
{
    delete ui;
}

void menuNiveles::menuBotonesNiveles(){

    QGraphicsScene *escenaMenuNiveles  = new QGraphicsScene();
    escenaMenuNiveles->setSceneRect(0,0,1280,720);
    ui->graphicsView->setScene(escenaMenuNiveles);

    QPushButton *botonNivel1 = new QPushButton("Nivel 1");

    /*botonNivel1->setStyleSheet("QPushButton {"
                               //"background-color: #4CAF50;"   //Diseño css para el boton
                               "color: white;"
                               "border: 2px solid #3e8e41;"
                               "border-radius: 10px;"
                               "font-size: 16px;"
                               "padding: 10px;"
                               "}");*/

    QGraphicsProxyWidget *convBotonNivel1 = escenaMenuNiveles->addWidget(botonNivel1);
    convBotonNivel1->setPos(450,300);
    escenaMenuNiveles->addItem(convBotonNivel1);

    QPushButton *botonNivel2 = new QPushButton("Nivel 2");

    QGraphicsProxyWidget *convBotonNivel2 = escenaMenuNiveles->addWidget(botonNivel2);
    convBotonNivel2->setPos(550,300);
    escenaMenuNiveles->addItem(convBotonNivel2);

    QPushButton *botonNivel3 = new QPushButton("Nivel 3");

    QGraphicsProxyWidget *convBotonNivel3 = escenaMenuNiveles->addWidget(botonNivel3);
    convBotonNivel3->setPos(650,300);
    escenaMenuNiveles->addItem(convBotonNivel3);

    escenaMenuNiveles->removeItem(convBotonNivel3);

    _nivelJuego = 1;
    _numScena = 1;

    connect(botonNivel1, &QPushButton::clicked, this, &menuNiveles::nuevaEscenaNivelJuego);
}
