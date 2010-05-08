#ifndef SKLEP_H
#define SKLEP_H

#include <QDebug>
#include <QtSql>
#include <QMainWindow>
#include <QGridLayout>
#include <QListWidgetItem>
#include <QMessageBox>

#include "sprzedawca.h"
#include "kierownik.h"
#include "zamawiajacy.h"
#include "../DBProxy/dbproxy.h"


namespace Ui {
    class Sklep;
}

class Sklep : public QMainWindow {
    Q_OBJECT
public:
    Sklep(QWidget *parent = 0);
    ~Sklep();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Sklep *ui;


    DBProxy baza;

    QString posadaLogowanie;
    QString osobaLogowanie;
    QList< DBProxy::Pracownik > pracownicy;

private slots:

    void on_listWidget_itemClicked(QListWidgetItem* item);
    void on_pushButton_clicked();
    void on_comboBox_currentIndexChanged(QString );
};

#endif // SKLEP_H
