#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{
    widjet = new QWidget(this);
    this->setCentralWidget(widjet);
    vLayout = new QVBoxLayout(widjet);
    tableWidget = new QTableWidget(widjet);
    tableWidget->setRowCount(10);
    tableWidget->setColumnCount(10);

    QPushButton* saveTable = new QPushButton("сохранить таблицу",widjet);



    connect(saveTable,&QPushButton::clicked,this,&MainWindow::save);


    vLayout->addWidget(tableWidget);
    vLayout->addWidget(saveTable);
    widjet->setMinimumSize(1044,500);
    widjet->setLayout(vLayout);
}

void MainWindow::openExcel()
{
    excel = new QAxObject("Excel.Application", this);
    workbooks = excel->querySubObject("Workbooks");
    workbook = workbooks->querySubObject("Open(const QString&)", QFileDialog::getOpenFileNames());
    sheets = workbook->querySubObject("Sheets");
    sheet = sheets->querySubObject("Item(int)", 1);
}

void MainWindow::writeInExcel()
{
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++){
            QAxObject* cell = sheet->querySubObject("Cells(int,int)", i+1, j+1);
            if(tableWidget->item(i,j)!=0) cell->setProperty("Value",QVariant(tableWidget->item(i,j)->data(0)));
            else cell->setProperty("Value"," ");
            delete cell;
        }
}

void MainWindow::closeExcel()
{
    workbook->dynamicCall("Save()");
    delete sheet;
    delete sheets;
    delete workbook;
    delete workbooks;
    excel->dynamicCall("Quit()");
    delete excel;
}

MainWindow::~MainWindow()
{

}



void MainWindow::save()
{
    openExcel();
    writeInExcel();
    closeExcel();

}



