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

    opcion = false;

    QGraphicsScene *escenaMenuPrincipal = new QGraphicsScene();
    escenaMenuPrincipal->setSceneRect(0,0,900,700);
    ui->graphicsView->setScene(escenaMenuPrincipal);

    QImage imagenFondo(":/imgNiveles/fondoImgInicio.png");

    escenaMenuPrincipal->setBackgroundBrush(imagenFondo);

    QString text1 = "Ingrese su nombre de Jugador:";
    QString text2 = "El juego esta basado en el Capitulo 5 'No es it', Temporada 34 de los Simpsons.";
    QFont font1("Arial", 16);
    QFont font2("Arial", 10);

    QGraphicsTextItem *textoInicio = new QGraphicsTextItem(text1);
    textoInicio->setFont(font1);
    escenaMenuPrincipal->addItem(textoInicio);
    textoInicio->setPos(200,430);

    QGraphicsTextItem *textoInfo = new QGraphicsTextItem(text2);
    textoInfo->setFont(font2);
    escenaMenuPrincipal->addItem(textoInfo);
    textoInfo->setPos(200,640);

}



void MainWindow::on_botonJugar_clicked(){

    if(opcion){
        menuNiveles *menu_niveles = new menuNiveles(this);
        menu_niveles->show();
    }else{

        QMessageBox *mensajeAgregar = new QMessageBox(this);
        mensajeAgregar->setText("Ingresa o agrga un Jugador...");
        mensajeAgregar->exec();
    }
}


void MainWindow::on_botonAgregar_clicked(){

    QString h = ui->entradaNombre->text();

    string nombre = h.toStdString();

    try{
        if(nombre == ""){throw 1;}

    }catch(int entradaVacia){
        if(entradaVacia == 1){

            QMessageBox *mensajeError = new QMessageBox(this);
            mensajeError->setText("El campo esta vacio...");
            mensajeError->exec();
            return;
        }
    }

    Juego juego;
    juego.actuNivelORdesacJug(false);//Desactiva el juagdor activado
    juego.setNombreJugador(nombre);
    juego.verificarJugador();//VErifica la existencia del jugador

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
            opcion = true;
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

    try{
        if(nombre == ""){throw 1;}

    }catch(int entradaVacia){
        if(entradaVacia == 1){

            QMessageBox *mensajeError = new QMessageBox(this);
            mensajeError->setText("El campo esta vacio...");
            mensajeError->exec();
            return;
        }
    }

    Juego juego;
    juego.actuNivelORdesacJug(false);
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
            opcion = true;
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


