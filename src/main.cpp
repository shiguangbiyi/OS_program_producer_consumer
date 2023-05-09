#include "widget.h"

#include <QApplication>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <windows.h>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;//主页面
    w.show();//主页面显示
    return a.exec();
}
