#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "personaje.h"
#include "niveljuego.h"
#include "obstaculos.h"
#include "enemigo.h"

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
    void nuevaEscena();
private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
