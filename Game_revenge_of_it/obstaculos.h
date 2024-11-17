#ifndef OBSTACULOS_H
#define OBSTACULOS_H
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

class Obstaculos{

    private:
        string direccionImg;
        int altoSprite;
        int anchoSprite;
        int cantidadObs;
        int posicionX;
        int posicionY;
    public:
        Obstaculos();
        map <int,int> datosSprites;
        void extraerDatosSprites(int,int);
        void capturarPosiciones(string);

        void setDireccionImg(string);
        void setCantidadObs(int);
        void setAltoSprite(int);
        void setAnchoSprite(int);
        void setPosicionX(int);
        void setPosicionY(int);

        string getDireccionImg() const;
        int getCantidadObs() const;
        int getAltoSprite() const;
        int getAnchoSprite() const;
        int getPosicionX() const;
        int getPosicionY() const;


};

#endif // OBSTACULOS_H
