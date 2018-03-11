#include "studentsworkshopdialog.h"
#include "ui_studentsworkshopdialog.h"

StudentsWorkshopDialog::StudentsWorkshopDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentsWorkshopDialog)
{
    ui->setupUi(this);
}

StudentsWorkshopDialog::~StudentsWorkshopDialog()
{
    delete ui;
}
