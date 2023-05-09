#include "widget.h"
#include "ui_widget.h"
#include "mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <windows.h>
#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QStackedWidget>
using namespace std;

int numProducers,numConsumers;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("主窗口");
    BUFFER =new MainWindow;
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_lineEdit_textChanged(const QString &arg1)
{
    bool ok;
    numProducers = arg1.toInt(&ok);
        if (ok) {
            // 转换成功，num 中包含整数值
            qDebug() << "输入的生产者数量为：" << numProducers;
        } else {
            // 转换失败，输入不是整数
            qDebug() << "输入的不是整数，请重新输入";
        }

}

void Widget::on_lineEdit_2_textChanged(const QString &arg1)
{
    bool ok;
    numConsumers = arg1.toInt(&ok);
        if (ok) {
            // 转换成功，num 中包含整数值
            qDebug() << "输入的消费者数量为：" <<  numConsumers;
        } else {
            // 转换失败，输入不是整数
            qDebug() << "输入的不是整数，请重新输入";
        }

}



void Widget::on_pushButton_clicked()
{
    BUFFER->show();
    this->hide();
    class thread programThread(&MainWindow::program, BUFFER);
    programThread.detach(); // 分离线程，避免阻塞主线程
}
