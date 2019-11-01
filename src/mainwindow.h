#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <string>
#include <QMainWindow>
#include "mainmemory.h"
#include "loadfiledialog.h"
#include "CPU.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
MainWindow(QWidget *parent = nullptr);
~MainWindow();
void updateText(std::string in);

private:
Ui::MainWindow *ui;
void save();
void createProcess(std::string instructions, int number, bool toRandom);
void loadFileThread();
char *parseCommand(char *cmd);
void cli();
bool isRunning;
void changeStatus();
loadFileDialog * loadfile;
void drawMemory();
signals:
void print(std::string in);
void done();
private slots:
void on_loadFile_clicked();
void on_startSim_clicked();
void on_comboBox_activated(const QString &arg1);
void on_algorithm_activated(const QString &arg1);
void on_timeUnit_activated(const QString &arg1);
};
#endif // MAINWINDOW_H
