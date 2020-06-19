#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <canvas.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Open_clicked();

    void on_Save_clicked();

    void on_Close_clicked();

    void setSize();

private:
    Ui::MainWindow *ui;
    Canvas* canvas;
    QString Color = "Black";
    QString Size = "1";
};
#endif // MAINWINDOW_H
