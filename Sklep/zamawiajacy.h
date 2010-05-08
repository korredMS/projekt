#ifndef ZAMAWIAJACY_H
#define ZAMAWIAJACY_H

#include <QWidget>

namespace Ui {
    class Zamawiajacy;
}

class Zamawiajacy : public QWidget {
    Q_OBJECT
public:
    Zamawiajacy(QWidget *parent = 0);
    ~Zamawiajacy();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Zamawiajacy *ui;
};

#endif // ZAMAWIAJACY_H
