#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QLabel>
#include <QKeyEvent>
#include <QMap>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString operand;
    QString opcode;
    QStack<QString> operands;
    QStack<QString> opcodes;
    QMap<int, QPushButton*> digitBTNs;

    QString caculation(bool *ok = NULL);
private slots:
    void btnNumClicked();

    void on_btnDecimal_clicked();

    void on_btnBackspace_clicked();

    void on_btnC_clicked();

    void btnBinaryOperatorClicked();

    void on_btnEqual_clicked();

    void btnUnaryOperatorClicked();

    virtual void keyPressEvent(QKeyEvent *event);
    void on_pushButton_clicked();

    void on_btnCE_clicked();

    void on_btnChange_clicked();

private:
    Ui::MainWindow *ui;
    QLabel *statusMsgLabel;
};
#endif // MAINWINDOW_H
