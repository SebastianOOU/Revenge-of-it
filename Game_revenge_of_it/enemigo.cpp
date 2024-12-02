#include "enemigo.h"

Enemigo::Enemigo(QGraphicsView *_vista,int _nivelJuego,int posX,int posY,int tamañoSuelo) : vista(_vista){

    setContador(0);

    setAltoSprite(60);
    setAnchoSprite(45);

    setSprite_x_img(0);
    setSprite_y_img(0);

    setPosicionX(posX);
    setPosicionY(posY);

    setMoverDe(true);
    setMoverIz(false);

    totalSuelo = tamañoSuelo - 20;
    posicionIncial = posX - 20;

    int velocidad = 0;
    //Segun el nivel del juego, la velocidad de movimento es diferente
    if(_nivelJuego == 1){ velocidad = 120; }

    else if(_nivelJuego== 2){ velocidad = 100; }

    else if(_nivelJuego == 3){ velocidad = 80; }

    spriteImg.load(":/spritesIMG/Captura_de_pantalla-removebg-preview.png");

    sprite = spriteImg.copy(getSprite_x_img(),getSprite_y_img(),getAnchoSprite(),getAltoSprite());
    setPixmap(sprite);
    setPos(getPosicionX(),getPosicionY());
    //Timer para el movimiento del enemigo
    timerMovimiento = new QTimer(this);
    connect(timerMovimiento,&QTimer::timeout,this,&Enemigo::actualizarSprite);
    timerMovimiento->start(velocidad);
}

Enemigo::Enemigo(){}

void Enemigo::actualizarSprite(){
    //Se verifican las posicones de los enemigos
    if(getMoverDe()){ moverAdelante();}
    //Evita que salgan de los limites
    if(getPosicionX() >= totalSuelo || getMoverIz()){

        setMoverDe(false);
        moverAtras();
        setMoverIz(true);
    }

    if(getPosicionX() <= posicionIncial){

        setMoverDe(true);
        moverAdelante();
        setMoverIz(false);
    }
}

void Enemigo::mostSprite(int _posicion){

    //Se captura la posicion dentro de la imagen de sprites
    setSprite_y_img(_posicion);
    //Se multiplica por el acho del sprite (mostrar el sprite siguiente)
    setSprite_x_img(getAnchoSprite() * getContador());
    //Toma una porcion de la imagen de sprites (un sprite de la matriz)
    sprite = spriteImg.copy(getSprite_x_img(),getSprite_y_img(),getAnchoSprite(),getAltoSprite());
    //Muestra la porcion de esprite en pantalla
    setPixmap(sprite);
    //Se contabiliza la cantidad de sprites
    setContador(getContador() + 1);
    //Si ya se recorrieron todos los sprites reinicio
    if(getContador() == 4){setContador(0); }
}

void Enemigo::moverAdelante(){

    setPosicionX(getPosicionX() + 5);
    setPos(getPosicionX(), getPosicionY());
    mostSprite(0);
}

void Enemigo::moverAtras(){

    setPosicionX(getPosicionX() - 5);
    setPos(getPosicionX(), getPosicionY());
    mostSprite(60);
}
