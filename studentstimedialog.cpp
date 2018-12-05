#include "studentstimedialog.h"
#include "ui_studentstimedialog.h"

StudentsTimeDialog::StudentsTimeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentsTimeDialog)
{
    ui->setupUi(this);
}

StudentsTimeDialog::~StudentsTimeDialog()
{
    delete ui;
}
