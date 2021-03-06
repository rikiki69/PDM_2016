#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "opencv2/opencv.hpp"
#include "webcam.h"
#include "element.h"
#include "tir.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *ev);
    Element * gettrebuchet() {return &trebuchet;}
    Element * getboule() {return &boule;}
    Element * getcible(){return &cible;}
    void resetaffichage();


public slots:
    void incrementHorloge();

private:
    Ui::MainWindow *ui;
    Element trebuchet;
    Element boule;
    Element bouleenlair;
    Element cible;
    Element camera;
    Tir *tir_;
    QTimer *timer_;
    bool tirencours;
    int horlogeS_;
    int horlogeM_;
};

#endif // MAINWINDOW_H
