#ifndef STUDENTSWORKSHOPDIALOG_H
#define STUDENTSWORKSHOPDIALOG_H

#include <QDialog>

namespace Ui {
class StudentsWorkshopDialog;
}

class StudentsWorkshopDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StudentsWorkshopDialog(QWidget *parent = 0);
    ~StudentsWorkshopDialog();

private:
    Ui::StudentsWorkshopDialog *ui;
};

#endif // STUDENTSWORKSHOPDIALOG_H
