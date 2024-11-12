#include "obstaculos.h"
#include <fstream>
#include <string>
#include <QDebug>


Obstaculos::Obstaculos() {

    direccionImg = "0";
    altoSprite = 0;
    anchoSprite = 0;
    posicionX = 0;
    posicionY = 0;
}


void Obstaculos::extraerDatosSprites(int _nivel, int _numScena){


    ifstream archivo, _archivo;
    string direccionNivel, datos, _datos;

    if(_nivel == 1){

        direccionNivel = ":/archivosDatosJuego/nivel1.txt";
    }else if(_nivel == 2){

        direccionNivel = ":/archivosDatosJuego/nivel2.txt";
    }else{

        direccionNivel = ":/archivosDatosJuego/nivel3.txt";
    }

    archivo.open("C:/Juego Revenge of it/Archivos/Game_revenge_of_it/archivosDatosJuego/nivel1.txt", ios::in);
    _archivo.open(direccionNivel, ios::in);

    if(!archivo.is_open() || !_archivo.is_open()){

        cout << "No se pudo abrir el archivo..." << endl;
    }

    while(getline(archivo,datos)){
        cout << "Leyendo línea: " << datos << endl;
        direccionImg = datos;

    }
    datos = "";
    archivo.close();

    int contador = 0,  b;
    bool opcion = false;

    while(getline(_archivo,datos)){

        if(contador == 0){

            char a = datos[2];
            b = a - '0';

            if(b == _numScena){

                a = datos[0];
                cantidadObs = a - '0';
                opcion = true;
                contador = 0;
            }
        }

        if(opcion && contador >= 1){

            capturarPosiciones(_datos);
        }

        if (contador == cantidadObs){
            break;
        }

        datos = "";
        contador++;
    }

    _archivo.close();

}

void Obstaculos::capturarPosiciones(string _datos){

    int longitud = _datos.size();
    string datos;

    for(int i = 0; i < longitud; i++){

        if(_datos[i] == ':'){

            posicionX = stoi(datos);
            datos = "";

        }else{

            datos += _datos[i];
        }

        if(i == longitud - 1){

            posicionY = stoi(datos);
        }
    }

    datosSprites[posicionX] = posicionY;
}

void Obstaculos::setCantidadObs(int _num){
    cantidadObs = _num;
}

int Obstaculos::getCantidadObs() const{
    return cantidadObs;
}
void Obstaculos::setDireccionImg(string _direccionImg){

    direccionImg = _direccionImg;
}

string Obstaculos::getDireccionImg() const{

    return direccionImg;
}

void Obstaculos::setAltoSprite(int _altoSprite){

    altoSprite = _altoSprite;
}

void Obstaculos::setAnchoSprite(int _anchoSprite){

    anchoSprite = _anchoSprite;
}

void Obstaculos::setPosicionX(int _posicionX){

    posicionX = _posicionX;
}

void Obstaculos::setPosicionY(int _posicionY){

    posicionY = _posicionY;
}

int Obstaculos::getAnchoSprite() const{

    return anchoSprite;
}

int Obstaculos::getAltoSprite() const{

    return altoSprite;
}

int Obstaculos::getPosicionX() const{

    return posicionX;
}

int Obstaculos::getPosicionY() const{

    return posicionY;
}
