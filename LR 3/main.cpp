#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VKAlina w;
    w.show();
    return a.exec();
}
