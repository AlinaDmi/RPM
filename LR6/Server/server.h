#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QSettings>
#include <QSqlDatabase>

class Server : public QObject
{
    Q_OBJECT
private:
    QWebSocketServer* webServer;
    QWebSocket* client;
    QList <QWebSocket*> clients;
    QSettings *settings;
    QSqlDatabase db;
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();
    QString getPort();
    QString getHost();
private:
    void sender(QString message);
    void connect_database();
    void record_message(QString nick, QString message);
public slots:
    void set_settings(QString host, quint16 port);
private slots:
    quint16 read_settings();
    void connect_user();
    void run_client_action(QString message);
    void disconnectUser();
    void Message();

signals:
    void info(QString info);
    void onoff_clicked();
};

#endif // SERVER_H
