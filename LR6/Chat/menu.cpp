#include "menu.h"
#include "ui_menu.h"
#include <QMessageBox>

Authorz::Authorz(QWidget *parent) :
    QDialog(parent), ui(new Ui::Authorz)
{
    ui->setupUi(this);
    connect(ui->Start, &QPushButton::clicked,
            this, &Authorz::on_Start_clicked);
}

Authorz::~Authorz(){
    delete ui;
}


QString Authorz::getNick(){
    return nick;
}

quint16 Authorz::getPort(){
    quint16 port = 1113;
    if (ui->port->displayText() == "") { return port; }
    else { return ui->port->displayText().toUInt(); }
}

void Authorz::on_Start_clicked()
{
    int wordCount = nick.split(" ").count();
    if(ui->nick->displayText() == "" ||
       ui->nick->displayText() == " " || wordCount > 1){
        QMessageBox::information(NULL,QObject::tr("Ошибка"), tr("Введите Имя например - Анна!"));
        return; }
    nick = ui->nick->displayText();
    this->close();
    emit Start(ui->nick->displayText());
}
