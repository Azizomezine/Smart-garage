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
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include "exportexcelobject.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPropertyAnimation>
#include <QFileDialog>//provides a dialog that allow users to select files or directories
#include <QtSerialPort/QSerialPort>
QT_CHARTS_USE_NAMESPACE
using namespace QtCharts;
using namespace qrcodegen;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("");
    QFile file("C:\\Users\\azizo\\Desktop\\esprit\\2eme\\projet c++\\Gestion_Client\\stylesheets\\Irrorater.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
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
}


MainWindow::~MainWindow()
{
    delete ui;
}





//*************************************crud************
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
    ui->tab_client->setModel(Etmp.afficher());
     QSqlQueryModel * model= new QSqlQueryModel;
                      model->setQuery("SELECT CIN FROM client");
                  ui->cin_comboBox2->setModel(model);
                      ui->cin_comboBox->setModel(model);
                      ui->cin_comboBox3->setModel(model);
}


//*************************Metiers******************
void MainWindow::on_pushButtonRechercher_clicked()
{

   Client C;

          QString REF=ui->REF2->text();

          ui->tab_client->setModel(C.rechercher(REF));


}

void MainWindow::on_Button_dcroissant_clicked()
{
  ui->tab_client->setModel(Etmp.trid());
}
void MainWindow::on_Button_croissant_clicked()
{
    ui->tab_client->setModel(Etmp.tri());
}

void MainWindow::on_pushButtonClient_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButtonAvis_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
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
{
     ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}





void MainWindow::on_stat_clicked()
{
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
{
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
{

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
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButtonajouter_clicked()
{
     ui->stackedWidget->setCurrentIndex(3);
}




void MainWindow::on_Actualiser_clicked()
{
 ui->tab_carte->setModel(ct.afficherCarte());
}

void MainWindow::on_pushButtonActualiser_3_clicked()
{
    ui->tab_client->setModel(Etmp.afficher());
     QSqlQueryModel * model= new QSqlQueryModel;
                      model->setQuery("SELECT CIN FROM client");
                  ui->cin_comboBox2->setModel(model);
                      ui->cin_comboBox->setModel(model);
                      ui->cin_comboBox3->setModel(model);
}


void MainWindow::on_excel_clicked()
{
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
{
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
{
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
{
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
}

void MainWindow::on_pushButtoninderx4_clicked()
{
      ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_cancel_clicked()
{
     this->close();
}
