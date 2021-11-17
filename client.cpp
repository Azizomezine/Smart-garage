#include "client.h"
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
Client::Client()
{
REF="";
NOM="";
PRENOM="";
CIN=0;
ADRESSE_Email="";
SERVICE="";
Numtel=0;
}
Client::Client(int CIN,QString REF,QString NOM,QString PRENOM,int Numtel,QString ADRESSE_EMAIL,QString SERVICE )
{
  this->REF=REF;
  this->NOM=NOM;
  this->PRENOM=PRENOM;
    this->CIN=CIN;
    this->ADRESSE_Email=ADRESSE_EMAIL;
  this->Numtel=Numtel;
    this->SERVICE=SERVICE;
}
QString Client::get_NOM(){return  NOM;}
QString Client::get_PRENOM(){return PRENOM;}
QString Client::get_ADRESSE_Email(){return ADRESSE_Email;}
QString Client::get_REF(){return  REF;}
QString Client::get_Service(){return SERVICE;}
int Client::get_CIN(){return  CIN;}
int Client::get_Numtel(){return  Numtel;}
void  Client::setREF(QString REF ){this->REF=REF;}
void  Client::setNOM(QString NOM){this->NOM=NOM;}
void  Client::setPRENOM(QString PRENOM){this->PRENOM=PRENOM;}
void  Client::setCIN( int CIN){this->CIN=CIN;}
void Client::setADRESSE_Email(QString ADRESSE_Email) {this->ADRESSE_Email=ADRESSE_Email;}
void Client::setService(QString SERVICE) {this->SERVICE=SERVICE;}
void  Client::setNumtel(int Numetel) {this->Numtel=Numetel;}
bool Client::ajouter()
{
QSqlQuery query;
QString CINstring=QString::number(CIN);
QString Numtel_string=QString::number(Numtel);
query.prepare("INSERT INTO CLIENT (CIN,REF, NOM,PRENOM,ADRESSE_Email,Numtel,SERVICE) "
                    "VALUES (:CIN, :REF, :NOM,:PRENOM,:ADRESSE_Email,:Numtel,:SERVICE)");
query.bindValue(":REF", REF);
query.bindValue(":NOM", NOM);
query.bindValue(":PRENOM", PRENOM);
query.bindValue(":CIN", CINstring );
query.bindValue(":ADRESSE_Email", ADRESSE_Email);
query.bindValue(":SERVICE", SERVICE);
query.bindValue(":Numtel",Numtel_string);
  return query.exec();

}
bool Client::supprimer(int CIN )
{
QSqlQuery query;
QString res= QString::number(CIN);
query.prepare("Delete from CLIENT where CIN = :CIN ");
query.bindValue(":CIN", res);
return    query.exec();
}
QSqlQueryModel * Client::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from CLIENT");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("REF"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE_Email"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Numtel"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("SERVICE"));

    return model;
}
bool Client::modifier(int CIN)
{
    QSqlQuery query;
    QString CINstring=QString::number(CIN);
    QString Numtel_string=QString::number(Numtel);
    query.prepare("UPDATE CLIENT SET CIN=CIN,REF=:REF,NOM=:NOM,PRENOM=:PRENOM,ADRESSE_Email=:ADRESSE_Email,Numtel=:Numtel,SERVICE=:SERVICE WHERE CIN=:CIN");
    query.bindValue(":REF", REF);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":CIN", CINstring );
    query.bindValue(":ADRESSE_Email", ADRESSE_Email);
    query.bindValue(":SERVICE", SERVICE);
    query.bindValue(":Numtel",Numtel_string);
    return    query.exec();

}
QSqlQueryModel * Client::rechercher(QString rech)
{
    QSqlQueryModel * model= new QSqlQueryModel();
        QString recher="select *  from client where REF like '%"+rech+"%'or NOM like '%"+rech+"%'or PRENOM like '%"+rech+"%'";//%rechercher  au mileu %
        model->setQuery(recher);
        return model;
}
QSqlQueryModel * Client::tri()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM client ORDER BY REF");
        return model;
}
QSqlQueryModel * Client::trid(){

   /*QSqlQuery *q = new QSqlQuery();*/
   QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM client ORDER BY REF DESC");
   /*q->exec();
   model->setQuery(*q);*/

   return model;
}
