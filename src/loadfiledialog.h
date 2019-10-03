#ifndef LOADFILEDIALOG_H
#define LOADFILEDIALOG_H

#include <QDialog>

namespace Ui {
class loadFileDialog;
}

class loadFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loadFileDialog(QWidget *parent = nullptr);
    ~loadFileDialog();

private:
    Ui::loadFileDialog *ui;
};

#endif // LOADFILEDIALOG_H
