#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTextStream"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName
                         (this, tr("Сохранить файл"),"",
                          tr("Images(* .png * .jpg)"));
        QImage image(ui->graphicsView->scene()->width(),
                     ui->graphicsView->scene()->height(),
                     QImage::Format_RGB32);
        image.fill(QColor(Qt::white).rgb());
        QPainter painter(&image);
        ui->graphicsView->scene()->render(&painter);
        painter.end();
        if(fileName.indexOf(".png") != -1 || fileName.indexOf(".jpg") != -1)
            image.save(fileName);
        else
            image.save(fileName.append(".png"));
}

void MainWindow::on_Open_clicked()
{
    QString fileName = QFileDialog::getOpenFileName
                (this, tr("Открыть файл"),"",
                 tr("Images(* .png * .jpg)"));
        Canvas* sceneImage = new Canvas;
        sceneImage->addPixmap(QPixmap(fileName));
        ui->graphicsView->setScene(sceneImage);
        sceneImage->setSize(ui->Size->displayText());
        sceneImage->setColor(ui->comboBox->currentText());
        connect(ui->comboBox, &QComboBox::currentTextChanged,
                sceneImage, &Canvas::setColor);
        connect(ui->Size, &QLineEdit::textChanged,
                sceneImage, &Canvas::setSize);
}

void MainWindow::on_Close_clicked()
{
    ui->graphicsView->setScene(this->canvas);
}

void MainWindow::setSize(){
    canvas->setSize(ui->Size->text());
}

