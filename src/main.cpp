#include "mainwindow.h"
#include "main.hpp"
#include <stdio.h>
#include <thread>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <locale>
#include <QApplication>
#include <QObject>
#include "PCB.hpp"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow simulatorUI;
    simulatorUI.show();

    return a.exec();
}
