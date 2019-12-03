#include "loadfiledialog.h"
#include "ui_loadfiledialog.h"
#include <fstream>
#include <fileoptionsdialog.h>
#include <randomfileoptionsdialog.h>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>
#include <QDebug>
#include <QJsonArray>
#include <QFile>

loadFileDialog::loadFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loadFileDialog)
{
    ui->setupUi(this);
}

loadFileDialog::~loadFileDialog()
{
    delete ui;
}

QJsonDocument loadFileDialog::loadFile(std::string fileName){

    QFile f(QString::fromUtf8(fileName.c_str()));
    f.open(QFile::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());

    return doc;

}



void loadFileDialog::passData(QJsonDocument data, int number, bool random){
    emit this->createProcesses( data, number,  random);
}


void loadFileDialog::on_pushButton_clicked()
{

    if(ui->fileNameInput->text().length() > 0) {
        QJsonDocument fileData = this->loadFile(ui->fileNameInput->text().toStdString());
        if(!fileData.isEmpty()) {


            fileOptionsDialog *dialog = new fileOptionsDialog();
            connect(dialog, &fileOptionsDialog::isDone, this, &loadFileDialog::passData);
            dialog->show();
            dialog->fileData(fileData);
            this->close();
        }

    }else{
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open Program File"), "",
                                                        tr("Program File (*.json);;All Files (*)"));
        QJsonDocument fileData = this->loadFile(fileName.toStdString());
        if(!fileData.isEmpty()) {
            fileOptionsDialog *dialog = new fileOptionsDialog();

            connect(dialog, &fileOptionsDialog::isDone, this, &loadFileDialog::passData);
            dialog->show();
            dialog->fileData(fileData);
            this->close();


        }

    }



}

void loadFileDialog::on_pushButton_2_clicked()
{
    randomFileOptionsDialog *dialog = new randomFileOptionsDialog();
    connect(dialog, &randomFileOptionsDialog::isDone, this, &loadFileDialog::passData);
    dialog->show();
    this->close();
}
