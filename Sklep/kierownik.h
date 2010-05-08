#ifndef KIEROWNIK_H
#define KIEROWNIK_H

#include <QWidget>

namespace Ui {
    class Kierownik;
}

class Kierownik : public QWidget {
    Q_OBJECT
public:
    Kierownik(QWidget *parent = 0);
    ~Kierownik();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Kierownik *ui;
};

#endif // KIEROWNIK_H
