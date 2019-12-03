#include "randomfileoptionsdialog.h"
#include "ui_randomfileoptionsdialog.h"
#include <QMessageBox>
#include <ctime>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

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
    std::vector<QString> names = {"Text Processor", "Web Browser", "Video Game", "Chat"};
    std::vector<QString> instrs = {"CALCULATE", "I/O", "OUT"};
    QString instr;

    QJsonDocument doc;

    QJsonObject obj;
    QJsonArray instructions;
    QJsonObject instruction;


    int runtime = 0;

    for(int i = 0; i < ui->numInstructions->value(); i++) {

        QString it = instrs.at(rand() % 2);
        int rt = (rand() % 75 + 1);
        if(it == "CALCULATE") {
            runtime += rt;
        }else if(it == "OUT") {
            it += names.at(rand()% 4);
        }

        instruction.insert("Type", it);
        instruction.insert("Burst", rt);
        instructions.append(instruction);
        instruction = QJsonObject();
    }

    obj.insert("instructions", instructions);
    obj.insert("Name", names.at(rand() % 4));
    obj.insert("Runtime", runtime);
    obj.insert("Memory", rand() % 4096 + 1);



    doc.setObject(obj);


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
