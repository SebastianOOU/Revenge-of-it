#include "personaje.h"
#include <QDebug>
#include <enemigo.h>
#include "enemigoit.h"

bool derech = false, izquierd = false, opcion = false;

Personaje::Personaje(QGraphicsView *_vista, int _numScena):vista(_vista) {

    moverAr = false; moverDe = false; moverIz = false;

    if(_numScena == 1){ contadorArmas = 0; }

    contador = 0;
    salud = 0;

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

    musicaGolpeArma = new QMediaPlayer(this);
    musicaGolpeArma->setSource(QUrl("qrc:/sonidos/young-man-being-hurt-95628.mp3"));
    volumen = new QAudioOutput(this);
    volumen->setVolume(1.0);
    musicaGolpeArma->setAudioOutput(volumen);
    musicaGolpeArma->setLoops(1);

    timerMoverPersonaje = new QTimer(this);
    connect(timerMoverPersonaje,&QTimer::timeout,this,&Personaje::moverPersonaje);
    timerMoverPersonaje->start(31);

    timermovimiento = new QTimer(this);
    connect(timermovimiento,&QTimer::timeout,this,&Personaje::aplicarFisica);
    // Intervalo de tiempo para la física
    timermovimiento->start(20);

    timerDetectarColItems = new QTimer(this);
    connect(timerDetectarColItems ,&QTimer::timeout,this,&Personaje::detectarColisionItemsScena);
    // Intervalo de tiempo para la física
    timerDetectarColItems ->start(30);

    choqueEnemigoAma = new QTimer(this);
    connect(choqueEnemigoAma, &QTimer::timeout, this, &Personaje::detectarColisionArma);
    choqueEnemigoAma->start(300);
}

Personaje::Personaje(){

    salud = 0;

    altoSprite = 69; anchoSprite = 270;

    sprite_x_img = 0; sprite_y_img = 0;

    posicionX = 20; posicionY = 10;

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

    bool intervaloPlatf = false; int posY;

    //Se resta para mover hacia izquierda
    posicionX -= 10;
    //Se pasa posicion en la imagen de sprites
    mostSprite(80);
    //Verifica si esat en intervalo de la plataforma
    verficarSobrePlataforma(intervaloPlatf, posY);

    if(!intervaloPlatf){ enElAire = true; }

    if(posicionX <= 5){ posicionX += 10; }

    //Definimos la posicion del sprite en la pantalla
    setPos(posicionX,posicionY);

    derech = false;
    izquierd = true;
}

void Personaje::camDerecha(){

    bool intervaloPlatf = false; int posY;

    //Se suma para mover hacia derecha
    posicionX += 10;
    //Se pasa posicion en la imagen de sprites
    mostSprite(0);
    //Verifica si esat en intervalo de la plataforma
    verficarSobrePlataforma(intervaloPlatf, posY);

    if(!intervaloPlatf){ enElAire = true; }

    //Definimos la posicion del sprite en la pantalla
    setPos(posicionX,posicionY);

    derech = true;
    izquierd = false;
}

void Personaje::capturarItemsPlataformas(QGraphicsRectItem *_items, int platX , int platY, int _tamanio){

    itemsPlataformas.push_back(_items);
    posicionPlataformas[platX][platY] = _tamanio;
}

void Personaje::saltar(){

     // Solo permite saltar si está en el suelo
    if(!enElAire){
        // Velocidad inicial hacia arriba
        velocidadY = -18;
        // Marca que el personaje está en el aire
        enElAire = true;
    }

    moverAr = false;
}

void Personaje::moverPersonaje(){

    if(posicionX > 1220 ){

        if(!opcion){

            emit llegarLimiteScena();
            posicionX = 0;
            opcion = true;

        }else{
            posicionX -= 10;
        }
    }

    if(moverAr){

        saltar();
        verfColisionPlataforma();

    }else if(moverDe){

        camDerecha();
        verfColisionPlataforma();

    }else if(moverIz){

        camIzquierda();
        verfColisionPlataforma();
    }
}

void Personaje::aplicarFisica(){

    bool intervaloPlatf = false; int posYPlatf;

    if (enElAire) {
        // Gravedad que aumenta la velocidadY
        velocidadY += 1;
        posicionY += velocidadY;

        verficarSobrePlataforma(intervaloPlatf, posYPlatf);
        //Verifica si esta sobre la plataforma
        if(intervaloPlatf && posicionY >= posYPlatf - 80 && posicionY <= posYPlatf- 50){

            posicionY = posYPlatf - 75;
            velocidadY = 0;
            enElAire = false;
        //Verifica si No esta sobre la plataforma
        }else if(intervaloPlatf && posicionY > posYPlatf  && posicionY < posYPlatf + 20){

            posicionY = 565;
            velocidadY = 0;
            enElAire = false;
        // Verifica si llegó al suelo
        }else if(posicionY >= 565){

            posicionY = 565;
            velocidadY = 0;
            enElAire = false;
        }
    }
    // Actualiza la posición en pantalla
    setPos(posicionX, posicionY);
}

void Personaje::keyPressEvent(QKeyEvent *event){

    if(event->key() == Qt::Key_A){

        moverIz = true;

    }else if(event->key() == Qt::Key_D){

        moverDe = true;

    }else if(event->key() == Qt::Key_W){

        moverAr = true;

    }else if(event->key() ==Qt::Key_Space){

        activarArma();
    }
}

void Personaje::keyReleaseEvent(QKeyEvent *event){

    if(event->key() == Qt::Key_A){

        moverIz = false;

    }else if(event->key() == Qt::Key_D){

        moverDe = false;

    }else if(event->key() == Qt::Key_W){

        moverAr = false;
    }
}

void Personaje::activarArma(){

    if(contadorArmas < 1){
        return;

    }else{

        contadorArmas -= 1;
        emit actualizarNumBombas();
    }

    Armas *nuevaArma = new Armas(vista, derech, izquierd,true);
    nuevaArma->lanzarArma(posicionX, posicionY);
    vista->scene()->addItem(nuevaArma);

    for(const auto& datosPos : posicionPlataformas){

        for(const auto& datos : datosPos.second){

            nuevaArma->captDatosPosicionPlat(datosPos.first, datos.first);
        }
    }

    connect(nuevaArma, &Armas::aumentarPuntaje, this, &Personaje::actualizarPunt);
}

void Personaje::actualizarPunt(){

    puntaje += 2;

    emit actuPuntInter();
}

void Personaje::verfColisionPlataforma(){

    bool intervaloPlatf = false; int posY;

    for(auto itemObs = itemsPlataformas.begin(); itemObs != itemsPlataformas.end(); itemObs++){

        if(this->collidesWithItem(*itemObs)){

            if(moverDe){

                verficarSobrePlataforma(intervaloPlatf,posY);
                //Si no esta en el intervalo de la plataforma se actualiza la posicion
                if(!intervaloPlatf){
                    posicionX -= 10;
                }

            }else if(moverIz){

                verficarSobrePlataforma(intervaloPlatf,posY);
                //Si no esta en el intervalo de la plataforma se actualiza la posicion
                if(!intervaloPlatf){
                    posicionX += 10;
                }

            }else if(moverAr){
                aplicarFisica();
            }
        }
    }
}

void Personaje::verficarSobrePlataforma(bool &_intervaloPlatf,int &Y){
    //Verifica si esta dentro del intervalo de las plataformas.
    for(const auto& posiciones : posicionPlataformas){

        for(const auto& datos : posiciones.second){
            //Se verifica la posicion en X del personaje con la posicion en X y el ancho de las plataformas
            if(moverDe && posicionX >= posiciones.first - 30 && posicionX <= posiciones.first + datos.second){

                _intervaloPlatf = true;
                Y = datos.first;
                break;

            }else if(moverIz && posicionX <= posiciones.first + datos.second - 30 && posicionX  >= posiciones.first - 30){

                _intervaloPlatf= true;
                Y = datos.first;
                break;

            }else if(posicionX >= posiciones.first - 20 && posicionX  <= posiciones.first + datos.second - 30){

                _intervaloPlatf = true;
                Y = datos.first;
                break;
            }
        }
    }
}

void Personaje::detectarColisionItemsScena(){

    for(QGraphicsItem *itemsScena : vista->scene()->items()){

       if(QGraphicsEllipseItem *ellipsePunt = dynamic_cast<QGraphicsEllipseItem*>(itemsScena)){

            if(this->collidesWithItem(ellipsePunt)){
                //Se aumente el contador de Armas (bombas) y el puntaje
                contadorArmas++;
                puntaje++;
                this->vista->scene()->removeItem(ellipsePunt);
                emit actuPuntInter();
                emit actualizarNumBombas();
            }

        }else if(EnemigoIT *enemigoPrincipal = dynamic_cast<EnemigoIT*>(itemsScena)){

            if(this->collidesWithItem(enemigoPrincipal)){
                salud = 345;//Si colisiona con el enemigo principal, se reduce la vida completamente
                emit reducirVida();
            }

        }else if(Enemigo *enemigo = dynamic_cast<Enemigo*>(itemsScena)){

            if(this->collidesWithItem(enemigo)){
                //Verifica si la colision fue sobre el enemigo
                if(posicionY <= enemigo->getPosicionY() - 30){

                    vista->scene()->removeItem(enemigo);
                    delete enemigo;
                    puntaje += 2;
                    emit actuPuntInter();
                }else{

                    salud = 0;
                    musicaGolpeArma->play();
                    //Verifica la posicion del personaje y actuliza su posicion
                    if(derech){ posicionX -= 30; }

                    else if(izquierd){ posicionX += 30; }

                    emit reducirVida();
                }
            }
        }
    }
}

void Personaje::detectarColisionArma(){

    for(QGraphicsItem *itemsScena : vista->scene()->items()){

        if(Armas *itemArma = dynamic_cast<Armas*> (itemsScena)){

            if(this->collidesWithItem(itemArma)){
                musicaGolpeArma->play();
                salud = 0;
                emit reducirVida();
            }
        }
    }
}

void Personaje::mostSpriteVida(int _salud){

    if(_salud == 0){ salud += 69; }

    else{ salud = _salud; }

    sprite_y_img = salud;
    spriteVida = spriteImgVida.copy(sprite_x_img, sprite_y_img,anchoSprite,altoSprite);
    setPixmap(spriteVida);
    setPos(10,5);

    if(salud == 345){ emit personajeSinSalud(); }
}

void Personaje::stopTimers(){

    opcion = false;
    //Se detienen los timers
    timerMoverPersonaje->stop();
    timermovimiento->stop();
    choqueEnemigoAma->stop();
    timerDetectarColItems->stop();
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

void Personaje::setEnElAire(bool _aire){
    enElAire = _aire;
}

void Personaje::setPuntaje(int _puntaje){

    puntaje = _puntaje;
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

bool Personaje::getEnElAire(){
    return enElAire;
}

int Personaje::getContador(){
    return contador;
}

int Personaje::getPuntaje(){
    return puntaje;
}










