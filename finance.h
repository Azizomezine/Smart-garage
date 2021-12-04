#ifndef FINANCE_H
#define FINANCE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QObject>
#include <QMessageBox>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
class Finance
{
private :
    int id_client , prix;
    QString type_paiment ;


public:
    Finance();
    Finance(int,int ,QString);
    void stat(QPieSeries *);
    void promotion(int,float);
    QString gettype_paiment(){return type_paiment;}
    int getid_client(){return id_client;}
    int getprix(){return prix;}
     void setid_client(int id_client){this->id_client=id_client;}
     void setprix(int prix){this->prix=prix;}
     void settype_paiment(QString type_paiment){this->type_paiment=type_paiment;}
    bool AjouterFacture();
    QSqlQueryModel* AfficherFacture();
    bool SupprimerFacture(int);
    QSqlQueryModel * chercher_id(QString);
        QSqlQueryModel * chercher_type(QString,QString);
        QSqlQueryModel * trier_type();

};

 #endif// FINANCE_H
