#include "personaje.h"
#include <QDebug>
#include <enemigo.h>
#include "enemigoit.h"

Personaje::Personaje(QGraphicsView *_vista, int _numScena):vista(_vista) {

    moverAr = false; moverDe = false; moverIz = false;

    if(_numScena == 1){

        contadorArmas = 20;
    }

    //Variables dimesiones sprite
    altoSprite = 80;
    anchoSprite = 50;

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

    choqueEnemigoAma = new QTimer(this);
    connect(choqueEnemigoAma, &QTimer::timeout, this, &Personaje::detectarChoqueArma);
    choqueEnemigoAma->start(150);
}

void Personaje::capturarEnemigos(QGraphicsPixmapItem *l){

    enemigos.push_back(l);
}

Personaje::Personaje(){

    salud = 0;

    altoSprite = 69;
    anchoSprite = 270;

    sprite_x_img = 0;
    sprite_y_img = 0;

    posicionX = 20;
    posicionY = 10;

    setFlag(QGraphicsItem::ItemIsFocusable);
    spriteImgVida.load(":/spritesIMG/vidaPersonaje.png");
    spriteVida = spriteImgVida.copy(sprite_x_img,sprite_y_img,anchoSprite,altoSprite);
    //Muestra la porcion de esprite en pantalla.
    setPixmap(spriteVida);
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
    if(contador == 8){contador = 0;}
}


void Personaje::camIzquierda(){

    //Se resta para mover hacia izquierda
    posicionX -= 8;
    //Se pasa posicion en la imagen de sprites
    mostSprite(80);

    bool a = false; int Y;

    verficarSobrePlataforma(posicionX, Y, a);

    if(!a){
        enElAire = true;
    }

    if(posicionX <= 10){
        posicionX += 8;
    }

    //Definimos la posicion del sprite en la pantalla
    setPos(posicionX,posicionY);

    verfColisionPlataforma();

    moverIz = true;
    moverDe = false;
}

void Personaje::camDerecha(){

    //Se suma para mover hacia derecha
    posicionX += 10;
    //Se pasa posicion en la imagen de sprites
    mostSprite(0);

    if(posicionX > 1220){
        qDebug() << "Hola";
        emit llegarLimiteScena();
        posicionX = 0;
    }

    bool z = false; int Y;

    verficarSobrePlataforma(posicionX, Y, z);

    if(!z){
        enElAire = true;
    }


    //Definimos la posicion del sprite en la pantalla
    setPos(posicionX,posicionY);

    verfColisionPlataforma();

    moverDe = true;
    moverIz = false;
    /*if(a){

        for(auto i = enemigos.begin(); i != enemigos.end(); i++){

            if(this->collidesWithItem(*i)){
                //a -= 10;
                posicionX -= 30;
                emit reducirVida();
                qDebug() << "El personaje a sido imapactado por un Enemigo: ";
            }
        }
    }*/

    for(QGraphicsItem *item : vista->scene()->items()){

        if(EnemigoIT *enemigoPrincipal = dynamic_cast<EnemigoIT*>(item)){
            if(this->collidesWithItem(enemigoPrincipal)){
                salud = 345;
                emit reducirVida();
                qDebug() << "El personaje a sido imapactado por un Enemigo: ";
            }
        }
        else if(Enemigo *bstaculos = dynamic_cast<Enemigo*>(item)){
            if(this->collidesWithItem(bstaculos)){
                salud = 0;
                emit reducirVida();
                qDebug() << "El personaje a sido imapactado por un Enemigo: ";
            }
        }
    }
}

void Personaje::capturarItemsPlataformas(/*QGraphicsRectItem *_items,*/ int platX , int platY, int _tamanio){

 //   itemsPlataformas.push_back(_items);
    posicionPlatafromas[platX][platY] = _tamanio;
}

void Personaje::saltar(){

     // Solo permite saltar si está en el suelo
    if(!enElAire){
        // Velocidad inicial hacia arriba
        velocidadY = -18;
        // Marca que el personaje está en el aire
        enElAire = true;
    }

    verfColisionPlataforma();
    moverAr = false;
}

void Personaje::moverPersonaje(int _tecla){

    //Se recibe el valor de la tecla y se evalua
    switch (_tecla) {
    //Si el valor de la tecla es igual "<---"
        case Qt::Key_A:

            moverIz = true;
            camIzquierda();
            break;

        case Qt::Key_D:

            moverDe = true;
            camDerecha();
           break;

        case Qt::Key_W:

            moverAr = true;
            saltar();
            break;

        case Qt::Key_Space:

            activarArma();
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
        bool a = false; int Y;
        verficarSobrePlataforma(posicionX, Y, a);

        if(a && posicionY >= Y - 80 && posicionY <= Y - 50){

            posicionY = Y - 75;
            velocidadY = 0;
            enElAire = false;

        }else if(posicionY >= 565){

            posicionY = 565;
            velocidadY = 0;
            enElAire = false;

        }else if(a && posicionY >= Y  && posicionY <= Y + 20){

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

void Personaje::activarArma(){



    if(contadorArmas < 1){

        qDebug() << "Ya no tiene armas...";
        return;
    }else{
        contadorArmas -= 1;
        emit reducirBombas();
    }

    Armas *nuevaArma = new Armas(vista, moverDe, moverIz,true);
    nuevaArma->lanzarArma(posicionX, posicionY);
    vista->scene()->addItem(nuevaArma);

    for(const auto& datosPos : posicionPlatafromas){

        for(const auto& datos : datosPos.second){

            nuevaArma->captDatosPosicionPlat(datosPos.first, datos.first);
        }


    }

    connect(nuevaArma, &Armas::aumentarPuntaje, this, &Personaje::actualizarPuntaje);

    qDebug() << "Te quedan: " << contadorArmas << " armas";
}

void Personaje::verfColisionPlataforma(){

    for(auto itemObs = itemsPlataformas.begin(); itemObs != itemsPlataformas.end(); itemObs++){

        if(this->collidesWithItem(*itemObs)){
            bool sobre = false; int Y;
            if(moverDe){

                verficarSobrePlataforma(posicionX,Y,sobre);

                if(!sobre){
                    posicionX -= 8;
                    qDebug() << "Colision detectada Derecha: " << " X: " << posicionX <<  " Y: " << posicionY;
                }
            }

            if(moverIz){

                verficarSobrePlataforma(posicionX,Y,sobre);

                if(!sobre){
                    posicionX += 8;
                    qDebug() << "Colision detectada Izquierda: " << " X: " << posicionX <<  " Y: " << posicionY;
                }
            }

            if(moverAr){
                aplicarFisica();
                qDebug() << "Colision detectada Arriba: " << " X: " << posicionX <<  " Y: " << posicionY;
            }
        }
    }
}

void Personaje::verficarSobrePlataforma(int X, int &Y, bool &sobre){


    for(const auto& posiciones : posicionPlatafromas){

        for(const auto& datos : posiciones.second){

            if(X >= posiciones.first - 30 && X <= posiciones.first + datos.second){
                sobre = true;
                Y = datos.first;
                break;
            }
        }
    }
}

void Personaje::detectarChoqueArma(){

    for(QGraphicsItem *item : this->vista->scene()->items()){
        if(Armas *bstaculos = dynamic_cast<Armas*> (item)){
            if(this->collidesWithItem(bstaculos)){
                qDebug() << "El personaje a sido imapactado por un arma: " << a;

                emit reducirVida();

            }
        }
    }
}

void Personaje::mostSpriteVida(int _salud){

    if(_salud == 0){
        salud += 69;

    }else{
        salud = _salud;
    }


    sprite_y_img = salud;

    spriteVida = spriteImgVida.copy(sprite_x_img, sprite_y_img,anchoSprite,altoSprite);

    setPixmap(spriteVida);

    setPos(10,5);

    if(salud == 345){

        emit personajeSinSalud();
    }
}

void Personaje::vaciarvector(){

    enemigos.clear();
    a = false;
    qDebug() << "Hola";
}

void Personaje::setAltoSprite(int _altoSprite){
    altoSprite = _altoSprite;
}

void Personaje::setAnchoSprite(int _anchoSprite){
    anchoSprite = _anchoSprite;
}

void Personaje::setPosicionX(qreal _posicionX){
    posicionX = _posicionX;
}

void Personaje::setPosicionY(qreal _posicionY){
    posicionY = _posicionY;
}

void Personaje::setSprite_x_img(int _sprite_x_img){
    sprite_x_img = _sprite_x_img;
}

void Personaje::setSprite_y_img(int _sprite_y_img){
    sprite_y_img = _sprite_y_img;
}

void Personaje::setSalud(int _salud){
    salud = _salud;
}

void Personaje::setContador(int _contador){
    contador = _contador;
}

void Personaje::setMoverDe(bool _moverDe){
    moverDe = _moverDe;
}

void Personaje::setMoverIz(bool _moverIz){
    moverIz = _moverIz;
}

void Personaje::setBombas(int _bombas){

    contadorArmas = _bombas;
}

void Personaje::setSpriteImg(QPixmap _spriteImg){
    spriteImg = _spriteImg;
}

void Personaje::setSprite(QPixmap _sprite){
    sprite = _sprite;
}

//GETTERS
int Personaje::getAltoSprite(){
    return altoSprite;
}

int Personaje::getAnchoSprite(){
    return anchoSprite;
}

qreal Personaje::getPosicionX(){
    return posicionX;
}

qreal Personaje::getPosicionY(){
    return posicionY;
}

int Personaje::getSprite_x_img(){
    return sprite_x_img;
}

int Personaje::getSprite_y_img(){
    return sprite_y_img;
}

int Personaje::getSalud(){
    return salud;
}

bool Personaje::getMoverDe(){
    return moverDe;
}

int Personaje::getBombas(){
    return contadorArmas;
}

bool Personaje::getMoverIz(){
    return moverIz;
}

QPixmap Personaje::getSpriteImg(){
    return spriteImg;
}










