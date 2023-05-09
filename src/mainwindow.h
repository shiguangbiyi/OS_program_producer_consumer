#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "widget.h"
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


const int BUFFER_SIZE = 20;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void pre(int id);
    void depre(int id);
    void inpre(int id,int pos);
    void outpre(int id,int pos);
    void wait(int id,int p_c);
    //缓冲区生产、消费指针
    int in = 0, out = 0;
    void push(int num);
    void pop();
    int front();
    void produce(int id);
    void consume(int id);
    void program();
private:
    Ui::MainWindow *ui;
    mutex mtx;                                      //互斥量，用于保护队列的访问
    mutex emfl;                                     //同步量，用于确保同步执行
    condition_variable cv_producer, cv_consumer;    //条件变量
    int numEmptyBuffer = BUFFER_SIZE;               //缓冲区中空区数量
    int numProducts = 0;                            //缓冲区中产品数量
    int buffer[25] = { 0 };                         //缓冲区
signals:
    void updateColumnView1(int id);
    void updateColumnView2(int id);
    void updateColumnView3(int id,int pos);
    void updateColumnView4(int id,int pos);
    void updateColumnView5(int id,int p_c);
};

#endif // MAINWINDOW_H
