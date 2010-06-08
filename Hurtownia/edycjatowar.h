#ifndef EDYCJATOWAR_H
#define EDYCJATOWAR_H

#include <QDialog>
#include <QMessageBox>
#include "../DBProxy/DBProxy.h"

namespace Ui {
    class EdycjaTowar;
}

class EdycjaTowar : public QDialog {
    Q_OBJECT
public:
    EdycjaTowar(QWidget  *parent, DBProxy &db, DBProxy::TowarHurtownia *towar = 0, bool dodajeNowyT = true);
    ~EdycjaTowar();

protected:
    void changeEvent(QEvent *e);

private:
    DBProxy &db;
    DBProxy::TowarHurtownia *mTowar;
    Ui::EdycjaTowar *ui;
    bool dodajeT;
    void czyscUi();

signals:
    void odswiezTabeleTowarow();

private slots:
    void on_buttonWyczyscT_clicked();
    void on_buttonDodajT_clicked();
    void on_buttonAnulujT_clicked();
};

#endif // EDYCJATOWAR_H
