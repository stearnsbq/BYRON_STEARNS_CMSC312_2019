#include "fileoptionsdialog.h"
#include "ui_fileoptionsdialog.h"

fileOptionsDialog::fileOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fileOptionsDialog)
{
    ui->setupUi(this);
}

fileOptionsDialog::~fileOptionsDialog()
{
    delete ui;
}
