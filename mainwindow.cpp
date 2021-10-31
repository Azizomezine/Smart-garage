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
ui->cin_2->setValidator(new QIntValidator(0,99999999,this));
ui->cin_3->setValidator(new QIntValidator(0,99999999,this));
ui->Numtel->setValidator(new QIntValidator(0,99999999,this));
ui->Numtel_2->setValidator(new QIntValidator(0,99999999,this));
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
    if(REF.isEmpty() || NOM.isEmpty() || PRENOM.isEmpty())
                         {
                             QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir les champs vides Pour continuez."),QMessageBox::Cancel);
                         }
    else
    {
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
    }}

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


        int  CIN=ui->cin_3->text().toInt();
        QString REF=ui->REF->text();
         QString NOM=ui->Nom->text();
          QString PRENOM=ui->Prenom->text();
           QString ADRESSE_EMAIL=ui->AdresseEmail_2->text();
         int Numtel=ui->Numtel_2->text().toInt();
        Client C(CIN,REF,NOM,PRENOM,Numtel,ADRESSE_EMAIL);
    bool test=C.modifier(CIN);
    if(CIN==0||REF.isEmpty() || NOM.isEmpty() || PRENOM.isEmpty())
                         {
                             QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir les champs vides Pour continuez."),QMessageBox::Cancel);
                         }
    else
    {
    if (test)
            { //Actualiser
         ui->tab_client->setModel(Etmp.afficher());
            QMessageBox:: information(nullptr, QObject::tr("OK"),
                                               QObject::tr("Modifier un Client effectué\n"
                                                           "click cancel to exit."),QMessageBox::Cancel);
            }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Ajout non effectué.\n"
                                              "click Cancel to exit."),QMessageBox::Cancel);

}}

void MainWindow::on_pushButtonActualiser_clicked()
{
     ui->tab_client->setModel(Etmp.afficher());
}

void MainWindow::on_pushButton_clicked()
{
      ui->tab_client->setModel(rechercher(ui->REF2->text()));
}
