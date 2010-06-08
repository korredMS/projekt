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
    EdycjaKategoria(QWidget *parent, DBProxy &db, DBProxy::Kategoria * kategoria = 0, bool dodanjeNowy = true);
    ~EdycjaKategoria();

protected:
    void changeEvent(QEvent *e);

private:
    DBProxy &db;
    DBProxy::Kategoria *mKategoria;
    Ui::EdycjaKategoria *ui;
    void  czyscUi();
    bool dodajeK;


private slots:
    void on_buttonDodajKategoria_clicked();
    void on_buttonAnulujKategoria_clicked();
signals:
    void odswiezTabeleKategoria();
    void odswiezTabelaTowarow();
};

#endif // EDYCJAKATEGORIA_H
