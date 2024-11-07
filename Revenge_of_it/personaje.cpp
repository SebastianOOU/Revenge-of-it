#include "personaje.h"
#include <QDebug>
Personaje::Personaje() {

    flechaDe = false; flechaIz = false; flechaAr = false;
    //Variables dimesiones sprite
    altoSprite = 72;
    anchoSprite = 46;
    //Variables posicion del sprite en la pantalla.
    posicionX = 30;
    posicionY = 500;
    //Variables posicion del sprite en la imagen de sprites
    sprite_x_img = 0;
    sprite_y_img = 0;
    //Se le indica que el sprite puede ser interactuado
    setFlag(QGraphicsItem::ItemIsFocusable);
    //Se esta pasando la direcion de la imagen de sprites.
    spriteImg.load(":/spritesIMG/Movimiento_personaje.png");
    //Toma una porcion de la imagen de sprites (un sprite de la matriz)
    sprite = spriteImg.copy(sprite_x_img,sprite_y_img,anchoSprite,altoSprite);
    //Muestra la porcion de esprite en pantalla.
    setPixmap(sprite);
}

void Personaje::mostSprite(int _posicion){
    //Se captura la posicion dentro de la imagen de sprites
    sprite_y_img = _posicion;
    //Se multiplica por el acho del sprite (mostrar el sprite siguiente)
    sprite_x_img = anchoSprite * contador;
    //Toma una porcion de la imagen de sprites (un sprite de la matriz)
    sprite = spriteImg.copy(sprite_x_img,sprite_y_img,anchoSprite,altoSprite);
    //Muestra la porcion de esprite en pantalla
    setPixmap(sprite);
    //Se contabiliza la cantidad de sprites
    contador++;
    //Si ya se recorrieron todos los sprites reinicio
    if(contador == 7){contador = 0;}
}

void Personaje::camIzquierda(){

    if(flechaIz){
        //Se resta para mover hacia izquierda
        posicionX += -5;
        //Se pasa posicion en la imagen de sprites
        mostSprite(72);
    }
    //Definimos la posicion del sprite en la pantalla
    setPos(posicionX,posicionY);
    flechaIz = false;
}

void Personaje::camDerecha(){

    if(flechaDe){
        //Se suma para mover hacia derecha
        posicionX += 5;
        //Se pasa posicion en la imagen de sprites
        mostSprite(0);
    }
    //Definimos la posicion del sprite en la pantalla
    setPos(posicionX,posicionY);
    flechaDe = false;
}

void Personaje::saltar(){

    if(flechaAr){
        //Se resta para mover hacia arriba (saltar)
        posicionY += -10;
        //Se pasa posicion en la imagen de sprites
        mostSprite(144);
    }
    //Definimos la posicion del sprite en la pantalla
    setPos(posicionX,posicionY);
    flechaDe = false;
}

void Personaje::moverPersonaje(int _tecla){
    //Se recibe el valor de la tecla y se evalua
    switch (_tecla) {
        //Si el valor de la tecla es igual "<---"
        case Qt::Key_Left:
            //True para Izquierda
            flechaIz = true;
            camIzquierda();
            break;            
        //Si el valor de la tecla es igual "--->"
        case Qt::Key_Right:           
            //True para Derecha
            flechaDe = true;
            camDerecha();
            break;          
        //Si el valor de la tecla es igual "^"
        case Qt::Key_Up:
            //True para arriba (saltar)
            flechaAr = true;
            saltar();
            break;
        default:
            break;
    }
}

void Personaje::keyPressEvent(QKeyEvent *event){
    //Capturo el valor de la tecla precionada
    int tecla = event->key();
    //Se llama la funcion y se pasa el valor de la tecla
    moverPersonaje(tecla);
}


