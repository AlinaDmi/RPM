#include "server.h"
#include <QtWebSockets>
#include <QDebug>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QFile>

Server::Server(QObject *parent) : QObject(parent),
    webServer (new QWebSocketServer(QStringLiteral("Сервер"),
                                    QWebSocketServer::NonSecureMode,
                                    this))
{
    if (webServer->listen(QHostAddress::Any, read_settings())){
        qDebug() << webServer->serverUrl();
        QMessageBox::information(NULL,QObject::tr("Information"), tr("Сервер запущен"));
        connect (webServer, &QWebSocketServer::newConnection,
                 this, &Server::connect_user);
    } else {
        QMessageBox::information(NULL,QObject::tr("Information"),
                                 tr("Сервер не запущен, попытайтесь еще "
                                    "или измените настройки подключения"));
    }
    clients.clear();
    db = QSqlDatabase::addDatabase("QSQLITE");
    connect_database();
}

Server::~Server(){
    clients.clear();
    db.close();
    emit info("Server close");
    webServer->close();
}

void Server::sender(QString message){
    foreach (client, clients) {
        QWebSocket* clientSocket = (QWebSocket*) client;
        clientSocket->sendTextMessage(message);
    }
}

void Server::connect_database()
{
    db.setDatabaseName("db.sqlite");
    if (db.open()){
        qInfo() << "База данных открыта";
        QFile f;
        f.setFileName(":/structure.txt");
        if(!f.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(NULL, QObject::tr("Information"),
                         tr("Файл структура базы данных не найден."));
            return;
        }
        QSqlQuery query;
        if(query.exec(f.readLine())) {qInfo() << "Таблица создана";}
        f.close();
    }
    else {
        qInfo() << "База данных не найдена.";}
}

void Server::record_message(QString nick, QString message)
{
    QSqlQuery query;
    query.prepare("INSERT INTO messages (id, nickname, message) VALUES (NULL, :nick, :mes)");
    query.bindValue(":nick", nick);
    query.bindValue(":mes", message);
    if(query.exec()) {emit info("Сообщение записано");}
}

void Server::set_settings(QString host, quint16 port)
{
    QFile f;
    f.setFileName("Settings.ini");
    if(f.open(QIODevice::ReadWrite)){
        settings = new QSettings("Settings.ini", QSettings::IniFormat);
        settings->beginGroup("Settings");
        settings->setValue( "host", host);
        settings->setValue("port", port);
        settings->endGroup();
        QMessageBox::information(NULL,QObject::tr("Information"), tr("Настройки изменены, измените настройки."));
    }
    f.close();
}

quint16 Server::read_settings()
{
    QFile f;
    f.setFileName("Settings.ini");
    if(f.exists()){
        settings = new QSettings("Settings.ini", QSettings::IniFormat);
        settings->beginGroup("Settings");
        QString host = settings->value("host").toString();
        quint16 port = settings->value("port").toUInt();
        settings->endGroup();
        return port;
    } else{
        settings = new QSettings(":/Settings.ini", QSettings::IniFormat);
        settings->beginGroup("Settings");
        QString host = settings->value("host").toString();
        quint16 port = settings->value("port").toUInt();
        settings->endGroup();
        return port;
    }
}

void Server::connect_user()
{
    emit info("Подключился новый пользователь!");
    client = webServer->nextPendingConnection();
    clients.push_back(client);
    Message();
    connect(client, &QWebSocket::textMessageReceived,
            this, &Server::run_client_action);
    connect(client, &QWebSocket::disconnected,
                this, &Server::disconnectUser);
}
void Server::run_client_action(QString message)
{

    QString nick, mes;
    QStringList mesList;
    mesList = message.split(" ");
    nick = mesList[0];
    mesList[0].clear();
    mes = mesList.join(" ");
    emit info("Получить сообщение от " + nick + ": " + mes);
    sender(nick + ": " + mes);
    record_message(nick, mes);
}

void Server::disconnectUser() {
    emit info("Пользователь вышел!");
    clients.removeOne(client);
    client->disconnect();
}

void Server::Message() {
    QSqlQuery query;
    int k, i=0;
    query.exec("SELECT COUNT(*) FROM messages");
    query.next();
    k = query.value(0).toInt();
    query.exec("SELECT * FROM messages");
    query.next();
    if(k > 10){
        while (i < (k-10)){
            query.next();
            i++;}}
    while(i<k){
        client->sendTextMessage(query.value(1).toString() +
                                ": " + query.value(2).toString());
        query.next();
        i++;}
}

QString Server::getPort()
{
    settings->beginGroup("Settings");
    QString port = settings->value("port").toString();
    settings->endGroup();
    return port;
}

QString Server::getHost()
{
    settings->beginGroup("Settings");
    QString host = settings->value("host").toString();
    settings->endGroup();
    return host;
}
