#include "obstaculos.h"
#include <string>
#include <QDebug>
#include "armas.h"

int nuevaPosX, nuevaPosY, velocidadTimer;

Obstaculos::Obstaculos(string _rutaNivel, int _numScena) {

    direccionNivel = _rutaNivel;

    cantidadObs = 1;
    numScena = _numScena;
}

Obstaculos::Obstaculos(QGraphicsView *_vista, int _nivelJuego) : vista(_vista), nivelJuego(_nivelJuego){

    pos_x_sprite = 0;
    pos_y_sprite = 0;

    contador = 0;

    setFlag(QGraphicsItem::ItemIsFocusScope);

    if(nivelJuego == 1){

        anchoSprite = 50;
        velocidadTimer = 600;
        spritImgCajas.load(":/imgNiveles/cajaSpriteLevel1.png");
    }else{

        anchoSprite = 70;
        velocidadTimer = 330;
        spritImgCajas.load(":/imgNiveles/cajaSpriteLevel3.png");
        //Timer para el movimiento pendular de la Caja
        timerMovPendulo = new QTimer(this);
        connect(timerMovPendulo, &QTimer::timeout, this, &Obstaculos::moverCajaPendulo);
        timerMovPendulo->start(32);
    }

    spritCaja = spritImgCajas.copy(pos_x_sprite,pos_y_sprite,anchoSprite,50);
    setPixmap(spritCaja);
    //Timer para detectar las colisones con las Cajas
    timerSpriteCaja = new QTimer(this);
    connect(timerSpriteCaja, &QTimer::timeout, this, &Obstaculos::activarObsNivel1_3);
    timerSpriteCaja->start(velocidadTimer);
}

void Obstaculos::activarObsNivel1_3(){

    for(QGraphicsItem *item : vista->scene()->items()){

        if(Armas *arma = dynamic_cast<Armas*>(item)){

            if(this->collidesWithItem(arma)){

                if(nivelJuego == 1){
                    cajaNivel1();
                }
                else{
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
    setPos(nuevaPosX,nuevaPosY);

    contador++;

    if(contador == 3){
        //Se cambia a la nueva posicion en la imagen
        pos_y_sprite += 50;
        contador = 0;
        //Verifica si es la ultima porcion de imagen de sprites
        if(pos_y_sprite == 150){

            emit nivelSuperado();
            timerMovPendulo->stop();
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
    //Verifica si es la ultima porcion de imagen de sprites
    if(contador == 6){

        emit nivelSuperado();
        timerSpriteCaja->stop();
    }
}

void Obstaculos::moverCajaPendulo(){

    static float angulo = 3.1416 / 4;
    static float velocidadAngular = 0.5;
    const float gravedad = 200;
    const float longitud = 200.0;
    const float deltaTiempo = 0.03;

    float aceleracionAngular = -(gravedad / longitud) * sin(angulo);

    velocidadAngular += aceleracionAngular * deltaTiempo;
    angulo += velocidadAngular * deltaTiempo;

    int posicionCentralX = 800, posicionCentralY = 50;
    nuevaPosX = posicionCentralX + static_cast<int>(longitud * sin(angulo));
    nuevaPosY = posicionCentralY + static_cast<int>(longitud * cos(angulo));

    setPos(nuevaPosX,nuevaPosY);
}

void Obstaculos::extraerDatosEnenim(){

    ifstream archivo; string datos;

    archivo.open(direccionNivel, ios::in);

    if(!archivo.is_open()){

        qDebug() << "No se pudo abrir el archivo...";
        return;
    }

    bool opcion1 = false, opcion2 = false; int contador = 0;

    while(getline(archivo,datos)){
        //Verifica si esta en los datos "enemigos"
        if(datos == "--"){ opcion1 = true; }
         //Verifica si esta en la cantidad de enemigos y numero de scena
        if(opcion1 && datos[1] == ':' && datos[2] == numScena + '0'){

            cantidadObs = datos[0] - '0';
            datos = "";
            opcion2 = true;
        }
        //Verifica si esta en la parte de datos "enemigos"
        if(opcion2 == true && datos != ""){

            capturarPosiciones(datos,true);
            contador++;
        }

        if(contador == cantidadObs){ break; }

        datos = "";
    }
}

void Obstaculos::extraerDatosSprites(){

    ifstream archivo; string  datos;

    archivo.open(direccionNivel, ios::in);

    bool opcion = false; int contador = 0;

    while(getline(archivo,datos)){
        //Verifica si esta en la cantidad de obstaculo y numero de scena
        if(datos[1] == ':' && datos[2] == numScena + '0'){

            cantidadObs = datos[0] - '0';
            datos = "";
            opcion = true;
        }
        //Verifica si esta en la parte de datos de Obstaculos
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

    int longitud = _datos.size(), cont = 0; string datos;

    for(int i = 0; i < longitud; i++){
        //Cada "," captura un dato del obstaculo
        if(_datos[i] == ','){
            //Agrega los datos al array en int
            arrayDatos[cont] = stoi(datos);
            cont++;
            datos = "";

        }else{datos += _datos[i]; }

        if(i == longitud - 1){ arrayDatos[cont] = stoi(datos); }
    }
    //Segun la opcion, agrega los datos al map que corresponde
    if(_enemin){
        datosEnemigo[arrayDatos[0]][arrayDatos[1]] = arrayDatos[2];

    }else{
        datosSprites[arrayDatos[0]][arrayDatos[1]] = arrayDatos[2];
    }

}

