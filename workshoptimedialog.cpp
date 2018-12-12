#include "workshoptimedialog.h"
#include "ui_workshoptimedialog.h"

WorkshopTimeDialog::WorkshopTimeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorkshopTimeDialog)
{
    ui->setupUi(this);
}

WorkshopTimeDialog::~WorkshopTimeDialog()
{
    delete ui;
}
