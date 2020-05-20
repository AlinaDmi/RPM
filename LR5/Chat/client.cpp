#include "client.h"
#include "ui_client.h"
#include <QDebug>
#include <QMessageBox>
#include <QWidget>
/**
 * @brief Создание окна и подключение к серверу
 * @author Dmitrieva Alina
 */
Client::Client(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
    sockCl = new QTcpSocket(this);
    sockCl->connectToHost("localhost", 33333, QTcpSocket::ReadWrite);
    if(sockCl->waitForConnected(30000)) {
        qInfo() << "Connected!";
        qInfo() << sockCl->peerAddress();
    } else{
         QMessageBox::information(NULL,QObject::tr("Информация"),tr("Нет подключения к серверу."));
    }

    connect(sockCl, &QTcpSocket::readyRead,this, &Client::readSocket);
    connect(ui->pushButton, &QPushButton::clicked,this, &Client::ButtonAction);
    connect(sockCl, &QTcpSocket::disconnected,this, &Client::serverDisconnect);
}
/**
 * @brief Удаление окна
 * @author Dmitrieva Alina
 */
Client::~Client()
{
    delete ui;
}
/**
 * @brief Ввод сообщения
 * @author Dmitrieva Alina
 */
void Client::ButtonAction()
{
    QFile file(QCoreApplication::applicationDirPath()+"/Name.txt");
    if(file.open(QIODevice::ReadOnly)){
            Name = file.readLine();
            file.close();
            chat = 1;
        }
    if (ui->message->text().toUtf8() == ""){
             QMessageBox::information(NULL,QObject::tr("Ошибка"),tr("Введите сообщение"));
             return;
        }
    else{
    sockCl->write( type.toUtf8()+ " " + Name.toUtf8() + " " + ui->message->text().toUtf8());
    return;
    }

}
/**
 * @brief Вывод на экран
 * @author Dmitrieva Alina
 */
void Client::readSocket()
{
    QString data = QString(sockCl->readAll());
    if(chat == 0)
    {
        ui->textEdit->append(data);
    }
    else
    {
    QStringList myStringList = data.split(" ");
    type = myStringList[0];
    QString name = myStringList[2]+" "+myStringList[3]+" ";
    myStringList[0].clear();
    myStringList[2].clear();
    myStringList[3].clear();
    QString str = myStringList.join(" ");
    str = "<div><font color=\"black\">"+str+"</font></div>";
    palitText();
    ui->textEdit->append(name);
    ui->textEdit->insertHtml(str);
    }
}
/**
 * @brief Покинули чат
 * @author Dmitrieva Alina
 */
void Client::serverDisconnect()
{
    QMessageBox::information(NULL,QObject::tr("Информация"),tr("Вы покинули чат"));
}
/**
 * @brief Выбор цвета пользователя
 * @author Dmitrieva Alina
 */
void Client::palitText()
{
    if (type == "Red")
    {
        ui->textEdit->setTextColor(QColor(255,7,7));

    }
    else if (type == "Green")
    {
        ui->textEdit->setTextColor(QColor(7,240,7));;
    }
    else if (type == "Yellow")
    {
        ui->textEdit->setTextColor(QColor(240,240,7));;
    }
    else if (type == "Blue")
    {
        ui->textEdit->setTextColor(QColor(7,34,240));;
    }
}
/**
 * @brief Выбор цвета пользователя из комбокс
 * @author Dmitrieva Alina
 */
void Client::on_comboBox_activated(const QString &arg1)
{
    type = arg1;
}
