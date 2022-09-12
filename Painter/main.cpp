#include "mainwindow.h"
#include<QSplashScreen>
#include <QApplication>
#include<QTimer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.showMaximized();
    QSplashScreen *splashScreen=new QSplashScreen(QPixmap(":/images/Final.jpg"));
    splashScreen->show();
    QTimer::singleShot(4000,splashScreen,SLOT(close()));
    QTimer::singleShot(4000,&w,SLOT(showMaximized()));
    //w.show();
    return a.exec();
}
