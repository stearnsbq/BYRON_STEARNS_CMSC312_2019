#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <string>
#include <QMainWindow>
#include "loadfiledialog.h"

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
    loadFileDialog * loadfile;
    void drawMemory();
signals:
    void print(std::string in);
private slots:
    void on_loadFile_clicked();
};
#endif // MAINWINDOW_H
