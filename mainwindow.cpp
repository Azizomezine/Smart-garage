#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QIntValidator>
#include "QrCode.hpp"
#include "client.h"
#include "avis.h"
#include "carte.h"
#include "voiture.h"
#include "finance.h"
#include <QtWidgets>
#include <QObject>
#include <QSqlQuery>
#include <QtWidgets>
#include <QHeaderView>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include "exportexcelobject.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPropertyAnimation>
#include <QFileDialog>//provides a dialog that allow users to select files or directories
#include <QtSerialPort/QSerialPort>
#include "notif.h"
#include <QSound>
#include <QMediaPlayer>
QT_CHARTS_USE_NAMESPACE
using namespace QtCharts;
using namespace qrcodegen;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //************* controle Aziz client************************************
    this->setStyleSheet("");
    QFile file("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\Gestion_Client\\stylesheets\\Aqua.qss");
    file.open(QFile::ReadOnly);
    QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integration_test\\music.wav");
    QString styleSheet = QLatin1String(file.readAll());
    ui->pushButtonRechercher->setIcon(QIcon("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integration_test\\image\\search"));
   ui->pushButtonAjouter->setIcon(QIcon("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integration_test\\image\\add-user"));
   ui->pushButtonSupprimer->setIcon(QIcon("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integration_test\\image\\remove-user"));

    //MainWindow.setStyleSheet(styl);
    qApp->setStyleSheet(styleSheet);
    ui->tab_client->setModel(Etmp.afficher());
    ui->tab_carte->setModel(ct.afficherCarte());
ui->tableavis->setModel(at.afficher());
 ui->tab_carte->setModel(ct.rechercherclient( cinc));
ui->cin->setValidator(new QIntValidator(0,99999999,this));
ui->Numtel->setValidator(new QIntValidator(0,99999999,this));
ui->Numtel_2->setValidator(new QIntValidator(0,99999999,this));
ui->AdresseEmail->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0-9_@.]{0,64}"), this ));
ui->Nom->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0]{0,10}"), this ));
ui->REF->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0-9]{0,10}"), this ));
ui->REF2->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0]{0,10}"), this ));
ui->Prenom->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0]{0,10}"), this ));
  ui->stackedWidget->setCurrentIndex(10);
//********************************controle yessin**********************************************
ui->le_id->setValidator( new QIntValidator(0,99999999,this));
   ui->tab_employe->setModel(p.afficher());
//   ******************************controle nour*****************************
   ui->tab_voiture->setModel(v.afficher());
   ui->rech_mat->setMaxLength(30);
//***********************************control rymel*********************
   f.stat(series);
   ui->idc->setValidator(new QIntValidator (0,999999,this));
    ui->tab_facture->setModel(f.AfficherFacture());
    QChart *chart = new QChart();
      chart->addSeries(series);
      chart->setTitle("Statistiques");
      chart->setBackgroundBrush(Qt::transparent);
      QChartView *chartview = new QChartView(chart);
      chartview->setRenderHint(QPainter::Antialiasing);
      chartview->setParent(ui->horizontalFrame);
      chartview->resize(400,300);

      chart->setAnimationOptions(QChart::AllAnimations);
      chart->legend()->setVisible(true);
      chart->legend()->setAlignment(Qt::AlignRight);
      series->setLabelsVisible(true);
 //********************************control chkmbo****************************
      ui->tab_for->setModel(F.afficher()); // UPDATE ECRAN D'AFFICHAGEE

      ui->REFERENCE_FOURNISSEUR->setMaxLength(12); //FORMATAGE D'AFFICHAGE
      ui->NOM->setMaxLength(20);
      ui->PRENOM->setMaxLength(20);
      ui->NUMERO_TELEPHONE->setMaxLength(8);
      ui->OFFRE->setMaxLength(12);
      ui->MODE->setMaxLength(12);
      ui->CIN_EMP->setMaxLength(8);
}


MainWindow::~MainWindow()
{
    delete ui;
}





//*************************************crud CLient aziz************
void MainWindow::on_pushButtonAjouter_clicked()
{
   /* QMediaPlayer *sound =new QMediaPlayer();
    sound-> setMedia(QUrl("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\Gestion_Client\\mixkit-quick-win-video-game-notification-269.wav"));
    sound ->play();*/
      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");
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
   /*else if ((CIN<10000000)||(CIN>99999999) )
           {

        QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("Echec de l'ajout veuillez verifier le CIN(8 chiffres)"),QMessageBox::Cancel);
    }
    else if ((Numtel<10000000)||(Numtel>99999999) )
           {

        QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("Echec de l'ajout veuillez verifier le num tel(8 chiffres)"),QMessageBox::Cancel);
    }*/

    else

    {
bool test=C.ajouter();
if (test)
        {
        QMessageBox:: information(nullptr, QObject::tr("OK"),
                                           QObject::tr("Ajout Client effectué\n"
                                                       "click cancel to exit."),QMessageBox::Cancel);
      int cin=ui->cin->text().toInt();
      int pt=100;
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
    QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

    int cin=ui->cin_comboBox->currentText().toInt();

    if(cin<=0)
           {
               QMessageBox::critical(0,qApp->tr("erreur"),
                                     qApp->tr("veillez remplir le champs vide"),QMessageBox::Cancel);
           }
    else {

    bool test=Etmp.supprimer(cin);
   bool test1=ct.supprimerCarte(cin);
    if (test)
            {

        /* ui->tab_client->setModel(Etmp.rechercher(""));
          ui->tab_client->clearSelection();*/

            QMessageBox:: information(nullptr, QObject::tr("OK"),
                                               QObject::tr("Suppression d'un client avec succes\n"
                                                           "click cancel to exit."),QMessageBox::Cancel);

            if (test1)
            {
                QMessageBox:: information(nullptr, QObject::tr("OK"),
                                                   QObject::tr("Suppression du carte client client avec succes\n"
                                                               "click cancel to exit."),QMessageBox::Cancel);
            }

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
     QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");
int CIN=ui->cin_comboBox->currentText().toInt();
         QString NOM=ui->Nom_2->text();
         QString REF=ui->REF_2->text();
          QString PRENOM=ui->Prenom_2->text();
           QString ADRESSE_EMAIL=ui->AdresseEmail_2->text();
         int Numtel=ui->Numtel_2->text().toInt();
         QString SERVICE=ui->comboBox_2->currentText();
        Client C(CIN,REF,NOM,PRENOM,Numtel,ADRESSE_EMAIL,SERVICE);
bool test=C.modifier(CIN);
    /*if ((Numtel<10000000)||(Numtel>99999999) )
           {

        QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("Echec de l'ajout veuillez verifier le num tel(8 chiffres)"),QMessageBox::Cancel);
    }
else {*/
    if (test)
            {

        int pt=100;
        if(SERVICE=="VIDANGE")
        {
            pt=50;
        }
        else if(SERVICE=="NETOYAGE")
        {
           pt=30;
        }
         Carte Cr(CIN,pt);
      bool     test1=Cr.modifierCarte(CIN);


          if(test1)
          {
              QMessageBox:: information(nullptr, QObject::tr("OK"),
                                                 QObject::tr("Modification  carte Client effectué\n"
                                                             "click cancel to exit."),QMessageBox::Cancel);
          }
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
    QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

    ui->tab_client->setModel(Etmp.afficher());
     QSqlQueryModel * model= new QSqlQueryModel;
                      model->setQuery("SELECT CIN FROM client");
                  ui->cin_comboBox2->setModel(model);
                      ui->cin_comboBox->setModel(model);
                      ui->cin_comboBox3->setModel(model);
}


//*************************Metiers AZIZ CLient******************
void MainWindow::on_pushButtonRechercher_clicked()
{
    QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

   Client C;

          QString REF=ui->REF2->text();

          ui->tab_client->setModel(C.rechercher(REF));


}

void MainWindow::on_Button_dcroissant_clicked()
{
  QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");
  ui->tab_client->setModel(Etmp.trid());
}
void MainWindow::on_Button_croissant_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

    ui->tab_client->setModel(Etmp.tri());
}

void MainWindow::on_pushButtonClient_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButtonAvis_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pushButton_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

   ui->stackedWidget->setCurrentIndex(11);
}

void MainWindow::on_pushButton_2_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

     ui->stackedWidget->setCurrentIndex(11);
}

void MainWindow::on_pushButtonAjouteravis_clicked()
{

    QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");


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
    QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

    QMessageBox msg;
          QItemSelectionModel *select = ui->tab_client->selectionModel();
          if (!select->hasSelection()){
               msg.setText("Please select something");

               msg.setIcon(msg.Critical);
               msg.exec();
               return;
          }
    int tabeq=ui->tab_client->currentIndex().row();//selectionner dons le tab client ligne
           QVariant idd=ui->tab_client->model()->data(ui->tab_client->model()->index(tabeq,0));//selectionne le cin exactement
           QString id= idd.toString();//convertir a une chaine
           QSqlQuery qry;//navigating and retrieving data from SQL queries which are executed on a QSqlDatabase.

           qry.prepare("select * from CLIENT where CIN=:id");//Prepares the SQL query  for execution. Returns true or false
           qry.bindValue(":id",id);//prendre valeur id et mettre dans table client
           qry.exec();//Executes a previously prepared SQL query
              QString  NOM,PRENOM,ADRESSE_Email,REF,NUMTEL,SERVICE,ide;

           while(qry.next()){//prend des variable de la base de donnes
               REF=qry.value(1).toString();
               NOM=qry.value(2).toString();
               PRENOM=qry.value(3).toString();
               ADRESSE_Email=qry.value(4).toString();
               NUMTEL=qry.value(5).toString();
               SERVICE=qry.value(6).toString();
           }
           ide=QString(id);
                  ide="CIN:"+ide+"REF:"+REF+"NOM:"+NOM+"PRENOM:"+PRENOM+"ADRESSE_Email:"+ADRESSE_Email+"Numtel:"+NUMTEL+"SERVICE:"+SERVICE;//pendre la chaine a code
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
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

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
                  ui->tableavis->setModel(at.afficher());
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
    QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

QMessageBox msg;


     QString type_avis=ui->typecomboBox_2->currentText();
      QString Avis=ui->texteavis_2->text();


      QItemSelectionModel *select = ui->tableavis->selectionModel();
     if (!select->hasSelection()){
          msg.setText("Please select something");

          msg.setIcon(msg.Critical);
          msg.exec();
          return;
     }
QString ref_avis =select->selectedRows(0).value(0).data().toString();
    if( type_avis.isEmpty() || Avis.isEmpty())
                         {
                             QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir les champs vides Pour continuez."),QMessageBox::Cancel);
                         }

    avis A( ref_avis, type_avis, Avis);
        bool test=A.modifier(ref_avis);


        if (test)
                {

                QMessageBox:: information(nullptr, QObject::tr("OK"),
                                                   QObject::tr("Modifier avis effectué\n"
                                                               "click cancel to exit."),QMessageBox::Cancel);
                //Actualiser
                                  ui->tableavis->setModel(at.afficher());


                }
            else
               { QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                      QObject::tr("Modifier avis non effectué.\n"
                                                  "click Cancel to exit."),QMessageBox::Cancel);}
}









void MainWindow::on_cin_comboBox2_activated(const QString &arg1)
{


        int MAT=ui->cin_comboBox2->currentText().toInt();

        QSqlQuery query;
        query.prepare("SELECT * FROM CLIENT WHERE CIN = :CIN");
        query.bindValue(":CIN",MAT);
        query.exec();

        while(query.next()){

            ui->REF_2->setText(query.value(1).toString());
            ui->Nom_2->setText(query.value(2).toString());
            ui->Prenom_2->setText(query.value(3).toString());
            ui->AdresseEmail_2->setText(query.value(4).toString());
             ui->Numtel_2->setText(query.value(5).toString());
             ui->comboBox_2->setCurrentText(query.value(6).toString());

    }
}


void MainWindow::on_pushButton_3_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

     ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_4_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

    ui->stackedWidget->setCurrentIndex(1);
}





void MainWindow::on_stat_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

    QSqlQueryModel * model= new QSqlQueryModel();

      model->setQuery("select * from CLIENT where SERVICE='VIDANGE' ");
      int number1=model->rowCount(); // calculer le nombre de client qui prendre VIDANGE
      model->setQuery("select * from CLIENT where SERVICE='NETOYAGE' ");
      int number2=model->rowCount();
      model->setQuery("select * from CLIENT where SERVICE='NETTOYAGE/VIDANGE' ");
      int number3=model->rowCount();
      int total=number1+number2+number3;
      QString a = QString(" VIDANGE "+QString::number((number1*100)/total,'f',2)+"%" );
      QString b = QString("NETOYAGE "+QString::number((number2*100)/total,'f',2)+"%" );
      QString c = QString("NETTOYAGE/VIDANGE "+QString::number((number3*100)/total,'f',2)+"%" );
      QPieSeries *series = new QPieSeries();
      series->append(a,number1);
      series->append(b,number2);
      series->append(c,number3);
      if (number1!= 0)
      {
          QPieSlice *slice = series->slices().at(0);
           if(number1>=number3 and number1>=number2)
           {slice->setExploded();
               slice->setPen(QPen(Qt::black,3));
                             slice->setBrush(Qt::red);
}
          slice->setLabelVisible();
          slice->setPen(QPen());
      }
      if (number2!=0)
      {
               // Add label, explode and define brush for 2nd slice
               QPieSlice *slice1 = series->slices().at(1);
                if(number2>=number3 and number2>=number1)
                {slice1->setExploded();
                    slice1->setPen(QPen(Qt::black,3));
                                  slice1->setBrush(Qt::red);
  }
               slice1->setLabelVisible();
      }
      if(number3!=0)
      {
               // Add labels to rest of slices
               QPieSlice *slice2 = series->slices().at(2);
               if(number3>=number2 and number3>=number1)
               {slice2->setExploded();
                   slice2->setPen(QPen(Qt::black,3));
                                 slice2->setBrush(Qt::red);
 }
               slice2->setLabelVisible();
      }
              // Create the chart widget
              QChart *chart = new QChart();
              // Add data to chart with title and hide legend
              chart->addSeries(series);
              chart->setTitle("Pourcentage Par SERVICE :Nombre Des CLient "+ QString::number(total));
              //chart->legend()->hide();
              // Used to display the chart
              QChartView *chartView = new QChartView(chart);
              chartView->setRenderHint(QPainter::Antialiasing);

              chartView->resize(1000,500);
              chartView->show();
}

void MainWindow::on_carte_client_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

    ui->stackedWidget->setCurrentIndex(2);
     ui->tab_carte->setModel(ct.afficherCarte());
     QItemSelectionModel *select = ui->tab_client->selectionModel();
    if (!select->hasSelection()){
        ui->stackedWidget->setCurrentIndex(2);
         ui->tab_carte->setModel(ct.afficherCarte());
    }
    else
{
        int CIN =select->selectedRows(0).value(0).data().toInt();
        ui->stackedWidget->setCurrentIndex(2);
         ui->tab_carte->setModel(ct.rechercherclient(CIN));

    }
}

void MainWindow::on_stat_avis_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");


        //![1]
            QBarSet *set0 = new QBarSet("Parfait");
            QBarSet *set1 = new QBarSet("satisfaisant");
            QBarSet *set2 = new QBarSet("Normal");
             QBarSet *set3 = new QBarSet("insatisfaisant");
             QBarSet *set4 = new QBarSet("médiocre");
            int nb0=0;
            QSqlQuery query0("select * from AVIS where TYPE_AVIS='Parfait'");// calculer le nombre de type avis=parfait
            while(query0.next())
            {
                nb0++;
            }
            int nb1=0;
            QSqlQuery query1("select * from AVIS where TYPE_AVIS='satisfaisant'");
            while(query1.next())
            {
                nb1++;
            }
            int nb2=0;
            QSqlQuery query2("select * from AVIS where TYPE_AVIS='Normal'");
            while(query2.next())
            {
                nb2++;
            }
            int nb3=0;
            QSqlQuery query3("select * from AVIS where TYPE_AVIS='insatisfaisant'");
            while(query3.next())
            {
                nb3++;
            }

            int nb4=0;
            QSqlQuery query4("select * from AVIS where TYPE_AVIS='mediocre'");
            while(query4.next())
            {
                nb4++;
            }
          *set0 << nb0 ;
          *set1 << nb1 ;
          *set2 << nb2 ;
           *set3 << nb3 ;
           *set4 << nb4 ;


        //![1]

        //![2]
            QBarSeries *series = new QBarSeries();
            series->append(set0);
            series->append(set1);
             series->append(set2);
              series->append(set3);
              series->append(set4);

        //![2]

        //![3]
            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("nombre_Avis");
            chart->setAnimationOptions(QChart::SeriesAnimations);
        //![3]

        //![4]
            QStringList categories;
            categories << "Type_Avis";

            QBarCategoryAxis *axisX = new QBarCategoryAxis();
            axisX->append(categories);
            chart->addAxis(axisX, Qt::AlignBottom);
            series->attachAxis(axisX);
       int nb=0;
       QSqlQuery query("select * from AVIS ");
       while(query.next())//Retrieves the next record in the result,
       {
           nb++;
       }

            QValueAxis *axisY = new QValueAxis();
            axisY->setRange(0,nb);
            chart->addAxis(axisY, Qt::AlignLeft);
            series->attachAxis(axisY);
        //![4]

        //![5]
            chart->legend()->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignBottom);
        //![5]

        //![6]

            // Used to display the chart
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);

            chartView->resize(1000,500);
            chartView->show();
}

void MainWindow::on_pushButtonreturn_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButtonajouter_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

     ui->stackedWidget->setCurrentIndex(3);
}




void MainWindow::on_Actualiser_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

 ui->tab_carte->setModel(ct.afficherCarte());
}

void MainWindow::on_pushButtonActualiser_3_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

    ui->tab_client->setModel(Etmp.afficher());
     QSqlQueryModel * model= new QSqlQueryModel;
                      model->setQuery("SELECT CIN FROM client");
                  ui->cin_comboBox2->setModel(model);
                      ui->cin_comboBox->setModel(model);
                      ui->cin_comboBox3->setModel(model);
}


void MainWindow::on_excel_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                       tr("Excel Files (*.xls)"));
       if (fileName.isEmpty())
           return;

       ExportExcelObject obj(fileName, "client", ui->tab_client);

       //colums to export
       obj.addField(0, "CIN", "char(50)");
       obj.addField(1, "REF", "char(50)");
       obj.addField(2, "NOM", "char(50)");
       obj.addField(3, "PRENOM", "char(50)");
       obj.addField(4, "ADRESSE", "char(50)");
       obj.addField(5, "NUMTEL", "char(50)");
       obj.addField(6, "SERVICE", "char(50)");



       int retVal = obj.export2Excel();
       if( retVal > 0)
       {
           QMessageBox::information(this, tr("Done"),
                                    QString(tr("%1 records exported!")).arg(retVal)
                                    );
       }
}
//*******************valeur ajouter
void MainWindow::on_pushButtonfichierpdf_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

    QString strStream;
       QTextStream out(&strStream);

       const int rowCount = ui->tab_client->model()->rowCount();
     const int columnCount = ui->tab_client->model()->columnCount();

       out <<  "<html>\n"
               "<head>\n"
               "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            <<  QString("<title>%1</title>\n").arg("Title")
             <<  "</head>\n"
              <<"<body bgcolor=#ffffff link=#5000A0>\n"

              //     "<align='right'> " << datefich << "</align>"
              <<"<center> <H1>Liste des clients </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";


       // headers
       out << "<thead><tr bgcolor=#f0f0f0>";
       for (int column = 0; column < columnCount; column++)
           if (!ui->tab_client->isColumnHidden(column))
               out << QString("<th>%1</th>").arg(ui->tab_client->model()->headerData(column, Qt::Horizontal).toString());
       out << "</tr></thead>\n";

       // data table
       for (int row = 0; row < rowCount; row++) {
           out << "<tr>";
           for (int column = 0; column < columnCount; column++) {
               if (!ui->tab_client->isColumnHidden(column)) {
                   QString data = ui->tab_client->model()->data(ui->tab_client->model()->index(row, column)).toString().simplified();
                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
               }
           }
           out << "</tr>\n";
       }
       out <<  "</table>\n"
               "</body>\n"
               "</html>\n";



           QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
           if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }
           QPrinter *printer=new  QPrinter(QPrinter::PrinterResolution);
           printer->setOutputFormat(QPrinter::PdfFormat);
           printer->setPaperSize(QPrinter::A4);
           printer->setOutputFileName(fileName);

           QTextDocument doc;
           doc.setHtml(strStream);
           doc.setPageSize(printer->pageRect().size()); // This is necessary if you want to hide the page number
           doc.print(printer);

           QPrinter *p=new QPrinter();
           QPrintDialog dialog(p,this);
           if(dialog.exec()== QDialog::Rejected)
           {
               return;
           }
}
void MainWindow::on_ajouter_pts_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

    QString SERVICE=ui->comboBox_3->currentText();
    if(SERVICE.isEmpty())
                         {
                             QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir les champs vides Pour continuez."),QMessageBox::Cancel);
                         }

      int cin=ui->cin_comboBox3->currentText().toInt();

int pt;
      QSqlQuery query;
      query.prepare("SELECT * FROM CARTE WHERE CIN = :CIN");
      query.bindValue(":CIN",cin);
      query.exec();

      while(query.next()){

          pt=query.value(1).toInt();}
/*
  QSqlQuery query("SELECT PTS FROM CARTE where CIN=:CIN");
query.bindValue(":CIN", cinc_string);
       while(query.next()){ // iterator via query.next() pour acceder au contenu
     pt=query.value(1).toInt();

       }*/

       if(SERVICE=="VIDANGE")
       {
           pt+=50;
       }
       else if(SERVICE=="NETOYAGE")
       {
          pt+=30;
       }
       else  if(SERVICE=="NETTOYAGE/VIDANGE")
       {pt+=100; }
       Carte Cr(cin,pt);
    bool     test1=Cr.modifierCarte(cin);

        if(test1)
        {
            QMessageBox:: information(nullptr, QObject::tr("OK"),
                                               QObject::tr("Ajout pts dans carte Client effectué\n"
                                                           "click cancel to exit."),QMessageBox::Cancel);
        }
}


void MainWindow::on_Applytheme_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

    QString item;
    item=ui->listheme->currentItem()->text();
    if(item=="Midnight Sky")
    {
        QFile file("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\Gestion_Client\\stylesheets\\Takezo.qss");
        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());
        //MainWindow.setStyleSheet(styl);
        qApp->setStyleSheet(styleSheet);
    }
    if(item=="Summer Citrus")
    {
        QFile file("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\Gestion_Client\\stylesheets\\Irrorater.qss");
        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());
        //MainWindow.setStyleSheet(styl);
        qApp->setStyleSheet(styleSheet);
    }
    if(item=="Hackerman")
    {
        QFile file("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\Gestion_Client\\stylesheets\\Hookmark.qss");
        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());
        //MainWindow.setStyleSheet(styl);
        qApp->setStyleSheet(styleSheet);
    }
    if(item=="Violet")
    {
        QFile file("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\Gestion_Client\\stylesheets\\Wstartpage.qss");
        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());
        //MainWindow.setStyleSheet(styl);
        qApp->setStyleSheet(styleSheet);
    }
    if(item=="Dark")
    {
        QFile file("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\Gestion_Client\\stylesheets\\Combinear.qss");
        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());
        //MainWindow.setStyleSheet(styl);
        qApp->setStyleSheet(styleSheet);
    }
    if(item=="Aqua")
    {
        QFile file("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\Gestion_Client\\stylesheets\\Aqua.qss");
        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());
        //MainWindow.setStyleSheet(styl);
        qApp->setStyleSheet(styleSheet);
    }
    if(item=="Orange")
    {
        QFile file("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\Gestion_Client\\stylesheets\\Webmas.qss");
        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());
        //MainWindow.setStyleSheet(styl);
        qApp->setStyleSheet(styleSheet);
    }

}

void MainWindow::on_pushButtoninderx4_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

      ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_cancel_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

     this->close();
}
void MainWindow::on_Login_clicked()
{

     QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integration_test\\mixkit-quick-win-video-game-notification-269.wav");
    if((ui->loginLineEdit->text()=="aziz")&&(ui->motDePasseLineEdit->text()=="esprit"))
       {QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integration_test\\welcome.wav");
        ui->stackedWidget->setCurrentIndex(11);}
    else
   if ((ui->loginLineEdit->text()=="yassin")&&(ui->motDePasseLineEdit->text()=="esprit"))
       { QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integration_test\\welcome.wav");
       ui->stackedWidget->setCurrentIndex(6);}
    else
    if ((ui->loginLineEdit->text()=="karim")&&(ui->motDePasseLineEdit->text()=="esprit"))
    {QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integration_test\\welcome.wav");
        ui->stackedWidget->setCurrentIndex(9);}
    else
    if ((ui->loginLineEdit->text()=="nour")&&(ui->motDePasseLineEdit->text()=="esprit"))
       {QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integration_test\\welcome.wav");
        ui->stackedWidget->setCurrentIndex(7);}
    else
    if ((ui->loginLineEdit->text()=="rymel")&&(ui->motDePasseLineEdit->text()=="esprit"))
       {QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integration_test\\welcome.wav");
        ui->stackedWidget->setCurrentIndex(8);}
    else
    if ((ui->loginLineEdit->text()=="admin")&&(ui->motDePasseLineEdit->text()=="admin"))
       { QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integration_test\\welcome.wav");
        ui->stackedWidget->setCurrentIndex(0);}
    else {
        QMessageBox:: information(nullptr, QObject::tr("OK"),
                                           QObject::tr("Mot de passe ou utilisateur incorrect\n"
                                                       "click cancel to exit."),QMessageBox::Cancel);
         ui->loginLineEdit->clear();
         ui->motDePasseLineEdit->clear();
    }
}

void MainWindow::on_pushButtonClient_3_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

     ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButtonAvis_5_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

        ui->stackedWidget->setCurrentIndex(4);
}

//*************************************************************************************************************************************
//Crud yessin perso
void MainWindow::on_pb_ajouter_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

    int CIN_EMP=ui->le_id->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
   QString fonction=ui->le_fonction->text();
  int salaire=ui->le_salaire->text().toInt();
   QString date=ui->le_date->text();
   personnel P(CIN_EMP,nom,prenom,fonction,salaire,date);

   bool test=P.ajouter();
   if (test){
    ui->tab_employe->setModel(p.afficher());
               QMessageBox:: information(nullptr, QObject::tr("OK"),
                                                  QObject::tr("Ajout effectué\n"
                                                              "click cancel to exit."),QMessageBox::Cancel);}
   else
       QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                   QObject::tr("Ajout non effectué.\n"
                                               "click Cancel to exit."),QMessageBox::Cancel);

}


void MainWindow::on_pb_supprimer_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

    personnel p1; p1.setCIN_EMP(ui->le_cin_supp->text().toInt());
    bool test=p1.supprimer(p1.get_CIN_EMP());
    QMessageBox msgBox;
    if (test){
        msgBox.setText("Supprimer avec succes.");
    ui->tab_employe->setModel(p.afficher());
    }
    else
        msgBox.setText("Echec de suppression");
        msgBox.exec();
}


void MainWindow::on_pbmodifier_clicked()
{      QSound::play("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\integrattion_test\\mixkit-quick-win-video-game-notification-269.wav");

   int CIN_EMP=ui->le_id_4->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
   QString fonction=ui->le_fonction_3->text();
  int salaire=ui->le_salaire_3->text().toInt();
   QString date=ui->le_date->text();
   personnel P(CIN_EMP,nom,prenom,fonction,salaire,date);

   bool test=P.modifier(CIN_EMP);
   if (test){
    ui->tab_employe->setModel(P.afficher());
               QMessageBox:: information(nullptr, QObject::tr("OK"),
                                                  QObject::tr("Modifier effectué\n"
                                                              "click cancel to exit."),QMessageBox::Cancel);}
   else {
       QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                   QObject::tr("Modifier non effectué.\n"
                                               "click Cancel to exit."),QMessageBox::Cancel);}
}

//metier yessin perso
void MainWindow::on_pb_rechercher_clicked()
{ personnel p;

    QString nom=ui->REF2->text();

    ui->tab_employe_1->setModel(p.recherche(nom));

}

void MainWindow::on_tri_clicked()
{
    ui->tab_employe->setModel(p.tri());
}

void MainWindow::on_tri2_clicked()
{
    ui->tab_employe->setModel(p.tri2());
}







void MainWindow::on_pushButtonAvis_2_clicked()
{
     ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_pushButton_5_clicked()
{
       ui->stackedWidget->setCurrentIndex(0);
}
//************************************************************
//nour
//--------------------------------------------------------------------------------------------------------------

//AJOUTER

void MainWindow::on_pb_ajouter_2_clicked()
{
    QString  NOM=ui->NOM->text();
    QString Modele=ui->Modele->currentText();
    QString Categorie=ui->Categorie-> text();
    QString Matricule=ui->Matricule-> text();



    voiture v(NOM, Modele, Categorie, Matricule) ;

bool test=v.ajouter();

if(test)
{
    //refresh
    ui->tab_voiture->setModel(v.afficher());
    QMessageBox::information( nullptr, QObject::tr("OK"),
                QObject::tr("Ajout successful.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}
else
    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("Ajout failed.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
//--------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------

//MODIFIER


void MainWindow::on_pb_modifier_clicked()
{

     QString NOM=ui->NOM_2->text();
     QString Modele=ui->Modele_3->currentText();
    QString Categorie=ui->Categorie_2->text();
    QString Matricule=ui->Matricule_2->text();


    voiture v2(NOM,Modele, Categorie, Matricule);

    bool test=v2.modifier(Matricule);
    if (test){



                QMessageBox:: information(nullptr, QObject::tr("OK"),
                                                   QObject::tr("Modification effectué\n"
                                                               "click cancel to exit."),QMessageBox::Cancel);
    //refresh
                ui->tab_voiture->setModel(v.afficher());
    }


    else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                    QObject::tr("Modification non effectué.\n"
                                                "click Cancel to exit."),QMessageBox::Cancel);}

}





//SUPPRIMER

void MainWindow::on_pb_supprimer_2_clicked()
{
    voiture v1;
    v1.setMatricule(ui->Matricule_supp->text());
    bool test=v1.supprimer(v1.get_Matricule());
    if(test)
    {
        //refresh
       ui->tab_voiture->setModel(v.afficher());

        QMessageBox::information( nullptr, QObject::tr("supprimé"),
                    QObject::tr("deleted successfully.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    }
    else
        QMessageBox::critical(nullptr, QObject::tr("pas supprimé"),
                    QObject::tr("Delete failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



}




void MainWindow::on_pb_exit_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox :: question (this,
                           "EXIT","Do you really want to exit?",
                        QMessageBox :: Yes | QMessageBox :: No);
    if (reply == QMessageBox :: Yes)
        {QApplication ::quit();}
    else {
        qDebug() <<"No is clicked";
         }

}

void MainWindow::on_radioButton_croissant_clicked()
{



         ui->tab_voiture->setModel(v.tri());


}

void MainWindow::on_radioButton_dcroissant_clicked()
{
    ui->tab_voiture->setModel(v.trid());

}

void MainWindow::on_rechercher_button_clicked()
{
    QString rech =ui->rech_mat->text();
            ui->tab_voiture->setModel(v.rechercher(rech));





}

void MainWindow::on_statsmed_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from VOITURE where Modele='RENAULT' ");
     int number1=model->rowCount();
     model->setQuery("select * from VOITURE where Modele='BMW' ");
     int number2=model->rowCount();
     model->setQuery("select * from VOITURE where Modele='OPEL' ");
     int number3=model->rowCount(); // calculer le nombre de VOITURE DE Modele OPEL
    model->setQuery("select * from VOITURE where Modele='Citroen' ");
          int number4=model->rowCount();
          model->setQuery("select * from VOITURE where Modele='PEUGEOT' ");
          int number5=model->rowCount();
     model->setQuery("select * from VOITURE where Modele='Autre' ");
     int number6=model->rowCount();
     int total=number1+number2+number3+number4+number5+number6;
     QString a = QString("RENAULT"+QString::number((number1*100)/total,'f',2)+"%" );
     QString b = QString("BMW"+QString::number((number2*100)/total,'f',2)+"%" );
     QString c = QString("OPEL"+QString::number((number3*100)/total,'f',2)+"%" );
     QString d = QString("Citroen" +QString::number((number4*100)/total,'f',2)+"%" );

      QString e = QString("PEUGEOT" +QString::number((number5*100)/total,'f',2)+"%" );

     QString f = QString("Autre "+QString::number((number6*100)/total,'f',2)+"%" );
     QPieSeries *series = new QPieSeries();
     series->append(a,number1);
     series->append(b,number2);
     series->append(c,number3);
     series->append(d,number4);
     series->append(e,number5);
     series->append(f,number6);
     if (number1!= 0)
     {
         QPieSlice *slice = series->slices().at(0);
         slice->setLabelVisible();
         slice->setPen(QPen());
     }
     if (number2!=0)
     {
              // Add label, explode and define brush for 2nd slice
              QPieSlice *slice1 = series->slices().at(1);
              //slice1->setExploded();
              slice1->setLabelVisible();
     }
     if(number3!=0)
     {
              // Add labels to rest of slices
              QPieSlice *slice2 = series->slices().at(2);
              //slice1->setExploded();
              slice2->setLabelVisible();
     }
     if(number4!=0)
     {
              // Add labels to rest of slices
              QPieSlice *slice3 = series->slices().at(3);
              //slice1->setExploded();
              slice3->setLabelVisible();
     }
     if(number5!=0)
     {
              // Add labels to rest of slices
              QPieSlice *slice4 = series->slices().at(4);
              //slice1->setExploded();
              slice4->setLabelVisible();
     }
     if(number6!=0)
     {
              // Add labels to rest of slices
              QPieSlice *slice5 = series->slices().at(5);
              //slice1->setExploded();
              slice5->setLabelVisible();
     }
             // Create the chart widget
             QChart *chart = new QChart();
             // Add data to chart with title and hide legend
             chart->addSeries(series);
             chart->setTitle("Pourcentage par modele de voiture :Nombre Des Modele "+ QString::number(total));
             chart->legend()->hide();
             // Used to display the chart
             QChartView *chartView = new QChartView(chart);
             chartView->setRenderHint(QPainter::Antialiasing);
             chartView->resize(1000,500);
             chartView->show();

}

void MainWindow::on_btn_export_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                        tr("Excel Files (*.xls)"));
        if (fileName.isEmpty())
            return;

        ExportExcelObject obj(fileName, "mydata", ui->tab_voiture);

        //colums to export
        obj.addField(0, "MATRICULE", "char(20)");
        obj.addField(1, "ANNONCE", "char(20)");
        obj.addField(2, "DOMAINE", "char(20)");
        obj.addField(3, "EXPERIENCE", "char(20)");
        obj.addField(4, "SALAIRE", "char(20)");




        int retVal = obj.export2Excel();
        if( retVal > 0)
        {
            QMessageBox::information(this, tr("Done"),
                                     QString(tr("%1 records exported!")).arg(retVal)
                                     );
        }
}

void MainWindow::on_btn_imp_clicked()
{
    QString strStream;
                             QTextStream out(&strStream);

                             const int rowCount = ui->tab_voiture->model()->rowCount();
                             const int columnCount = ui->tab_voiture->model()->columnCount();
                             QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                             out <<"<html>\n"
                                   "<head>\n"
                                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                 << "<title>ERP - COMmANDE LIST<title>\n "
                                 << "</head>\n"
                                 "<body bgcolor=#ffffff link=#5000A0>\n"
                                 "<h1 style=\"text-align: center;\"><strong> ******LISTE DES  licence commerciale ******"+TT+" </strong></h1>"
                                 "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                                   "</br> </br>";
                             // headers
                             out << "<thead><tr bgcolor=#d6e5ff>";
                             for (int column = 0; column < columnCount; column++)
                                 if (!ui->tab_voiture->isColumnHidden(column))
                                     out << QString("<th>%1</th>").arg(ui->tab_voiture->model()->headerData(column, Qt::Horizontal).toString());
                             out << "</tr></thead>\n";

                             // data table
                             for (int row = 0; row < rowCount; row++) {
                                 out << "<tr>";
                                 for (int column = 0; column < columnCount; column++) {
                                     if (!ui->tab_voiture->isColumnHidden(column)) {
                                         QString data =ui->tab_voiture->model()->data(ui->tab_voiture->model()->index(row, column)).toString().simplified();
                                         out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                     }
                                 }
                                 out << "</tr>\n";
                             }
                             out <<  "</table>\n"
                                 "</body>\n"
                                 "</html>\n";

                             QTextDocument *document = new QTextDocument();
                             document->setHtml(strStream);

                             QPrinter printer;

                             QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                             if (dialog->exec() == QDialog::Accepted) {
                                 document->print(&printer);
                             }

                             delete document;


}












void MainWindow::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_6_clicked()
{
     ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_pushbutton_finance_clicked()
{
  ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_pushButton_14_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
//*********************************************************************FINANCE_rymel**********************************************************
void MainWindow::on_baj_clicked()
{
    int prix=ui->ps->text().toInt();
    int id_client=ui->idc->text().toInt();
    QString type_paiment=ui->tp->text();
    Finance F ( prix ,id_client,type_paiment );
 bool   test=F.AjouterFacture();
    f.stat(series);
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



void MainWindow::on_pb_supprimer2_clicked()
{
    Finance f1 ; f1.setid_client(ui->le_id_sup->text().toInt());
   bool test=f1.SupprimerFacture(f1.getid_client());
   QMessageBox msg;
   if (test)
      { msg.setText("suppression avec succées");
       f.stat(series);}
       else msg.setText("echec de suppression");
   msg.exec();

}
void MainWindow::on_pushButton_13_clicked()
{

    f.promotion(ui->lineEditPr->text().toInt(),ui->lineEditPourcentage->text().toFloat());
    QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Promotion a ete fait.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_11_clicked()
{
    QString strStream;
                       QTextStream out(&strStream);

                        const int rowCount = ui->tab_facture->model()->rowCount();
                        const int columnCount = ui->tab_facture->model()->columnCount();
                       out <<  "<html>\n"
                       "<head>\n"
                                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                        <<  QString("<title>%1</title>\n").arg("strTitle")
                                        <<  "</head>\n"
                                        "<body bgcolor=#ffffff link=#5000A0>\n"

                                       //     "<align='right'> " << datefich << "</align>"
                                        "<center> <H1>Liste des factures</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                    // headers
                                    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                    out<<"<cellspacing=10 cellpadding=3>";
                                    for (int column = 0; column < columnCount; column++)
                                        if (!ui->tab_facture->isColumnHidden(column))
                                            out << QString("<th>%1</th>").arg(ui->tab_facture->model()->headerData(column, Qt::Horizontal).toString());
                                    out << "</tr></thead>\n";

                                    // data table
                                    for (int row = 0; row < rowCount; row++) {
                                        out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                        for (int column = 0; column < columnCount; column++) {
                                            if (!ui->tab_facture->isColumnHidden(column)) {
                                                QString data = ui->tab_facture->model()->data(ui->tab_facture->model()->index(row, column)).toString().simplified();
                                                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                            }
                                        }
                                        out << "</tr>\n";
                                    }
                                    out <<  "</table> </center>\n"
                                        "</body>\n"
                                        "</html>\n";

                              QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                                if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                               QPrinter printer (QPrinter::PrinterResolution);
                                printer.setOutputFormat(QPrinter::PdfFormat);
                               printer.setPaperSize(QPrinter::A4);
                              printer.setOutputFileName(fileName);

                               QTextDocument doc;
                                doc.setHtml(strStream);
                                doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                                doc.print(&printer);
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->tab_facture->setModel(f.trier_type());
}

void MainWindow::on_pushButton_12_clicked()
{
       ui->tab_facture->setModel(f.chercher_type(ui->comboBox->currentText(),ui->rech->text()));
}


void MainWindow::on_statperso_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * from PERSONNEL where SALAIRE < 1000 ");
        float salaire=model->rowCount();
        model->setQuery("select * from PERSONNEL where SALAIRE  between 1000 and 2000 ");
        float salaire1=model->rowCount();
        model->setQuery("select * from PERSONNEL where SALAIRE>2000 ");
        float salaire2=model->rowCount();
        float total=salaire+salaire1+salaire2;
        QString a = QString("moins de 1000 DT  "+QString::number((salaire*100)/total,'f',2)+"%" );
        QString b = QString("entre 1000 et 2000 DT "+QString::number((salaire1*100)/total,'f',2)+"%" );
        QString c = QString("+2000 DT "+QString::number((salaire2*100)/total,'f',2)+"%" );
        QPieSeries *series = new QPieSeries();
        series->append(a,salaire);
        series->append(b,salaire1);
        series->append(c,salaire2);
        if (salaire!= 0)
        {
            QPieSlice *slice = series->slices().at(0);
            slice->setLabelVisible();
            slice->setPen(QPen());
        }
        if ( salaire1!=0)
        {
                 // Add label, explode and define brush for 2nd slice
                 QPieSlice *slice1 = series->slices().at(1);
                 //slice1->setExploded();
                 slice1->setLabelVisible();
        }
        if(salaire2!=0)
        {
                 // Add labels to rest of slices
                 QPieSlice *slice2 = series->slices().at(2);
                 //slice1->setExploded();
                 slice2->setLabelVisible();
        }
                // Create the chart widget
                QChart *chart = new QChart();
                // Add data to chart with title and hide legend
                chart->addSeries(series);
                chart->setTitle("Pourcentage Par SALAIRE :Nombre Des EMPLACEMENT "+ QString::number(total));
                chart->legend()->hide();
                // Used to display the chart
                QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);
                chartView->resize(1000,500);
                chartView->show();
}
void MainWindow::on_radioButton_clicked()
{ QMessageBox:: information(nullptr, QObject::tr("OK"),
                            QObject::tr("l'employe qui est responsable des CLIENT est present\n"
                                        "click cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_radioButton_2_clicked()
{QMessageBox:: information(nullptr, QObject::tr("OK"),
                           QObject::tr("l'employe qui est responsable des FINANCE est present\n"
                                       "click cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_radioButton_3_clicked()
{
    QMessageBox:: information(nullptr, QObject::tr("OK"),
                                       QObject::tr("l'employe qui est responsable des FOURNISSEUR est present\n"
                                                   "click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_radioButton_4_clicked()
{
    QMessageBox:: information(nullptr, QObject::tr("OK"),
                                       QObject::tr("l'employe qui est responsable des VOITURE est present\n"
                                                   "click cancel to exit."),QMessageBox::Cancel);
}








void MainWindow::on_exportperso_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                       tr("Excel Files (*.xls)"));
       if (fileName.isEmpty())
           return;

       ExportExcelObject obj(fileName, "PERSONNEL", ui->tab_employe);

       //colums to export
       obj.addField(0, "CIN", "char(50)");
       obj.addField(1, "NOM", "char(50)");
       obj.addField(2, "PRENOM", "char(50)");
       obj.addField(3, "FONCTION", "char(50)");
       obj.addField(4, "SALAIRE", "char(50)");
       obj.addField(5, "DATEN", "char(50)");



       int retVal = obj.export2Excel();
       if( retVal > 0)
       {
           QMessageBox::information(this, tr("Done"),
                                    QString(tr("%1 records exported!")).arg(retVal)
                                    );
       }
}
//********************************************Karim Fournisseur*******************************************

void MainWindow::on_return_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushbutton_fournisseur_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);

}

void MainWindow::on_pushButtonAjouter_2_clicked()
{

    QString  REFERENCE_FOURNISSEUR=ui->REFERENCE_FOURNISSEUR->text();
    QString  NOM=ui->NOM->text();
    QString  PRENOM=ui->PRENOM->text();
    QString  NUMERO_TELEPHONE=ui->NUMERO_TELEPHONE->text();
    QString  OFFRE=ui->OFFRE->text();
    QString  MODE_PAIMENT=ui->MODE->text();
    QString  CIN_EMP=ui->CIN_EMP->text();



    FOURNISSEUR f(REFERENCE_FOURNISSEUR ,NOM ,PRENOM ,NUMERO_TELEPHONE ,OFFRE ,MODE_PAIMENT ,CIN_EMP);
bool test=f.ajouter();
if (test)
        { //Actualiser
     ui->tab_for->setModel(Etmp.afficher());

     notif m("FOURNISSEUR","fournisseur ajouter avec succees");

              m.afficher();
        }
    else
   { notif m("FOURNISSEUR","fournisseur non ajouter");

             m.afficher();}
}
void MainWindow::on_supp_clicked()
{
    FOURNISSEUR f1;
   // f1.setREFERENCE_FOURNISSEUR(ui->code_supp->text());
     //bool test=Etmp.supprimer(f1.get_REFERENCE_FOURNISSEUR());

    QString code_for=ui->code_supp->text();
    bool test=F.supprimer(code_for);
        if (test)
                {
            //actualiser
             ui->tab_for->setModel(Etmp.afficher());
             notif m("FOURNISSEUR","SUPPRIMER");

                      m.afficher();

                }
            else
        {
            ui->tab_for->setModel(Etmp.afficher());
            notif m("FOURNISSEUR","SUPPRIMER");

                     m.afficher();
}
}

void MainWindow::on_Mod_2_clicked()
{
    QString  REFERENCE_FOURNISSEUR=ui->REFERENCE_FOURNISSEUR->text();
    QString NOM=ui->NOM->text();
    QString PRENOM=ui->PRENOM->text();
    QString NUMERO_TELEPHONE=ui->NUMERO_TELEPHONE->text();
    QString OFFRE=ui->OFFRE->text();
    QString MODE_PAIMENT=ui->MODE->text();
    QString CIN_EMP=ui->CIN_EMP->text();

          FOURNISSEUR f(REFERENCE_FOURNISSEUR ,NOM ,PRENOM ,NUMERO_TELEPHONE ,OFFRE ,MODE_PAIMENT ,CIN_EMP);
          bool test=f.modifier(REFERENCE_FOURNISSEUR ,NOM ,PRENOM ,NUMERO_TELEPHONE ,OFFRE ,MODE_PAIMENT ,CIN_EMP);
          if (test)
                  { //Actualiser
               ui->tab_for->setModel(Etmp.afficher());
                  QMessageBox:: information(nullptr, QObject::tr("OK"),
                                                     QObject::tr("modification effectué\n"
                                                                 "click cancel to exit."),QMessageBox::Cancel);
                  }
              else
                  QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                        QObject::tr("modification non effectué.\n"
                                                    "click Cancel to exit."),QMessageBox::Cancel);
 }

/*
void MainWindow::on_rechercher_button_clicked()
{
    QString rech =ui->code_supp->text();
        ui->tab_for->setModel(Etmp.rechercher(rech));
}

*/

/*void MainWindow::on_envoyer_clicked()
{
    // This is a first demo application of the SmtpClient for Qt project

        // First we need to create an SmtpClient object
        // We will use the Gmail's smtp server (smtp.gmail.com, port 465, ssl)

        SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

        // We need to set the username (your email address) and the password
        // for smtp authentification.

        smtp.setUser("karimchecambou123@gmail.com");
        smtp.setPassword("livealifeuwillremember.");

        // Now we create a MimeMessage object. This will be the email.

        MimeMessage message;
        QString mal =ui->mail->text();
        QString sub =ui->subject->text();
        QString com =ui->commande->toPlainText();
        message.setSender(new EmailAddress("karimchecambou123@gmail.com", "chkampawlow"));
        message.addRecipient(new EmailAddress(mal, "karim checambou"));
        message.setSubject(sub);

        // Now add some text to the email.
        // First we create a MimeText object.

        MimeText text;

        text.setText(com);

        // Now add it to the mail

        message.addPart(&text);

        // Now we can send the mail

        smtp.connectToHost();
        smtp.login();
        if(smtp.sendMail(message))
        {
            QMessageBox::information(this,"ok","message envoyer");
        }
        else
        {
            QMessageBox::critical(this,"Error","message non envoyer");
        }
        smtp.quit();
}*/



void MainWindow::on_trierc_currentTextChanged(const QString &arg1)
{
    FOURNISSEUR c;
            ui->tab_for->setModel(c.trier(arg1));
}


void MainWindow::on_pushButton_15_clicked()
{
        FOURNISSEUR c;
    QString rech =ui->code_supp->text();
           ui->tab_for->setModel(c.rechercher(rech));
}



void MainWindow::on_pb_exit_3_clicked()
{
 ui->stackedWidget->setCurrentIndex(10);
}




void MainWindow::on_theme_clicked()
{
  ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_pb_exit_4_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}
