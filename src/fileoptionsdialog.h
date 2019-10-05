#ifndef FILEOPTIONSDIALOG_H
#define FILEOPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class fileOptionsDialog;
}

class fileOptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit fileOptionsDialog(QWidget *parent = nullptr);
    ~fileOptionsDialog();
    void fileData(std::string data);
signals:
    void isDone(std::string data, int number, bool random);

private slots:
    void on_done_clicked();


private:
    Ui::fileOptionsDialog *ui;
        std::string file;
};

#endif // FILEOPTIONSDIALOG_H
