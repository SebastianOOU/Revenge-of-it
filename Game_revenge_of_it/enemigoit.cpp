#include "enemigoit.h"

EnemigoIT::EnemigoIT( QGraphicsView *_vista) : vista(_vista) {
    setAltoSprite(100);
    setAnchoSprite(70);

    posicionX = 1000;
    posicionY = 565;

    setMoverDe(false);
    setMoverIz(false);

    contador = 0;

    setSprite_x_img(0);
    setSprite_x_img(0);

    spriteImg.load(":/spritesIMG/movimientoEnemigoIt.png");

    sprite = spriteImg.copy(getSprite_x_img(),getSprite_y_img(),getAnchoSprite(),getAltoSprite());
    setPixmap(sprite);
    setPos(posicionX,posicionY);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento,&QTimer::timeout,this,&EnemigoIT::actualizarSprite);
    timerMovimiento->start(140);

    timerArma = new QTimer(this);
    connect(timerArma,&QTimer::timeout,this,&EnemigoIT::activarArma);
    timerArma->start(3000);

}

void EnemigoIT::actualizarSprite(){

    if (contador % 7 == 0){

        int randomState = rand() % 3;
        cambiarEstado(randomState);
    }

    switch (estado) {
    case 0:
        moverAdelante();
        break;
    case 1:
        moverAtras();
        break;
    default:
        break;
    }
}

void EnemigoIT::mostSprite(int _posicion){

    //Se captura la posicion dentro de la imagen de sprites
    setSprite_y_img(_posicion);
    //Se multiplica por el acho del sprite (mostrar el sprite siguiente)
    setSprite_x_img(getAnchoSprite() * contador);
    //Toma una porcion de la imagen de sprites (un sprite de la matriz)
    sprite = spriteImg.copy(getSprite_x_img(),getSprite_y_img(),getAnchoSprite(),getAltoSprite());
    //Muestra la porcion de esprite en pantalla
    setPixmap(sprite);
    //Se contabiliza la cantidad de sprites
    contador++;
    //Si ya se recorrieron todos los sprites reinicio
    if(contador == 7){contador = 0; }
}

void EnemigoIT::moverAdelante(){

    posicionX += 5;
    setPos(posicionX, posicionY);
    mostSprite(0);

    setMoverDe(true);
    setMoverIz(false);
}

void EnemigoIT::moverAtras(){

    posicionX -= 5;
    setPos(posicionX,posicionY);
    mostSprite(100);

    setMoverDe(false);
    setMoverIz(true);
}

//Saltar pendiente

void EnemigoIT::cambiarEstado(int _nuevoEstado){
    estado = _nuevoEstado;
}

void EnemigoIT::activarArma(){

    qDebug() << "Arma activada enemigoIT";

    Armas *nuevaArma = new Armas(vista,getMoverDe(),getMoverIz(),false);
    nuevaArma->lanzarArma(posicionX,posicionY);
    vista->scene()->addItem(nuevaArma);
}

void EnemigoIT::pausarLanzarBombas(){
    timerArma->stop();
}
//Aplicar fisica pendiente
