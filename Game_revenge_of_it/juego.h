#ifndef JUEGO_H
#define JUEGO_H

#include <iostream>
#include <vector>
using namespace std;

class Juego{
    private:
        string nombreJugador;
        bool nombre;
        int puntaje;
        bool jugadorExiste;

        vector <string> datosJugadores;

    public:
        Juego();

        void verificarJugador();
        void activarJugador(bool);
        void agregarJugador();
        void capturarDatosJugador(string,int);
        void extraerPuntaje();

        void setNombreJugador(string);
        void setPuntajeJugador(int);
        string getNombreJugador();
        bool getJugadorExiste();
        int getPuntaje();
};

#endif // JUEGO_H
