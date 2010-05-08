#ifndef SPRZEDAWCA_H
#define SPRZEDAWCA_H

#include <QWidget>
#include <QMessageBox>

#include "../DBProxy/dbproxy.h"

namespace Ui {
    class Sprzedawca;
}

class Sprzedawca : public QWidget {
    Q_OBJECT
public:
    Sprzedawca(QWidget *parent = 0);
    ~Sprzedawca();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Sprzedawca *ui;

private slots:
    void on_pushButton_clicked();
};

#endif // SPRZEDAWCA_H
