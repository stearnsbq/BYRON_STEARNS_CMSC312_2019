#include "randomfileoptionsdialog.h"
#include "ui_randomfileoptionsdialog.h"

randomFileOptionsDialog::randomFileOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::randomFileOptionsDialog)
{
    ui->setupUi(this);
}

randomFileOptionsDialog::~randomFileOptionsDialog()
{
    delete ui;
}



//std::vector<QString> names = {"Text Processor", "Web Browser", "Video Game", "Chat"};
//std::vector<QString> instrs = {"CALCULATE", "I/O"};
//QString instr;
//unsigned int runtime = 0;
//for(int i = 0; i < 100; i++){
//    QString it = instrs.at(rand() % 2);
//    unsigned int rt = (rand() % 75 + 1);
//    if(it == "CALCULATE"){
//        runtime += rt;
//    }
//    instr += QString("%1 %2\n").arg(it, QString::number(rt));
//}
//instr += "EXE";
//QString file = QString("Name: %1\nTotal runtime: %2\nMemory: %3\n\n%4").arg(names.at(rand() % 4), QString::number(runtime), QString::number(rand() % 4096), instr);
//ui->filePreview->setText(file);

void randomFileOptionsDialog::on_generate_clicked()
{
    std::vector<QString> names = {"Text Processor", "Web Browser", "Video Game", "Chat"};
    std::vector<QString> instrs = {"CALCULATE", "I/O", "OUT"};
    QString instr;
    unsigned int runtime = 0;
    for(int i = 0; i < 100; i++){
        QString it = instrs.at(rand() % 2);
        unsigned int rt = (rand() % 75 + 1);
        if(it == "CALCULATE"){
            runtime += rt;
        }else if(it == "OUT"){
            it += names.at(rand()% 4);
        }
        instr += QString("%1 %2\n").arg(it, QString::number(rt));
    }
    instr += "EXE";
    QString file = QString("Name: %1\nTotal runtime: %2\nMemory: %3\n\n%4").arg(names.at(rand() % 4), QString::number(runtime), QString::number(rand() % 4096), instr);
    ui->plainTextEdit->setPlainText(file);

}
