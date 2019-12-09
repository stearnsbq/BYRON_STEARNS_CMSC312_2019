#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <string>
#include <QMainWindow>
#include "mainmemory.h"
#include "loadfiledialog.h"
#include "CPU.hpp"
#include <QJsonDocument>
#include <shorttermscheduler.h>
#include <QGraphicsRectItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
Q_DECLARE_METATYPE(ALGORITHM)

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
MainWindow(QWidget *parent = nullptr);
~MainWindow();
//void updateText(std::string in);


private:
Ui::MainWindow *ui;
std::vector<QGraphicsRectItem *> memory;
void save();
void initUI();
void initProcessList();
void createProcess(QJsonDocument instructions, int number, bool toRandom);
void loadFileThread();
char *parseCommand(char *cmd);
void cli();
bool isRunning;
void changeStatus();
loadFileDialog * loadfile;
void simulateOS();
void drawMemory();
void updateMemoryGraphic(int frameNumber, bool beingUsed);
void updateProcessList(Process p);
void updateNewQueue();
void updateReadyQueue();
void updateWaitingQueue();
void updateMemoryBar(int amount);
void onSetCritical(bool set);
void onSetLoad(int core, int load);
signals:
void setMemoryGraphic(int frameNumber, bool beingUsed);
void print(std::string in);
void done();
void updateProcessListGUI(Process p);
void updateMemoryBarGUI(int amount);
void setCritical(bool set);
void setLoad(int core, int load);
private slots:
void on_loadFile_clicked();
void on_startSim_clicked();
void on_timeUnit_activated(const QString &arg1);
void on_stop_clicked();
};

#endif // MAINWINDOW_H
