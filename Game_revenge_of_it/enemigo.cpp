#include "enemigo.h"
#include <cstdlib>  // Para rand()
#include <ctime>    // Para time()

// Ajusta el nivel del suelo según tu pantalla
const int nivelSuelo = 600;
// Aumenta la velocidad inicial para saltar más alto
const int velocidadSaltoInicial = -7;
// Gravedad constante (se puede ajustar)
const float gravedad = 0.3;

Enemigo::Enemigo(int x, int y, int ancho, int alto) : estado(0){

    contador = 0;
    velocidadY = 0;
    enElAire = false;
    altoSprite = alto;
    posicionX = x;
    posicionY = y;
    anchoSprite = ancho;

    srand(static_cast<unsigned int>(time(0)));

    spriteImg.load(":/spritesIMG/movimientoEnemigoPrincipal.png");

    sprite_x_img = 0;
    sprite_y_img = 0;

    sprite = spriteImg.copy(sprite_x_img,sprite_y_img,anchoSprite,altoSprite);
    setPixmap(sprite);
    setPos(posicionX,posicionY);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento,&QTimer::timeout,this,&Enemigo::actualizarSprite);
    timerMovimiento->start(140);
}

void Enemigo::dimensionarSprite(int _nuevoAncho, int _nuevoAlto){

    anchoSprite = _nuevoAncho;
    altoSprite = _nuevoAlto;
    setPixmap(sprite.scaled(anchoSprite,altoSprite));
}

void Enemigo::actualizarSprite(){

    /*sprite_x_img = anchoSprite * contador;
    sprite = spriteImg.copy(sprite_x_img, sprite_y_img, anchoSprite, altoSprite);
    setPixmap(sprite);
    contador++;*/


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

void Enemigo::mostSprite(int _posicion, int _posicionID){

    //Se captura la posicion dentro de la imagen de sprites
    sprite_y_img = _posicion;
    //Se multiplica por el acho del sprite (mostrar el sprite siguiente)
    sprite_x_img = anchoSprite * contador;

    if(_posicionID == 1){
        if (contador == 2){
            anchoSprite = 54;
        }else if(contador == 3){
            anchoSprite = 50;
        }else if(contador == 4){
            anchoSprite = 55;
        }else if(contador == 5){
            anchoSprite = 55;
        }else if(contador == 6){
            anchoSprite = 55;
        }else if(contador == 7){
            anchoSprite = 71;
        }else{
            anchoSprite = 52;
        }
    }
    //Toma una porcion de la imagen de sprites (un sprite de la matriz)
    sprite = spriteImg.copy(sprite_x_img,sprite_y_img,anchoSprite,altoSprite);
    //Muestra la porcion de esprite en pantalla
    setPixmap(sprite);
    //Se contabiliza la cantidad de sprites
    contador++;
    //Si ya se recorrieron todos los sprites reinicio
    if(contador == 7){contador = 0;}
}

void Enemigo::moverAdelante(){

    posicionX += 5;
    setPos(posicionX, posicionY);
    mostSprite(0,1);
}

void Enemigo::moverAtras(){

    posicionX -= 5;
    setPos(posicionX,posicionY);
    mostSprite(90,2);
}

//Saltar pendiente

void Enemigo::cambiarEstado(int _nuevoEstado){
    estado = _nuevoEstado;
}

//Aplicar fisica pendiente
