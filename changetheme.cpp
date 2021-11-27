#include "changetheme.h"
#include "ui_changetheme.h"
#include <QFile>
Changetheme::Changetheme(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Changetheme)
{
    ui->setupUi(this);
}

Changetheme::~Changetheme()
{
    delete ui;
}



void Changetheme::on_Applytheme_clicked()
{
    QString item;
    item=ui->listheme->currentItem()->text();
    if(item=="Midnight Sky")
    {
        QFile file("C:\\Users\\khali\\Desktop\\integration finaleee!!!\\E-Health_2A1\\Integration_Ehealth\\stylesheets\\Takezo.qss");
        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());
        //MainWindow.setStyleSheet(styl);
        qApp->setStyleSheet(styleSheet);
    }
    if(item=="Summer Citrus")
    {
        QFile file("C:\\Users\\khali\\Desktop\\integration finaleee!!!\\E-Health_2A1\\Integration_Ehealth\\stylesheets\\Irrorater.qss");
        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());
        //MainWindow.setStyleSheet(styl);
        qApp->setStyleSheet(styleSheet);
    }
    if(item=="Hackerman")
    {
        QFile file("C:\\Users\\khali\\Desktop\\integration finaleee!!!\\E-Health_2A1\\Integration_Ehealth\\stylesheets\\Hookmark.qss");
        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());
        //MainWindow.setStyleSheet(styl);
        qApp->setStyleSheet(styleSheet);
    }
    if(item=="Violet")
    {
        QFile file("C:\\Users\\khali\\Desktop\\integration finaleee!!!\\E-Health_2A1\\Integration_Ehealth\\stylesheets\\Wstartpage.qss");
        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());
        //MainWindow.setStyleSheet(styl);
        qApp->setStyleSheet(styleSheet);
    }
    if(item=="Dark")
    {
        //C:\Users\khali\Desktop\integration finaleee!!!\E-Health_2A1\Integration_Ehealth\stylesheets
        QFile file("C:\\Users\\khali\\Desktop\\integration finaleee!!!\\E-Health_2A1\\Integration_Ehealth\\stylesheets\\Combinear.qss");
        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());
        //MainWindow.setStyleSheet(styl);
        qApp->setStyleSheet(styleSheet);
    }
}

void Changetheme::on_cancel_clicked()
{
    this->close();
}
