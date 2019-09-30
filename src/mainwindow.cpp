#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton *ptr = ui->openFileButton;
    ptr->setToolTip("load a program file");
    QObject::connect(ptr, SIGNAL(clicked()),this, SLOT(save()) );
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::save(){

}

