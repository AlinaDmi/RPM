#include "bubblesort.h"

BubbleSort::BubbleSort(QObject *parent,int *mass,int val) : QObject(parent)
{
    massiv=mass;
    n=val;
}

bool BubbleSort::running() const
{
    return m_running;
}

void BubbleSort::run()
{
    while(m_running){
    for(int i = 1; i < n; ++i)
            for(int r = 0; r < n-i; r++){
                sortMass(r);
                if(m_running==false)
                    return;
            }
    setRunning(false); }
    emit finished();
    return;
}

void BubbleSort::sortMass(int r)
{
    if(massiv[r] < massiv[r+1]){
        int temp = massiv[r];
        massiv[r] = massiv[r+1];
        massiv[r+1] = temp;
    }
}

void BubbleSort::setRunning(bool running)
{
    if (m_running == running)
        return;

    m_running = running;
    emit runningChanged(running);
}

void BubbleSort::getMassiv()
{
    emit nowMassiv(massiv);
}
