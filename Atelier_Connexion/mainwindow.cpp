#include "mainwindow.h"
#include <QMessageBox>
#include "ui_mainwindow.h"
#include"voiture.h"
#include <QDebug>


#include <QSqlTableModel>

#include <QSqlQueryModel>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>


#include<iostream>
#include"voiture.h"
#include<QMessageBox>
#include<QTextStream>
#include<QIntValidator>
#include<QFile>
#include<QTextStream>
#include<QPixmap>
#include <QPrinter>
#include <QPrintDialog>
#include"exportexcel.h"





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tab_voiture->setModel(v.afficher());
    ui->rech_mat->setMaxLength(30);

}


MainWindow::~MainWindow()
{
    delete ui;

}

//--------------------------------------------------------------------------------------------------------------

//AJOUTER

void MainWindow::on_pb_ajouter_clicked()
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

     QString NOM=ui->NOM->text();
     QString Modele=ui->Modele->currentText();
    QString Categorie=ui->Categorie->text();
    QString Matricule=ui->Matricule->text();


    voiture v2;

    bool test=v2.modifier(NOM,Modele,Categorie,Matricule);
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

void MainWindow::on_pb_supprimer_clicked()
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

        exportExcel obj(fileName, "mydata", ui->tab_voiture);

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
