#include "menu.h"

#include <QApplication>
/**
 * @author Dmitrieva Alina
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    menu w;
    w.show();
    return a.exec();
}
