#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "personnel.h"
#include <QIntValidator>
#include <QMessageBox>

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
