#include "randomfileoptionsdialog.h"
#include "ui_randomfileoptionsdialog.h"

randomFileOptionsDialog::randomFileOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::randomFileOptionsDialog)
{
    ui->setupUi(this);
}

randomFileOptionsDialog::~randomFileOptionsDialog()
{
    delete ui;
}
