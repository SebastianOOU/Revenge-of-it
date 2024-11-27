#include "obstaculos.h"
#include <string>
#include <QDebug>
#include "armas.h"

Obstaculos::Obstaculos(string _rutaNivel, int _numScena) {

    direccionNivel = _rutaNivel;

    cantidadObs = 1;
    numScena = _numScena;
}

Obstaculos::Obstaculos(){}

Obstaculos::Obstaculos(QGraphicsView *_vista, int _nivelJuego) : vista(_vista), nivelJuego(_nivelJuego){

    pos_x_sprite = 0;
    pos_y_sprite = 0;


    contador = 0;

    setFlag(QGraphicsItem::ItemIsFocusScope);

    if(nivelJuego == 1){

        anchoSprite = 50;
        spritImgCajas.load(":/imgNiveles/cajaSpriteLevel1.png");
    }else{

        anchoSprite = 70;
        spritImgCajas.load(":/imgNiveles/cajaSpriteLevel3.png");
    }

    spritCaja = spritImgCajas.copy(pos_x_sprite,pos_y_sprite,anchoSprite,50);

    setPixmap(spritCaja);

    timerSpriteCaja = new QTimer(this);
    connect(timerSpriteCaja, &QTimer::timeout, this, &Obstaculos::activarObsNivel1_3);
    timerSpriteCaja->start(600);
}

void Obstaculos::activarObsNivel1_3(){

    for(QGraphicsItem *item : vista->scene()->items()){
        if(Armas *arma = dynamic_cast<Armas*>(item)){

            if(this->collidesWithItem(arma)){

                if(nivelJuego == 1){

                    cajaNivel1();

                }else{

                    cajaNivel3();
                }

            }
        }
    }
}

void Obstaculos::cajaNivel3(){

    pos_x_sprite = anchoSprite * contador;

    spritCaja = spritImgCajas.copy(pos_x_sprite,pos_y_sprite,anchoSprite,50);

    setPixmap(spritCaja);

    setPos(300,580);

    contador++;

    if(contador == 3){
        pos_y_sprite += 50;
        contador = 0;

        if(pos_y_sprite == 150){

            emit nivelSuperado();
            timerSpriteCaja->stop();
        }
    }
}

void Obstaculos::cajaNivel1(){

    pos_x_sprite = anchoSprite * contador;

    spritCaja = spritImgCajas.copy(pos_x_sprite,pos_y_sprite,anchoSprite,50);

    setPixmap(spritCaja);

    setPos(980,350);

    contador++;

    if(contador == 6){

        emit nivelSuperado();
        timerSpriteCaja->stop();
    }
}

void Obstaculos::extraerDatosEnenim(){

    ifstream archivo;
    string datos;

    archivo.open(direccionNivel, ios::in);

    if(!archivo.is_open()){

        qDebug() << "No se pudo abrir el archivo...";
        return;
    }

    bool opcion1 = false, opcion2 = false; int contador = 0;

    while(getline(archivo,datos)){

        if(datos == "--"){

            opcion1 = true;
        }

        if(opcion1 && datos[1] == ':' && datos[2] == numScena + '0'){

            cantidadObs = datos[0] - '0';
            datos = "";
            opcion2 = true;
        }

        if(opcion2 == true && datos != ""){

            capturarPosiciones(datos,true);
            contador++;
        }

        if(contador == cantidadObs){ break; }

        datos = "";
    }
}

void Obstaculos::extraerDatosSprites(){

    ifstream archivo;
    string  datos;

    archivo.open(direccionNivel, ios::in);

    bool opcion = false; int contador = 0;

    while(getline(archivo,datos)){

        if(datos[1] == ':' && datos[2] == numScena + '0'){

            cantidadObs = datos[0] - '0';
            datos = "";
            opcion = true;
        }
        qDebug() << datos;
        if(opcion == true && datos != ""){

            capturarPosiciones(datos, false);
            contador++;
        }

        if(contador == cantidadObs){ break; }

        datos = "";
    }
    archivo.close();
}

void Obstaculos::capturarPosiciones(string _datos, bool _enemin){

    int longitud = _datos.size(), cont = 0;
    string datos;

    for(int i = 0; i < longitud; i++){

        if(_datos[i] == ','){

            arrayDatos[cont] = stoi(datos);
            cont++;
            datos = "";
        }else{

            datos += _datos[i];
        }

        if(i == longitud - 1){

            arrayDatos[cont] = stoi(datos);
        }
    }

    if(_enemin){ datosEnemigo[arrayDatos[0]][arrayDatos[1]] = arrayDatos[2]; }
    else{ datosSprites[arrayDatos[0]][arrayDatos[1]] = arrayDatos[2]; }
}

