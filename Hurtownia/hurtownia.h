#ifndef HURTOWNIA_H
#define HURTOWNIA_H

#include <QMainWindow>
#include <QInputDialog>
#include <QMessageBox>

#include "../DBProxy/dbproxy.h"


namespace Ui {
    class Hurtownia;
}

class Hurtownia : public QMainWindow {
    Q_OBJECT
public:
    Hurtownia(QWidget *parent = 0);
    ~Hurtownia();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Hurtownia *ui;
};

#endif // HURTOWNIA_H
//cokolwiek
