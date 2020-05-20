#include "menu.h"
#include "ui_menu.h"
#include "client.h"
#include <QFile>
/**
 * @brief Создание окна, подключение к чату
 * @author Dmitrieva Alina
 */
menu::menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}
/**
 * @brief Создание окна чата
 * @author Dmitrieva Alina
 */
void menu::on_connect_clicked()
{
    Name = ui->name->text();
    int wordCount = Name.split(" ").count();
    if(wordCount!=2)
    {
       ui->name->setText("Введите Фамилию и Имя еще раз");
    }
    else
    {
        QString path = QCoreApplication::applicationDirPath();
        QFile file(path+"/Name.txt");
        file.open(QIODevice::WriteOnly);
        file.write(Name.toUtf8());
        file.close();
        Client window;
        window.setModal(true);
        window.exec();
    }

}


