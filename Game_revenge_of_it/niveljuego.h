#ifndef NIVELJUEGO_H
#define NIVELJUEGO_H

#include <QObject>
#include <QPixmap>
#include <QGraphicsPixmapItem>

class NivelJuego : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
private:
    QPixmap spriteImg;
    QPixmap sprite;
    int altoImgFondo;
    int anchoImgFondo;
public:
    NivelJuego();
};

#endif // NIVELJUEGO_H
