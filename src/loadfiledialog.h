#ifndef LOADFILEDIALOG_H
#define LOADFILEDIALOG_H

#include <QDialog>
#include <QJsonDocument>

namespace Ui {
class loadFileDialog;
}

class loadFileDialog : public QDialog
{
Q_OBJECT

public:
explicit loadFileDialog(QWidget *parent = nullptr);
~loadFileDialog();

private slots:
void on_pushButton_clicked();

void on_pushButton_2_clicked();

signals:
void createProcesses(QJsonDocument data, int number, bool random);

private:
Ui::loadFileDialog *ui;
QJsonDocument loadFile(std::string fileName);
void passData(QJsonDocument data, int number, bool random);
};

#endif // LOADFILEDIALOG_H
