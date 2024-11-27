#include "niveljuego.h"
#include <fstream>
#include <QDebug>

NivelJuego::NivelJuego(int _nivel, int _numScena) : nivel(_nivel) , numScena(_numScena) {

    nivelBlocked = true;

    direccFondoImg();
}

void NivelJuego::direccFondoImg(){

    string arrayRects[2] = {":/spritesIMG/obstaculo_bloques.png",":/spritesIMG/bloquePlataforma2.png"};

    string arrayDireccionFondo[6] = {":/imgNiveles/fondoImgLevel 1.1.png", ":/imgNiveles/fondoImgNivel2.1.png", ":/imgNiveles/fondoNivel3.1.png",
                                    ":/imgNiveles/fondoImgLevel1.2.png", ":/imgNiveles/fondoImgNivel2.2.png", ":/imgNiveles/fondoNivel3.2.png"};

    for(int i = 0; i < 6; i++){

        if(i == nivel - 1 && numScena == 1){
            qDebug() << "Hola fondo";

            direccionFondo = arrayDireccionFondo[i];

        }else if (i == nivel - 1 && numScena == 2){

            direccionFondo = arrayDireccionFondo[i + 3];
        }
    }

    if(nivel == 2){ direccFondoRects = arrayRects[1]; }else{ direccFondoRects = arrayRects[0]; }
}

void NivelJuego::extraerDatosJugador(){

    ifstream archivo;
    string datos;

    archivo.open("jugadorDatos.txt", ios::in);

    if(!archivo.is_open()){

        qDebug() << "No se pudo abrir el archivo...";
        return;
    }

    while(getline(archivo,datos)){

        if(datos[0] == '0'){

            datos = "";
            continue;
        }

        verificarNivel(datos);
        break;
    }

    archivo.close();
}

void NivelJuego::verificarNivel(string _datos){

    int longitud = _datos.size(), a;
    string datos; int contador = 0;

    for(int i = 0; i < longitud; i++){

        if(_datos[i] == ','){

            if(contador == 1){
                nombreJugador = datos;
            }

            if(contador >= 2){

                a = datos[0] - '0';

                if(a == nivel){

                    if(datos[2] == '1'){

                        nivelBlocked = false;
                    }
                    break;
                }

            }

            contador++;
            datos = "";
        }else{
            datos += _datos[i];
        }
    }

}

string NivelJuego::rutaNivel(){

    string datosRutaNiveles[3] = {"nivel1.txt", "nivel2.txt", "nivel3.txt"};

    string direccion;

    for(int i = 0; i < 3; i++){

        if(i == nivel - 1){

            direccion = datosRutaNiveles[i];
            break;
        }
    }
    return direccion;
}

void NivelJuego::setDireccionFondo(string _direccionFondo){

    direccionFondo = _direccionFondo;
}

void NivelJuego::setDireccFonsoRects(string _direcc){
    direccFondoRects = _direcc;
}

void NivelJuego::setNivelBlocked(bool _nivelBlocked){

    nivelBlocked = _nivelBlocked;
}

string NivelJuego::getDireccionFondo(){
    return direccionFondo;
}

string NivelJuego::getDireccFondoRects(){
    return direccFondoRects;
}

bool NivelJuego::getNivelBlocked(){
    return nivelBlocked;
}

string NivelJuego::getNombreJugador(){
    return nombreJugador;
}
