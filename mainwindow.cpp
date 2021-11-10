#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QIntValidator>
#include "QrCode.hpp"
#include "client.h"
#include "avis.h"
#include <QtWidgets>
#include <QObject>
#include <QSqlQuery>
#include <QtWidgets>
#include <QHeaderView>
using namespace qrcodegen;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_client->setModel(Etmp.afficher());
ui->tableavis->setModel(at.afficher());
ui->cin->setValidator(new QIntValidator(111111111,99999999,this));
ui->Numtel->setValidator(new QIntValidator(0,99999999,this));
ui->Numtel_2->setValidator(new QIntValidator(0,99999999,this));
ui->Nom->setMaxLength(10);
ui->REF->setMaxLength(20);
ui->REF2->setMaxLength(30);
ui->Prenom->setMaxLength(30);

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
     QString SERVICE=ui->comboBox->currentText();
    Client C(CIN,REF,NOM,PRENOM,Numtel,ADRESSE_EMAIL,SERVICE);
    if(CIN<=0||REF.isEmpty() || NOM.isEmpty() || PRENOM.isEmpty() ||SERVICE.isEmpty())
                         {
                             QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir les champs vides Pour continuez."),QMessageBox::Cancel);
                         }

    else

    {
bool test=C.ajouter();
if (test)
        {
        QMessageBox:: information(nullptr, QObject::tr("OK"),
                                           QObject::tr("Ajout Client effectué\n"
                                                       "click cancel to exit."),QMessageBox::Cancel);
        }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Client exist deja.\n"
                                          "click Cancel to exit."),QMessageBox::Cancel);
    }}

void MainWindow::on_pushButtonSupprimer_clicked()
{
    int cin=ui->cin_comboBox->currentText().toInt();

    if(cin<=0)
           {
               QMessageBox::critical(0,qApp->tr("erreur"),
                                     qApp->tr("veillez remplir le champs vide"),QMessageBox::Cancel);
           }
    else {
        QMessageBox::critical(0,qApp->tr("attention"),
                                    qApp->tr("voulez vous supprimer cette depense?"),QMessageBox::Yes,QMessageBox::No);
        if(QMessageBox::Yes)
               {
    bool test=Etmp.supprimer(cin);


    if (test)
            {

         ui->tab_client->setModel(Etmp.rechercher(""));
          ui->tab_client->clearSelection();
            QMessageBox:: information(nullptr, QObject::tr("OK"),
                                               QObject::tr("Suppression d'un client avec succes\n"
                                                           "click cancel to exit."),QMessageBox::Cancel);

            QSqlQueryModel * model= new QSqlQueryModel;
                   model->setQuery("SELECT CIN FROM client");

                   ui->cin_comboBox->setModel(model);

            }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Suppression non effectué.\n"
                                              "click Cancel to exit."),QMessageBox::Cancel);
}}}

void MainWindow::on_pushButtonModifier_clicked()
{
int CIN=ui->cin_comboBox->currentText().toInt();
         QString NOM=ui->Nom->text();
         QString REF=ui->REF->text();
          QString PRENOM=ui->Prenom->text();
           QString ADRESSE_EMAIL=ui->AdresseEmail_2->text();
         int Numtel=ui->Numtel_2->text().toInt();
         QString SERVICE=ui->comboBox_2->currentText();
        Client C(CIN,REF,NOM,PRENOM,Numtel,ADRESSE_EMAIL,SERVICE);
    bool test=C.modifier(CIN);


    if (test)
            {

            QMessageBox:: information(nullptr, QObject::tr("OK"),
                                               QObject::tr("Modifier un Client effectué\n"
                                                           "click cancel to exit."),QMessageBox::Cancel);
            QSqlQueryModel * model= new QSqlQueryModel;
            model->setQuery("SELECT CIN FROM CLIENT");

            }
        else
           { QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Ajout non effectué.\n"
                                              "click Cancel to exit."),QMessageBox::Cancel);}

}


void MainWindow::on_pushButtonActualiser_clicked()
{
    ui->tab_client->setModel(Etmp.afficher());
     QSqlQueryModel * model= new QSqlQueryModel;
                      model->setQuery("SELECT CIN FROM client");
                  ui->cin_comboBox2->setModel(model);
                      ui->cin_comboBox->setModel(model);
}



void MainWindow::on_pushButtonRechercher_clicked()
{

   Client C;

          QString REF=ui->REF2->text();

          ui->tab_client->setModel(C.rechercher(REF));


}

void MainWindow::on_pushButtontrier_clicked()
{
    Client C;

           QString REF=ui->REF2->text();

           ui->tab_client->setModel(C.tri());
}

void MainWindow::on_pushButtonClient_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButtonAvis_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_clicked()
{
   ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_2_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButtonAjouteravis_clicked()
{



    QString ref_avis=ui->Ref_avis->text();
     QString type_avis=ui->Type_avis->text();
      QString Avis=ui->texteavis->text();
    avis A( ref_avis, type_avis, Avis);
    if(ref_avis.isEmpty() || type_avis.isEmpty() || Avis.isEmpty())
                         {
                             QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir les champs vides Pour continuez."),QMessageBox::Cancel);
                         }

    else
    {
bool test=A.ajouter();
if (test)
        { //Actualiser

        QMessageBox:: information(nullptr, QObject::tr("OK"),
                                           QObject::tr("Ajout effectué\n"
                                                       "click cancel to exit."),QMessageBox::Cancel);
        }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "click Cancel to exit."),QMessageBox::Cancel);
    }
}




void MainWindow::on_qrcodegen_clicked()
{

    QMessageBox msg;
          QItemSelectionModel *select = ui->tab_client->selectionModel();
          if (!select->hasSelection()){
               msg.setText("Please select something");

               msg.setIcon(msg.Critical);
               msg.exec();
               return;
          }
    int tabeq=ui->tab_client->currentIndex().row();
           QVariant idd=ui->tab_client->model()->data(ui->tab_client->model()->index(tabeq,0));
           QString id= idd.toString();
           QSqlQuery qry;
           qry.prepare("select * from CLIENT where CIN=:id");
           qry.bindValue(":id",id);
           qry.exec();
              QString  NOM,PRENOM,ADRESSE_Email,REF,NUMTEL,SERVICE,ide;

           while(qry.next()){
               REF=qry.value(1).toString();
               NOM=qry.value(2).toString();
               PRENOM=qry.value(3).toString();
               ADRESSE_Email=qry.value(4).toString();
               NUMTEL=qry.value(5).toString();
               SERVICE=qry.value(6).toString();
           }
           ide=QString(id);
                  ide="CIN:"+ide+"REF:"+REF+"NOM:"+NOM+"PRENOM:"+PRENOM+"ADRESSE_Email:"+ADRESSE_Email+"Numtel:"+NUMTEL+"SERVICE:"+SERVICE;
           QrCode qr = QrCode::encodeText(ide.toUtf8().constData(), QrCode::Ecc::HIGH);

           // Read the black & white pixels
           QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
           for (int y = 0; y < qr.getSize(); y++) {
               for (int x = 0; x < qr.getSize(); x++) {
                   int color = qr.getModule(x, y);  // 0 for white, 1 for black

                   // You need to modify this part
                   if(color==0)
                       im.setPixel(x, y,qRgb(254, 254, 254));
                   else
                       im.setPixel(x, y,qRgb(0, 0, 0));
               }
           }
           im=im.scaled(200,200);
           ui->qrcodecommande->setPixmap(QPixmap::fromImage(im));

}
void MainWindow::on_pushButtonActualiser_2_clicked()
{
ui->tableavis->setModel(at.afficher());
}

void MainWindow::on_pushButtonSupprimer_2_clicked()
{
    QMessageBox msg;
           QItemSelectionModel *select = ui->tableavis->selectionModel();
          if (!select->hasSelection()){
               msg.setText("Please select something");

               msg.setIcon(msg.Critical);
               msg.exec();
               return;
          }


              QString ref =select->selectedRows(0).value(0).data().toString();

              if(at.supprimer(ref))
              { //Actualiser
                  ui->tab_client->setModel(at.afficher());
                  QMessageBox:: information(nullptr, QObject::tr("OK"),
                                                     QObject::tr("Suppression effectué\n"
                                                                 "click cancel to exit."),QMessageBox::Cancel);
                  }
              else
                  QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                        QObject::tr("Suppression non effectué.\n"
                                                    "click Cancel to exit."),QMessageBox::Cancel);
              }




void MainWindow::on_pushButtonModifieravis_clicked()
{

}








