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
    QString table = "CREATE TABLE Employee (id_employee INT(11) NOT NULL,Name Text NOT NULL, Sex Text,PRIMARY KEY (id_employee));";
    query.exec(table);
    query.exec("INSERT INTO Employee VALUES (1, 'Gordienko','Male'), (2, 'Serov','Male') ,(3, 'Bereza','Male');");
    table = "CREATE TABLE Customer (id_customer INT(11) NOT NULL,Name Text NOT NULL, Sex Text,PRIMARY KEY (id_customer));";
    query.exec(table);
    query.exec("INSERT INTO Customer VALUES (1, 'Borisov','Male'), (2, 'Smirnov','Male') ,(3, 'Vinogradov','Male');");
}
void SQLAlina::Dtemplate()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName(PathB);
    if(!db.open()){ui->connectError->setText(db.lastError().text());}
    else{ui->PathB->setText("Вы подключились!");}
    QSqlQuery query;
    QString table = "CREATE TABLE Employee (id_employee INT(11) NOT NULL,Name Text NOT NULL, Sex Text,PRIMARY KEY (id_employee));";
    query.exec(table);
    query.exec("INSERT INTO Employee VALUES (1, 'Dmitrieva','Female'), (2, 'Agapova','Female') ,(3, 'Bereza','Male');");
    table = "CREATE TABLE Customer (id_customer INT(11) NOT NULL,Name Text NOT NULL, Sex Text,PRIMARY KEY (id_customer));";
    query.exec(table);
    query.exec("INSERT INTO Customer VALUES (1, 'Borisov','Male'), (2, 'Smirnov','Male') ,(3, 'Vinogradov','Male');");
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
