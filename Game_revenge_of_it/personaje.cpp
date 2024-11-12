#include "personaje.h"
#include <QDebug>
Personaje::Personaje(QGraphicsView *vista):vista(vista) {

    flechaDe = false; flechaIz = false; flechaAr = false;
    //Variables dimesiones sprite
    altoSprite = 78;
    anchoSprite = 49;
    //Variables posicion del sprite en la pantalla.
    posicionX = 30;
    posicionY = 565;
    //Variables posicion del sprite en la imagen de sprites
    sprite_x_img = 0;
    sprite_y_img = 0;
    //Se le indica que el sprite puede ser interactuado
    setFlag(QGraphicsItem::ItemIsFocusable);
    //Se esta pasando la direcion de la imagen de sprites.
    spriteImg.load(":/spritesIMG/movimientoPersonaje.png");
    //Toma una porcion de la imagen de sprites (un sprite de la matriz)
    sprite = spriteImg.copy(sprite_x_img,sprite_y_img,anchoSprite,altoSprite);
    //Muestra la porcion de esprite en pantalla.
    setPixmap(sprite);

    timermovimiento = new QTimer(this);
    connect(timermovimiento,&QTimer::timeout,this,&Personaje::aplicarFisica);
    // Intervalo de tiempo para la física
    timermovimiento->start(20);
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

Personaje::Personaje(){

    setFlag(QGraphicsItem::ItemIsFocusable);
    spriteImgVida.load(":/spritesIMG/vidaPersonaje.png");
    spriteVida = spriteImgVida.copy(0,0,270,69);
    //Muestra la porcion de esprite en pantalla.
    setPixmap(spriteVida);

}
void Personaje::camIzquierda(){

    if(flechaIz){
        //Se resta para mover hacia izquierda
        posicionX += -5;
        //Se pasa posicion en la imagen de sprites
        mostSprite(78);
        //Verifica si hay un colision con un obstaculo TODAVIA EN PRUEBAS.
        /*for(QGraphicsItem *item : vista->scene()->items()){
            if(QGraphicsRectItem *bstaculos = dynamic_cast<QGraphicsRectItem*>(item)){
                if(this->collidesWithItem(bstaculos)){
                    posicionY -= 5;
                }
            }
        }*/
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

        if(posicionX > 1220){
            qDebug() << "Hola";
            emit llegarLimiteScena();
        }

        //Verifica si hay un colision con un obstaculo TODAVIA EN PRUEBAS.
        /*for(QGraphicsItem *item : vista->scene()->items()){
            if(QGraphicsRectItem *bstaculos = dynamic_cast<QGraphicsRectItem*>(item)){
                if(this->collidesWithItem(bstaculos)){
                    posicionY += 10;
                    qDebug() << "Hola";
                }
            }
        }*/

    }
    //Definimos la posicion del sprite en la pantalla
    setPos(posicionX,posicionY);
    flechaDe = false;


}

void Personaje::saltar(){
     // Solo permite saltar si está en el suelo
    if(!enElAire){
        // Velocidad inicial hacia arriba
        velocidadY = -15;
        // Marca que el personaje está en el aire
        enElAire = true;

        //Verifica si hay un colision con un obstaculo TODAVIA EN PRUEBAS.
        /*for(QGraphicsItem *item : vista->scene()->items()){
            if(QGraphicsRectItem *bstaculos = dynamic_cast<QGraphicsRectItem*>(item)){
                if(this->collidesWithItem(bstaculos)){
                    posicionX -= 5;
                }
            }
        }*/
    }
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

void Personaje::aplicarFisica(){
    if (enElAire) {
        // Gravedad que aumenta la velocidadY
        velocidadY += 1;
        posicionY += velocidadY;

        // Verifica si llegó al suelo
        if (posicionY >= 565) {
            posicionY = 565;
            velocidadY = 0;
            enElAire = false;
        }
    }

    // Actualiza la posición en pantalla
    setPos(posicionX, posicionY);
}
void Personaje::keyPressEvent(QKeyEvent *event){
    //Capturo el valor de la tecla precionada
    int tecla = event->key();
    //Se llama la funcion y se pasa el valor de la tecla
    moverPersonaje(tecla);
}


