#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>
#include <QDebug>
#include <QIntValidator>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_client->setModel(Etmp.afficher());
ui->cin->setValidator(new QIntValidator(0,99999999,this));

}


MainWindow::~MainWindow()
{
    delete ui;
}






void MainWindow::on_pushButtonAjouter_clicked()
{
    int  CIN=ui->cin->text().toInt();
    QString REF=ui->REF->text();
     QString NOM=ui->Nom->text();
      QString PRENOM=ui->Prenom->text();
       QString ADRESSE_EMAIL=ui->Nom->text();
     int Numtel=ui->Numtel->text().toInt();
    Client C(CIN,REF,NOM,PRENOM,Numtel,ADRESSE_EMAIL);
bool test=C.ajouter();
if (test)
        { //Actualiser
     ui->tab_client->setModel(Etmp.afficher());
        QMessageBox:: information(nullptr, QObject::tr("OK"),
                                           QObject::tr("Ajout effectué\n"
                                                       "click cancel to exit."),QMessageBox::Cancel);
        }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "click Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButtonSupprimer_clicked()
{
    Client c;c.setCIN(ui->cin_2->text().toInt());
    bool test=Etmp.supprimer(c.get_CIN());
    QMessageBox msgBox;
    if (test)
            {
        //actualiser
         ui->tab_client->setModel(Etmp.afficher());
            QMessageBox:: information(nullptr, QObject::tr("OK"),
                                               QObject::tr("Suppression effectué\n"
                                                           "click cancel to exit."),QMessageBox::Cancel);
            }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Suppression non effectué.\n"
                                              "click Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButtonModifier_clicked()
{


        int  CIN=ui->cin->text().toInt();
        QString REF=ui->REF->text();
         QString NOM=ui->Nom->text();
          QString PRENOM=ui->Prenom->text();
           QString ADRESSE_EMAIL=ui->Nom->text();
         int Numtel=ui->Numtel->text().toInt();
        Client C(CIN,REF,NOM,PRENOM,Numtel,ADRESSE_EMAIL);
    bool test=C.modifier(CIN);
    if (test)
            { //Actualiser
         ui->tab_client->setModel(Etmp.afficher());
            QMessageBox:: information(nullptr, QObject::tr("OK"),
                                               QObject::tr("Ajout effectué\n"
                                                           "click cancel to exit."),QMessageBox::Cancel);
            }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Ajout non effectué.\n"
                                              "click Cancel to exit."),QMessageBox::Cancel);

}
