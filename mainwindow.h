#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QPushButton>

#include "ui_studentsworkshopdialog.h"
#include "ui_studentstimedialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    struct time{
        QString day;
        QTime from;
        QTime to;
    };
    Ui::MainWindow *ui;
    Ui::StudentsWorkshopDialog SWUi;
    Ui::StudentsTimeDialog STUi;
    QSettings data;
    void loadData();
    void saveData();
    QPushButton* createNewStudent;
    QPushButton* createNewWorkshop;
    QDialog *SWDialog = new QDialog(this);
    QDialog *STDialog = new QDialog(this);
    QHash<QString, QString> studentsChoice;
    QHash<QString, time> studentsTime;
};

#endif // MAINWINDOW_H
