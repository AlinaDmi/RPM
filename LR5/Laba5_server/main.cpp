#include "server.h"

#include <QApplication>
/**
 * @author Dmitrieva Alina
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    server w;
    w.show();
    return a.exec();
}
