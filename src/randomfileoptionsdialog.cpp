#include "randomfileoptionsdialog.h"
#include "ui_randomfileoptionsdialog.h"
#include <QMessageBox>
#include <ctime>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <programfilegenerator.h>

randomFileOptionsDialog::randomFileOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::randomFileOptionsDialog)
{
    ui->setupUi(this);
    srand(time(nullptr));
}

randomFileOptionsDialog::~randomFileOptionsDialog()
{
    delete ui;
}



void randomFileOptionsDialog::on_generate_clicked()
{

    programfilegenerator gen = programfilegenerator();

    QJsonDocument doc = gen.generate(ui->numInstructions->value());

    ui->plainTextEdit->setPlainText(doc.toJson().toStdString().c_str());
    this->fileData = doc;

}

void randomFileOptionsDialog::on_done_clicked()
{
    if(!fileData.isEmpty()) {
        emit isDone(fileData, ui->numProc->value(), true);
        QMessageBox::about(this, "Success", "Program loaded! " + QString::number(ui->numProc->value()) + " Processes created !");
        this->close();
    }

}
