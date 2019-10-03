#include "loadfiledialog.h"
#include "ui_loadfiledialog.h"

loadFileDialog::loadFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loadFileDialog)
{
    ui->setupUi(this);
}

loadFileDialog::~loadFileDialog()
{
    delete ui;
}
