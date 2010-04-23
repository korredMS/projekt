#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QInputDialog>
#include <QMainWindow>
#include <QMessageBox>

#include "../DBProxy/dbproxy.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

    void wyczyscAktualnePola();

    DBProxy *db;

private slots:
    void on_pushButton_41_clicked();
    void on_pushButton_40_clicked();
    void on_pushButton_39_clicked();
    void on_pushButton_38_clicked();
    void on_pushButton_37_clicked();
    void on_pushButton_36_clicked();
    void on_pushButton_35_clicked();
    void on_pushButton_33_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
