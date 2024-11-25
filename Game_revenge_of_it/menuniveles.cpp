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

    vida = false;

    escenaNivelJuego = new QGraphicsScene();
    escenaNivelJuego->setSceneRect(0,0,1280,720);
    ui->graphicsView->setScene(escenaNivelJuego);

    menuBotonesNiveles();
}

void menuNiveles::nuevaEscenaNivelJuego(/*int _nivelJuego, int _numScena*/){

    bool nivelBlocked; QString direccionImgFondo; string rutaNivel;

    NivelJuego nuevoNivel(_nivelJuego);
    nuevoNivel.extraerDatosJugador();

    nivelBlocked = nuevoNivel.getNivelBlocked();
    rutaNivel = nuevoNivel.rutaNivel();
    direccionImgFondo = QString::fromStdString(nuevoNivel.getDireccionFondo());

    if(nivelBlocked){
        //FALTA PARA MOSTRAR UN MENSAJE POR PANTALLA E INFORMARLE AL USUARIO
        return;
    }

    QPixmap imagenFondo(direccionImgFondo);

    if(_numScena != 2){

        QGraphicsPixmapItem *imagenFondoJuego = new QGraphicsPixmapItem(imagenFondo);
        escenaNivelJuego->addItem(imagenFondoJuego);
    }

    nuevoPersonaje = new Personaje(ui->graphicsView);
    this->ui->graphicsView->scene()->addItem(nuevoPersonaje);
    nuevoPersonaje->setPos(60,75);
    nuevoPersonaje->setFocus();

    if(!vida){

        vidaPersonaje = new Personaje();
        this->ui->graphicsView->scene()->addItem(vidaPersonaje);
        vidaPersonaje->setPos(10,5);
        vida = true;
    }

    if(_numScena == 2){

        EnemigoIT *nuevoEnemigo = new EnemigoIT(ui->graphicsView);
        nuevoEnemigo->setPos(800,550);
        this->ui->graphicsView->scene()->addItem(nuevoEnemigo);

        enemigos.push_back(nuevoEnemigo);
    }

    Obstaculos *nuevoObstaculo = new Obstaculos(rutaNivel, _numScena);
    nuevoObstaculo->extraerDatosSprites();
    nuevoObstaculo->extraerDatosEnenim();

    QBrush brushObstaculo(QImage(":/spritesIMG/obstaculo_bloques.png"));

    QPen pen(Qt::gray, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    for(const auto& posiciones : nuevoObstaculo->datosSprites){

        for(const auto& datos : posiciones.second){

            QGraphicsRectItem *plataformaObs = new QGraphicsRectItem(posiciones.first,datos.first,datos.second,40);

            plataformaObs->setBrush(brushObstaculo);
            plataformaObs->setPen(pen);
            this->ui->graphicsView->scene()->addItem(plataformaObs);

            nuevoPersonaje->capturarItemsPlataformas(plataformaObs, posiciones.first, datos.first, datos.second);
        }
    }

    for(auto& posiciones : nuevoObstaculo->datosEnemigo){

        for(auto& datos : posiciones.second){

            Enemigo *nemigo = new Enemigo(ui->graphicsView,posiciones.first,datos.second,datos.first);
            nemigo->setPos(posiciones.first,datos.second);
            this->ui->graphicsView->scene()->addItem(nemigo);
            nuevoPersonaje->capturarEnemigos(nemigo);

            enemigos.push_back(nemigo);
        }
    }

    connect(nuevoPersonaje, &Personaje::llegarLimiteScena,this,&menuNiveles::cambioEscenaDentroNivelJuego);
    connect(nuevoPersonaje, &Personaje::reducirVida,this,&menuNiveles::reducirVidas);
    connect(vidaPersonaje, &Personaje::personajeSinSalud, this, &menuNiveles::mostGameOver);
}

void menuNiveles::cambioEscenaDentroNivelJuego(){

    _numScena = 2;

   /*for(QGraphicsItem *item : this->ui->graphicsView->scene()->items()){
        if(QGraphicsProxyWidget *bstaculos = dynamic_cast<QGraphicsProxyWidget*>(item)){
            this->ui->graphicsView->scene()->removeItem(bstaculos);
            delete bstaculos;
        }
    }*/

    eliminarObjetos();

    //mostGameOver();

    nuevaEscenaNivelJuego();
}

void menuNiveles::eliminarObjetos(){

     auto i = enemigos.begin();

    while(i != enemigos.end()){

        this->ui->graphicsView->scene()->removeItem(*i);

        qDebug() << "Eliminado de la scena";
        delete *i;
        qDebug() << "Eliminado de la memoria";

        i = enemigos.erase(i);
    }

    this->ui->graphicsView->scene()->removeItem(nuevoPersonaje);

}

void menuNiveles::menuBotonesNiveles(){

    /*QGraphicsScene *escenaMenuNiveles  = new QGraphicsScene();
    escenaMenuNiveles->setSceneRect(0,0,1280,720);
    ui->graphicsView->setScene(escenaMenuNiveles);*/

    QPixmap imagenFondo(":/imgNiveles/Revenge of it.png");

    QGraphicsPixmapItem *imagenFondoOver = new QGraphicsPixmapItem(imagenFondo);
    this->ui->graphicsView->scene()->addItem(imagenFondoOver);

    string arrayNom[3] = {"Nivel 1", "Nivel 2", "Nivel 3"};
    vector <QPushButton *> botonesNiveles;

    for(int i = 1; i <= 3; i++){

        QPushButton *botonNivel = new QPushButton(QString::fromStdString(arrayNom[i - 1]));

        botonNivel->setStyleSheet("QPushButton {" "background-color: #808b96;" "border: none;" "color: white;"
                                  "font-size: 20px;" "padding: 10px 30px;" "}");

        botonesNiveles.push_back(botonNivel);

        QGraphicsProxyWidget *convBotonNivel = this->ui->graphicsView->scene()->addWidget(botonNivel);
        convBotonNivel->setPos(290 * i,490);
        this->ui->graphicsView->scene()->addItem(convBotonNivel);
    }

    _nivelJuego = 1;
    _numScena = 1;


    connect(botonesNiveles[0], &QPushButton::clicked,this,&menuNiveles::cambioNivel1);
    connect(botonesNiveles[1], &QPushButton::clicked,this,&menuNiveles::cambioNivel2);
    connect(botonesNiveles[2], &QPushButton::clicked,this,&menuNiveles::cambioNivel3);

}

void menuNiveles::mostGameOver(){

    eliminarObjetos();

    qDebug() << "Buenas tardes";

    QPixmap imagenFondo(":/imgNiveles/GameOver.png");

    qDebug() << "Buenas tardes1";

    QGraphicsPixmapItem *imagenFondoOver = new QGraphicsPixmapItem(imagenFondo);
    escenaNivelJuego->addItem(imagenFondoOver);

    qDebug() << "Buenas tardes2";

    QFont font1("Arial",20, QFont::Bold);

    qDebug() << "Buenas tardes3";

    QGraphicsTextItem *textScore = new QGraphicsTextItem("Score:");
    textScore->setPos(150, 350);
    textScore->setFont(font1);
    this->ui->graphicsView->scene()->addItem(textScore);

    qDebug() << "Buenas tardes4";

    QFont font2("Arial",20);

    QString nom = "Sebastian, ¡tú salud se ha terminado!";

    QGraphicsTextItem *textInformacion = new QGraphicsTextItem(nom);
    textInformacion->setPos(150, 250);
    textInformacion->setFont(font2);
    this->ui->graphicsView->scene()->addItem(textInformacion);

    qDebug() << "Buenas tardes5";

    QPushButton *botonAceptar = new QPushButton("Aceptar",this);

    botonAceptar->setStyleSheet("QPushButton {" "color: white;" "border: 3px solid white;" "border-radius: 10px;"
                                "font-size: 20px;" "padding: 10px 30px;""}");
    qDebug() << "Buenas tardes6";

    QGraphicsProxyWidget *convBotonAceptar = this->ui->graphicsView->scene()->addWidget(botonAceptar);
    convBotonAceptar->setPos(350,420);
    this->ui->graphicsView->scene()->addItem(convBotonAceptar);

    qDebug() << "Buenas tardes buenas";

    connect(botonAceptar, &QPushButton::clicked,this,&menuNiveles::menuBotonesNiveles);

    vida = false;

    qDebug() << "Buenas tardes buenas trgfghyh";
}

void menuNiveles::cambioNivel1(){

    _nivelJuego = 1;
    _numScena = 1;

    nuevaEscenaNivelJuego();
}

void menuNiveles::cambioNivel2(){

    _nivelJuego = 2;
    _numScena = 1;

    nuevaEscenaNivelJuego();
}

void menuNiveles::cambioNivel3(){

    _nivelJuego = 3;
    _numScena = 1;

    nuevaEscenaNivelJuego();
}

void menuNiveles::reducirVidas(){

    vidaPersonaje->mostSpriteVida();
}

menuNiveles::~menuNiveles()
{
    delete ui;
    //delete nuevoEnemigo;
   // delete nuevoPersonaje;
}
