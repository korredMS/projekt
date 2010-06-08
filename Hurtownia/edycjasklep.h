#ifndef EDYCJASKLEP_H
#define EDYCJASKLEP_H

#include <QDialog>
#include <QMessageBox>
#include "../DBProxy/DBProxy.h"

namespace Ui {
    class EdycjaSklep;
}

class EdycjaSklep : public QDialog {
    Q_OBJECT
public:
    EdycjaSklep(QWidget *parent, DBProxy &db, DBProxy::Sklep *sklep = 0, bool dodajeNowy = true);
    ~EdycjaSklep();

protected:
    void changeEvent(QEvent *e);

private:
    DBProxy &db;
    DBProxy::Sklep *mSklep;
    Ui::EdycjaSklep *ui;
    void czyscUi();
    bool dodaje;
public slots:
    void zapiszClicked();

private slots:

    void on_buttonWyczyscS_clicked();
    void on_anulujButton_clicked();

signals:
    void odswiezTabeleSklepu();
};

#endif // EDYCJASKLEP_H
