#include "armas.h"
#include <QGraphicsRectItem>
#include "enemigo.h"
#include "enemigoit.h"
#include "obstaculos.h"
Armas::Armas(QGraphicsView *_vista, bool _derecha, bool _izquierda, bool _personEnemin) : vista(_vista) {

    derecha = _derecha;
    izquierda = _izquierda;

    personORenemin = _personEnemin;

    gravedad = 9.8;
    posicion = 0;
    spriteY = 0;
    spriteX = 0;

    xArma = 0;
    yArma = 0;

    velocidadInicialArma = 0;
    anguloArma = 0;

    setFlag(QGraphicsItem::ItemIsFocusable);

    spriteImgArma.load(":/spritesIMG/imagenBomba.png");

    spriteArma = spriteImgArma.copy(0,0,40,35);

    setPixmap(spriteArma);

    timerArma = new QTimer(this);
    connect(timerArma, &QTimer::timeout, this, &Armas::moverArma);

    timerExplosion = new QTimer(this);
    connect(timerExplosion, &QTimer::timeout,this,&Armas::actiAnimExplocion);
}

Armas::Armas(){}

void Armas::lanzarArma(float _posicionX, float _posicionY){

    if(derecha){

        xArma = _posicionX + 50;

    }else if(izquierda){

        xArma = _posicionX - 50;

        spriteArma = spriteImgArma.copy(0,35,40,35);

        setPixmap(spriteArma);

    }else{

        xArma = _posicionX + 50;
    }

    yArma = _posicionY - 10;

    setPos(xArma, yArma);

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

    setPos(nuevaXArma, nuevaYArma);
    //bool opcion = true;

    verificarColision();
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

    bool colisionTierra = true;

    for (const auto& datosPos : posicionesPlataforma){

        int posX = datosPos.first, posY = datosPos.second;

        if(nuevaXArma >= posX - 40 && nuevaYArma >= posY- 50 && nuevaYArma <= posY + 40 && nuevaXArma <= posX + 200){

            qDebug() << "Colicion detectada";
            timerArma->stop();

            timerExplosion->start(30);

            colisionTierra = false;
        }
    }

    if(colisionTierra && nuevaYArma >= 600){

        qDebug() << "Colicion detectada con tierra";
        timerArma->stop();


        timerExplosion->start(30);
    }

    for(QGraphicsItem *item : vista->scene()->items()){
        if(EnemigoIT *bstaculo = dynamic_cast<EnemigoIT*>(item)){
            if(this->collidesWithItem(bstaculo)){

                qDebug() << "La bomba impacto con Enemigo IT: ";
            }
        }else if(Enemigo *bstaculos = dynamic_cast<Enemigo*>(item)){
                if(this->collidesWithItem(bstaculos)){

                    timerArma->stop();

                    timerExplosion->start(30);

                    if(personORenemin){

                        vista->scene()->removeItem(bstaculos);
                        delete bstaculos;

                        emit aumentarPuntaje();

                    }
                    qDebug() << "la bomba impacto con un enemigo";
                }
        }else if(Obstaculos *bstaculs = dynamic_cast<Obstaculos*>(item)){
            if(this->collidesWithItem(bstaculs)){

                timerArma->stop();

                timerExplosion->start(30);

                qDebug() << "La bomba imapcato con un obstculo";
            }
        }else if(Personaje *person = dynamic_cast<Personaje*>(item)){

            if(this->collidesWithItem(person)){

                timerArma->stop();

                timerExplosion->start(30);

                qDebug() << "La bomba impacto con el personaje";
            }
        }
    }
}

void Armas::captDatosPosicionPlat(int _X, int _Y){

    posicionesPlataforma[_X] = _Y;
}
