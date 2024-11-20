#include "niveljuego.h"
#include <fstream>
#include <QDebug>
NivelJuego::NivelJuego(int _nivel) : nivel(_nivel) {


    nivelBlocked = true;

    if(nivel == 1){

        direccionFondo = ":/spritesIMG/fondoImgLevel 1.png";
    }else if(nivel == 2){

        direccionFondo = "";
    }else{

        direccionFondo = "";
    }

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
    string datos; bool opcion =  false;

    for(int i = 0; i < longitud; i++){

        if(_datos[i] == ':'){

            datos = "";
            opcion = true;

        }else{
            datos += _datos[i];
        }

        if(opcion){

            if(_datos[i] == ','){

                a = datos[0] - '0';

                if(a == nivel){

                    if(datos[2] == '1'){

                        nivelBlocked = false;
                    }
                    break;
                }
                datos = "";
            }
        }
    }
}

void NivelJuego::setDireccionFondo(string _direccionFondo){

    direccionFondo = _direccionFondo;
}

void NivelJuego::setNivelBlocked(bool _nivelBlocked){

    nivelBlocked = _nivelBlocked;
}

string NivelJuego::getDireccionFondo(){
    return direccionFondo;
}

bool NivelJuego::getNivelBlocked(){
    return nivelBlocked;
}
