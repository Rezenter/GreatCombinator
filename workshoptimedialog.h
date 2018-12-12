#ifndef WORKSHOPTIMEDIALOG_H
#define WORKSHOPTIMEDIALOG_H

#include <QDialog>

namespace Ui {
class WorkshopTimeDialog;
}

class WorkshopTimeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WorkshopTimeDialog(QWidget *parent = nullptr);
    ~WorkshopTimeDialog();

private:
    Ui::WorkshopTimeDialog *ui;
};

#endif // WORKSHOPTIMEDIALOG_H
