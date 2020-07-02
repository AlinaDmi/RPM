#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chart = new QChart();

    createMassiv();


    series = new QBarSeries();
    series->append(getDiagram());
    chart->addSeries(series);
    chart->setTitle("Среднее значение по сортировке");

    createAxisX();

    createAxisY();

    chartView = new QChartView(ui->widget);
    chartView->setRenderHint(QPainter::Antialiasing);
    chart->legend()->setVisible(0);

    chartView->setChart(chart);
    chartView->resize(ui->widget->size());


    thread=new QThread();
    bubble=new BubbleSort(nullptr,massiv,n);
    bubble->moveToThread(thread);
    timer=new QTimer();
    sortMassiv();

    connect(ui->start,&QPushButton::clicked,this,&MainWindow::buttons);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createAxisX()
{
    QStringList categories;
    for(int i=1;i<=n/1000;i++)
        categories.append(QString::number(i));
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
}

void MainWindow::createAxisY()
{
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Среднее");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
}

void MainWindow::createMassiv()
{
    massiv=new int[n];
    QRandomGenerator generator;

    for(int i=0;i<n;i++)
        massiv[i]=generator.bounded(1,1000000);
}

bool MainWindow::event(QEvent *event)
{
    if(event->type()==QEvent::Resize)
        chartView->resize(ui->widget->size());
    return QMainWindow::event(event);
}

void MainWindow::sortMassiv()
{
    connect(ui->start,&QPushButton::clicked,this,&MainWindow::beginSort);
    connect(ui->exit,&QPushButton::clicked,this,&MainWindow::endSort);

    connect(thread, &QThread::started, bubble, &BubbleSort::run);
    connect(timer,&QTimer::timeout,bubble,&BubbleSort::getMassiv, Qt::DirectConnection);
    connect(bubble,&BubbleSort::nowMassiv,this,&MainWindow::getMassiv, Qt::DirectConnection);
    connect(bubble,&BubbleSort::finished,this,&MainWindow::stopTimer);
    connect(bubble,&BubbleSort::finished,bubble,&BubbleSort::getMassiv, Qt::DirectConnection);
    connect(bubble,&BubbleSort::finished,this,&MainWindow::resultSort);
}

void MainWindow::beginSort()
{
    bubble->setRunning(true);
    thread->start();
    timer->start(3000);
}

void MainWindow::endSort()
{
    if(end==0){
    timer->stop();
    bubble->setRunning(false);
    thread->exit();
    thread->wait(4000);
    qInfo()<<thread->isRunning();
    }
    this->close();
}

void MainWindow::getMassiv(int *mass)
{
    massiv=mass;
    series->remove(set);
    series->insert(0,getDiagram());
}

QBarSet* MainWindow::getDiagram()
{
    set = new QBarSet("This");
    int k=0,p=1000,iter=0;
    avgForValues(k,p,iter);
    QColor col;
    col.setRgb(0,0,0);
    set->setColor(col);
    return set;
}

void MainWindow::avgForValues(int k,int p,int iter)
{
    while(p<=n){
        int buf=0;
        for (int i=k;i<p;i++)
            buf+=massiv[i];
        buf=buf/1000;
        set->insert(iter,buf);
        iter++;
        k=p;
        p+=1000;
    }
}

void MainWindow::buttons()
{
    ui->start->setDisabled(1);
}

void MainWindow::stopTimer()
{
    timer->stop();
    qInfo()<<"Timer is:"+QString::number(timer->isActive());
}

void MainWindow::resultSort()
{
    thread->exit();
    thread->wait(4000);
    qInfo()<<thread->isRunning();
    end=1;
}
