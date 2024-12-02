#include "menuniveles.h"
#include "ui_menuniveles.h"
#include <QGraphicsView>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QGraphicsPixmapItem>
#include <QMessageBox>

menuNiveles::menuNiveles(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::menuNiveles)
{
    ui->setupUi(this);

    nivelJuego = 0;
    puntaje = 0;
    numScena = 0;

    escenaNivelJuego = new QGraphicsScene();
    escenaNivelJuego->setSceneRect(0,0,1280,720);
    ui->graphicsView->setScene(escenaNivelJuego);
    escenaNivelJuego->setBackgroundBrush(Qt::black);

    musicaFondo = new QMediaPlayer(this);
    musicaFondo->setSource(QUrl("qrc:/sonidos/musicaFondo.mp3"));
    volumen = new QAudioOutput(this);
    volumen->setVolume(0.8);
    musicaFondo->setAudioOutput(volumen);
    musicaFondo->setLoops(QMediaPlayer::Infinite);

    juego.extraerPuntaje();

    menuBotonesNiveles();

    timer = new QTimer(this);

    connect(timer,&QTimer::timeout, this,&menuNiveles::createAndMoveEllipse);
}

void menuNiveles::nuevaEscenaNivelJuego(){

    bool nivelBlocked; QString direccionImgFondo, rutFondoRects; string rutaNivel;

    NivelJuego nuevoNivel(nivelJuego, numScena);
    nuevoNivel.extraerDatosJugador();

    nivelBlocked = nuevoNivel.getNivelBlocked();
    rutaNivel = nuevoNivel.rutaNivel();
    direccionImgFondo = QString::fromStdString(nuevoNivel.getDireccionFondo());
    rutFondoRects = QString::fromStdString(nuevoNivel.getDireccFondoRects());
    nombreJug = nuevoNivel.getNombreJugador();

    try{
        //Verifica si el nivel esta bloqueado
        if(nivelBlocked){
            menuBotonesNiveles();
            throw 1;
        }else{
            musicaFondo->play();
        }

    }catch(int errorBlock){

        if(errorBlock == 1){

            QMessageBox *mensajeError = new QMessageBox(this);
            mensajeError->setText("¡Nivel bloqueado!");
            mensajeError->setInformativeText("Por favor, supera el nivel anterior.");
            mensajeError->exec();
            menuBotonesNiveles();
            return;
        }
    }

    QPixmap imagenFondo(direccionImgFondo);
    QFont font("Arial",20, QFont::Bold);

    escenaNivelJuego->setBackgroundBrush(imagenFondo);

    if(numScena != 2){

        nuevoPersonaje = new Personaje(ui->graphicsView,numScena);
        nuevoPersonaje->setPuntaje(juego.getPuntaje());
        this->ui->graphicsView->scene()->addItem(nuevoPersonaje);
        nuevoPersonaje->setPos(60,75);
        nuevoPersonaje->setFocus();

        connect(nuevoPersonaje, &Personaje::llegarLimiteScena,this,&menuNiveles::cambioEscenaDentroNivelJuego);
        connect(nuevoPersonaje, &Personaje::reducirVida,this,&menuNiveles::reducirVidas);
        connect(nuevoPersonaje, &Personaje::actuPuntInter, this, &menuNiveles::actualizarPunt);
        connect(nuevoPersonaje, &Personaje::actualizarNumBombas, this, &menuNiveles::actualNumBombas);

        vidaPersonaje = new Personaje();
        this->ui->graphicsView->scene()->addItem(vidaPersonaje);
        vidaPersonaje->setPos(10,5);

        connect(vidaPersonaje, &Personaje::personajeSinSalud, this, &menuNiveles::mostGameOver);

        QGraphicsTextItem *textScore = new QGraphicsTextItem("Score : ");
        this->ui->graphicsView->scene()->addItem(textScore);
        textScore->setPos(20,80);
        textScore->setFont(font);

        textValorPun = new QGraphicsTextItem(QString::number(nuevoPersonaje->getPuntaje()));
        textValorPun->setPos(130,80);
        textValorPun->setFont(font);
        this->ui->graphicsView->scene()->addItem(textValorPun);

        QGraphicsTextItem *textBombas = new QGraphicsTextItem("Bombas : ");
        this->ui->graphicsView->scene()->addItem(textBombas );
        textBombas->setPos(20,120);
        textBombas->setFont(font);

        textValorBom = new QGraphicsTextItem(QString::number(nuevoPersonaje->getBombas()));
        textValorBom->setPos(160,120);
        textValorBom->setFont(font);
        this->ui->graphicsView->scene()->addItem(textValorBom);

        QGraphicsTextItem *textNivel = new QGraphicsTextItem("Nivel " + QString::number(nivelJuego));
        this->ui->graphicsView->scene()->addItem(textNivel);
        textNivel->setPos(600,20);
        textNivel->setFont(font);

        QPushButton *botonMenu = new QPushButton("Salir");

        botonMenu->setStyleSheet("QPushButton {" "color: white;" "font-size: 15px;" "padding: 10px 20px;" "}");

        QGraphicsProxyWidget *convBotonMenu = this->ui->graphicsView->scene()->addWidget(botonMenu);
        convBotonMenu->setPos(400,10);
        this->ui->graphicsView->scene()->addItem(convBotonMenu);

        connect(botonMenu, &QPushButton::clicked,this,&menuNiveles::nuevoMenu);

        timer->start(2500);

    }else{

        timer->stop();

        nuevoEnemigo = new EnemigoIT(ui->graphicsView, nivelJuego);
        nuevoEnemigo->setPos(880,280);
        this->ui->graphicsView->scene()->addItem(nuevoEnemigo);

        connect(nuevoEnemigo, &EnemigoIT::eneminItdead, this, &menuNiveles::nivelSuperadoMost);

        if(nivelJuego == 2){

            QGraphicsTextItem *textVidaIT = new QGraphicsTextItem("IT : ");
            this->ui->graphicsView->scene()->addItem(textVidaIT);
            textVidaIT->setPos(1000,20);
            textVidaIT->setFont(font);

            textVidaIt = new QGraphicsTextItem(QString::number(nuevoEnemigo->getSalud()));
            this->ui->graphicsView->scene()->addItem(textVidaIt );
            textVidaIt ->setPos(1060,20);
            textVidaIt ->setFont(font);

            connect(nuevoEnemigo, &EnemigoIT::actuVidaIT, this, &menuNiveles::actuVidaEneIT);
        }
    }

    if(numScena == 2 && nivelJuego == 1){

        obsCaja = new Obstaculos(ui->graphicsView,nivelJuego);
        this->ui->graphicsView->scene()->addItem(obsCaja );
        obsCaja ->setPos(980,350);

        connect(obsCaja, &Obstaculos::nivelSuperado, this,&menuNiveles::nivelSuperadoMost);

    }else if (numScena == 2 && nivelJuego == 3){

        obsCaja = new Obstaculos(ui->graphicsView,nivelJuego);
        this->ui->graphicsView->scene()->addItem(obsCaja );
        obsCaja ->setPos(800,80);

        connect(obsCaja, &Obstaculos::nivelSuperado, this,&menuNiveles::nivelSuperadoMost);
    }

    Obstaculos *nuevoObstaculo = new Obstaculos(rutaNivel, numScena);
    nuevoObstaculo->extraerDatosSprites();
    nuevoObstaculo->extraerDatosEnenim();

    QPixmap imgObstaculo(rutFondoRects);

    QPen pen(Qt::gray, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    for(const auto& posiciones : nuevoObstaculo->datosSprites){

        for(const auto& datos : posiciones.second){

            QGraphicsRectItem *plataformaObs = new QGraphicsRectItem(posiciones.first,datos.first,datos.second,40);

            plataformaObs->setBrush(imgObstaculo);
            plataformaObs->setPen(pen);
            this->ui->graphicsView->scene()->addItem(plataformaObs);

            nuevoPersonaje->capturarItemsPlataformas(plataformaObs,posiciones.first, datos.first, datos.second);
        }
    }

    for(auto& posiciones : nuevoObstaculo->datosEnemigo){

        for(auto& datos : posiciones.second){

            Enemigo *nemigo = new Enemigo(ui->graphicsView,nivelJuego,posiciones.first,datos.second,datos.first);
            nemigo->setPos(posiciones.first,datos.second);
            this->ui->graphicsView->scene()->addItem(nemigo);
        }
    }
}

void menuNiveles::cambioEscenaDentroNivelJuego(){

    numScena = 2;

    eliminarObjetosDentroJuego();
    nuevaEscenaNivelJuego();
}

void menuNiveles::eliminarGrafico(){

    for(QGraphicsItem *itemGraf : this->ui->graphicsView->scene()->items()){

        if(QGraphicsProxyWidget *itemBoton = dynamic_cast<QGraphicsProxyWidget*>(itemGraf)){

            this->ui->graphicsView->scene()->removeItem(itemBoton);

        }else if(QGraphicsTextItem *textoGraf = dynamic_cast<QGraphicsTextItem*>(itemGraf)){

            this->ui->graphicsView->scene()->removeItem(textoGraf);

        }else if(QGraphicsPixmapItem *imgGraf = dynamic_cast<QGraphicsPixmapItem*>(itemGraf)){

            this->ui->graphicsView->scene()->removeItem(imgGraf);
        }
    }
}

void menuNiveles::eliminarObjetosDentroJuego(){

    for(QGraphicsItem *itemObje : this->ui->graphicsView->scene()->items()){

        if(QGraphicsRectItem *objeRect = dynamic_cast<QGraphicsRectItem *>(itemObje)){

            this->ui->graphicsView->scene()->removeItem(objeRect);

        }else if(Enemigo *objEnemin = dynamic_cast<Enemigo*>(itemObje)){

            this->ui->graphicsView->scene()->removeItem(objEnemin);
        }
    }
    nuevoPersonaje->posicionPlataformas.clear();
    nuevoPersonaje->itemsPlataformas.clear();
}

void menuNiveles::eliminarObjetos(){

    timer->stop();

    nuevoPersonaje->itemsPlataformas.clear();
    nuevoPersonaje->posicionPlataformas.clear();
    nuevoPersonaje->stopTimers();
    puntaje = nuevoPersonaje->getPuntaje();
    this->ui->graphicsView->scene()->removeItem(nuevoPersonaje);
    this->ui->graphicsView->scene()->removeItem(vidaPersonaje);


    for(QGraphicsItem *objScena : this->ui->graphicsView->scene()->items()){

        if(EnemigoIT *enemigoIT = dynamic_cast<EnemigoIT *>(objScena)){

            enemigoIT->pausarLanzarBombas();

            this->ui->graphicsView->scene()->removeItem(enemigoIT);

        }else if(Enemigo *enemigo = dynamic_cast<Enemigo*>(objScena)){

            enemigo->timerMovimiento->stop();

            this->ui->graphicsView->scene()->removeItem(enemigo);

        }else if(QGraphicsRectItem *objRect = dynamic_cast<QGraphicsRectItem*>(objScena)){

            this->ui->graphicsView->scene()->removeItem(objRect);

        }else if(Obstaculos *objObs = dynamic_cast<Obstaculos*>(objScena)){

            this->ui->graphicsView->scene()->removeItem(objObs);

        }else if(QGraphicsTextItem *textoGraf = dynamic_cast<QGraphicsTextItem*>(objScena)){

            this->ui->graphicsView->scene()->removeItem(textoGraf);

        }else if(QGraphicsEllipseItem *ellipsePun = dynamic_cast<QGraphicsEllipseItem*>(objScena)){

            this->ui->graphicsView->scene()->removeItem(ellipsePun);

        }else if(Armas *bomba = dynamic_cast<Armas *>(objScena)){

            this->ui->graphicsView->scene()->removeItem(bomba);

        }if(QGraphicsProxyWidget *itemBoton = dynamic_cast<QGraphicsProxyWidget*>(objScena)){

            this->ui->graphicsView->scene()->removeItem(itemBoton);
        }
    }
}

void menuNiveles::nuevoMenu(){

    musicaFondo->stop();

    eliminarObjetos();
    eliminarGrafico();
    menuBotonesNiveles();
}
void menuNiveles::menuBotonesNiveles(){

    eliminarGrafico();

    QPixmap imagenFondo(":/imgNiveles/fondoImgNiveles.png");

    escenaNivelJuego->setBackgroundBrush(imagenFondo);

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

    connect(botonesNiveles[0], &QPushButton::clicked,this,&menuNiveles::cambioNivel1);
    connect(botonesNiveles[1], &QPushButton::clicked,this,&menuNiveles::cambioNivel2);
    connect(botonesNiveles[2], &QPushButton::clicked,this,&menuNiveles::cambioNivel3);
}

void menuNiveles::mostGameOver(){

    musicaFondo->stop();

    eliminarObjetos();

    juego.setPuntajeJugador(puntaje);
    juego.setNombreJugador(nombreJug);
    juego.activarJugador(false);

    escenaNivelJuego->setBackgroundBrush(Qt::black);

    QPixmap imagenFondo(":/imgNiveles/GameOver.png");

    QGraphicsPixmapItem *imagenFondoOver = new QGraphicsPixmapItem(imagenFondo);
    escenaNivelJuego->addItem(imagenFondoOver);
    imagenFondoOver->setPos(250,30);

    QFont font1("Arial",20, QFont::Bold);

    QGraphicsTextItem *textScore = new QGraphicsTextItem("Score:");
    textScore->setPos(400, 380);
    textScore->setFont(font1);
    this->ui->graphicsView->scene()->addItem(textScore);

    QFont font2("Arial",20);

    QGraphicsTextItem *textValorScore = new QGraphicsTextItem(QString::number(puntaje));
    textValorScore->setPos(500, 380);
    textValorScore->setFont(font2);
    this->ui->graphicsView->scene()->addItem(textValorScore);

    QString nom = QString::fromStdString(nombreJug) + ", ¡tú salud se ha terminado!";

    QGraphicsTextItem *textInformacion = new QGraphicsTextItem(nom);
    textInformacion->setPos(400, 280);
    textInformacion->setFont(font2);
    this->ui->graphicsView->scene()->addItem(textInformacion);

    QPushButton *botonAceptar = new QPushButton("Aceptar");

    botonAceptar->setStyleSheet("QPushButton {" "color: white;" "border: 3px solid white;" "border-radius: 10px;"
                                "font-size: 20px;" "padding: 10px 30px;""}");

    QGraphicsProxyWidget *convBotonAceptar = this->ui->graphicsView->scene()->addWidget(botonAceptar);
    convBotonAceptar->setPos(580,500);
    this->ui->graphicsView->scene()->addItem(convBotonAceptar);

    connect(botonAceptar, &QPushButton::clicked,this,&menuNiveles::menuBotonesNiveles);
}

void menuNiveles::nivelSuperadoMost(){

    eliminarObjetos();

    musicaFondo->stop();

    if(nivelJuego == 1){ puntaje += 100; }
    else if(nivelJuego == 2){ puntaje += 200; }
    else if(nivelJuego == 3){ puntaje += 300; }

    juego.setPuntajeJugador(puntaje);
    juego.setNombreJugador(nombreJug);
    juego.activarJugador(false);
    juego.actuNivelORdesacJug(true,nivelJuego);

    QPixmap imagenFondo(":/imgNiveles/fondoNivelSuperado.png");

    escenaNivelJuego->setBackgroundBrush(imagenFondo);

    QFont font1("Arial",20, QFont::Bold);

    QFont font2("Arial",20);

    QString nom = QString::fromStdString(nombreJug) + ", ¡Magnifico!";

    QGraphicsTextItem *textInformacion = new QGraphicsTextItem(nom);
    textInformacion->setPos(500, 320);
    textInformacion->setFont(font2);
    this->ui->graphicsView->scene()->addItem(textInformacion);

    QGraphicsTextItem *textScore = new QGraphicsTextItem("Score:");
    textScore->setPos(400, 420);
    textScore->setFont(font1);
    this->ui->graphicsView->scene()->addItem(textScore);

    QGraphicsTextItem *textValorScore = new QGraphicsTextItem(QString::number(puntaje));
    textValorScore->setPos(500, 420);
    textValorScore->setFont(font2);
    this->ui->graphicsView->scene()->addItem(textValorScore);

    QPushButton *botonAceptar = new QPushButton("Aceptar");

    botonAceptar->setStyleSheet("QPushButton {" "color: white;" "border: 3px solid white;" "border-radius: 10px;"
                                "font-size: 20px;" "padding: 10px 30px;""}");

    QGraphicsProxyWidget *convBotonAceptar = this->ui->graphicsView->scene()->addWidget(botonAceptar);
    convBotonAceptar->setPos(580,500);
    this->ui->graphicsView->scene()->addItem(convBotonAceptar);

    connect(botonAceptar, &QPushButton::clicked,this,&menuNiveles::menuBotonesNiveles);
}

void menuNiveles::createAndMoveEllipse(){

    // Crear una elipse en una posición aleatoria en la parte superior
    int xPos = rand() % static_cast<int>(this->ui->graphicsView->scene()->width()); // Posición aleatoria

    QPen pen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(0, 0, 20, 20);

    // Aplicar una textura a la elipse usando QBrush
    QBrush brush(QPixmap(":/spritesIMG/fondoImgEllipse.jpg")); // Reemplaza la ruta con tu imagen
    ellipse->setBrush(brush);
    ellipse->setPen(pen);

    ellipse->setPos(xPos, -50); // Inicia fuera de la pantalla
    this->ui->graphicsView->scene()->addItem(ellipse);

    // Crear un temporizador para mover la elipse hacia abajo
    QTimer *fallingTimer = new QTimer(this); // Asignar al objeto cayendoPuntos como padre
    connect(fallingTimer, &QTimer::timeout, [=]() {
        ellipse->moveBy(0, 5); // Baja 5 píxeles cada vez
        if (ellipse->y() > this->ui->graphicsView->scene()->height()) { // Eliminar si sale de la pantalla
            this->ui->graphicsView->scene()->removeItem(ellipse);
            delete ellipse;
            fallingTimer->stop(); // Detener el temporizador
            fallingTimer->deleteLater(); // Eliminar el temporizador
        }
    });
    fallingTimer->start(25); // Velocidad de caída (25 ms)
}

void menuNiveles::cambioNivel1(){

    nivelJuego = 1;
    numScena = 1;

    eliminarGrafico();

    nuevaEscenaNivelJuego();
}

void menuNiveles::cambioNivel2(){

    nivelJuego = 2;
    numScena = 1;

    eliminarGrafico();

    nuevaEscenaNivelJuego();
}

void menuNiveles::cambioNivel3(){

    nivelJuego = 3;
    numScena = 1;

    eliminarGrafico();

    nuevaEscenaNivelJuego();
}

void menuNiveles::reducirVidas(){

    int _salud = nuevoPersonaje->getSalud();

    vidaPersonaje->mostSpriteVida(_salud);
}

void menuNiveles::actualNumBombas(){

    int bombas = nuevoPersonaje->getBombas();

    textValorBom->setPlainText(QString::number(bombas));
}

void menuNiveles::closeEvent(QCloseEvent *event){

    musicaFondo->stop();

    if(nivelJuego != 0){
        eliminarObjetos();

    }
    event->accept();
}

void menuNiveles::actualizarPunt(){

    int punt = nuevoPersonaje->getPuntaje();

    textValorPun->setPlainText(QString::number(punt));
}

void menuNiveles::actuVidaEneIT(){

    int salud = nuevoEnemigo->getSalud();

    textVidaIt->setPlainText(QString::number(salud));
}
menuNiveles::~menuNiveles(){

    delete ui;
}
