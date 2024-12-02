#include "juego.h"
#include <fstream>
#include <QDebug>

vector <string> datosJugador;

Juego::Juego() {

    jugadorExiste = false; puntaje = 0;
}

void Juego::verificarJugador(){

    ifstream archivo;
    string datos;

    archivo.open("jugadorDatos.txt", ios::in);

    if(!archivo.is_open()){

        qDebug() << "No se pudo abrir el archivo...";
        return;
    }

    while(getline(archivo,datos)){

        int longitud = datos.size(), contador = 0;
        string _datos;

        for(int i = 0; i < longitud; i++){
            //Cada "," se captura un nuevo dato del jugador
            if(datos[i] == ','){

                if(contador == 1){
                    //Verifica si el nombre del jugador existe
                    if(_datos == nombreJugador){
                        jugadorExiste = true;
                        return;
                    }
                }
                _datos = ""; contador++;

            }else{ _datos += datos[i]; }
        }
    }

    archivo.close();
}

void Juego::agregarJugador(){

    ofstream archivo;

    archivo.open("jugadorDatos.txt", ios::app);

    if(!archivo.is_open()){

        qDebug() << "No se pudo abrir el archivo...";
        return;
    }
    //Agrega al nuevo juagdor con el nivel 1 desbloqueado
    archivo << "1," << nombreJugador << ",1/1" << ",2/0" << ",3/0" << ",0," << endl;

    archivo.close();
}

void Juego::activarJugador(bool _activar){

    ifstream archivo;
    ofstream _archivo;
    string datos;

    archivo.open("jugadorDatos.txt", ios::in);

    if(!archivo.is_open()){

        qDebug() << "No se pudo abrir el archivo...";
        return;
    }

    while(getline(archivo,datos)){

        int longitud = datos.size(), contador = 0;
        string _datos;

        for(int i = 0; i < longitud; i++){
            //Cada "," se captura un nuevo dato del jugador
            if(datos[i] == ','){

                if(contador == 1){
                    //Se capturan los datos segun el nombre de jugador
                    if(_datos == nombreJugador){
                        capturarDatosJugador(datos,longitud);
                        break;
                    }else{
                        datosJugadores.push_back(datos);
                        break;
                    }
                }
                _datos = ""; contador++;

            }else{ _datos += datos[i]; }
        }
    }

    datosJugadores.shrink_to_fit();
    archivo.close();

    _archivo.open("jugadorDatos.txt", ios::out);
    //Se escriben los datos en le archivo
    for(auto i = datosJugadores.begin(); i != datosJugadores.end(); i++){ _archivo << *i << endl; }

    datosJugadores.clear();
    //Verifica si se activa el juagdor o actuliza el puntaje
    if(_activar){ datosJugador[0] = "1"; }

    else{ datosJugador[5] = std::to_string(puntaje); }
    //Se escriben los datos en le archivo
    for(auto i = datosJugador.begin(); i != datosJugador.end(); i++){ _archivo << *i << ","; }

    datosJugador.clear();

    _archivo << endl;
    _archivo.close();
}

void Juego::capturarDatosJugador(string _datos, int _longitud){

    string a;

    for(int i = 0; i < _longitud; i++){
        //Cada "," se captura un nuevo dato del jugador
        if(_datos[i] == ','){
            datosJugador.push_back(a);
            a = "";
        }else{
            a += _datos[i];
        }
    }

    datosJugador.shrink_to_fit();
    //Se captura el nombre del jugador
    nombreJugador = datosJugador[1];
}

void Juego::extraerPuntaje(){

    ifstream archivo; string datos;

    archivo.open("jugadorDatos.txt", ios::in);

    if(!archivo.is_open()){

        qDebug() << "No se pudo abrir el archivo...";
        return;
    }

    while(getline(archivo,datos)){

        int longitud = datos.size(), contador = 0;
        string _datos;

        for(int i = 0; i < longitud; i++){
            //Cada "," se captura un nuevo dato del jugador
            if(datos[i] == ','){

                if(contador == 0){
                    if(_datos != "1"){
                        break;
                    }
                }
                //Verifica si esta en la parte del puntaje
                if(contador == 5){
                    puntaje = stoi(_datos);
                }

                _datos = ""; contador++;

            }else{ _datos += datos[i]; }
        }
    }
    archivo.close();
}

void Juego::actuNivelORdesacJug(bool _opcion, int _nivel){

    ifstream archivo; ofstream _archivo; string datos;
    bool vacio = true;

    archivo.open("jugadorDatos.txt", ios::in);

    if(!archivo.is_open()){

        qDebug() << "No se pudo abrir el archivo...";
        return;
    }

    while(getline(archivo, datos)){
        vacio = false;
        //Verifica si el jugador esta activo
        if(datos[0] == '1'){

            int longitud = datos.size();
            capturarDatosJugador(datos,longitud);

        }else{ datosJugadores.push_back(datos); }
    }

    datosJugadores.shrink_to_fit();

    _archivo.open("jugadorDatos.txt", ios::out);
    //Verifica si es desbloquear nivel o desactivar jugador
    if(_opcion && !vacio){

        if(_nivel == 1){
            datosJugador[3] = "2/1";
        }
        else if(_nivel == 2){
            datosJugador[4] = "3/1";
        }

    }else if(!vacio){ datosJugador[0] = "0"; }
    //Se escriben los datos en le archivo
    for(auto i = datosJugadores.begin(); i != datosJugadores.end(); i++){ _archivo << *i << endl; }

    datosJugadores.clear();
    //Se escriben los datos en le archivo
    for(auto i = datosJugador.begin(); i != datosJugador.end(); i++){ _archivo << *i << ","; }

    datosJugador.clear();

    _archivo << endl;
    _archivo.close();
}

void Juego::setPuntajeJugador(int _puntaje){
    puntaje = _puntaje;
}

void Juego::setNombreJugador(string _nombre){
    nombreJugador = _nombre;
}

string Juego::getNombreJugador(){
    return nombreJugador;
}

bool Juego::getJugadorExiste(){
    return jugadorExiste;
}

int Juego::getPuntaje(){
    return puntaje;
}
