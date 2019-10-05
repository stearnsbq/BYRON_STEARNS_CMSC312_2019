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

private:
    Ui::fileOptionsDialog *ui;
};

#endif // FILEOPTIONSDIALOG_H
