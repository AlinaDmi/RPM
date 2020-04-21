#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include "Snap.h"

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
private slots:
    void clearAll();
    void digitClicked();
    void unaryOperatorClicked();
    void additiveOperatorClicked();
    void multiplicativeOperatorClicked();
    void operatedTan();
    void equalClicked();
    void pointClicked();
    void changeSignClicked();
    void backspaceClicked();

private:

    Button *createButton(const QString &text, const char *member);
    void abortOperation();
    void abortOperationTrig();
    void additiveOperatorClicked1(double operand1);
    void additiveOperatorClicked2(double operand1);
    void equalClicked1(double operand1);
    void equalClicked2(double operand2);
    double operatedSQLG(QString textBut, double operandBut);
    double operatedTrig(QString textBut, double operandBut);
    bool calculate(double rightOperand, const QString &pendingOperator);
    bool PlusMinuscalculate(double rightOperand, const QString &pendingOperator);

    double sumInMemory;

    double sumSoFar;

    double factorSoFar;

    QString pendingAdditiveOperator;

    QString pendingMultiplicativeOperator;

    bool waitingForOperand;

    QLineEdit *display;

    enum { NumDigitButtons = 10 };
    Button *digitButtons[NumDigitButtons];
};

#endif
