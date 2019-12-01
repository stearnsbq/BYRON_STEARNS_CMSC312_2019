#include "fileoptionsdialog.h"
#include "ui_fileoptionsdialog.h"
#include <QString>
#include <QMessageBox>
fileOptionsDialog::fileOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fileOptionsDialog)
{
    ui->setupUi(this);
}

fileOptionsDialog::~fileOptionsDialog()
{
    delete ui;
}


void fileOptionsDialog::fileData(QJsonDocument data){
    this->file = data;
    ui->filePreview->setPlainText(QString::fromUtf8(data.toJson().toStdString().c_str()));
}

void fileOptionsDialog::on_done_clicked()
{
    emit this->isDone(file,ui->procCount->value(), ui->isRandom->isChecked());
    QMessageBox::about(this, "Success", "Program loaded! " + QString::number(ui->procCount->value()) + " Processes created !");
    this->close();
}
