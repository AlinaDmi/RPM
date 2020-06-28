#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebSocket>
#include "menu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QWebSocket *socketClient;
    QString nick = " ";
    quint16 port;
    Authorz* dialog;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void execButtonAction();
    void read_Socket(QString message);
    void connected();
    void set_Name(QString name);
    void authorz();
    void serverDisconnected();
};
#endif // MAINWINDOW_H
