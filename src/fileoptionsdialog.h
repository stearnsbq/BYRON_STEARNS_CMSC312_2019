#ifndef FILEOPTIONSDIALOG_H
#define FILEOPTIONSDIALOG_H

#include <QDialog>
#include <QJsonDocument>
namespace Ui {
class fileOptionsDialog;
}

class fileOptionsDialog : public QDialog
{
Q_OBJECT

public:
explicit fileOptionsDialog(QWidget *parent = nullptr);
~fileOptionsDialog();
void fileData(QJsonDocument data);
signals:
void isDone(QJsonDocument data, int number, bool random);

private slots:
void on_done_clicked();


private:
Ui::fileOptionsDialog *ui;
QJsonDocument file;
};

#endif // FILEOPTIONSDIALOG_H
