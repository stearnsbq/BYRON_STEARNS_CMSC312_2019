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
#include <QSplashScreen>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap img(":/img/resources/osSim.png");
    QSplashScreen load(img);

    load.show();
    std::this_thread::sleep_for(std::chrono::seconds(2));


    MainWindow simulatorUI;
    simulatorUI.show();
    load.finish(&simulatorUI);
    return a.exec();
}
