#ifndef RANDOMFILEOPTIONSDIALOG_H
#define RANDOMFILEOPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class randomFileOptionsDialog;
}

class randomFileOptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit randomFileOptionsDialog(QWidget *parent = nullptr);
    ~randomFileOptionsDialog();
signals:
    void isDone(std::string data, int number, bool random);

private slots:
    void on_generate_clicked();

    void on_done_clicked();

private:
    Ui::randomFileOptionsDialog *ui;
    std::string fileData;
};

#endif // RANDOMFILEOPTIONSDIALOG_H
