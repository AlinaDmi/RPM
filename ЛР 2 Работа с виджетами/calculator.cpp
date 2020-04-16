#include "calculator.h"
#include "Snap.h"
#include <QGridLayout>
#include <iostream>
#include <QLineEdit>
#include <QtMath>
#include <QPalette>
using namespace std;
Calculator::Calculator(QWidget *parent): QWidget(parent), sumInMemory(0.0), sumSoFar(0.0), factorSoFar(0.0), waitingForOperand(true)
{
    QPalette p;
    p.setColor(backgroundRole(), QColor(70,70,70));
    this->setPalette(p);
    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);
    display->setStyleSheet("QLineEdit { background: rgb(200, 200, 200); selection-background-color: rgb(100, 50, 0); }");
    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);
    for (int i = 0; i < NumDigitButtons; ++i)
    {
      digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));
    }
    Button *pointButton = createButton(tr("."), SLOT(pointClicked()));
    Button *changeSignButton = createButton(tr("±"), SLOT(changeSignClicked()));
    Button *backspaceButton = createButton(tr("⌦"), SLOT(backspaceClicked()));
    Button *clearAllButton = createButton(tr("Clear All"), SLOT(clearAll()));
    Button *divisionButton = createButton(tr("÷"), SLOT(multiplicativeOperatorClicked()));
    Button *timesButton = createButton(tr("×"), SLOT(multiplicativeOperatorClicked()));
    Button *powerButton = createButton(tr("n"), SLOT(multiplicativeOperatorClicked()));
    Button *minusButton = createButton(tr("-"), SLOT(additiveOperatorClicked()));
    Button *plusButton = createButton(tr("+"), SLOT(additiveOperatorClicked()));
    Button *squareRootButton = createButton(tr("Sqrt"), SLOT(unaryOperatorClicked()));
    Button *reciprocalButton = createButton(tr("lg(x)"), SLOT(unaryOperatorClicked()));
    Button *tanButton = createButton(tr("Tan(x)"), SLOT(operatedTan()));
    Button *sinButton = createButton(tr("Sin(x)"), SLOT(unaryOperatorClicked()));
    Button *cosButton = createButton(tr("Cos(x)"), SLOT(unaryOperatorClicked()));
    Button *equalButton = createButton(tr("="), SLOT(equalClicked()));
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(display, 0, 1, 1, 5);
    mainLayout->addWidget(backspaceButton, 1, 5);
    mainLayout->addWidget(clearAllButton, 1, 1);
    mainLayout->addWidget(tanButton, 1, 2);
    mainLayout->addWidget(sinButton, 1, 3);
    mainLayout->addWidget(cosButton, 1, 4);

    for (int i = 1; i < NumDigitButtons; ++i)
    {
        int row = ((9 - i) / 3) + 2;
        int column = ((i - 1) % 3) + 1;
        mainLayout->addWidget(digitButtons[i], row, column);
    }
    mainLayout->addWidget(digitButtons[0], 5, 1);
    mainLayout->addWidget(pointButton, 5, 2);
    mainLayout->addWidget(changeSignButton, 5, 3);
    mainLayout->addWidget(divisionButton, 2, 4);
    mainLayout->addWidget(timesButton, 3, 4);
    mainLayout->addWidget(minusButton, 4, 4);
    mainLayout->addWidget(plusButton, 5, 4);
    mainLayout->addWidget(squareRootButton, 2, 5);
    mainLayout->addWidget(powerButton, 3, 5);
    mainLayout->addWidget(reciprocalButton, 4, 5);
    mainLayout->addWidget(equalButton, 5, 5);
    setLayout(mainLayout);
    setWindowTitle(tr("Calculator"));
}

void Calculator::digitClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    int digitValue = clickedButton->text().toInt();
    if (display->text() == "0" && digitValue == 0.0)
        return;
    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    display->setText(display->text() + QString::number(digitValue));
}

void Calculator::unaryOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button*>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    operand = operatedSQLG(clickedOperator, operand);
    operand = operatedTrig(clickedOperator, operand);
    display->setText(QString::number(operand));
    waitingForOperand = true;
}

void Calculator::additiveOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    if (!clickedButton){return;}
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    additiveOperatorClicked1(operand);
    additiveOperatorClicked2(operand);
    pendingAdditiveOperator = clickedOperator;
    waitingForOperand = true;
}

void Calculator::additiveOperatorClicked1(double operand1)
{
    if (!pendingMultiplicativeOperator.isEmpty()){
    if (!calculate(operand1, pendingMultiplicativeOperator)) {
        abortOperation();
        return;
    }
    display->setText(QString::number(factorSoFar));
    operand1 = factorSoFar;
    factorSoFar = 0.0;
    pendingMultiplicativeOperator.clear();
    }
}

void Calculator::additiveOperatorClicked2(double operand2)
{
    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand2, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(sumSoFar));
    } else {
        sumSoFar = operand2;
    }
}

void Calculator::multiplicativeOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    if (!clickedButton){return;}
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    if (!pendingMultiplicativeOperator.isEmpty()){
        if (!calculate(operand, pendingMultiplicativeOperator)){
            abortOperation(); return;
        }
        display->setText(QString::number(factorSoFar));
    }
    else{factorSoFar = operand;}
    pendingMultiplicativeOperator = clickedOperator; waitingForOperand = true;
}

void Calculator::equalClicked()
{
    double operand = display->text().toDouble();
    equalClicked1(operand);
    equalClicked2(operand);
    display->setText(QString::number(sumSoFar));
    sumSoFar = 0.0;
    waitingForOperand = true;
}
void Calculator::equalClicked1(double operand1)
{
    if (!pendingMultiplicativeOperator.isEmpty()){
        if (!calculate(operand1, pendingMultiplicativeOperator)) {
            abortOperation();return;
        }
        operand1 = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
}
void Calculator::equalClicked2(double operand2)
{
    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand2, pendingAdditiveOperator)) {
            abortOperation();return;
        }
        pendingAdditiveOperator.clear();
    } else {
        sumSoFar = operand2;
    }
}
void Calculator::pointClicked()
{
    if (waitingForOperand)
        display->setText("0");
    if (!display->text().contains('.'))
        display->setText(display->text() + tr("."));
    waitingForOperand = false;
}

void Calculator::changeSignClicked()
{
    QString text = display->text();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    display->setText(text);
}

void Calculator::backspaceClicked()
{
    if (waitingForOperand)
        return;
    QString text = display->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
    }
    display->setText(text);
}

void Calculator::clearAll()
{
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    display->setText("0");
    waitingForOperand = true;
}

Button *Calculator::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

void Calculator::abortOperation()
{
    clearAll();
    display->setText(tr("###"));
}

void Calculator::abortOperationTrig()
{
    clearAll();
    display->setText(tr("∞"));
}

double Calculator::operatedSQLG(QString textBut, double operandBut)
{
    if (textBut == ("Sqrt")){
        if (operandBut < 0.0){
           abortOperation();
        }
        operandBut=sqrt(operandBut);
    }else if (textBut == tr("lg(x)")){
        if (operandBut == 0.0){
            abortOperation();
        }
        operandBut=log10(operandBut);
 }
   return operandBut;
}
void Calculator::operatedTan()
{
    Button *textButton = qobject_cast<Button*>(sender());
    QString textBut = textButton->text();
    double operandBut = display->text().toDouble();
    if (textBut== tr("Tan(x)")){
         if((operandBut == 90.00)||(operandBut == 270.00))
         {
            abortOperationTrig(); return;
         }
         else
         {
          operandBut=tan(operandBut*3.14/180);
         }
        }
    display->setText(QString::number(operandBut));
    waitingForOperand = true;
}
double Calculator::operatedTrig(QString textBut, double operandBut)
{
        if (textBut == tr("Sin(x)")){
        operandBut=sin(operandBut*3.14/180);
        }
        else if (textBut == tr("Cos(x)")){
        operandBut=cos(operandBut*3.14/180);
        }
        return operandBut;
}

bool Calculator::calculate(double rightOperand, const QString &pendingOperator)
{

    if (pendingOperator == tr("×")) {
        factorSoFar *= rightOperand;
    }else if (pendingOperator == tr("n")) {
        factorSoFar=pow(factorSoFar,rightOperand);
    } else if (pendingOperator == tr("÷")) {
        if (rightOperand == 0.0)
            return false;
        factorSoFar /= rightOperand;
    }
    PlusMinuscalculate( rightOperand, pendingOperator);
    return true;
}
bool Calculator::PlusMinuscalculate(double rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == tr("+")){
        sumSoFar += rightOperand;
    }
    else if (pendingOperator == tr("-")) {
        sumSoFar -= rightOperand;
    }
    return true;
}

