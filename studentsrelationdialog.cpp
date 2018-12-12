#include "studentsrelationdialog.h"
#include "ui_studentsrelationdialog.h"

StudentsRelationDialog::StudentsRelationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentsRelationDialog)
{
    ui->setupUi(this);
}

StudentsRelationDialog::~StudentsRelationDialog()
{
    delete ui;
}
