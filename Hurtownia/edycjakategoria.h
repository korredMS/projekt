#ifndef EDYCJAKATEGORIA_H
#define EDYCJAKATEGORIA_H

#include <QDialog>
#include <QMessageBox>
#include "../DBProxy/DBProxy.h"

namespace Ui {
    class EdycjaKategoria;
}

class EdycjaKategoria : public QDialog {
    Q_OBJECT
public:
    EdycjaKategoria(QWidget *parent, DBProxy &db);
    ~EdycjaKategoria();

protected:
    void changeEvent(QEvent *e);

private:
    DBProxy &db;
    Ui::EdycjaKategoria *ui;
    void  czyscUi();

private slots:
    void on_buttonDodajKategoria_clicked();
    void on_buttonAnulujKategoria_clicked();
};

#endif // EDYCJAKATEGORIA_H
