#include "loadfiledialog.h"
#include "ui_loadfiledialog.h"
#include <fstream>
#include <fileoptionsdialog.h>
#include <randomfileoptionsdialog.h>
#include <QMessageBox>
#include <QFileDialog>

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

std::string loadFileDialog::loadFile(std::string fileName){
    std::string programFileBuf;

    std::ifstream programFile(fileName);
    if (!programFile)
    {
        QMessageBox::warning(this, "Error", "File not found");
        return nullptr;
    }
    bool isValid = false;
    for (std::string line; getline(programFile, line);)
    {
        programFileBuf += line + "\n";
        if (line == "EXE")
        {
            isValid = true;
        }
    }
    if(!isValid){
        QMessageBox::warning(this, "Error", "Invalid Program File");
        return nullptr;
    }
    return programFileBuf;
}



void loadFileDialog::passData(std::string data, int number, bool random){
   emit this->createProcesses( data,  number,  random);
}


void loadFileDialog::on_pushButton_clicked()
{

    if(ui->fileNameInput->text().length() > 0){
        std::string fileData = this->loadFile(ui->fileNameInput->text().toStdString());

        fileOptionsDialog *dialog = new fileOptionsDialog();
        connect(dialog, &fileOptionsDialog::isDone, this, &loadFileDialog::passData);
        dialog->show();
        dialog->fileData(fileData);
        this->close();

    }else{
        QString fileName = QFileDialog::getOpenFileName(this,
                tr("Open Programfile"), "",
                tr("Program File (*.txt);;All Files (*)"));
        std::string fileData = this->loadFile(fileName.toStdString());

        fileOptionsDialog *dialog = new fileOptionsDialog();

        connect(dialog, &fileOptionsDialog::isDone, this, &loadFileDialog::passData);
        dialog->show();
        dialog->fileData(fileData);
        this->close();


    }



}

void loadFileDialog::on_pushButton_2_clicked()
{
randomFileOptionsDialog *dialog = new randomFileOptionsDialog();
connect(dialog, &randomFileOptionsDialog::isDone, this, &loadFileDialog::passData);
dialog->show();
this->close();
}
