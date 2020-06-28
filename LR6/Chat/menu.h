#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QDialog>

namespace Ui {class Authorz;}

class Authorz : public QDialog
{
    Q_OBJECT

public:
    explicit Authorz(QWidget *parent = nullptr);
    ~Authorz();
    QString getNick();
    quint16 getPort();
private:
    Ui::Authorz *ui;
    QString nick;
private slots:
    void on_Start_clicked();

signals:
    void Start(QString nick);
};

#endif // AUTHORIZATION_H
