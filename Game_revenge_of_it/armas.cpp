#include "armas.h"
#include <QGraphicsRectItem>
Armas::Armas(QGraphicsView *_vista, bool _derecha, bool _izquierda) : vista(_vista) {

    derecha = _derecha;
    izquierda = _izquierda;

    gravedad = 9.8;
    posicion = 0;
    spriteY = 0;
    spriteX = 0;

    xArma = 0;
    yArma = 0;

    velocidadInicialArma = 0;
    anguloArma = 0;

    timerArma = new QTimer(this);
    connect(timerArma, &QTimer::timeout, this, &Armas::moverArma);

    timerExplosion = new QTimer(this);
    connect(timerExplosion, &QTimer::timeout,this,&Armas::actiAnimExplocion);
}


void Armas::lanzarArma(qreal _posicionX, qreal _posicionY){

    QBrush brushElipse(QImage(":/spritesIMG/imagen_bomba.png"));

    QPen pen(Qt::gray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    arma = new QGraphicsEllipseItem(0,0, 20, 20);
    arma->setBrush(brushElipse);
    arma->setPen(pen);
    vista->scene()->addItem(arma);
    //if(scene()) scene()->addItem(bomba);REVISAR

    if(derecha){

        xArma = _posicionX + 50;
    }else if(izquierda){

        xArma = _posicionX - 50;
    }else{

        xArma = _posicionX + 50;
    }

    yArma = _posicionY - 10;

    arma->setPos(xArma, yArma);

    velocidadInicialArma = 100;
    anguloArma = 10;
    tiempoArma = 0;

    timerArma->start(60);
}


void Armas::moverArma(){


    //Calcula los componentes de la velocidad
    float anguloRad = anguloArma * M_PI / 180;
    float vx = velocidadInicialArma * cos(anguloRad);
    float vy = velocidadInicialArma * sin(anguloRad);

    tiempoArma += timerArma->interval() / 190.0;

    if(derecha){
        nuevaXArma = xArma + vx * tiempoArma;
    }else if(izquierda){
        nuevaXArma = xArma - vx * tiempoArma;
    }else{
       nuevaXArma = xArma + vx * tiempoArma;
    }

    nuevaYArma = yArma -(vy * tiempoArma - 0.5 * gravedad * tiempoArma * tiempoArma);
    //Actualiza la posicion de la bomba

    arma->setPos(nuevaXArma, nuevaYArma);
    //bool opcion = true;

    for(QGraphicsItem *item : vista->scene()->items()){
        if(QGraphicsRectItem *bstaculos = dynamic_cast<QGraphicsRectItem*>(item)){
            if(this->collidesWithItem(bstaculos)){

                timerExplosion->start(30);

                timerArma->stop();

                vista->scene()->removeItem(arma);
                delete arma;

                arma = nullptr;
                qDebug() << "Bomba impacto con un obstaculo: ";
            }
        }
    }

    /*if(xArma + 20 >= 535){

                timerExplosion->start(50);
                qDebug() << "Colicion detectada";
                timerArma->stop();

                vista->scene()->removeItem(arma);
                delete arma;
                timerExplosion->start(30);
                arma = nullptr;

                opcion = false;
    }*/

    verificarColision();

    //Verifica si la bomba toco el suelo.
    /*if(nuevaYArma >= 580 && opcion){
        timerExplosion->start(30);

        timerArma->stop();

        vista->scene()->removeItem(arma);
        delete arma;

        arma = nullptr;

    }*/
}


void Armas::actiAnimExplocion(){

    setFlag(QGraphicsItem::ItemIsFocusable);

    spriteExplosion.load(":/spritesIMG/animacionExplosion.png");

    mostAnimExplosion();
}

void Armas::mostAnimExplosion(){
    //Se captura la posicion dentro de la imagen de sprites
    spriteY = posicion;
    //Se multiplica por el acho del sprite (mostrar el sprite siguiente)
    spriteX = 80 * contador;
    //Toma una porcion de la imagen de sprites (un sprite de la matriz)
    explosion = spriteExplosion.copy(spriteX,spriteY,80,80);
    //Muestra la porcion de esprite en pantalla
    setPixmap(explosion);

    setPos(nuevaXArma,nuevaYArma);
    //Se contabiliza la cantidad de sprites
    contador++;
    //Si ya se recorrieron todos los sprites reinicio

    if(contador == 5){
        contador = 0; posicion += 80;

        if(posicion == 400){
            timerExplosion->stop();
        }
    }
}

void Armas::verificarColision(){

    for (const auto& datosPos : posicionesPlataforma){

        int posX = datosPos.first, posY = datosPos.second;

        if(nuevaXArma >= posX - 40 && nuevaYArma >= posY- 50 && nuevaYArma <= posY + 40 && nuevaXArma <= posX + 200){

            qDebug() << "Colicion detectada";
            timerArma->stop();

            vista->scene()->removeItem(arma);
            delete arma;
            timerExplosion->start(30);
            arma = nullptr;
        }
    }
}

void Armas::captDatosPosicionPlat(int _X, int _Y){

    posicionesPlataforma[_X] = _Y;
}
