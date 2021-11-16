#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QIntValidator>
#include "QrCode.hpp"
#include "client.h"
#include "avis.h"
#include "carte.h"
#include <QtWidgets>
#include <QObject>
#include <QSqlQuery>
#include <QtWidgets>
#include <QHeaderView>
#include "QCustomPlot.h"
using namespace qrcodegen;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::makePlot();
    ui->tab_client->setModel(Etmp.afficher());
ui->tableavis->setModel(at.afficher());
ui->cin->setValidator(new QIntValidator(0,99999999,this));
ui->Numtel->setValidator(new QIntValidator(0,99999999,this));
ui->Numtel_2->setValidator(new QIntValidator(0,99999999,this));
ui->AdresseEmail->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0-9_@.]{0,64}"), this ));
ui->Nom->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0]{0,10}"), this ));
ui->REF->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0-9]{0,10}"), this ));
ui->REF2->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0]{0,10}"), this ));
ui->Prenom->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0]{0,10}"), this ));
}


MainWindow::~MainWindow()
{
    delete ui;
}






void MainWindow::on_pushButtonAjouter_clicked()
{

    int  CIN=ui->cin->text().toInt();
//recuperation des donnees
    QString REF=ui->REF->text();
     QString NOM=ui->Nom->text();
      QString PRENOM=ui->Prenom->text();
       QString ADRESSE_EMAIL=ui->AdresseEmail->text();
     int Numtel=ui->Numtel->text().toInt();
     QString SERVICE=ui->comboBox->currentText();
     //ajout
    Client C(CIN,REF,NOM,PRENOM,Numtel,ADRESSE_EMAIL,SERVICE);
    if(CIN<=0||REF.isEmpty() || NOM.isEmpty() || PRENOM.isEmpty() ||SERVICE.isEmpty() || ADRESSE_EMAIL.isEmpty())
                         {
                             QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir les champs vides Pour continuez."),QMessageBox::Cancel);
                         }
   else if ((CIN<10000000)||(CIN>99999999) )
           {

        QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("Echec de l'ajout veuillez verifier le CIN(8 chiffres)"),QMessageBox::Cancel);
    }
    else if ((Numtel<10000000)||(Numtel>99999999) )
           {

        QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("Echec de l'ajout veuillez verifier le num tel(8 chiffres)"),QMessageBox::Cancel);
    }

    else

    {
bool test=C.ajouter();
if (test)
        {
        QMessageBox:: information(nullptr, QObject::tr("OK"),
                                           QObject::tr("Ajout Client effectué\n"
                                                       "click cancel to exit."),QMessageBox::Cancel);
      int cin=ui->cin->text().toInt();
      int pt=80;
      if(SERVICE=="VIDANGE")
      {
          pt=50;
      }
      else if(SERVICE=="NETOYAGE")
      {
         pt=30;
      }
       Carte Cr(cin,pt);
    bool     test1=Cr.ajouterCarte();
        QMessageBox msgBox;

        if(test1)
        {
            QMessageBox:: information(nullptr, QObject::tr("OK"),
                                               QObject::tr("Ajout carte Client effectué\n"
                                                           "click cancel to exit."),QMessageBox::Cancel);
        }
         ui->cin->clear();
         ui->REF->clear();
         ui->Prenom->clear();
         ui->Nom->clear();
         ui->Numtel->clear();
        ui->AdresseEmail->clear();
        ui->comboBox->setCurrentIndex(0);
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

    bool test=Etmp.supprimer(cin);


    if (test)
            {

        /* ui->tab_client->setModel(Etmp.rechercher(""));
          ui->tab_client->clearSelection();*/
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
}}

void MainWindow::on_pushButtonModifier_clicked()
{
int CIN=ui->cin_comboBox->currentText().toInt();
         QString NOM=ui->Nom_2->text();
         QString REF=ui->REF_2->text();
          QString PRENOM=ui->Prenom_2->text();
           QString ADRESSE_EMAIL=ui->AdresseEmail_2->text();
         int Numtel=ui->Numtel_2->text().toInt();
         QString SERVICE=ui->comboBox_2->currentText();
        Client C(CIN,REF,NOM,PRENOM,Numtel,ADRESSE_EMAIL,SERVICE);
bool test=C.modifier(CIN);
    if ((Numtel<10000000)||(Numtel>99999999) )
           {

        QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("Echec de l'ajout veuillez verifier le num tel(8 chiffres)"),QMessageBox::Cancel);
    }
else {
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

}}


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

void MainWindow::on_Button_dcroissant_clicked()
{
  ui->tab_client->setModel(Etmp.tri());
}
void MainWindow::on_Button_croissant_clicked()
{
    ui->tab_client->setModel(Etmp.trid());
}

void MainWindow::on_pushButtonClient_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButtonAvis_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
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
     QString type_avis=ui->typecomboBox->currentText();
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

QMessageBox msg;

  QString ref_avis=ui->Ref_avis->text();
     QString type_avis=ui->typecomboBox_2->currentText();
      QString Avis=ui->texteavis_2->text();

             QItemSelectionModel *select = ui->tableavis->selectionModel();
            if (!select->hasSelection()){
                 msg.setText("Please select something");

                 msg.setIcon(msg.Critical);
                 msg.exec();
                 return;
            }

    if( type_avis.isEmpty() || Avis.isEmpty())
                         {
                             QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir les champs vides Pour continuez."),QMessageBox::Cancel);
                         }

    avis A( ref_avis, type_avis, Avis);
        bool test=A.modifier(ref_avis);


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









void MainWindow::on_cin_comboBox2_activated(const QString &arg1)
{
    /*QSqlQueryModel * model= new QSqlQueryModel;
        model->setQuery("SELECT MATRICULE_FISCALE FROM client_fidele");*/

        int MAT=ui->cin_comboBox2->currentText().toInt();

        QSqlQuery query;
        query.prepare("SELECT * FROM CLIENT WHERE CIN = :CIN");
        query.bindValue(":CIN",MAT);
        query.exec();
       // ui->tabWidget->setCurrentIndex(12);
       // ui->comboBox_ref_modifier_2->setModel(model);
        while(query.next()){
            //ui->lineEdit_matricule_11->setText(query.value(0).toString());
            ui->REF_2->setText(query.value(1).toString());
            ui->Nom_2->setText(query.value(2).toString());
            ui->Prenom_2->setText(query.value(3).toString());
            ui->AdresseEmail_2->setText(query.value(4).toString());
             ui->Numtel_2->setText(query.value(5).toString());
             ui->comboBox_2->setCurrentText(query.value(6).toString());

    }
}

void MainWindow::on_pushButton_3_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::makePlot()
{
    //set-up
       QLinearGradient gradient(0, 0, 0, 400);
       gradient.setColorAt(0, QColor(90, 90, 90));
       gradient.setColorAt(0.38, QColor(105, 105, 105));
       gradient.setColorAt(1, QColor(70, 70, 70));
       ui->customPlot->setBackground(QBrush(gradient));
       QCPBars *regen = new QCPBars( ui->customPlot->xAxis,  ui->customPlot->yAxis);
       regen->setAntialiased(false);
       regen->setStackingGap(1);
       regen->setName("nbr_client");
       regen->setPen(QPen(QColor(255, 170, 0).lighter(130)));
       regen->setBrush(QColor(255, 170, 0));

       //x axis
       QVector<double> ticks;
       QVector<QString> labels;
       ticks << 1 << 2 << 3;
       labels << "VIDANGE" << "NETOYAGE" << "NETTOYAGE/VIDANGE" ;
       QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
       textTicker->addTicks(ticks, labels);

       ui->customPlot->xAxis->setTicker(textTicker);
        ui->customPlot->xAxis->setTickLabelRotation(60);
        ui->customPlot->xAxis->setSubTicks(false);
        ui->customPlot->xAxis->setTickLength(0, 4);
       ui->customPlot->xAxis->setRange(0, 8);
       ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
       ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
       ui->customPlot->xAxis->grid()->setVisible(true);
        ui->customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
        ui->customPlot->xAxis->setTickLabelColor(Qt::white);
        ui->customPlot->xAxis->setLabelColor(Qt::white);

       //y axis

        ui->customPlot->yAxis->setRange(0,30);//intervale de x
        ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
        ui->customPlot->yAxis->setBasePen(QPen(Qt::white));
       ui->customPlot->yAxis->setTickPen(QPen(Qt::white));
       ui->customPlot->yAxis->setSubTickPen(QPen(Qt::white));
      ui->customPlot->yAxis->grid()->setSubGridVisible(true);
      ui->customPlot->yAxis->setTickLabelColor(Qt::white);
      ui->customPlot->yAxis->setLabelColor(Qt::white);
       ui->customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
       ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

   //data
       QVector<double> regenData;

       QSqlQuery query1("select SUM(nbr_client)from CLIENT where SERVICE='VIDANGE'  ");

       while (query1.next()) {
                   int  nbr_faute=0;
                    int nbr_fauteee=0;
                               int  nbr_fautee = query1.value(0).toInt();

                 QSqlQuery query2("select SUM(nbr_client)from CLIENT where TYPE='NETOYAGE'");
                 while (query2.next()) {

                                         nbr_faute = query2.value(0).toInt();
                                         QSqlQuery query3("select SUM(QUANTITE)from CLIENT where TYPE='NETTOYAGE/VIDANGE'");
                                         while (query3.next()) {
                                             nbr_fauteee = query3.value(0).toInt();
                                             break;
                                         }
                                        }
                 regenData<< nbr_fautee << nbr_faute<< nbr_fauteee;
                               break;
                              }

       regen->setData(ticks, regenData);

       //legend


        ui->customPlot->legend->setVisible(true);
        ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
       ui->customPlot->legend->setBrush(QColor(255, 255, 255, 100));
       ui->customPlot->legend->setBorderPen(Qt::NoPen);

       QFont legendFont = font();
       legendFont.setPointSize(10);
       ui->customPlot->legend->setFont(legendFont);
       ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}



