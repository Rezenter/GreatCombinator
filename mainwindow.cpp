#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCoreApplication>
#include <QSpinBox>
#include <QListWidget>

#include <QDebug>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Great Combinator");
    ui->studentsTable->setSelectionMode(QAbstractItemView::NoSelection);
    QStringList studentLabels;
    studentLabels.append("Use");
    studentLabels.append("Name");
    studentLabels.append("Surname");
    studentLabels.append("Weight");
    studentLabels.append("Workshops");
    studentLabels.append("Time");
    studentLabels.append("Relations");
    studentLabels.append("History");
    studentLabels.append("Remove");
    ui->studentsTable->setColumnCount(studentLabels.size());
    ui->studentsTable->setHorizontalHeaderLabels(studentLabels);
    ui->studentsTable->insertRow(0);
    createNewStudent = new QPushButton(ui->studentsTable);
    createNewStudent->setText("new");
    QPalette pal = createNewStudent->palette();
    pal.setColor(QPalette::Button, QColor(Qt::green));
    createNewStudent->setAutoFillBackground(true);
    createNewStudent->setPalette(pal);
    ui->studentsTable->setCellWidget(0, 1, createNewStudent);
    QObject::connect(createNewStudent, &QPushButton::pressed, this, [=]{
        int row = ui->studentsTable->rowCount() - 1;
        ui->studentsTable->insertRow(row);
        QTableWidgetItem* use = new QTableWidgetItem("");
        use->setCheckState(Qt::Checked);
        use->setFlags(use->flags().setFlag(Qt::ItemIsEditable, false));
        ui->studentsTable->setItem(row, 0, use);
        ui->studentsTable->setItem(row, 1, new QTableWidgetItem("Name"));
        ui->studentsTable->setItem(row, 2, new QTableWidgetItem("Surname"));
        QSpinBox* weight = new QSpinBox(ui->studentsTable);
        weight->setValue(1);
        ui->studentsTable->setCellWidget(row, 3, weight);
        QPushButton* workshops = new QPushButton(ui->studentsTable);
        workshops->setProperty("row", row);
        workshops->setText("edit");
        ui->studentsTable->setCellWidget(row, 4, workshops);
        QObject::connect(workshops, &QPushButton::pressed, this, [=]{
            int editingRow = QObject::sender()->property("row").toInt();
            QString key = ui->studentsTable->item(editingRow, 1)->text() + "_" + ui->studentsTable->item(editingRow, 2)->text();
            QList<QString> choice = studentsChoice.values(key);
            for(int i = 0; i < SWUi.table->rowCount(); ++i){
                SWUi.table->item(i, 1)->setText(ui->workshopTable->item(i, 1)->text());
                if(choice.contains(SWUi.table->item(i, 1)->text())){
                    SWUi.table->item(i, 0)->setCheckState(static_cast<Qt::CheckState>(2));
                }else{
                    SWUi.table->item(i, 0)->setCheckState(static_cast<Qt::CheckState>(0));
                }
            }
            SWDialog->setProperty("row", editingRow);
            SWDialog->show();
        });
        QPushButton* time = new QPushButton(ui->studentsTable);
        time->setProperty("row", row);
        time->setText("edit");
        ui->studentsTable->setCellWidget(row, 5, time);
        QObject::connect(time, &QPushButton::pressed, this, [=]{
            int editingRow = QObject::sender()->property("row").toInt();
            //call dialog
            //setText
            time->setText("edited");
        });
        QPushButton* relations = new QPushButton(ui->studentsTable);
        relations->setProperty("row", row);
        relations->setText("edit");
        ui->studentsTable->setCellWidget(row, 6, relations);
        QObject::connect(relations, &QPushButton::pressed, this, [=]{
            int editingRow = QObject::sender()->property("row").toInt();
            //call dialog
            //setText
            relations->setText("edited");
        });
        QListWidget* history = new QListWidget(ui->studentsTable);
        history->addItem("none");
        ui->studentsTable->setCellWidget(row, 7, history);
        QPushButton* remove = new QPushButton(ui->studentsTable);
        remove->setProperty("row", row);
        remove->setText("remove");
        QPalette pal = remove->palette();
        pal.setColor(QPalette::Button, QColor(Qt::red));
        remove->setAutoFillBackground(true);
        remove->setPalette(pal);
        ui->studentsTable->setCellWidget(row, 8, remove);
        QObject::connect(remove, &QPushButton::pressed, this, [=]{
            int removingRow = QObject::sender()->property("row").toInt();
            ui->studentsTable->removeRow(removingRow);                                              //memory leak
            for(int i = removingRow; i < ui->studentsTable->rowCount() - 1; ++i){
                ui->studentsTable->cellWidget(i, 8)->setProperty("row", i);
            }
        });
    });

    ui->workshopTable->setSelectionMode(QAbstractItemView::NoSelection);
    QStringList workshopLabels;
    workshopLabels.append("Use");
    workshopLabels.append("Name");
    workshopLabels.append("Real Cap.");
    workshopLabels.append("Weight Cap.");
    workshopLabels.append("Time");
    workshopLabels.append("Remove");
    ui->workshopTable->setColumnCount(workshopLabels.size());
    ui->workshopTable->setHorizontalHeaderLabels(workshopLabels);
    ui->workshopTable->insertRow(0);
    createNewWorkshop = new QPushButton(ui->workshopTable);
    createNewWorkshop->setText("new");
    pal = createNewWorkshop->palette();
    pal.setColor(QPalette::Button, QColor(Qt::green));
    createNewWorkshop->setAutoFillBackground(true);
    createNewWorkshop->setPalette(pal);
    ui->workshopTable->setCellWidget(0, 1, createNewWorkshop);
    QObject::connect(createNewWorkshop, &QPushButton::pressed, this, [=]{
        int row = ui->workshopTable->rowCount() - 1;
        ui->workshopTable->insertRow(row);
        QTableWidgetItem* use = new QTableWidgetItem("");
        use->setCheckState(Qt::Checked);
        use->setFlags(use->flags().setFlag(Qt::ItemIsEditable, false));
        ui->workshopTable->setItem(row, 0, use);
        ui->workshopTable->setItem(row, 1, new QTableWidgetItem("Name"));
        QSpinBox* rCap = new QSpinBox(ui->workshopTable);
        rCap->setValue(10);
        ui->workshopTable->setCellWidget(row, 2, rCap);
        QSpinBox* wCap = new QSpinBox(ui->workshopTable);
        wCap->setValue(10);
        ui->workshopTable->setCellWidget(row, 3, wCap);
        QPushButton* time = new QPushButton(ui->workshopTable);
        time->setProperty("row", row);
        time->setText("edit");
        ui->workshopTable->setCellWidget(row, 4, time);
        QObject::connect(time, &QPushButton::pressed, this, [=]{
            int editingRow = QObject::sender()->property("row").toInt();
            //call dialog
            //setText
            time->setText("edited");
        });
        QPushButton* remove = new QPushButton(ui->workshopTable);
        remove->setProperty("row", row);
        remove->setText("remove");
        QPalette pal = remove->palette();
        pal.setColor(QPalette::Button, QColor(Qt::red));
        remove->setAutoFillBackground(true);
        remove->setPalette(pal);
        ui->workshopTable->setCellWidget(row, 5, remove);
        QObject::connect(remove, &QPushButton::pressed, this, [=]{
            int removingRow = QObject::sender()->property("row").toInt();
            ui->workshopTable->removeRow(removingRow);                                              //memory leak
            SWUi.table->removeRow(removingRow);
            for(int i = removingRow; i < ui->workshopTable->rowCount() - 1; ++i){
                ui->workshopTable->cellWidget(i, 5)->setProperty("row", i);
            }
        });
        SWUi.table->insertRow(row);
        use = new QTableWidgetItem("");
        use->setCheckState(Qt::Checked);
        use->setFlags(use->flags().setFlag(Qt::ItemIsEditable, false));
        SWUi.table->setItem(row, 0, use);
        SWUi.table->setItem(row, 1, new QTableWidgetItem("Name"));
    });


    SWUi.setupUi(SWDialog);
    SWUi.table->setSelectionMode(QAbstractItemView::NoSelection);
    QStringList SWLabels;
    SWLabels.append("Use");
    SWLabels.append("Name");
    SWUi.table->setColumnCount(SWLabels.size());
    SWUi.table->setHorizontalHeaderLabels(SWLabels);
    SWDialog->setWindowTitle("Assign/edit students workshops");
    SWDialog->setModal(true);
    QObject::connect(SWDialog, &QDialog::accepted, this, [=]{
        int row = SWDialog->property("row").toInt();
        QString key = ui->studentsTable->item(row, 1)->text() + "_" + ui->studentsTable->item(row, 2)->text();
        int j = 0;
        studentsChoice.remove(key);
        for(int i = 0; i < SWUi.table->rowCount(); ++i){
            if(SWUi.table->item(i, 0)->checkState() == Qt::Checked){
                studentsChoice.insertMulti(key, SWUi.table->item(i, 1)->text());
                ++j;
            }
        }
        dynamic_cast<QPushButton*>(ui->studentsTable->cellWidget(row, 4))->setText("selected " + QString::number(j));
    });

    loadData();
}

MainWindow::~MainWindow()
{
    saveData();
    delete SWDialog;
    delete createNewStudent;
    delete createNewWorkshop;
    delete ui;
}


void MainWindow::loadData(){
    QSettings data(QApplication::applicationDirPath() + "/data.ini", QSettings::IniFormat);
    data.beginGroup("common");
        resize(data.value("windowSize", QSize(800, 600)).toSize());
        move(data.value("windowPosition", QPoint(0, 0)).toPoint());
    data.endGroup();
    data.beginGroup("students");
        int columnCount = data.beginReadArray("columns");
            for(int i = 0; i < columnCount; ++i){
                data.setArrayIndex(i);
                ui->studentsTable->setColumnWidth(i, data.value("width", 20). toInt());
            }
        data.endArray();
        int rowCount = data.beginReadArray("rows");
        for(int i = 0; i < rowCount; ++i){
            data.setArrayIndex(i);
            createNewStudent->pressed();
            ui->studentsTable->item(i, 0)->setCheckState(static_cast<Qt::CheckState>(data.value("use", Qt::Unchecked).toUInt()));
            ui->studentsTable->item(i, 1)->setText(data.value("name", "not loaded").toString());
            ui->studentsTable->item(i, 2)->setText(data.value("surname", "not loaded").toString());
            QSpinBox* weight = dynamic_cast<QSpinBox*> ((ui->studentsTable->cellWidget(i, 3)));
            weight->setValue(data.value("weight", 1).toInt());
            int choiceSize = data.beginReadArray("workshops");
                QString key = ui->studentsTable->item(i, 1)->text() + "_" + ui->studentsTable->item(i, 2)->text();
                for(int j = 0; j < choiceSize; ++j){
                    data.setArrayIndex(j);
                    studentsChoice.insertMulti(key, data.value("chosen", "not Loaded").toString());
                }
                dynamic_cast<QPushButton*>(ui->studentsTable->cellWidget(i, 4))->setText("selected " + QString::number(choiceSize));
            data.endArray();
            /*
            studentLabels.append("Workshops");
            studentLabels.append("Time");
            studentLabels.append("Relations");
            */
            QListWidget* history = dynamic_cast<QListWidget*> ((ui->studentsTable->cellWidget(i, 7)));
            history->clear();
            int itemsCount = data.beginReadArray("history");
            for(int j = 0; j < itemsCount; ++j){
                data.setArrayIndex(j);
                history->addItem(data.value("item", "not loaded").toString());
            }
            data.endArray();
        }
        data.endArray();
    data.endGroup();
    data.beginGroup("SWDialog");
        SWDialog->resize(data.value("dialogSize", QSize(800, 600)).toSize());
        SWDialog->move(data.value("dialogPosition", QPoint(0, 0)).toPoint());
        columnCount = data.beginReadArray("columns");
        for(int i = 0; i < columnCount; ++i){
            data.setArrayIndex(i);
            SWUi.table->setColumnWidth(i, data.value("width", 20). toInt());
        }
        data.endArray();
    data.endGroup();
    data.beginGroup("workshops");
        columnCount = data.beginReadArray("columns");
        for(int i = 0; i < columnCount; ++i){
            data.setArrayIndex(i);
            ui->workshopTable->setColumnWidth(i, data.value("width", 20). toInt());
        }
        data.endArray();
        rowCount = data.beginReadArray("rows");
        for(int i = 0; i < rowCount; ++i){
            data.setArrayIndex(i);
            createNewWorkshop->pressed();
            ui->workshopTable->item(i, 0)->setCheckState(static_cast<Qt::CheckState>(data.value("use", Qt::Unchecked).toUInt()));
            ui->workshopTable->item(i, 1)->setText(data.value("name", "not loaded").toString());
            QSpinBox* rCap = dynamic_cast<QSpinBox*> ((ui->workshopTable->cellWidget(i, 2)));
            rCap->setValue(data.value("rCap", 1).toInt());
            QSpinBox* wCap = dynamic_cast<QSpinBox*> ((ui->workshopTable->cellWidget(i, 3)));
            wCap->setValue(data.value("wCap", 1).toInt());
            /*
            workshopLabels.append("Time");
            */
        }
        data.endArray();
    data.endGroup();
}

void MainWindow::saveData(){
    QSettings data(QApplication::applicationDirPath() + "/data.ini", QSettings::IniFormat);
    data.clear();
    data.beginGroup("common");
        data.setValue("windowSize", size());
        data.setValue("windowPosition", pos());
    data.endGroup();
    data.beginGroup("students");
        data.beginWriteArray("columns");
        for(int i = 0; i < ui->studentsTable->columnCount(); ++i){
            data.setArrayIndex(i);
            data.setValue("width", ui->studentsTable->columnWidth(i));
        }
        data.endArray();
        data.beginWriteArray("rows");
        for(int i = 0; i < ui->studentsTable->rowCount() - 1; ++i){
            data.setArrayIndex(i);
            data.setValue("use", ui->studentsTable->item(i, 0)->checkState());
            data.setValue("name", ui->studentsTable->item(i, 1)->text());
            data.setValue("surname", ui->studentsTable->item(i, 2)->text());
            QSpinBox* weight = dynamic_cast<QSpinBox*> ((ui->studentsTable->cellWidget(i, 3)));
            data.setValue("weight", weight->value());
            data.beginWriteArray("workshops");
                QString key = ui->studentsTable->item(i, 1)->text() + "_" + ui->studentsTable->item(i, 2)->text();
                QList<QString> choice = studentsChoice.values(key);
                qDebug() << key << choice;
                for(int j = 0; j < choice.size(); ++j){
                    data.setArrayIndex(j);
                    data.setValue("chosen", choice.at(j));
                }
            data.endArray();
            /*
            studentLabels.append("Time");
            studentLabels.append("Relations");
            */
            QListWidget* history = dynamic_cast<QListWidget*> ((ui->studentsTable->cellWidget(i, 7)));
            data.beginWriteArray("history");
            for(int j = 0; j < history->count(); ++j){
                data.setArrayIndex(j);
                data.setValue("item", history->item(j)->text());
            }
            data.endArray();
        }
        data.endArray();
    data.endGroup();
    data.beginGroup("SWDialog");
        data.setValue("dialogSize", SWDialog->size());
        data.setValue("dialogPosition", SWDialog->pos());
        data.beginWriteArray("columns");
        for(int i = 0; i < SWUi.table->columnCount(); ++i){
            data.setArrayIndex(i);
            data.setValue("width", SWUi.table->columnWidth(i));
        }
        data.endArray();
    data.endGroup();
    data.beginGroup("workshops");
        data.beginWriteArray("columns");
        for(int i = 0; i < ui->workshopTable->columnCount(); ++i){
            data.setArrayIndex(i);
            data.setValue("width", ui->workshopTable->columnWidth(i));
        }
        data.endArray();
        data.remove("rows");
        data.beginWriteArray("rows");
        for(int i = 0; i < ui->workshopTable->rowCount() - 1; ++i){
            data.setArrayIndex(i);
            data.setValue("use", ui->workshopTable->item(i, 0)->checkState());
            data.setValue("name", ui->workshopTable->item(i, 1)->text());
            QSpinBox* rCap = dynamic_cast<QSpinBox*> ((ui->workshopTable->cellWidget(i, 2)));
            data.setValue("rCap", rCap->value());
            QSpinBox* wCap = dynamic_cast<QSpinBox*> ((ui->workshopTable->cellWidget(i, 3)));
            data.setValue("wCap", wCap->value());
            /*
            workshopLabels.append("Time");
            */
        }
        data.endArray();
    data.endGroup();
}
