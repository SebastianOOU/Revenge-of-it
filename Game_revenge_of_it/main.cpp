#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    /*Juego juego;
    juego.mostrarMenu();*/

    return a.exec();
}
