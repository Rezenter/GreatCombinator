#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QPushButton>

#include "ui_studentsworkshopdialog.h"

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
    Ui::MainWindow *ui;
    Ui::StudentsWorkshopDialog SWUi;
    QSettings data;
    void loadData();
    void saveData();
    QPushButton* createNewStudent;
    QPushButton* createNewWorkshop;
    QDialog *SWDialog = new QDialog(this);
    QHash<QString, QString> studentsChoice;
};

#endif // MAINWINDOW_H
