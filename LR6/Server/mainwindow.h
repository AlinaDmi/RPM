#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QCloseEvent>
#include <QWebSocketServer>
#include "server.h"
#include <QSystemTrayIcon>
#include <QAction>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent * event);
private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void on_callapse_clicked();
    void exit();
    void on_onoff_clicked();

    void on_SaveSetting_clicked();

private:
    Ui::MainWindow * ui;
    QSystemTrayIcon * trayIcon;
    int CE = 0;
    int Save = 0;
    Server* server;
    void lurk_elements();
    void show_elements();
    void server_start();
    void get_info(QString info);
    void set_settings();
signals:
    void callapse();
    void onoff_clicked();
};
#endif // MAINWINDOW_H
