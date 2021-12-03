#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "personnel.h"
#include <QIntValidator>
#include <QMessageBox>

#include <QSqlQueryModel>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator( new QIntValidator(0,99999999,this));
    ui->tab_employe->setModel(p.afficher());


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
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
{
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
{
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




void MainWindow::on_present_clicked()
{


        QMessageBox:: information(nullptr, QObject::tr("OK"),
                                           QObject::tr("l'employe qui est responsable des CLIENT est present\n"
                                                       "click cancel to exit."),QMessageBox::Cancel);



}

void MainWindow::on_present_2_clicked()
{
    QMessageBox:: information(nullptr, QObject::tr("OK"),
                                       QObject::tr("l'employe qui est responsable des FINANCE est present\n"
                                                   "click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_present_3_clicked()
{
    QMessageBox:: information(nullptr, QObject::tr("OK"),
                                       QObject::tr("l'employe qui est responsable des FOURNISSEUR est present\n"
                                                   "click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_present_4_clicked()
{
    QMessageBox:: information(nullptr, QObject::tr("OK"),
                                       QObject::tr("l'employe qui est responsable des VOITURE est present\n"
                                                   "click cancel to exit."),QMessageBox::Cancel);
}



void MainWindow::on_pushButton_clicked()
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



