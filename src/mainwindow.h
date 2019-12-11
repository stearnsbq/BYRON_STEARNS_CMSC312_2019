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
#include <QTableWidget>

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
Ui::MainWindow *ui;
//void updateText(std::string in);


private:

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
void printText(std::string in);
void onUpdateSchedulerUI(Process p, std::string widget, int q = -1, int core = 1);
void onSetFreeFrameCount(int count);
void onSetUsedFrameCount(int count);



signals:
void setMemoryGraphic(int frameNumber, bool beingUsed);
void print(std::string in);
void done();
void updateProcessListGUI(Process p);
void updateMemoryBarGUI(int amount);
void setCritical(bool set);
void setLoad(int core, int load);
void updateSchedulerUI(Process p, std::string widget, int q = -1, int core = 1);
void setFreeFrameCount(int count);
void setUsedFrameCount(int count);
private slots:
void on_loadFile_clicked();
void on_startSim_clicked();
void on_stop_clicked();
void on_CommandInput_returnPressed();
};

#endif // MAINWINDOW_H
