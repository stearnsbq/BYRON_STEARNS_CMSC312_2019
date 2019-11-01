#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <string>
#include "mainwindow.h"
#include "main.hpp"
#include <stdio.h>
#include <thread>
#include <QPushButton>
#include <string.h>
#include <string>
#include <stdlib.h>
#include "fileoptionsdialog.h"
#include <fstream>
#include <QGraphicsRectItem>
#include <sstream>
#include <iostream>
#include <locale>
#include <QApplication>
#include <QPainter>
#include <QObject>
#include "PCB.hpp"
#include <QScrollBar>
#include <QGraphicsScene>
#include <QMap>
#include "loadfiledialog.h"
#include <QMessageBox>


using namespace std;

QTextEdit *ptr;

void MainWindow::createProcess(string instructions, int number, bool toRandom)
{
    Process p = Process();
    istringstream f(instructions);
    for (string line; getline(f, line);)
    {
        if (line.find("Name:") != string::npos)
        {
            string name = line.substr(line.find(":") + 2);

            p.setName(name);
        }
        else if (line.find("Total runtime:") != string::npos)
        {
            string runtime = line.substr(line.find(":") + 2);

            if(!toRandom) {
                p.setCycles(stoi(runtime));
            }
        }
        else if (line.find("Memory:") != string::npos)
        {
            string memory = line.substr(line.find(":") + 2);
            p.setMemoryReq(stoi(memory));
        }
        else
        {
            if (line.length() > 0)
            {
                if (line == "EXE")
                {
                    break;
                }
                p.addInstruction(line, toRandom);
            }
        }
    }
    for (int i = 0; i < number; i++)
    {
        p.setPriority(0);
        kernel::getInstance().newProcess(p);
    }
    cout << "Program: " << p.getName() << " Loaded!"<< " Processes created: " << number  << endl;
}



void MainWindow::updateText(std::string in){
    QString str = QString::fromUtf8(in.c_str());
    ptr->append(str);
    ptr->verticalScrollBar()->setValue(ptr->verticalScrollBar()->maximum());
}


void MainWindow::changeStatus(){
    QPalette pal;
    pal.setColor(QPalette::WindowText, Qt::red);
    ui->isRunning->setText("Not Running...");
    ui->isRunning->setPalette(pal);
    this->isRunning = false;


}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    kernel::getInstance().window = this;
    qRegisterMetaType<std::string>("std::string");
    connect(this, &MainWindow::print, this, &MainWindow::updateText);
    connect(this, &MainWindow::done, this, &MainWindow::changeStatus);
    ptr = ui->simulatorOut;
    ptr->setReadOnly(true);
    QPalette pal;
    pal.setColor(QPalette::WindowText, Qt::red);
    ui->isRunning->setPalette(pal);
    this->isRunning = false;
    ui->MLQListView->setVisible(false);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::save(){

}


void MainWindow::on_loadFile_clicked()
{
    this->loadfile = new loadFileDialog();
    this->loadfile->setFixedSize(this->loadfile->size());
    connect(this->loadfile, &loadFileDialog::createProcesses, this, &MainWindow::createProcess);
    ui->simulatorOut->clear();
    loadfile->show();

}

void MainWindow::on_startSim_clicked()
{
    if(!this->isRunning) {
        QPalette pal;
        pal.setColor(QPalette::WindowText, Qt::green);
        ui->isRunning->setText("Running!");
        ui->isRunning->setPalette(pal);
        std::thread run = std::thread(&CPU::start, &CPU::getInstance(), ui->time->value(), ui->timeUnit->currentText());
        run.detach();
        this->isRunning = true;
    }else{
        QMessageBox::warning(this, "Already Running!!", "The simulator is already running!");
    }

}

void MainWindow::on_algorithm_activated(const QString &arg1)
{

}

void MainWindow::on_timeUnit_activated(const QString &arg1)
{

}
