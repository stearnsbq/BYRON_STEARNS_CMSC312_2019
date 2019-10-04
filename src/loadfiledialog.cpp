#include "loadfiledialog.h"
#include "ui_loadfiledialog.h"
#include <fstream>
#include <QMessageBox>

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

void loadFileDialog::on_pushButton_clicked()
{
    if(ui->fileNameInput->text().length() > 0){
        std::string programFileBuf;

        std::ifstream programFile("C:\\Users\\quinn\\Desktop\\dev\\BYRON_STEARNS_CMSC312_2019\\src\\" + ui->fileNameInput->text().toUtf8());
        if (!programFile)
        {
            QMessageBox::warning(this, "Error", "File not found");
            return;
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
            return;
        }

        ui->filePreview->setText(QString::fromUtf8(programFileBuf.c_str()));
        emit this->createProcesses(programFileBuf,ui->spinBox->value(), ui->checkBox->isChecked());
    }



}

void loadFileDialog::on_pushButton_2_clicked()
{
    std::vector<QString> names = {"Text Processor", "Web Browser", "Video Game", "Chat"};
    std::vector<QString> instrs = {"CALCULATE", "I/O"};
    QString instr;
    unsigned int runtime = 0;
    for(int i = 0; i < 100; i++){
        QString it = instrs.at(rand() % 2);
        unsigned int rt = (rand() % 75 + 1);
        if(it == "CALCULATE"){
            runtime += rt;
        }
        instr += QString("%1 %2\n").arg(it, QString::number(rt));
    }
    instr += "EXE";
    QString file = QString("Name: %1\nTotal runtime: %2\nMemory: %3\n\n%4").arg(names.at(rand() % 4), QString::number(runtime), QString::number(rand() % 4096), instr);
    ui->filePreview->setText(file);
}
