#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QtCharts>
#include<QDebug>
#include<QRandomGenerator>
#include"bubblesort.h"

QT_CHARTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /**
     * @brief event Обработка событий
     * @param event Событие
     * @return Событие
     */
    bool event(QEvent *event) override;
    /**
     * @brief sortMassiv Connect для выполнения сортировки
     */
    void sortMassiv();
    /**
     * @brief getDiagram Определение множества значений для диаграммы
     * @return Множество
     */
    QBarSet* getDiagram();
    /**
     * @brief avgForValues Вычисление среднего значения
     */
    void avgForValues(int,int,int);
    /**
     * @brief createAxisX Создание оси X
     */
    void createAxisX();
    /**
     * @brief createAxisY Создание оси Y
     */
    void createAxisY();
    /**
     * @brief createMassiv Создание массива
     */
    void createMassiv();
public slots:
    /**
     * @brief beginSort Начало сортировки
     */
    void beginSort();
    /**
     * @brief endSort Прерывание сортировки
     */
    void endSort();
    /**
     * @brief resultSort Окончание сортировки
     */
    void resultSort();
    /**
     * @brief getMassiv Получение массива
     * @param mass Массив
     */
    void getMassiv(int* mass);
    /**
     * @brief buttons Блокирование кнопки
     */
    void buttons();
    /**
     * @brief stopTimer Остановка таймера
     */
    void stopTimer();
private:
    Ui::MainWindow *ui;
    QChart *chart;
    QChartView *chartView;
    int *massiv;
    int n=500000;
    QThread *thread;
    BubbleSort *bubble;
    QTimer *timer;
    QBarSeries *series;
    QBarSet *set;
    bool end=0;
};
#endif // MAINWINDOW_H
