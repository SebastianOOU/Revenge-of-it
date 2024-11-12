#include "niveljuego.h"

NivelJuego::NivelJuego() {

    altoImgFondo = 720;
    anchoImgFondo = 1280;

    setFlag(QGraphicsItem::ItemIsFocusable);
    spriteImg.load(":/spritesIMG/fondoImgLevel 1.png");
    sprite = spriteImg.copy(0,0,anchoImgFondo,altoImgFondo);
    setPixmap(sprite);
}
