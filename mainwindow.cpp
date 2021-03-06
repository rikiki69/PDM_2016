#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv2/opencv.hpp"
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>


using namespace cv;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->openGLWidget->settrebuchet(&trebuchet);
    ui->openGLWidget->setcamera(&camera);
    ui->openGLWidget->setboule(&boule);
    ui->openGLWidget->setcible(&cible);
    ui->openGLWidget->setbouleenlair(&bouleenlair);
    ui->webcam->setTrebuchet(&trebuchet);


    tir_ = new Tir(this);
    tir_->setboule(&boule);
    tir_->setbouleenlair(&bouleenlair);
    tir_->setcible(&cible);
    tir_->settrebuchet(&trebuchet);

    ui->webcam->setTir(tir_);
    tirencours=false;
    horlogeS_ = 0;
    horlogeM_ = 0;


    resetaffichage();

    timer_ = new QTimer(this);
    connect(ui->webcam, SIGNAL(changementOpenGl()), ui->openGLWidget, SLOT(updateGL()));
    connect(tir_, SIGNAL(changementOpenGl()), ui->openGLWidget, SLOT(updateGL()));
    connect(timer_, SIGNAL(timeout()), this, SLOT(incrementHorloge()));
    timer_->start(1000);
    QTimer *timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()),tir_, SLOT(updatetime()));
    timer2->start(10);


}



MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::keyPressEvent ( QKeyEvent * event ){
     if(!ui->webcam->mainDetected() && event->key() == Qt::Key_Escape){
        qDebug() << "Main Detectée";
        Mat hand = Mat(ui->webcam->image(), ui->webcam->rectMain()).clone();
        ui->webcam->setImageMain(hand);
        ui->webcam->setMainDetected(true);
        return;
    }
}
void MainWindow::resetaffichage()
{
    //initialisation du trébuchet
    trebuchet.setsize(0.02);
    trebuchet.setpos(0,-5,0);
    trebuchet.setrot(0,0,-20);
     //trebuchet.setrot(45,-45,-20);
    trebuchet.setdisplayed(true);

    //initialisation de la boule
    boule.setsize(0.2);
    boule.setpos(0,0.1,-4);
    boule.setdisplayed(true);

    //initialisation de la boule en l'air
    bouleenlair.setdisplayed(false);
    bouleenlair.setsize(0.01);
    bouleenlair.setpos(0,0,0.8);

    //initialisation de la cible
    cible.setdisplayed(true);
    cible.setsize(0.15);
    cible.setpos(0,3,1);
    cible.setrot(60,0,0);

    //initialisation de la camera
    camera.setdisplayed(true);
    camera.setpos (0,-0.03,-0.27);
    camera.setrot(275,0,350);

    //position de la bouboule 0 -2.15 0.35
}


void MainWindow::incrementHorloge(){
    horlogeS_ += 1;
    if(horlogeS_ >= 60){
        horlogeS_ = 0;
        horlogeM_ += 1;
    }
    ui->timerLabel->setText(QString::number(horlogeM_) + "min " + QString::number(horlogeS_)+"s");
}
