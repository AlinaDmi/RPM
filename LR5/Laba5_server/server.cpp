#include "server.h"
#include <QDebug>
#include <QTime>
/**
 * @brief Реализация Сервера
 * @author Dmitrieva Alina
 */
server::server(QWidget *parent): QWidget(parent)
{
    tcpServer = new QTcpServer(this);

    connect(tcpServer, &QTcpServer::newConnection,
            this, &server::connectUser);

    if (tcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
    }
    else {
        qDebug() << QString::fromUtf8("Сервер запущен!");
    }
    connect(this, &server::serverClose,
                this, &QCoreApplication::quit);
    clients.clear();
    list.clear();
}
/**
 * @brief Закрытие сервера
 * @author Dmitrieva Alina
 */
server::~server()
{
    emit serverClose();
}
/**
 * @brief Подключение пользователя
 * @author Dmitrieva Alina
 */
void server::connectUser()
{
    qInfo() << QString::fromUtf8("У нас новое соединение!");
    foreach (client, clients) {
            QTcpSocket* clientSock = (QTcpSocket*) client;
            QTextStream str (clientSock);
            str << QString::fromUtf8(" Один новый пользователь");
        }

    client = tcpServer->nextPendingConnection();
    clients.push_back(client);
    this->Message();

    connect(client, &QTcpSocket::readyRead,this, &server::ClientAction);
    connect(client, &QTcpSocket::disconnected,this, &server::disconnectUser);
}
/**
 * @brief Работа с Клиентом
 * @author Dmitrieva Alina
 */
void server::ClientAction()
{
    setlocale(LC_ALL,"Russian");
    k++;
    QTcpSocket* clientSocket = (QTcpSocket*) sender();
    QTextStream stream (clientSocket);
    QString nickname;
    QString message;
    QString str, str1, type;
    for (int i = 0;i < 100;i++){
        if(i==0){stream >> type;}
        else if((i>0)&&(i < 3)) {stream >> str;
        nickname+=" "+str;}
        else if (i > 3) {stream >> str1;
        message+=" "+str1;}    
    }
    qDebug() << nickname;
    qInfo() << QString::fromUtf8( "Получить сообщение от ") << nickname << "- " << message;

    foreach (client, clients){
        QTcpSocket* clSock = (QTcpSocket*) client;
        QTextStream str (clSock);
        str << type+" "+ nickname + " - " + message;
    }

    file.setFileName("Client.txt");
    list.push_back(nickname + " - " + message+"\n");

    if(!file.open(QIODevice::WriteOnly)){
        qInfo() << QString::fromUtf8("Файл не открывается...");
    }

    if (k > 10){
        list.removeFirst();
    }

    QTextStream _stream_(&file);
    foreach(QString str, list){
        if (str != ""){
           _stream_ << str << endl;
       }
    }
    file.close();
}
/**
 * @brief Закрытие сервера по условию
 * @author Dmitrieva Alina
 */
void server::disconnectUser() {
    setlocale(LC_ALL,"Russian");
    qInfo() << QString::fromUtf8( "Пользователь покинул чат");

    foreach (client, clients) {
        QTcpSocket* clientSock = (QTcpSocket*) client;
        QTextStream str (clientSock);
        str << QString::fromUtf8( "    Осталься один пользователь");
    }
    clients.removeOne(client);
    client->disconnect();
    if(clients.size() == 0)
        emit serverClose();
}
/**
 * @brief Работа с сообщениями
 * @author Dmitrieva Alina
 */
void server::Message() {
    setlocale(LC_ALL,"Russian");
    file.setFileName("Client.txt");
    if(!file.open(QIODevice::ReadOnly)){
        qInfo() << QString::fromUtf8("Файл не открывается...");
    }

    QTcpSocket* clSock = (QTcpSocket*) client;
    QTextStream str (clSock);
    QTextStream stream(&file);
    QString stn,sts;
    QFile file("Client.txt");
        if(file.open(QIODevice::ReadOnly |QIODevice::Text))
        {
            while(!file.atEnd())
            {
                QString st = file.readLine();
                str << st;
            }
        file.close();
        }
        else
        {
            qDebug()<< "don't open file";
        }
}

