# OS_program_producer_consumer
生产者-消费者演示程序

一、项目背景及需求

生产者消费者问题演示程序是一个经典的并发编程问题，它涉及到多个生产者和消费者同时访问共享缓冲区的情况，需要确保生产者和消费者之间的同步和互斥。
该演示程序通过使用 C++11 标准中的线程库和条件变量实现了一个基本的生产者消费者问题。在该程序中，生产者线程生产产品并将其放入共享缓冲区，而消费者线程从共享缓冲区中取出产品并进行消费。为了避免生产者和消费者之间的竞争条件，该程序使用了互斥量和条件变量来同步和协调它们之间的行为。
该演示程序的目的是展示生产者消费者问题的解决方案，并通过可视化界面直观地演示生产者和消费者之间的交互过程，从而更好地理解并发编程的基本原理和技术。
项目具体需求：
有界缓冲区有20个存储单元，存取数据为1-20这20个整型数；当生产者和消费者对有界缓冲区进行操作后,即时显示有界缓冲区的全部内容、当前位置、生产者/消费者进程的标识符；生产者和消费者各有两个以上；

二、开发/运行环境

环境: Windows 10 2004

语言: C++ / MinGW x64 8.1.0 / Qt 5.13.1

三、系统架构

项目文件:
```
    └─p_c_program
        │  README.md
        │
        ├─release
        │  │  p_c_program.exe
        │  │  libgcc_s_seh-1.dll
        │  │  libstdc++-6.dll
        │  │  Qt5Core.dll
        │  │  Qt5Gui.dll
        │  │  Qt5Widgets.dll
        │  │
        │  ├─platforms
        │  │      qwindows.dll
        │  │
        │  └─styles
        │          qwindowsvistastyle.dll
        │
        └─src
            main.cpp
            mainwindow.cpp
            mainwindow.h
            mainwindow.ui
            p-c_program.pro
            p-c_program.pro.user
            widget.cpp
            widget.h
            widget.ui
```
项目总共包含两个页面，主页面：widget.ui；演示页面：mainwindow.ui

四、页面介绍

主页面（widget.ui）：用于提示用户输入生产者、消费者的数量，点击“开始运行”后即可进入演示页面查看演示过程。页面简洁清晰。

演示页面（mainwindow.ui）：根据主页面输入的生产者、消费者数量，演示生产者、消费者使用缓冲区的情况。其中，三排矩形中，中间的矩形阵即代表缓冲区，分别编号1,2,3…，20，当矩阵被涂红即代表缓冲区中有资源，变白即代表该区空闲。第一排矩形用于显示生产者的指针(in)，数字显示的位置即为指针所在位置，数字表示生产者的编号，如图，即表示生产者0在6号位生产；第三排矩形用于显示消费者的指针(out)，数字显示的位置即为指针所在的位置，数字表示消费者的编号，如图，即表示消费者2在3号位消费。


当生产者比消费者显著较少时，缓冲区容易缺乏资源，当缓冲区没有资源而消费者线程请求资源时，下方将会出现等待信息，表示消费者等待缓冲区有新的资源。
当消费者比生产者显著较少时，缓冲区容易被占满，当缓冲区没有空闲区而生产者线程生产资源时，下方将会出现等待信息，表示生产者等待缓冲区有新的空间。



五、算法介绍

本程序在Qt框架下将两个页面分别建立成两个类，其中演示窗口类中用于创建线程和演示线程。
MainWindow窗口类中各函数作用：
void program()用于创建线程，并在线程结束时回收线程；
void produce()用于运行生产者线程；
void consume()用于运行消费者线程；
void push(int num)用于从队列中加入元素；
void pop()用于从队列中取出元素；
int front()用于返回队列最前的元素；
void pre(int id)用于实现加入元素的ui表现
void depre(int id)用于实现取出元素的ui表现
void inpre(int id,int pos)用于实现加入指针的ui表现
void outpre(int id,int pos)用于实现取出指针的ui表现
void wait(int id,int p_c);用于实现等待信息的ui表现

多线程调度算法：
重要程序源代码：
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

本算法使用了一个互斥量mtx作为锁，在生产者或消费者进入临界区时，mtx会上锁，在退出临界区时，mtx会解锁，这样就实现了互斥操作，在代码中，上锁为：mtx.lock()；解锁为mtx.unlock()。
同步的实现是用同步变量emfl，当生产者完成生产会通知消费者进行消费，或消费者完成消费会通知生产者进行生产，这样实现同步操作，在代码中，unique_lock<mutex> lockemfl(emfl)和cv_producer.notify_all(); lockemfl.unlock()为一对同步操作。
本程序使用的是C++标准库中的<mutex>等头文件，方便实现。

六、可行性分析

1.死锁问题：由于生产者和消费者之间的资源竞争，存在死锁的可能性。例如，当缓冲区已满，生产者线程将被阻塞，同时消费者线程又无法消费产品而被阻塞，从而导致死锁。为了避免死锁，程序使用了条件变量进行同步，当缓冲区已满时，生产者线程等待条件变量，当缓冲区已空时，消费者线程等待条件变量，从而避免了死锁问题。

2.竞态条件问题：由于多个线程同时访问共享变量，可能会出现竞态条件问题。例如，多个线程同时访问缓冲区、空闲缓冲区数量、产品数量等共享变量时，可能会导致数据不一致。为了避免竞态条件问题，程序使用了互斥量进行同步，确保同一时间只有一个线程能够访问共享变量。

3.缓冲区溢出问题：由于缓冲区是有限的，如果生产者生产的速度过快，可能会导致缓冲区溢出。为了避免缓冲区溢出问题，程序在生产者线程中使用了空闲缓冲区数量变量进行计数，当空闲缓冲区数量为0时，生产者线程等待条件变量，直到有空闲缓冲区可用。

4.缓冲区空闲问题：由于消费者消费的速度可能会比生产者生产的速度慢，可能会导致缓冲区一直处于空闲状态。为了避免缓冲区空闲问题，程序在消费者线程中使用了产品数量变量进行计数，当产品数量为0时，消费者线程等待条件变量，直到有产品可消费。
基于上述考虑，可以认为上述程序是可行的，并且在正确使用互斥量和条件变量的情况下，能够正确解决生产者-消费者问题。
