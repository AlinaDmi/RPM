#include "sqlalina.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SQLAlina w;
    w.show();
    return a.exec();
}
