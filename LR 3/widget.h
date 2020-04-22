#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUrl>
#include <QString>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>
#include <QEventLoop>
#include <QLabel>
#include <QLineEdit>
namespace Ui {
class VKAlina;
}

class VKAlina: public QWidget
{
    Q_OBJECT

public:
    explicit VKAlina(QWidget *parent = 0);
    ~VKAlina();
signals:
    void auth_success();

private:
    Ui::VKAlina *ui;
    QString token = "6021c2296021c2296021c229826051322c660216021c2293eaeb0e9bd93804e08cfe920";
    QString user_id;
    QString userName;
    QNetworkAccessManager *networkManagerFr;
    QNetworkAccessManager *networkManagerUS;
private slots:
    void on_Poisk_clicked();
    void onResult(QNetworkReply *reply);
    void onResultUser(QNetworkReply *replyUs);


public slots:
    void get_user();
    void get_friends();
};

#endif // WIDGET_H
