#include "client.h"
#include "menu.h"
#include "ui_client.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dialog = new Authorz();
    this->authorz();
    this->nick = dialog->getNick();
    this->port = dialog->getPort();
    ui->Name->setText(this->nick);
    if (nick != " "){
        socketClient = new QWebSocket();
        QUrl urlServer = QUrl(QString("ws://127.0.0.1:"));
        urlServer.setPort(port);
        socketClient->open(urlServer);
    }

    connect(socketClient, &QWebSocket::connected,
            this, &MainWindow::connected);
    connect(ui->send, &QPushButton::clicked,
            this, &MainWindow::execButtonAction);
    connect(socketClient, &QWebSocket::textMessageReceived,
            this, &MainWindow::read_Socket);
    connect(dialog, &Authorz::Start,
            this, &MainWindow::set_Name);
    connect(socketClient, &QWebSocket::disconnected,
            this, &MainWindow::serverDisconnected);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connected(){
    QMessageBox::information(NULL, QObject::tr("Информация"),
                             tr("Подключение прошло успешно!"));
}

void MainWindow::execButtonAction()
{
    if(ui->message->text().toUtf8() == ""){
         QMessageBox::information(NULL,QObject::tr("Ошибка"),
                                  tr("Введите сообщение"));
         return;
    } else {
        socketClient->sendTextMessage((nick + " " + ui->message->displayText()));
        ui->message->clear();
    }
}

void MainWindow::read_Socket(QString message)
{
    ui->textEdit->append(message);
}

void MainWindow::set_Name(QString nickname){
    this->nick = nickname;
    ui->Name->setText(nick);
}

void MainWindow::authorz(){
    dialog->exec();
    this->close();
}

void MainWindow::serverDisconnected()
{
    QMessageBox::information(NULL,QObject::tr("Информация"),
                             tr("Нет подключения к серверу"));   
}
