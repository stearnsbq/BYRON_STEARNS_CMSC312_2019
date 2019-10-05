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

private:
    Ui::randomFileOptionsDialog *ui;
};

#endif // RANDOMFILEOPTIONSDIALOG_H
