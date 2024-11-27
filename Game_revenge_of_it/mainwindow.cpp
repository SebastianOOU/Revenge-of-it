#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *escenaMenuPrincipal = new QGraphicsScene();
    escenaMenuPrincipal->setSceneRect(0,0,800,600);
    ui->graphicsView->setScene(escenaMenuPrincipal);


}



void MainWindow::on_botonJugar_clicked()
{
    menuNiveles *menu_niveles = new menuNiveles(this);
    menu_niveles->show();
}


void MainWindow::on_botonAgregar_clicked(){

    QString h = ui->entradaNombre->text();

    string nombre = h.toStdString();

    Juego juego;
    juego.setNombreJugador(nombre);
    juego.verificarJugador();

    bool jugadorExit;

    try{

        jugadorExit =  juego.getJugadorExiste();

        if(jugadorExit){ throw 1;}
        else{
            juego.agregarJugador();
            QMessageBox *mensajeAgregar = new QMessageBox(this);
            mensajeAgregar->setText("Jugador agregado exitozamente...");
            mensajeAgregar->setInformativeText("Click en Jugar, ¡Empieza el Juego!");
            mensajeAgregar->exec();
        }

    }catch (int jugExiste){

        if(jugExiste == 1){

            QMessageBox *mensajeError = new QMessageBox(this);
            mensajeError->setText("El jugador ya existe...");
            mensajeError->setInformativeText("Por favor, ingrese un nombre diferente.");
            mensajeError->exec();
            return;
        }
    }

}


void MainWindow::on_botonIngresar_clicked(){

    QString h = ui->entradaNombre->text();

    string nombre = h.toStdString();

    Juego juego;
    juego.setNombreJugador(nombre);
    juego.verificarJugador();

    bool jugadorExit;

    try{

        jugadorExit =  juego.getJugadorExiste();

        if(!jugadorExit){ throw 1;}
        else{
            juego.activarJugador(true);
            QMessageBox *mensajeAgregar = new QMessageBox(this);
            mensajeAgregar->setText("Ingreso con exito..");
            mensajeAgregar->setInformativeText("Click en Jugar, ¡Empieza el Juego!");
            mensajeAgregar->exec();
        }

    }catch (int jugExiste){

        if(jugExiste == 1){

            QMessageBox *mensajeError = new QMessageBox(this);
            mensajeError->setText("El jugador no existe");
            mensajeError->setInformativeText("Por favor, verifique su entrada.");
            mensajeError->exec();
            return;
        }
    }
}

MainWindow::~MainWindow(){

    delete ui;
}


