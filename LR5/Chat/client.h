#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtNetwork>
#include <iostream>
#include "menu.h"
/**
 * @brief класс client
 * @author Dmitrieva Alina
 */
namespace Ui {
class Client;
}

class Client : public QDialog
{
    Q_OBJECT


public:
    Client(QWidget *parent = nullptr);
    ~Client();

private:
    Ui::Client *ui;
    QTcpSocket *sockCl;
    QString Name;
    int chat = 0;
    QString type = "Red";
private slots:
    void ButtonAction();
    void readSocket();
    void serverDisconnect();
    void on_comboBox_activated(const QString &arg1);
    void palitText();
};

#endif // DIALOG_H
