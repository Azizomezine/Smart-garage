#include "client.h"

Client::Client()
{
REF="";
NOM="";
PRENOM="";
CIN=0;
ADRESSE_Email="";
Numtel=0;
}
Client::Client(int CIN,QString REF,QString NOM,QString PRENOM,int Numtel,QString ADRESSE_EMAIL )
{
  this->REF=REF;
  this->NOM=NOM;
  this->PRENOM=PRENOM;
    this->CIN=CIN;
    this->ADRESSE_Email=ADRESSE_EMAIL;
  this->Numtel=Numtel;
}
QString Client::get_NOM(){return  NOM;}
QString Client::get_PRENOM(){return PRENOM;}
QString Client::get_ADRESSE_Email(){return ADRESSE_Email;}
QString Client::get_REF(){return  REF;}
int Client::get_CIN(){return  CIN;}
int Client::get_Numtel(){return  Numtel;}
void  Client::setREF(QString REF ){this->REF=REF;}
void  Client::setNOM(QString NOM){this->NOM=NOM;}
void  Client::setPRENOM(QString PRENOM){this->PRENOM=PRENOM;}
void  Client::setCIN( int CIN){this->CIN=CIN;}
void Client::setADRESSE_Email(QString ADRESSE_Email) {this->ADRESSE_Email=ADRESSE_Email;}
void  Client::setNumtel(int Numetel) {this->Numtel=Numetel;}

bool Client::ajouter()
{
QSqlQuery query;
QString CINstring=QString::number(CIN);
QString Numtel_string=QString::number(Numtel);
query.prepare("INSERT INTO CLIENT (CIN,REF, NOM,PRENOM,ADRESSE_Email,Numtel) "
                    "VALUES (:CIN, :REF, :NOM,:PRENOM,:ADRESSE_Email,:Numtel)");
query.bindValue(":REF", REF);
query.bindValue(":NOM", NOM);
query.bindValue(":PRENOM", PRENOM);
query.bindValue(":CIN", CINstring );
query.bindValue(":ADRESSE_Email", ADRESSE_Email);
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

    return model;
}
bool Client::modifier(int CIN)
{
    QSqlQuery query;
    QString CINstring=QString::number(CIN);
    QString Numtel_string=QString::number(Numtel);
    query.prepare("UPDATE CLIENT SET CIN=CIN,REF=:REF,NOM=:NOM,PRENOM=:PRENOM,ADRESSE_Email=:ADRESSE_Email,Numtel=:Numtel WHERE CIN=:CIN");
    query.bindValue(":REF", REF);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":CIN", CINstring );
    query.bindValue(":ADRESSE_Email", ADRESSE_Email);
    query.bindValue(":Numtel",Numtel_string);
    return    query.exec();

}
QSqlQueryModel * Client::rechercher(QString search)
{
    QSqlQueryModel * model= new QSqlQueryModel();
       QString qry="select * from supplement where IDS like '%"+search+"%' or NOM like '%"+search+"%' or TYPE like '%"+search+"%' or PRIX like '%"+search+"%' ";
       qDebug()<<qry;

       model->setQuery(qry);
       return model;
}
