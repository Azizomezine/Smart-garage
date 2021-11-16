#include "personnel.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

personnel::personnel()
{
CIN_EMP=0;
NOM="";
PRENOM="";
FONCTION="";
SALAIRE=0;
DATE="";
}

personnel::personnel(int CIN_EMP,QString NOM,QString PRENOM,QString FONCTION,int SALAIRE,QString DATE)
{ //
this->CIN_EMP=CIN_EMP;
this->NOM=NOM;
this->PRENOM=PRENOM;
this->FONCTION=FONCTION;
this->SALAIRE=SALAIRE;
this->DATE=DATE;
}
//getters
int personnel::get_CIN_EMP(){return  CIN_EMP;}
QString personnel::get_NOM(){return NOM;}
QString personnel::get_PRENOM(){return PRENOM;}
QString personnel::get_FONCTION(){return FONCTION;}
int personnel::get_SALAIRE(){return  SALAIRE ;}
QString personnel::get_DATE(){return  DATE;}
//setters
void  personnel::setCIN_EMP( int CIN_EMP){this->CIN_EMP=CIN_EMP;}
void  personnel::setNOM(QString NOM){this->NOM=NOM;}
void  personnel::setPRENOM(QString PRENOM){this->PRENOM=PRENOM;}
void  personnel::setFONCTION(QString FONCTION){this->FONCTION=FONCTION;}
void  personnel::setSALAIRE( int SALAIRE){this->SALAIRE=SALAIRE;}
void  personnel::setDATE( QString DATE){this->DATE=DATE;}


bool personnel::ajouter()
{

QSqlQuery query;
QString CIN_EMPstring=QString::number(CIN_EMP);
QString SALAIREstring=QString::number(SALAIRE);
query.prepare("INSERT INTO PERSONNEL ( CIN_EMP,NOM, PRENOM,FONCTION,  SALAIRE ,DATEN) "
                           "VALUES (:CIN_EMP, :NOM,:PRENOM,:FONCTION,:SALAIRE,:DATEN)");
query.bindValue(":CIN_EMP", CIN_EMPstring );
query.bindValue(":NOM", NOM);
query.bindValue(":PRENOM", PRENOM);
query.bindValue(":FONCTION", FONCTION);
query.bindValue(":SALAIRE", SALAIREstring);
query.bindValue(":DATEN", DATE);
 return query.exec();
}

QSqlQueryModel* personnel::afficher(){
    QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM personnel");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN_EMP"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("fonction"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("salaire"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("date"));
    return model;
}

bool personnel::supprimer(int CIN_EMP ){
QSqlQuery query;
QString res= QString::number(CIN_EMP);
query.prepare("Delete from personnel where CIN_EMP = :CIN_EMP ");
query.bindValue(0, CIN_EMP);
return    query.exec();
}

bool personnel::modifier(int CIN_EMP)
{
    QSqlQuery query;
    QString CIN_EMPstring=QString::number(CIN_EMP);
    QString SALAIRE_string=QString::number(SALAIRE);
    query.prepare("UPDATE PERSONNEL SET CIN_EMP=CIN_EMP,NOM=:NOM,PRENOM=:PRENOM,FONCTION=:FONCTION,SALAIRE=:SALAIRE,DATEN=:DATEN WHERE CIN_EMP=:CIN_EMP");
    query.bindValue(":CIN_EMP", CIN_EMPstring );
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":FONCTION", FONCTION);
    query.bindValue(":SALAIRE", SALAIRE_string);
    query.bindValue(":DATEN", DATE);
 return    query.exec();
}



QSqlQueryModel * personnel::recherche(QString rech)
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * from PERSONNEL where NOM LIKE '%"+rech+"%'  ");

    return model;
}

QSqlQueryModel * personnel::tri()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM PERSONNEL ORDER BY NOM");
        return model;
}

QSqlQueryModel * personnel::tri2()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM PERSONNEL ORDER BY SALAIRE");
        return model;
}
