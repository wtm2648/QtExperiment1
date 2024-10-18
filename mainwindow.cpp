#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    digitBTNs = {
        {Qt::Key_0, ui->btnNum0},
        {Qt::Key_1, ui->btnNum1},
        {Qt::Key_2, ui->btnNum2},
        {Qt::Key_3, ui->btnNum3},
        {Qt::Key_4, ui->btnNum4},
        {Qt::Key_5, ui->btnNum5},
        {Qt::Key_6, ui->btnNum6},
        {Qt::Key_7, ui->btnNum7},
        {Qt::Key_8, ui->btnNum8},
        {Qt::Key_9, ui->btnNum9},
    };

    foreach(auto btn, digitBTNs)
        connect(btn,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    //connect(ui->btnNum0,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum1,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum2,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum3,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum4,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum5,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum6,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum7,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum8,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum9,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    connect(ui->btnAdd,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnSubtra,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnMulti,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnDevide,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));

    connect(ui->btnReciprocal,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSquare,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSquareRoot,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnPercentage,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::caculation(bool *ok)
{
    double result = 0;
    if(operands.size()==2 && opcodes.size()>0){
        //先取操作数
        double operand1 = operands.front().toDouble();
        operands.pop_front();
        double operand2 = operands.front().toDouble();
        operands.pop_front();

        //取操作符
        QString op = opcodes.front();
        opcodes.pop_front();

        if(op == "+"){
            result = operand1 + operand2;
        }
        else if(op == "-"){
            result = operand1 - operand2;
        }
        else if(op == "×"){
            result = operand1 * operand2;
        }
        else if(op == "÷"){
            if(operand2 != 0){
                result = operand1 / operand2;
            }
            else{
                ui->btnCE->clicked();
                return "除数不能为0";
            }
        }
        operands.push_back(QString::number(result));
    }

    return QString::number(result);
}


void MainWindow::btnNumClicked()
{
    QString digit = qobject_cast<QPushButton *>(sender())->text();
    if(digit == "0" && operand == "0")
        return;
    if(operand == "0" && digit != "0")
        operand.clear();
    operand += digit;
    ui->display->setText(operand);
}


void MainWindow::on_btnDecimal_clicked()
{
    if(!operand.contains(".") && operand != "")
        operand += ".";
    ui->display->setText(operand);
}


void MainWindow::on_btnBackspace_clicked()
{
    operand = operand.left(operand.length() - 1);
    ui->display->setText(operand);
}


void MainWindow::on_btnC_clicked()
{
    operand.clear();
    ui->display->setText(operand);
}

void MainWindow::btnBinaryOperatorClicked()
{
    QString opcode = qobject_cast<QPushButton *>(sender())->text();
    if(operand != ""){
        operands.push_back(operand);
        operand.clear();

        opcodes.push_back(opcode);
    }

    QString result = caculation();
    ui->display->setText(result);
}

void MainWindow::on_btnEqual_clicked()
{
    if(operand != ""){
        operands.push_back(operand);
        operand.clear();
    }

    QString result = caculation();
    ui->display->setText(result);
}

void MainWindow::btnUnaryOperatorClicked()
{
    if(operand != ""){
        double result = operand.toDouble();
        operand.clear();

        QString op = qobject_cast<QPushButton*>(sender())->text();

        if(op == "%"){
            result /= 100.0;
        }
        else if(op == "1/x"){
            result = 1/result;
        }
        else if(op == "x^2"){
            result *= result;
        }
        else if(op == "√"){
            if(result < 0){
                operand = "无实数解";
                ui->display->setText(operand);
                return;
            }
            else{
                result = sqrt(result);
            }
        }
        operand = QString::number(result);

        ui->display->setText(operand);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    foreach(auto btnKey, digitBTNs.keys()){
        if(event->key() == btnKey){
            digitBTNs[btnKey]->animateClick(100);
        }
    }
    if(event->key() == Qt::Key_Backspace){
        ui->btnBackspace->animateClick(100);
    }
    if(event->key() == Qt::Key_Plus){
        ui->btnAdd->animateClick(100);
    }
    if(event->key() == Qt::Key_Minus){
        ui->btnSubtra->animateClick(100);
    }
    if(event->key() == Qt::Key_Asterisk){
        ui->btnMulti->animateClick(100);
    }
    if(event->key() == Qt::Key_Slash){
        ui->btnDevide->animateClick(100);
    }
    if(event->key() == Qt::Key_Equal){
        ui->btnEqual->animateClick(100);
    }
    if(event->key() == Qt::Key_Period){
        ui->btnDecimal->animateClick(100);
    }
}


void MainWindow::on_btnChange_clicked()
{
    operand = "-" + operand;
    ui->display->setText(operand);

}


void MainWindow::on_btnCE_clicked()
{
    operand.clear();
    operands.clear();
    opcode.clear();
    opcodes.clear();
    ui->display->setText(operand);
}

