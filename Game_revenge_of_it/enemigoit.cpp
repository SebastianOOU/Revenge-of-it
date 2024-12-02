#include "enemigoit.h"

int matrizDatosEnemigoIT[3][4] = {{900,200,280,1600},{900,300,300,1000},{650,200,330,700}};
int tamanio, velocidad, posicX, colli = 0;

EnemigoIT::EnemigoIT( QGraphicsView *_vista, int _nivel) : vista(_vista), nivel(_nivel) {

    for(int fila = 0; fila < 3; fila++){

        if(nivel == fila + 1){
            //Se capturan los datos de las posiciones del enemigo
            for(int columna = 0; columna < 4; columna++){

                if(columna == 0){ setPosicionX(matrizDatosEnemigoIT[fila][columna]); }
                else if(columna == 1){ tamanio = matrizDatosEnemigoIT[fila][columna]; }
                else if(columna == 2){ setPosicionY(matrizDatosEnemigoIT[fila][columna]); }
                else if(columna == 3){ velocidad = matrizDatosEnemigoIT[fila][columna]; }
            }
        }
    }
    setAltoSprite(120);
    setAnchoSprite(80);

    setMoverDe(false);
    setMoverIz(false);
    setEnElAire(false);

    setSalud(100);
    setContador(0);

    posicX = getPosicionX();
    tamanio += getPosicionX();

    setSprite_x_img(0);
    setSprite_x_img(0);

    spriteImg.load(":/spritesIMG/movimientoEnemigoIt.png");

    sprite = spriteImg.copy(getSprite_x_img(),getSprite_y_img(),getAnchoSprite(),getAltoSprite());
    setPixmap(sprite);
    setPos(getPosicionX(), getPosicionY());
    //Timer para el movimiento del personaje
    timerMovimiento = new QTimer(this);
    connect(timerMovimiento,&QTimer::timeout,this,&EnemigoIT::actualizarSprite);
    timerMovimiento->start(140);
    //Timer para lanzar las Armas
    timerArma = new QTimer(this);
    connect(timerArma,&QTimer::timeout,this,&EnemigoIT::activarArma);
    timerArma->start(velocidad);
}

void EnemigoIT::actualizarSprite(){

    if (getContador() % 7 == 0){

        int randomState = rand() % 3;
        cambiarEstado(randomState);
    }

    if(nivel == 2){ verificarChoqueArma(); }
    //Verifica la posicion en X del enemigo. Evita que salga de los limites indicados
    if(getPosicionX() <= posicX - 20){ estado = 0;}
    else if(getPosicionX() >= tamanio - 50){ estado = 1; }

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
    setSprite_x_img(getAnchoSprite() * getContador());
    //Toma una porcion de la imagen de sprites (un sprite de la matriz)
    sprite = spriteImg.copy(getSprite_x_img(),getSprite_y_img(),getAnchoSprite(),getAltoSprite());
    //Muestra la porcion de esprite en pantalla
    setPixmap(sprite);
    //Se contabiliza la cantidad de sprites
    setContador(getContador() + 1);
    //Si ya se recorrieron todos los sprites reinicio
    if(getContador() == 7){setContador(0); }
}

void EnemigoIT::moverAdelante(){

    setPosicionX(getPosicionX() + 8);
    setPos(getPosicionX(), getPosicionY());
    mostSprite(0);

    setMoverDe(true);
    setMoverIz(false);
}

void EnemigoIT::moverAtras(){

    setPosicionX(getPosicionX() - 8);
    setPos(getPosicionX(), getPosicionY());
    mostSprite(120);

    setMoverDe(false);
    setMoverIz(true);
}

void EnemigoIT::cambiarEstado(int _nuevoEstado){
    estado = _nuevoEstado;
}

void EnemigoIT::activarArma(){

    Armas *nuevaArma = new Armas(vista,getMoverDe(),getMoverIz(),false);
    nuevaArma->lanzarArma(getPosicionX(), getPosicionY());
    vista->scene()->addItem(nuevaArma);
}

void EnemigoIT::reducirVidaEne(){

    setSalud(getSalud() - 5);

    emit actuVidaIT();
    //Indica que la salud del enemigo se ah terminado
    if(getSalud() == 0){ emit eneminItdead(); }
}

void EnemigoIT::verificarChoqueArma(){

    for(QGraphicsItem *itemScena : vista->scene()->items()){

        if(Armas *itemArmas = dynamic_cast<Armas *> (itemScena)){

            if(this->collidesWithItem(itemArmas)){

                colli++;
                //Cada 4 colisiones se reduce la vida del enemigo
                if(colli == 4){

                    reducirVidaEne();
                    colli = 0;
                }
            }
        }
    }
}

void EnemigoIT::pausarLanzarBombas(){
    timerArma->stop();
}
