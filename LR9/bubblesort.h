#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <QObject>
#include<QDebug>

class BubbleSort : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
public:
    explicit BubbleSort(QObject *parent = nullptr,int *mass=nullptr,int val=0);
    /**
     * @brief running Возврат проверки выполнения сортировки
     * @return Проверка для выполнения сортировки
     */
    bool running() const;
    /**
     * @brief sortMass Сортировка пузырьком
     */
    void sortMass(int);

public slots:
    /**
     * @brief run Выполнение сортировки
     */
    void run();
    /**
     * @brief setRunning Установка проверки выполнения сортировки
     * @param running Проверка для выполнения сортировки
     */
    void setRunning(bool running);
    /**
     * @brief getMassiv Получение массива
     */
    void getMassiv();

private:
    int *massiv;
    int n;
    bool m_running;


signals:
    /**
     * @brief nowMassiv Сигнал для передачи массива
     */
    void nowMassiv(int*);
    /**
     * @brief finished Окончание сортировки
     */
    void finished();
    /**
     * @brief runningChanged Сигнал смены значения у проверки для выполнения сортировки
     * @param running  Проверка для выполнения сортировки
     */
    void runningChanged(bool running);

};

#endif // BUBBLESORT_H
