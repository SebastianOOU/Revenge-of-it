 #ifndef MENUNIVELES_H
#define MENUNIVELES_H

#include <QMainWindow>
#include "nivel1.h"

namespace Ui {
class menuNiveles;
}

class menuNiveles : public QMainWindow
{
    Q_OBJECT

public:
    explicit menuNiveles(QWidget *parent = nullptr);
    ~menuNiveles();

private slots:
    void on_pushButton_clicked();

private:
    Ui::menuNiveles *ui;
};

#endif // MENUNIVELES_H
