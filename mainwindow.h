#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>

#include "ui_studentsworkshopdialog.h"
#include "ui_studentstimedialog.h"
#include "ui_studentsrelationdialog.h"
#include "ui_workshoptimedialog.h"
#include <QRandomGenerator>

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
    struct relation{
        QString target;
        int rel;
    };
    Ui::MainWindow *ui;
    Ui::StudentsWorkshopDialog SWUi;
    Ui::StudentsTimeDialog STUi;
    Ui::StudentsRelationDialog SRUi;
    Ui::WorkshopTimeDialog WTUi;
    QSettings data;
    void loadData();
    void saveData();
    QPushButton* createNewStudent;
    QPushButton* createNewWorkshop;
    QDialog *SWDialog = new QDialog(this);
    QDialog *STDialog = new QDialog(this);
    QDialog *SRDialog = new QDialog(this);
    QDialog *WTDialog = new QDialog(this);
    QHash<QString, QString> studentsChoice;
    QHash<QString, time> studentsTime;
    QHash<QString, relation> studentsRelation;
    QHash<QString, time> workshopsTime;
    QRandomGenerator random;
    bool compare(int a, int b);
};

#endif // MAINWINDOW_H
