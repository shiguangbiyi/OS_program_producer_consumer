#include "mainwindow.h"
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

extern int numProducers,numConsumers;//根据主页面输入得到的生产者和消费者数量

//Mainwindow类构造函数
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("演示窗口");
    connect(this, &MainWindow::updateColumnView1, this, &MainWindow::pre);//信号，用来表示当缓存区有资源时，将该缓存区变红
    connect(this, &MainWindow::updateColumnView2, this, &MainWindow::depre);//信号，用来表示当缓存区资源被消耗时，将该缓存区变白
    connect(this, &MainWindow::updateColumnView3, this, &MainWindow::inpre);//信号，用来表示生产者指针和生产者编号
    connect(this, &MainWindow::updateColumnView4, this, &MainWindow::outpre);//信号，用来表示消费者指针和消费者编号
    connect(this, &MainWindow::updateColumnView5, this, &MainWindow::wait);//信号，用来表示生产者或消费者的等待信息
}

//Mainwindow类析构函数
MainWindow::~MainWindow()
{
    delete ui;
}

//MainWindow类，用于改变界面内控件状态
//根据缓冲区编号将缓冲区涂红
void MainWindow::pre(int id){
    switch(id){
        case 1:
            ui->columnView->setStyleSheet("background-color: red;");
            break;
        case 2:
            ui->columnView_2->setStyleSheet("background-color: red;");
            break;
        case 3:
            ui->columnView_3->setStyleSheet("background-color: red;");
            break;
        case 4:
            ui->columnView_4->setStyleSheet("background-color: red;");
            break;
        case 5:
            ui->columnView_5->setStyleSheet("background-color: red;");
            break;
        case 6:
            ui->columnView_6->setStyleSheet("background-color: red;");
            break;
        case 7:
            ui->columnView_7->setStyleSheet("background-color: red;");
            break;
        case 8:
            ui->columnView_8->setStyleSheet("background-color: red;");
            break;
        case 9:
            ui->columnView_9->setStyleSheet("background-color: red;");
            break;
        case 10:
            ui->columnView_10->setStyleSheet("background-color: red;");
            break;
        case 11:
            ui->columnView_11->setStyleSheet("background-color: red;");
            break;
        case 12:
            ui->columnView_12->setStyleSheet("background-color: red;");
            break;
        case 13:
            ui->columnView_13->setStyleSheet("background-color: red;");
            break;
        case 14:
            ui->columnView_14->setStyleSheet("background-color: red;");
            break;
        case 15:
            ui->columnView_15->setStyleSheet("background-color: red;");
            break;
        case 16:
            ui->columnView_16->setStyleSheet("background-color: red;");
            break;
        case 17:
            ui->columnView_17->setStyleSheet("background-color: red;");
            break;
        case 18:
            ui->columnView_18->setStyleSheet("background-color: red;");
            break;
        case 19:
            ui->columnView_19->setStyleSheet("background-color: red;");
            break;
        case 20:
            ui->columnView_20->setStyleSheet("background-color: red;");
            break;
        default:
            break;
    }
}

//根据缓冲区编号将缓冲区涂白
void MainWindow::depre(int id){
    switch(id){
        case 1:
            ui->columnView->setStyleSheet("background-color: white;");
            break;
        case 2:
            ui->columnView_2->setStyleSheet("background-color: white;");
            break;
        case 3:
            ui->columnView_3->setStyleSheet("background-color: white;");
            break;
        case 4:
            ui->columnView_4->setStyleSheet("background-color: white;");
            break;
        case 5:
            ui->columnView_5->setStyleSheet("background-color: white;");
            break;
        case 6:
            ui->columnView_6->setStyleSheet("background-color: white;");
            break;
        case 7:
            ui->columnView_7->setStyleSheet("background-color: white;");
            break;
        case 8:
            ui->columnView_8->setStyleSheet("background-color: white;");
            break;
        case 9:
            ui->columnView_9->setStyleSheet("background-color: white;");
            break;
        case 10:
            ui->columnView_10->setStyleSheet("background-color: white;");
            break;
        case 11:
            ui->columnView_11->setStyleSheet("background-color: white;");
            break;
        case 12:
            ui->columnView_12->setStyleSheet("background-color: white;");
            break;
        case 13:
            ui->columnView_13->setStyleSheet("background-color: white;");
            break;
        case 14:
            ui->columnView_14->setStyleSheet("background-color: white;");
            break;
        case 15:
            ui->columnView_15->setStyleSheet("background-color: white;");
            break;
        case 16:
            ui->columnView_16->setStyleSheet("background-color: white;");
            break;
        case 17:
            ui->columnView_17->setStyleSheet("background-color: white;");
            break;
        case 18:
            ui->columnView_18->setStyleSheet("background-color: white;");
            break;
        case 19:
            ui->columnView_19->setStyleSheet("background-color: white;");
            break;
        case 20:
            ui->columnView_20->setStyleSheet("background-color: white;");
            break;
        default:
            break;
    }
}

//根据缓冲区编号和生产者编号显示生产者指针
void MainWindow::inpre(int id,int pos){
    ui->label_23->setText("等待信息：");
    switch(pos){
        case 1:
            ui->textEdit->setStyleSheet("font-size: 25px;");
            ui->textEdit->setText(QString("%1").arg(id));
            ui->textEdit_20->setText("");
            break;
        case 2:
            ui->textEdit_2->setStyleSheet("font-size: 25px;");
            ui->textEdit_2->setText(QString("%1").arg(id));
            ui->textEdit->setText("");
            break;
        case 3:
            ui->textEdit_3->setStyleSheet("font-size: 25px;");
            ui->textEdit_3->setText(QString("%1").arg(id));
            ui->textEdit_2->setText("");
            break;
        case 4:
            ui->textEdit_4->setStyleSheet("font-size: 25px;");
            ui->textEdit_4->setText(QString("%1").arg(id));
            ui->textEdit_3->setText("");
            break;
        case 5:
            ui->textEdit_5->setStyleSheet("font-size: 25px;");
            ui->textEdit_5->setText(QString("%1").arg(id));
            ui->textEdit_4->setText("");
            break;
        case 6:
            ui->textEdit_6->setStyleSheet("font-size: 25px;");
            ui->textEdit_6->setText(QString("%1").arg(id));
            ui->textEdit_5->setText("");
            break;
        case 7:
            ui->textEdit_7->setStyleSheet("font-size: 25px;");
            ui->textEdit_7->setText(QString("%1").arg(id));
            ui->textEdit_6->setText("");
            break;
        case 8:
            ui->textEdit_8->setStyleSheet("font-size: 25px;");
            ui->textEdit_8->setText(QString("%1").arg(id));
            ui->textEdit_7->setText("");
            break;
        case 9:
            ui->textEdit_9->setStyleSheet("font-size: 25px;");
            ui->textEdit_9->setText(QString("%1").arg(id));
            ui->textEdit_8->setText("");
            break;
        case 10:
            ui->textEdit_10->setStyleSheet("font-size: 25px;");
            ui->textEdit_10->setText(QString("%1").arg(id));
            ui->textEdit_9->setText("");
            break;
        case 11:
            ui->textEdit_11->setStyleSheet("font-size: 25px;");
            ui->textEdit_11->setText(QString("%1").arg(id));
            ui->textEdit_10->setText("");
            break;
        case 12:
            ui->textEdit_12->setStyleSheet("font-size: 25px;");
            ui->textEdit_12->setText(QString("%1").arg(id));
            ui->textEdit_11->setText("");
            break;
        case 13:
            ui->textEdit_13->setStyleSheet("font-size: 25px;");
            ui->textEdit_13->setText(QString("%1").arg(id));
            ui->textEdit_12->setText("");
            break;
        case 14:
            ui->textEdit_14->setStyleSheet("font-size: 25px;");
            ui->textEdit_14->setText(QString("%1").arg(id));
            ui->textEdit_13->setText("");
            break;
        case 15:
            ui->textEdit_15->setStyleSheet("font-size: 25px;");
            ui->textEdit_15->setText(QString("%1").arg(id));
            ui->textEdit_14->setText("");
            break;
        case 16:
            ui->textEdit_16->setStyleSheet("font-size: 25px;");
            ui->textEdit_16->setText(QString("%1").arg(id));
            ui->textEdit_15->setText("");
            break;
        case 17:
            ui->textEdit_17->setStyleSheet("font-size: 25px;");
            ui->textEdit_17->setText(QString("%1").arg(id));
            ui->textEdit_16->setText("");
            break;
        case 18:
            ui->textEdit_18->setStyleSheet("font-size: 25px;");
            ui->textEdit_18->setText(QString("%1").arg(id));
            ui->textEdit_17->setText("");
            break;
        case 19:
            ui->textEdit_19->setStyleSheet("font-size: 25px;");
            ui->textEdit_19->setText(QString("%1").arg(id));
            ui->textEdit_18->setText("");
            break;
        case 20:
        ui->textEdit_20->setStyleSheet("font-size: 25px;");
            ui->textEdit_20->setText(QString("%1").arg(id));
            ui->textEdit_19->setText("");
            break;
        default:
            break;
    }
}

//根据缓冲区编号和消费者编号显示消费者指针
void MainWindow::outpre(int id,int pos){
    ui->label_23->setText("等待信息：");
    switch(pos){
        case 1:
            ui->textEdit_21->setStyleSheet("font-size: 25px;");
            ui->textEdit_21->setText(QString("%1").arg(id));
            ui->textEdit_40->setText("");
            break;
        case 2:
            ui->textEdit_22->setStyleSheet("font-size: 25px;");
            ui->textEdit_22->setText(QString("%1").arg(id));
            ui->textEdit_21->setText("");
            break;
        case 3:
            ui->textEdit_23->setStyleSheet("font-size: 25px;");
            ui->textEdit_23->setText(QString("%1").arg(id));
            ui->textEdit_22->setText("");
            break;
        case 4:
            ui->textEdit_24->setStyleSheet("font-size: 25px;");
            ui->textEdit_24->setText(QString("%1").arg(id));
            ui->textEdit_23->setText("");
            break;
        case 5:
            ui->textEdit_25->setStyleSheet("font-size: 25px;");
            ui->textEdit_25->setText(QString("%1").arg(id));
            ui->textEdit_24->setText("");
            break;
        case 6:
            ui->textEdit_26->setStyleSheet("font-size: 25px;");
            ui->textEdit_26->setText(QString("%1").arg(id));
            ui->textEdit_25->setText("");
            break;
        case 7:
            ui->textEdit_27->setStyleSheet("font-size: 25px;");
            ui->textEdit_27->setText(QString("%1").arg(id));
            ui->textEdit_26->setText("");
            break;
        case 8:
            ui->textEdit_28->setStyleSheet("font-size: 25px;");
            ui->textEdit_28->setText(QString("%1").arg(id));
            ui->textEdit_27->setText("");
            break;
        case 9:
            ui->textEdit_29->setStyleSheet("font-size: 25px;");
            ui->textEdit_29->setText(QString("%1").arg(id));
            ui->textEdit_28->setText("");
            break;
        case 10:
            ui->textEdit_30->setStyleSheet("font-size: 25px;");
            ui->textEdit_30->setText(QString("%1").arg(id));
            ui->textEdit_29->setText("");
            break;
        case 11:
            ui->textEdit_31->setStyleSheet("font-size: 25px;");
            ui->textEdit_31->setText(QString("%1").arg(id));
            ui->textEdit_30->setText("");
            break;
        case 12:
            ui->textEdit_32->setStyleSheet("font-size: 25px;");
            ui->textEdit_32->setText(QString("%1").arg(id));
            ui->textEdit_31->setText("");
            break;
        case 13:
            ui->textEdit_33->setStyleSheet("font-size: 25px;");
            ui->textEdit_33->setText(QString("%1").arg(id));
            ui->textEdit_32->setText("");
            break;
        case 14:
            ui->textEdit_34->setStyleSheet("font-size: 25px;");
            ui->textEdit_34->setText(QString("%1").arg(id));
            ui->textEdit_33->setText("");
            break;
        case 15:
            ui->textEdit_35->setStyleSheet("font-size: 25px;");
            ui->textEdit_35->setText(QString("%1").arg(id));
            ui->textEdit_34->setText("");
            break;
        case 16:
            ui->textEdit_36->setStyleSheet("font-size: 25px;");
            ui->textEdit_36->setText(QString("%1").arg(id));
            ui->textEdit_35->setText("");
            break;
        case 17:
            ui->textEdit_37->setStyleSheet("font-size: 25px;");
            ui->textEdit_37->setText(QString("%1").arg(id));
            ui->textEdit_36->setText("");
            break;
        case 18:
            ui->textEdit_38->setStyleSheet("font-size: 25px;");
            ui->textEdit_38->setText(QString("%1").arg(id));
            ui->textEdit_37->setText("");
            break;
        case 19:
            ui->textEdit_39->setStyleSheet("font-size: 25px;");
            ui->textEdit_39->setText(QString("%1").arg(id));
            ui->textEdit_38->setText("");
            break;
        case 20:
            ui->textEdit_40->setStyleSheet("font-size: 25px;");
            ui->textEdit_40->setText(QString("%1").arg(id));
            ui->textEdit_39->setText("");
            break;
        default:
            break;
    }
}

//显示等待信息
void MainWindow::wait(int id,int p_c){
    if(p_c==0){
        ui->label_23->setText("等待信息：生产者"+QString::number(id)+"正在等待缓冲区产生空单元");
    }
    else{
        ui->label_23->setText("等待信息：消费者"+QString::number(id)+"正在等待缓冲区有新的资源");
    }
}

//将资源加入队列
void MainWindow::push(int num) {
    buffer[in] = num;
    in++;
}
//将资源取出队列
void MainWindow::pop() {
    buffer[out] = 0;
    out++;
}
//返回队列的前续元素
int MainWindow::front() {
    return in;
}

//生产者进程
void MainWindow::produce(int id) {
    while (true) {
        // 生产一个产品
        int product = front() + 1;

        // 获取空缓冲区
        unique_lock<mutex> lockemfl(emfl);
        while (numEmptyBuffer == 0) {
            cout << "Producer " << id << " waiting for empty buffer..." << endl;
            emit updateColumnView5(id,0);//修改等待区ui状态
            cv_producer.wait(lockemfl);
        }


        mtx.lock();//P(mutex)操作

        // 放入产品，这段是临界区内容
        push(product);
        ++numProducts;
        cout << "Producer " << id << " produced product: " << in << endl;
        emit updateColumnView1(in);//修改缓冲区ui状态
        emit updateColumnView3(id,in);//修改指针区ui状态
        Sleep(100);
        --numEmptyBuffer;
        if (in == 20)
            in = 0;
        mtx.unlock();//互斥夹紧


        // 通知消费者,相当于V(full)操作

        cv_consumer.notify_all();
        lockemfl.unlock();

        // 等待随机时间后再次生产
        this_thread::sleep_for(chrono::milliseconds(100 + rand() % 1000));//加100是统一等待100毫秒
    }
}
//消费者进程
void MainWindow::consume(int id) {

    while (true) {
        // 从缓冲区取出数据
        int product;


        // 获取空缓冲区，相当于P(full)操作
        unique_lock<mutex> lockemfl(emfl);
        while (numProducts == 0)
        {
            cout << "Consumer " << id << " waiting for product..." << endl;
            emit updateColumnView5(id,1);//修改等待区ui状态
            cv_consumer.wait(lockemfl);
        }


        mtx.lock();//P(mutex)操作

        // 取出产品，这段是临界区内容
        --numProducts;
        product = front();
        pop();
        cout << "Consumer " << id << " consumed product: " << out << endl;
        emit updateColumnView2(out);//修改缓冲区ui状态
        emit updateColumnView4(id,out);//修改指针区ui状态
        Sleep(100);
        ++numEmptyBuffer;
        if (out == 20)
            out = 0;
        mtx.unlock();//互斥夹紧


        // 通知生产者

        cv_producer.notify_all();
        lockemfl.unlock();

        // 等待随机时间后再次消费
        this_thread::sleep_for(chrono::milliseconds(100 + rand() % 1000));//加100是统一等待100毫秒
    }
}
//bool stopThreads = false;
//进程创建函数
void MainWindow::program() {
    srand((unsigned int)(time(0)));
    vector<class thread> producerThreads;
    vector<class thread> consumerThreads;
    for (int i = 0; i < numProducers; ++i)
        producerThreads.emplace_back(&MainWindow::produce, this, i);

    for (int i = 0; i < numConsumers; ++i)
        consumerThreads.emplace_back(&MainWindow::consume, this, i);

    for (auto& t : producerThreads)
        t.join();

    for (auto& t : consumerThreads)
        t.join();
}

