#include "client.h"

#include <QApplication>
/**
 * @author Maxim Gordienko
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
