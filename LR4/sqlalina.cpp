#include "sqlalina.h"
#include "ui_sqlalina.h"
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStringList>
#include <QApplication>
SQLAlina::SQLAlina(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SQLAlina)
{
    ui->setupUi(this);
}

SQLAlina::~SQLAlina()
{
    delete ui;
    connect(this, SIGNAL(TCreate_clicked()),this,SLOT(on_TCreate_clicked()));
}


void SQLAlina::on_ConnectDatabase_clicked()
{
   ui->comboBox->clear();
   QStringList starNamecombox = {"Таблица"};
   ui->comboBox->addItems(starNamecombox);
   QSqlQuery query;
   QString path = QCoreApplication::applicationDirPath();
   PathB = ui->PathB->text();
   if(!QFile(path + "/"+PathB+".db").exists()){
       QFile mFile(path + "/"+PathB+".db");
       mFile.open(QIODevice::WriteOnly);
       mFile.close();
       Dtemplate();
       }
   else{
       db = QSqlDatabase::addDatabase("QSQLITE");
       db.setHostName("localhost");
       db.setDatabaseName(PathB);
       if(!db.open()){ui->connectError->setText(db.lastError().text());}
       else{ui->PathB->setText("Вы подключились!");}
       BDproverkaT();
       QStringList tables = db.tables();
       countTable = tables.count();
       for(int i=0; i < countTable; i++){
       ui->comboBox->addItem(tables.value(i));
       }
      }
}
void SQLAlina::BDproverkaT()
{
    QSqlQuery query;
    query.exec("SELECT count(*) FROM sqlite_master WHERE type = 'table'");
    query.first();
    int i = query.value(0).toInt();
    if( i == 0)
    {
     BDcreateT();
    }
}
void SQLAlina::BDcreateT()
{
    QSqlQuery query;
    QString table = "CREATE TABLE Pets (id_pet INT(11) NOT NULL,Name Text NOT NULL, Vid Text,PRIMARY KEY (id_pet));";
    query.exec(table);
    query.exec("INSERT INTO Pets VALUES (1, 'Popov','Panda'), (2, 'Shastun','Tiger') ,(3, 'Pozov','Dolphin');");
    table = "CREATE TABLE Zoo (id_zoo INT(11) NOT NULL,Name Text NOT NULL, City Text,PRIMARY KEY (id_zoo));";
    query.exec(table);
    query.exec("INSERT INTO Zoo VALUES (1, 'Arton Funs','Voronezh'), (2, 'Illisa ZooLand','Berlin') ,(3, 'Tropical','Paris');");
}
void SQLAlina::Dtemplate()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName(PathB);
    if(!db.open()){ui->connectError->setText(db.lastError().text());}
    else{ui->PathB->setText("Вы подключились!");}
    BDcreateT();
    QStringList tables = db.tables();
    countTable = tables.count();
    for(int i=0; i < countTable; i++){
    ui->comboBox->addItem(tables.value(i));
    }
}

void SQLAlina::on_ZaprosButton_clicked()
{
    ui->ErrorDate_2->clear();
    QSqlQuery query;
    QString tableZapros = ui->Zapros->text();
    QSqlQueryModel *setquery = new QSqlQueryModel;
    setquery->setQuery(tableZapros);
    QTableView *tv = new QTableView(this);
    tv->setModel(setquery);
    ui->tableView->setModel(setquery);
    bool b_table = query.exec(tableZapros);
        if(!b_table){
           ui->ErrorDate_2->setText("Запрос не выполнен");
        }
        else{
           ui->ErrorDate_2->setText("Запрос выполнен");
        }
}

void SQLAlina::on_TCreate_clicked()
{
    QSqlQuery query;
    QString tableName = ui->TableN->text();
    QString table = "CREATE TABLE " + tableName +" (id_" + tableName + " INTEGER NOT NULL, "+ "PRIMARY KEY(id_" + tableName +"));";;
    bool b_table = query.exec(table);
        if(!b_table)
        {
           ui->Error_Create->setText("Не удается создать таблицу!");
        }
        else
        {
          ui->connectError->clear();
        }
}

void SQLAlina::on_TDrop_clicked()
{
    QSqlQuery query;
    QString tableName = ui->TableN->text();
    QString table = "DROP TABLE " + tableName;
    bool b_table = query.exec(table);
        if(!b_table)
        {
           ui->Error_Create->setText("Не удалить таблицу!");
        }
        else
        {
          ui->Error_Create->setText("Успешно удалена, обновите страницу!");
        }
}
void SQLAlina::on_Type_activated(const QString &arg1)
{
    type = arg1;
}
void SQLAlina::on_comboBox_activated(const QString &arg1)
{
    types = arg1;
    model = new QSqlTableModel(this, db);
    model->setTable(arg1);
    model->select();
    ui->tableView->setModel(model);
}

void SQLAlina::on_CreateColumn_clicked()
{
    QSqlQuery query;
    QString tableName = ui->tableName->text();
    QString table = "ALTER TABLE " + ui->tableName->text() + " ADD "+ui->nameColumn->text()+" NULL ;";

    bool b_table = query.exec(table);
        if(!b_table)
        {
           ui->Error_Create->setText("Столбец не создан");
        }
        else
        {
          ui->connectError->clear();
        }
}
void SQLAlina::on_Addstring_clicked()
{
    QSqlQuery query;
    QString tableName = ui->tableName->text();
    QString table = "INSERT INTO " +ui->tableName->text() +
            "("+ui->nameColumn->text()+") VALUES ("+ ui->StringDate->text() +");";
    bool b_table = query.exec(table);
        if(!b_table)
        {
           ui->Error_Create->setText("Cтрока не создан");
        }
        else
        {
            ui->connectError->clear();
        }
}

void SQLAlina::on_DeleteDate_clicked()
{
    QSqlQuery query;
    QString tableName = ui->tableName->text();
    QString table = "DELETE FROM " +tableName +
            " WHERE "+ui->nameColumn->text()+" == "+ ui->StringDate->text()  +";";
    bool b_table = query.exec(table);
        if(!b_table)
        {
           ui->Error_Create->setText("Не удалить строку!");
        }
        else
        {
            ui->connectError->clear();
        }
}

void SQLAlina::on_ReturnBD_clicked()
{
    db.close();
    ui->PathB->setText(PathB);
    ui->comboBox->clear();
    QStringList starNamecombox = {"Таблица"};
    ui->comboBox->addItems(starNamecombox);
    on_ConnectDatabase_clicked();
}

void SQLAlina::on_Push_2_clicked()
{
    QSqlQuery query;
    QString table = "INSERT INTO " + types +
             " VALUES ( "+ ui->Data_id_2->text() +" ,'"+ui->DATA_Name_2->text()+"','"+ ui->DATA_SEX_2->text()+"');";
    bool b_table = query.exec(table);
        if(!b_table)
        {
           ui->Error_Create->setText("Невозможно выполнить операцию!");
        }
        else
        {
            ui->Error_Create->clear();
            on_comboBox_activated(types);
        }
}

void SQLAlina::on_Save_2_clicked()
{
    QSqlQuery query;
    QString table = "UPDATE " + types +" "+ "SET"+" "+" "
            + ui->Name_2->text()+"='"+ ui->DATA_Name_2->text()+"'," +" "+ ui->Sex_2->text()+"='"+ ui->DATA_SEX_2->text()+
            "' where "+ui->id_Name_2->text()+"="+ ui->Data_id_2->text() +";";
    bool b_table = query.exec(table);
        if(!b_table)
        {
           ui->Error_Create->setText("Не добавить данные, ошибка в данных!");
        }
        else
        {
            ui->connectError->clear();
            on_comboBox_activated(types);
        }
}

void SQLAlina::on_Delete_2_clicked()
{
    QSqlQuery query;
    QString table = "DELETE FROM " + types +
            " WHERE "+ui->id_Name_2->text()+" == "+ ui->Data_id_2->text()  +";";
    bool b_table = query.exec(table);
        if(!b_table)
        {
           ui->Error_Create->setText("Не удалить строку!");
        }
        else
        {
            ui->connectError->clear();
            on_comboBox_activated(types);
        }
}
