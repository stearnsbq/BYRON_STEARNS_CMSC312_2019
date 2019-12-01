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
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <programfilegenerator.h>


using namespace std;

QTextEdit *ptr;

void MainWindow::createProcess(QJsonDocument programFile, int number, bool toRandom)
{
    Process p = Process();

    QJsonObject obj = programFile.object();
    QJsonArray arr = obj["instructions"].toArray();


    p.setName(obj["Name"].toString().toStdString());
    p.setCycles(obj["Runtime"].toInt());
    p.setMemoryReq(obj["Memory"].toInt());


    foreach (QJsonValue value, arr) {
        QJsonObject obj = value.toObject();
        p.addInstruction(obj, toRandom);
    }


    for (int i = 0; i < number; i++)
    {
        p.setPriority(rand()% 100 + 1);
        kernel::getInstance().newProcess(p);
    }
    cout << "Program: " << p.getName() << " Loaded!"<< " Processes created: " << number  << endl;
    this->initProcessList();
}



void MainWindow::onSetLoad(int core, int load){
    if(core == 1) {
        ui->core1->display(load);
    }else{
        ui->core2->display(load);
    }
}

void MainWindow::updateText(std::string in){
//    QString str = QString::fromUtf8(in.c_str());
//    ptr->append(str);
//    ptr->verticalScrollBar()->setValue(ptr->verticalScrollBar()->maximum());
}


void MainWindow::changeStatus(){
    QPalette pal;
    pal.setColor(QPalette::WindowText, Qt::red);
    ui->isRunning->setText("Not Running...");
    ui->isRunning->setPalette(pal);
    this->isRunning = false;


}

void MainWindow::initProcessList(){
    std::unordered_map<int, Process> processes = kernel::getInstance().getListOfProcesses();
    ui->processList->setRowCount(processes.size());
    for(std::pair<int, Process> e : processes) {
        QTableWidgetItem * name =  new QTableWidgetItem(QString::fromUtf8(e.second.getName().c_str()));
        name->setToolTip(e.second.toString());
        ui->processList->setItem(e.first, 0, new QTableWidgetItem(QString::number(e.second.getPid())));
        ui->processList->setItem(e.first, 1, name );
        ui->processList->setItem(e.first, 2, new QTableWidgetItem(e.second.getStateString()));
    }
}

void MainWindow::updateProcessList(Process p){

    if(ui->processList->rowCount() < kernel::getInstance().getListOfProcesses().size() - 1) {
        ui->processList->setRowCount(kernel::getInstance().getListOfProcesses().size() - 1);
    }

    QTableWidgetItem * pid =  new QTableWidgetItem(QString::number(p.getPid()));
    QTableWidgetItem * name =  new QTableWidgetItem(QString::fromUtf8(p.getName().c_str()));
    QTableWidgetItem * state =  new QTableWidgetItem(p.getStateString());

    name->setToolTip(p.toString());

    ui->processList->setItem(p.getPid(), 0, pid);
    ui->processList->setItem(p.getPid(), 1, name);
    ui->processList->setItem(p.getPid(), 2, state);

}

void MainWindow::updateMemoryBar(int amount){
    this->ui->memoryUsage->setValue(this->ui->memoryUsage->value() + amount);

}

void MainWindow::onSetCritical(bool set){
    if(set) {
        ui->criticalSecFrame->setStyleSheet("background-color: green;");
    }else{
        ui->criticalSecFrame->setStyleSheet("background-color: red;");
    }

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(width(), height());
    srand(time(nullptr));
    kernel::getInstance().window = this;
    qRegisterMetaType<std::string>("std::string");
    qRegisterMetaType<Process>("Process");
    connect(this, &MainWindow::print, this, &MainWindow::updateText);
    connect(this, &MainWindow::done, this, &MainWindow::changeStatus);
    connect(this, &MainWindow::updateProcessListGUI, this, &MainWindow::updateProcessList);
    connect(this, &MainWindow::updateMemoryBarGUI, this, &MainWindow::updateMemoryBar);
    connect(this, &MainWindow::setCritical, this, &MainWindow::onSetCritical);
    connect(this, &MainWindow::setLoad, this, &MainWindow::onSetLoad);
    ptr = ui->simulatorOut;
    ptr->setReadOnly(true);
    ui->processList->setColumnWidth(0, 15);
    this->ui->memoryUsage->setRange(0, 4096000);
    ui->processList->verticalHeader()->setVisible(false);
    QPalette pal;
    pal.setColor(QPalette::WindowText, Qt::red);
    ui->isRunning->setPalette(pal);
    this->isRunning = false;
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


void MainWindow::simulateOS(){

    programfilegenerator gen = programfilegenerator();

    while(true) {

        if((rand() % 100) < 5) {
            this->createProcess(gen.generate(), 1, false);
        }


        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 256 + 32));

    }

}

void MainWindow::on_startSim_clicked()
{
    kernel::getInstance().shutDown = false;

    if(!this->isRunning) {
        QPalette pal;
        pal.setColor(QPalette::WindowText, Qt::green);
        ui->isRunning->setText("Running!");
        ui->isRunning->setPalette(pal);

        if(ui->simulate->isChecked()) {

            std::thread sim(&MainWindow::simulateOS, this);
            sim.detach();
        }

        CPU::getInstance().start(ui->time->value(), ui->timeUnit->currentText());

        this->isRunning = true;
    }else{
        QMessageBox::warning(this, "Already Running!!", "The simulator is already running!");
    }

}

void MainWindow::on_algorithm_activated(const QString &arg1)
{
//    if(arg1 == "Round Robin") {
//        kernel::getInstance().setShortTermAlgo(ROUND_ROBIN);
//    }else if(arg1 == "Multi-Level Feedback Queue") {
//        kernel::getInstance().setShortTermAlgo(MULTILEVEL_FEEDBACK_QUEUE);
//    }

}

void MainWindow::on_timeUnit_activated(const QString &arg1)
{

}

void MainWindow::on_stop_clicked()
{
    this->isRunning = false;
    kernel::getInstance().shutDown = true;
}
