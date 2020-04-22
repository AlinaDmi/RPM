#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
QT_BEGIN_NAMESPACE
namespace Ui { class SQLAlina ; }
QT_END_NAMESPACE

class SQLAlina  : public QWidget
{
    Q_OBJECT
public:
    SQLAlina (QWidget *parent = nullptr);
    ~SQLAlina ();
signals:
    void TCreate_clicked();
private slots:

    void on_ConnectDatabase_clicked();

    void on_ZaprosButton_clicked();

    void on_TCreate_clicked();

    void on_TDrop_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_Type_activated(const QString &arg1);

    void on_CreateColumn_clicked();

    void on_Addstring_clicked();

    void on_DeleteDate_clicked();

    void on_ReturnBD_clicked();
    void BDproverkaT();
    void BDcreateT();

private:
    Ui::SQLAlina  *ui;
    QSqlDatabase db;
    QString PathB;
    QSqlTableModel* model;
    int countTable;
    QString type;
    void Dtemplate();
};
#endif // WIDGET_H
