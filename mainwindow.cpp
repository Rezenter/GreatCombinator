#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCoreApplication>
#include <QSpinBox>
#include <QListWidget>
#include <algorithm>

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
        weight->setMinimum(1);
        weight->setValue(1);
        ui->studentsTable->setCellWidget(row, 3, weight);
        QPushButton* workshops = new QPushButton(ui->studentsTable);
        workshops->setProperty("row", row);
        workshops->setText("edit");
        ui->studentsTable->setCellWidget(row, 4, workshops);
        QObject::connect(workshops, &QPushButton::pressed, this, [=]{
            int editingRow = QObject::sender()->property("row").toInt();
            QString key = ui->studentsTable->item(editingRow, 1)->text() + "_" + ui->studentsTable->item(editingRow, 2)->text();
            SWDialog->setWindowTitle("Assign/edit " + key + " workshops");
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
            QString key = ui->studentsTable->item(editingRow, 1)->text() + "_" + ui->studentsTable->item(editingRow, 2)->text();
            STDialog->setWindowTitle("Assign/edit " + key + " free time");
            while(STUi.table->rowCount() > 0){
                STUi.table->removeRow(0);
            }
            QList<MainWindow::time> times = studentsTime.values(key);
            for(int i = 0; i < times.length(); ++i){
                STUi.dayComboBox->setCurrentText(times.at(i).day);
                STUi.fromTimeEdit->setTime(times.at(i).from);
                STUi.toTimeEdit->setTime(times.at(i).to);
                STUi.addTimeButton->pressed();
            }
            STDialog->setProperty("row", editingRow);
            STDialog->show();
        });
        QPushButton* relations = new QPushButton(ui->studentsTable);
        relations->setProperty("row", row);
        relations->setText("edit");
        ui->studentsTable->setCellWidget(row, 6, relations);
        QObject::connect(relations, &QPushButton::pressed, this, [=]{
            int editingRow = QObject::sender()->property("row").toInt();
            QString key = ui->studentsTable->item(editingRow, 1)->text() + "_" + ui->studentsTable->item(editingRow, 2)->text();
            SRDialog->setWindowTitle("Assign/edit " + key + " relations");
            while(SRUi.table->rowCount() > 0){
                SRUi.table->removeRow(0);
            }
            QList<MainWindow::relation> relations = studentsRelation.values(key);
            for(int i = 0; i < ui->studentsTable->rowCount() - 1; ++i){
                SRUi.table->insertRow(i);
                QTableWidgetItem* name = new QTableWidgetItem((ui->studentsTable->item(i, 1)->text() + "_" + ui->studentsTable->item(i, 2)->text()));
                name->setFlags(use->flags().setFlag(Qt::ItemIsEditable, false));
                SRUi.table->setItem(i, 0, name);
                QButtonGroup* rowGroup = new QButtonGroup(SRUi.table);
                rowGroup->setProperty("row", i);
                QRadioButton* good = new QRadioButton(SRUi.table);
                QPalette pal = good->palette();
                pal.setColor(QPalette::Button, QColor(Qt::green));
                good->setAutoFillBackground(true);
                good->setPalette(pal);
                SRUi.table->setCellWidget(i, 1, good);
                rowGroup->addButton(good, 1);
                QRadioButton* neutral = new QRadioButton(SRUi.table);
                pal = neutral->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                neutral->setAutoFillBackground(true);
                neutral->setPalette(pal);
                SRUi.table->setCellWidget(i, 2, neutral);
                neutral->setChecked(true);
                rowGroup->addButton(neutral, 0);
                QRadioButton* bad = new QRadioButton(SRUi.table);
                pal = bad->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                bad->setAutoFillBackground(true);
                bad->setPalette(pal);
                SRUi.table->setCellWidget(i, 3, bad);
                rowGroup->addButton(bad, -1);
                QRadioButton* chaotic = new QRadioButton(SRUi.table);
                pal = chaotic->palette();
                pal.setColor(QPalette::Button, QColor(Qt::yellow));
                chaotic->setAutoFillBackground(true);
                chaotic->setPalette(pal);
                SRUi.table->setCellWidget(i, 4, chaotic);
                rowGroup->addButton(chaotic, 2);
                if(i == editingRow){
                    good->setCheckable(false);
                    bad->setCheckable(false);
                    chaotic->setCheckable(false);
                }else{
                    foreach (MainWindow::relation rel, relations) {
                        if(rel.target == name->text()){
                            switch (rel.rel) {
                                case -1:
                                    bad->setChecked(true);
                                    break;
                                case 1:
                                    good->setChecked(true);
                                    break;
                                default:
                                    chaotic->setChecked(true);
                                break;
                            }
                        }
                    }
                }
            }
            SRDialog->setProperty("row", editingRow);
            SRDialog->show();
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
            ui->studentsTable->removeRow(removingRow);                                              //minor memory leak
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
            QString key = ui->workshopTable->item(editingRow, 1)->text();
            WTDialog->setWindowTitle("Assign/edit " + key + " open time");
            while(WTUi.table->rowCount() > 0){
                WTUi.table->removeRow(0);
            }
            QList<MainWindow::time> times = workshopsTime.values(key);
            for(int i = 0; i < times.length(); ++i){
                WTUi.dayComboBox->setCurrentText(times.at(i).day);
                WTUi.fromTimeEdit->setTime(times.at(i).from);
                WTUi.toTimeEdit->setTime(times.at(i).to);
                WTUi.addTimeButton->pressed();
            }
            WTDialog->setProperty("row", editingRow);
            WTDialog->show();
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
            ui->workshopTable->removeRow(removingRow);                                              //minor memory leak
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
    STUi.setupUi(STDialog);
    STUi.table->setSelectionMode(QAbstractItemView::NoSelection);
    QStringList STLabels;
    STLabels.append("day");
    STLabels.append("from");
    STLabels.append("to");
    STLabels.append("Del");
    STUi.table->setColumnCount(STLabels.size());
    STUi.table->setHorizontalHeaderLabels(STLabels);
    pal = STUi.addTimeButton->palette();
    pal.setColor(QPalette::Button, QColor(Qt::green));
    STUi.addTimeButton->setAutoFillBackground(true);
    STUi.addTimeButton->setPalette(pal);
    QObject::connect(STUi.addTimeButton, &QPushButton::pressed, this, [=]{
        int row = STUi.table->rowCount();
        STUi.table->insertRow(row);
        QTableWidgetItem* day = new QTableWidgetItem(STUi.dayComboBox->currentText());
        day->setFlags(day->flags().setFlag(Qt::ItemIsEditable, false));
        STUi.table->setItem(row, 0, day);
        QTableWidgetItem* from = new QTableWidgetItem(STUi.fromTimeEdit->text());
        from->setFlags(from->flags().setFlag(Qt::ItemIsEditable, false));
        STUi.table->setItem(row, 1, from);
        QTableWidgetItem* to = new QTableWidgetItem(STUi.toTimeEdit->text());
        to->setFlags(to->flags().setFlag(Qt::ItemIsEditable, false));
        STUi.table->setItem(row, 2, to);
        QPushButton* remove = new QPushButton(STUi.table);
        remove->setProperty("row", row);
        remove->setText("Del");
        QPalette pal = remove->palette();
        pal.setColor(QPalette::Button, QColor(Qt::red));
        remove->setAutoFillBackground(true);
        remove->setPalette(pal);
        STUi.table->setCellWidget(row, 3, remove);
        QObject::connect(remove, &QPushButton::pressed, this, [=]{
            int removingRow = QObject::sender()->property("row").toInt();
            STUi.table->removeRow(removingRow);                                              //minor memory leak
            for(int i = removingRow; i < STUi.table->rowCount(); ++i){
                STUi.table->cellWidget(i, 3)->setProperty("row", i);
            }
        });
    });
    STDialog->setWindowTitle("Assign/edit students free time");
    STDialog->setModal(true);
    QObject::connect(STDialog, &QDialog::accepted, this, [=]{
        int row = STDialog->property("row").toInt();
        QString key = ui->studentsTable->item(row, 1)->text() + "_" + ui->studentsTable->item(row, 2)->text();
        studentsTime.remove(key);
        for(int i = 0; i < STUi.table->rowCount(); ++i){
            MainWindow::time time;
            time.day = STUi.table->item(i, 0)->text();
            time.from = QTime::fromString(STUi.table->item(i, 1)->text(), "HH:mm");
            time.to = QTime::fromString(STUi.table->item(i, 2)->text(), "HH:mm");
            studentsTime.insertMulti(key, time);
        }
        dynamic_cast<QPushButton*>(ui->studentsTable->cellWidget(row, 5))->setText("selected " + QString::number(STUi.table->rowCount()));
    });
    SRUi.setupUi(SRDialog);
    SRUi.table->setSelectionMode(QAbstractItemView::NoSelection);
    QStringList SRLabels;
    SRLabels.append("Name");
    SRLabels.append("Good");
    SRLabels.append("Neutral");
    SRLabels.append("Bad");
    SRLabels.append("Chaotic");
    SRUi.table->setColumnCount(SRLabels.size());
    SRUi.table->setHorizontalHeaderLabels(SRLabels);
    SRDialog->setWindowTitle("Assign/edit students relations");
    SRDialog->setModal(true);
    QObject::connect(SRDialog, &QDialog::accepted, this, [=]{
        int row = SRDialog->property("row").toInt();
        QString key = ui->studentsTable->item(row, 1)->text() + "_" + ui->studentsTable->item(row, 2)->text();
        studentsRelation.remove(key);
        int relation = 0;
        for(int i = 0; i < SRUi.table->rowCount(); ++i){
            if(i != row){
                QString target = SRUi.table->item(i, 0)->text();
                MainWindow::relation rel;
                rel.target = target;
                if(dynamic_cast<QRadioButton*>(SRUi.table->cellWidget(i, 1))->isChecked()){
                    rel.rel = 1;
                }else if(dynamic_cast<QRadioButton*>(SRUi.table->cellWidget(i, 2))->isChecked()){
                    rel.rel = 0;
                }else if(dynamic_cast<QRadioButton*>(SRUi.table->cellWidget(i, 3))->isChecked()){
                    rel.rel = -1;
                }else {
                    rel.rel = random.bounded(-1, 2);
                }
                studentsRelation.insertMulti(key, rel);
                relation += rel.rel;
            }
        }
        dynamic_cast<QPushButton*>(ui->studentsTable->cellWidget(row, 6))->setText("relation " + QString::number(relation));
    });
    WTUi.setupUi(WTDialog);
    WTUi.table->setSelectionMode(QAbstractItemView::NoSelection);
    QStringList WTLabels;
    WTLabels.append("day");
    WTLabels.append("from");
    WTLabels.append("to");
    WTLabels.append("Del");
    WTUi.table->setColumnCount(WTLabels.size());
    WTUi.table->setHorizontalHeaderLabels(WTLabels);
    pal = WTUi.addTimeButton->palette();
    pal.setColor(QPalette::Button, QColor(Qt::green));
    WTUi.addTimeButton->setAutoFillBackground(true);
    WTUi.addTimeButton->setPalette(pal);
    QObject::connect(WTUi.addTimeButton, &QPushButton::pressed, this, [=]{
        int row = WTUi.table->rowCount();
        WTUi.table->insertRow(row);
        QTableWidgetItem* day = new QTableWidgetItem(WTUi.dayComboBox->currentText());
        day->setFlags(day->flags().setFlag(Qt::ItemIsEditable, false));
        WTUi.table->setItem(row, 0, day);
        QTableWidgetItem* from = new QTableWidgetItem(WTUi.fromTimeEdit->text());
        from->setFlags(from->flags().setFlag(Qt::ItemIsEditable, false));
        WTUi.table->setItem(row, 1, from);
        QTableWidgetItem* to = new QTableWidgetItem(WTUi.toTimeEdit->text());
        to->setFlags(to->flags().setFlag(Qt::ItemIsEditable, false));
        WTUi.table->setItem(row, 2, to);
        QPushButton* remove = new QPushButton(WTUi.table);
        remove->setProperty("row", row);
        remove->setText("Del");
        QPalette pal = remove->palette();
        pal.setColor(QPalette::Button, QColor(Qt::red));
        remove->setAutoFillBackground(true);
        remove->setPalette(pal);
        WTUi.table->setCellWidget(row, 3, remove);
        QObject::connect(remove, &QPushButton::pressed, this, [=]{
            int removingRow = QObject::sender()->property("row").toInt();
            WTUi.table->removeRow(removingRow);                                              //minor memory leak
            for(int i = removingRow; i < WTUi.table->rowCount(); ++i){
                WTUi.table->cellWidget(i, 3)->setProperty("row", i);
            }
        });
    });
    WTDialog->setWindowTitle("Assign/edit workshop free time");
    WTDialog->setModal(true);
    QObject::connect(WTDialog, &QDialog::accepted, this, [=]{
        int row = WTDialog->property("row").toInt();
        QString key = ui->workshopTable->item(row, 1)->text();
        workshopsTime.remove(key);
        for(int i = 0; i < WTUi.table->rowCount(); ++i){
            MainWindow::time time;
            time.day = WTUi.table->item(i, 0)->text();
            time.from = QTime::fromString(WTUi.table->item(i, 1)->text(), "HH:mm");
            time.to = QTime::fromString(WTUi.table->item(i, 2)->text(), "HH:mm");
            workshopsTime.insertMulti(key, time);
        }
        dynamic_cast<QPushButton*>(ui->workshopTable->cellWidget(row, 4))->setText("selected " + QString::number(WTUi.table->rowCount()));
    });
    loadData();
    QObject::connect(ui->shuffleButton, &QPushButton::pressed, this, [=]{//_______________________________________________________________________________________________
        if(ui->studentsTable->rowCount() > 1){
            QVector<int> sortedStudents;
            QPoint max(0, 1);//max weight
            for(int i = 0; i < ui->studentsTable->rowCount() - 1; ++i){
                for(int row = 0; row < ui->studentsTable->rowCount() - 1; ++row){
                    if(!sortedStudents.contains(row)){
                        //sort
                        int weight = dynamic_cast<QSpinBox*>(ui->studentsTable->cellWidget(row, 3))->value();
                        qDebug() << weight;
                        /*
                        if(){

                        }
                        */
                    }
                }
            }
        }
    });
}

MainWindow::~MainWindow()
{
    saveData();
    delete SWDialog;
    delete STDialog;
    delete SRDialog;
    delete WTDialog;
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
            QString key = ui->studentsTable->item(i, 1)->text() + "_" + ui->studentsTable->item(i, 2)->text();
            int choiceSize = data.beginReadArray("workshops");
                for(int j = 0; j < choiceSize; ++j){
                    data.setArrayIndex(j);
                    studentsChoice.insertMulti(key, data.value("chosen", "not Loaded").toString());
                }
                dynamic_cast<QPushButton*>(ui->studentsTable->cellWidget(i, 4))->setText("selected " + QString::number(choiceSize));
            data.endArray();
            int timeSize = data.beginReadArray("times");
                for(int j = 0; j < timeSize; ++j){
                    data.setArrayIndex(j);
                    MainWindow::time time;
                    time.day = data.value("day", "not Loaded").toString();
                    time.from = data.value("from", "00:00").toTime();
                    time.to = data.value("to", "00:00").toTime();
                    studentsTime.insertMulti(key, time);
                }
                dynamic_cast<QPushButton*>(ui->studentsTable->cellWidget(i, 5))->setText("selected " + QString::number(timeSize));
            data.endArray();
            int relSize = data.beginReadArray("relations");
                int relation = 0;
                for(int j = 0; j < relSize; ++j){
                    data.setArrayIndex(j);
                    MainWindow::relation rel;
                    rel.target = data.value("target", "not Loaded").toString();
                    rel.rel = data.value("rel", "0").toInt();
                    studentsRelation.insertMulti(key, rel);
                    relation += rel.rel;
                }
                dynamic_cast<QPushButton*>(ui->studentsTable->cellWidget(i, 6))->setText("relation " + QString::number(relation));
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
    data.beginGroup("STDialog");
        STDialog->resize(data.value("dialogSize", QSize(800, 600)).toSize());
        STDialog->move(data.value("dialogPosition", QPoint(0, 0)).toPoint());
        columnCount = data.beginReadArray("columns");
        for(int i = 0; i < columnCount; ++i){
            data.setArrayIndex(i);
            STUi.table->setColumnWidth(i, data.value("width", 20). toInt());
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
            QString key = ui->workshopTable->item(i, 1)->text();
            int timeSize = data.beginReadArray("times");
                for(int j = 0; j < timeSize; ++j){
                    data.setArrayIndex(j);
                    MainWindow::time time;
                    time.day = data.value("day", "not Loaded").toString();
                    time.from = data.value("from", "00:00").toTime();
                    time.to = data.value("to", "00:00").toTime();
                    workshopsTime.insertMulti(key, time);
                }
                dynamic_cast<QPushButton*>(ui->workshopTable->cellWidget(i, 4))->setText("selected " + QString::number(timeSize));
            data.endArray();
        }
        data.beginGroup("WTDialog");
            WTDialog->resize(data.value("dialogSize", QSize(800, 600)).toSize());
            WTDialog->move(data.value("dialogPosition", QPoint(0, 0)).toPoint());
            columnCount = data.beginReadArray("columns");
            for(int i = 0; i < columnCount; ++i){
                data.setArrayIndex(i);
                WTUi.table->setColumnWidth(i, data.value("width", 20). toInt());
            }
            data.endArray();
        data.endGroup();
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
            QString key = ui->studentsTable->item(i, 1)->text() + "_" + ui->studentsTable->item(i, 2)->text();
            data.beginWriteArray("workshops");
                QList<QString> choice = studentsChoice.values(key);
                for(int j = 0; j < choice.size(); ++j){
                    data.setArrayIndex(j);
                    data.setValue("chosen", choice.at(j));
                }
            data.endArray();
            data.beginWriteArray("times");
                QList<MainWindow::time> times = studentsTime.values(key);
                for(int j = 0; j < times.size(); ++j){
                    data.setArrayIndex(j);
                    data.setValue("day", times.at(j).day);
                    data.setValue("from", times.at(j).from);
                    data.setValue("to", times.at(j).to);
                }
            data.endArray();
            data.beginWriteArray("relations");
                QList<MainWindow::relation> relations = studentsRelation.values(key);
                for(int j = 0; j < relations.size(); ++j){
                    data.setArrayIndex(j);
                    data.setValue("target", relations.at(j).target);
                    data.setValue("rel", relations.at(j).rel);
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
    data.beginGroup("STDialog");
        data.setValue("dialogSize", STDialog->size());
        data.setValue("dialogPosition", STDialog->pos());
        data.beginWriteArray("columns");
        for(int i = 0; i < STUi.table->columnCount(); ++i){
            data.setArrayIndex(i);
            data.setValue("width", STUi.table->columnWidth(i));
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
            QString key = ui->workshopTable->item(i, 1)->text();
            data.beginWriteArray("times");
                QList<MainWindow::time> times = workshopsTime.values(key);
                for(int j = 0; j < times.size(); ++j){
                    data.setArrayIndex(j);
                    data.setValue("day", times.at(j).day);
                    data.setValue("from", times.at(j).from);
                    data.setValue("to", times.at(j).to);
                }
            data.endArray();
        }
        data.beginGroup("WTDialog");
            data.setValue("dialogSize", WTDialog->size());
            data.setValue("dialogPosition", WTDialog->pos());
            data.beginWriteArray("columns");
            for(int i = 0; i < WTUi.table->columnCount(); ++i){
                data.setArrayIndex(i);
                data.setValue("width", WTUi.table->columnWidth(i));
            }
            data.endArray();
        data.endGroup();
        data.endArray();
    data.endGroup();
}

bool MainWindow::compare(int a, int b){
    int wa = dynamic_cast<QSpinBox*>(ui->studentsTable->cellWidget(a, 3))->value();
    int wb = dynamic_cast<QSpinBox*>(ui->studentsTable->cellWidget(b, 3))->value();
    return (wa > wb);
}
