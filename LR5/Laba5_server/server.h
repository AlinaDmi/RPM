#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork>

QT_BEGIN_NAMESPACE
namespace Ui { class server; }
QT_END_NAMESPACE
/**
 * @brief Класс Сервер
 * @author Dmitrieva Alina
 */
class server : public QWidget
{
    Q_OBJECT

public:
    server(QWidget *parent = nullptr);
    ~server();

private:
    Ui::server *ui;
    QTcpServer* tcpServer;
    QTcpSocket* client;
    QList <QTcpSocket*> clients;
    QFile file;
    QStringList list;
    int k = 0;

private slots:
    void connectUser();
    void ClientAction();
    void disconnectUser();
    void Message();
signals:
    void serverClose();
};

#endif // WIDGET_H
