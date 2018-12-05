#ifndef STUDENTSTIMEDIALOG_H
#define STUDENTSTIMEDIALOG_H

#include <QDialog>

namespace Ui {
class StudentsTimeDialog;
}

class StudentsTimeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StudentsTimeDialog(QWidget *parent = nullptr);
    ~StudentsTimeDialog();

private:
    Ui::StudentsTimeDialog *ui;
};

#endif // STUDENTSTIMEDIALOG_H
