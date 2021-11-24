#include "mainwindow.h"
#include <QApplication>
//#include <QLabel>
#include <QMessageBox>
#include "connection.h"




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Connection c;
    bool test=c.createconnect();
    MainWindow w;
    if(test)
    {w.show();
        QMessageBox::information( nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

        //QLabel *Label = new QLabel ("Welcome to smart garage");
        //Label ->setWindowTitle("SMART GARAGE");
        //Label ->show();

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);




    return a.exec();
}
