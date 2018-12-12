#ifndef STUDENTSRELATIONDIALOG_H
#define STUDENTSRELATIONDIALOG_H

#include <QDialog>

namespace Ui {
class StudentsRelationDialog;
}

class StudentsRelationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StudentsRelationDialog(QWidget *parent = nullptr);
    ~StudentsRelationDialog();

private:
    Ui::StudentsRelationDialog *ui;
};

#endif // STUDENTSRELATIONDIALOG_H
