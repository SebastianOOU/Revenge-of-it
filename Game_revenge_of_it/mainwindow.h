#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "menuniveles.h"
#include "juego.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);


    ~MainWindow();

private slots:


    void on_botonJugar_clicked();

    void on_botonAgregar_clicked();

    void on_botonIngresar_clicked();

private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
