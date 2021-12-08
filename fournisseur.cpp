#include "fournisseur.h"

FOURNISSEUR::FOURNISSEUR()
{
REFERENCE_FOURNISSEUR="";
NOM="";
PRENOM="";
NUMERO_TELEPHONE="";
OFFRE="";
MODE_PAIMENT="";
CIN_EMP="";
}

FOURNISSEUR::FOURNISSEUR(QString REFERENCE_FOURNISSEUR ,QString NOM ,QString PRENOM ,QString NUMERO_TELEPHONE ,QString OFFRE ,QString MODE_PAIMENT ,QString CIN_EMP)
{
    this->REFERENCE_FOURNISSEUR=REFERENCE_FOURNISSEUR;
    this->NOM=NOM;
    this->PRENOM=PRENOM;
    this->NUMERO_TELEPHONE=NUMERO_TELEPHONE;
    this->OFFRE=OFFRE;
    this->MODE_PAIMENT=MODE_PAIMENT;
    this->CIN_EMP=CIN_EMP;
}
QString FOURNISSEUR::get_REFERENCE_FOURNISSEUR(){return  REFERENCE_FOURNISSEUR;}
QString FOURNISSEUR::get_NOM(){return  NOM;}
QString FOURNISSEUR::get_PRENOM(){return PRENOM;}
QString FOURNISSEUR::get_NUMERO_TELEPHONE(){return NUMERO_TELEPHONE;}
QString FOURNISSEUR::get_OFFRE(){return OFFRE;}
QString FOURNISSEUR::get_MODE_PAIMENT(){return MODE_PAIMENT;}
QString FOURNISSEUR::get_CIN_EMP(){return  CIN_EMP;}


void  FOURNISSEUR::setREFERENCE_FOURNISSEUR(QString REFERENCE_FOURNISSEUR) {this->REFERENCE_FOURNISSEUR=REFERENCE_FOURNISSEUR;}
void  FOURNISSEUR::setNOM(QString NOM){this->NOM=NOM;}
void  FOURNISSEUR::setPRENOM(QString PRENOM){this->PRENOM=PRENOM;}
void  FOURNISSEUR::setNUMERO_TELEPHONE(QString NUMERO_TELEPHONE){this->NUMERO_TELEPHONE=NUMERO_TELEPHONE;}
void  FOURNISSEUR::setOFFRE(QString OFFRE) {this->OFFRE=OFFRE;}
void  FOURNISSEUR::setMODE_PAIMENT(QString MODE_PAIMENT) {this->MODE_PAIMENT=MODE_PAIMENT;}
void  FOURNISSEUR::setCIN_EMP(QString CIN_EMP) {this->CIN_EMP=CIN_EMP;}

bool FOURNISSEUR::ajouter()
{
QSqlQuery query;

query.prepare("INSERT INTO FOURNISSEUR (REFERENCE_FOURNISSEUR ,NOM ,PRENOM ,NUMERO_TELEPHONE ,OFFRE ,MODE_PAIMENT ,CIN_EMP) "
                    "VALUES (:REFERENCE_FOURNISSEUR ,:NOM ,:PRENOM ,:NUMERO_TELEPHONE ,:OFFRE ,:MODE_PAIMENT ,:CIN_EMP)");
query.bindValue(":REFERENCE_FOURNISSEUR", REFERENCE_FOURNISSEUR);
query.bindValue(":NOM",NOM);
query.bindValue(":PRENOM", PRENOM);
query.bindValue(":NUMERO_TELEPHONE", NUMERO_TELEPHONE);
query.bindValue(":OFFRE", OFFRE);
query.bindValue(":MODE_PAIMENT",MODE_PAIMENT);
query.bindValue(":CIN_EMP",CIN_EMP );

  return query.exec();
}

QSqlQueryModel * FOURNISSEUR::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from FOURNISSEUR");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE_FOURNISSEUR"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUMERO_TELEPHONE"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("OFFRE "));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("MODE_PAIMENT "));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("CIN_EMP "));

    return model;
}

bool FOURNISSEUR::supprimer(QString REFERENCE_FOURNISSEUR)
{
QSqlQuery query;
query.prepare("Delete from FOURNISSEUR where REFERENCE_FOURNISSEUR = :REFERENCE_FOURNISSEUR ");
query.bindValue(0,REFERENCE_FOURNISSEUR);
//query.bindValue(":code_supp",REFERENCE_FOURNISSEUR);
return    query.exec();
}

bool FOURNISSEUR::modifier(QString REFERENCE_FOURNISSEUR ,QString NOM ,QString PRENOM ,QString NUMERO_TELEPHONE ,QString OFFRE ,QString MODE_PAIMENT ,QString CIN_EMP)
{
    QSqlQuery query;
        query.prepare("UPDATE FOURNISSEUR SET NOM=:NOM , PRENOM=:PRENOM,NUMERO_TELEPHONE=:NUMERO_TELEPHONE,OFFRE=:OFFRE,MODE_PAIMENT=:MODE_PAIMENT,CIN_EMP=:CIN_EMP WHERE REFERENCE_FOURNISSEUR=:REFERENCE_FOURNISSEUR");
        query.bindValue(":REFERENCE_FOURNISSEUR", REFERENCE_FOURNISSEUR);
        query.bindValue(" :NOM",NOM);
        query.bindValue(":PRENOM", PRENOM);
        query.bindValue(":NUMERO_TELEPHONE", NUMERO_TELEPHONE);
        query.bindValue(":OFFRE", OFFRE );
        query.bindValue(":MODE_PAIMENT", MODE_PAIMENT );
        query.bindValue(":CIN_EMP", CIN_EMP );
        return    query.exec();
}

QSqlQueryModel* FOURNISSEUR :: trier(QString curent)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    if(curent=="ordre alphabetique croissant"){
   model->setQuery("SELECT * FROM FOURNISSEUR ORDER BY NOM,PRENOM ASC ");}
    if(curent=="ordre alphabetiques decroissant"){
   model->setQuery("SELECT * FROM FOURNISSEUR ORDER BY NOM,PRENOM DESC ");}
    if(curent=="offre croissant"){
   model->setQuery("SELECT * FROM FOURNISSEUR ORDER BY OFFRE ASC ");}
    if(curent=="offre decroissant"){
   model->setQuery("SELECT * FROM FOURNISSEUR ORDER BY OFFRE DESC ");}
    if(curent=="reference croissant"){
   model->setQuery("SELECT * FROM FOURNISSEUR ORDER BY REFERENCE_FOURNISSEUR ASC ");}
    if(curent=="reference decroissant"){
   model->setQuery("SELECT * FROM FOURNISSEUR ORDER BY REFERENCE_FOURNISSEUR DESC ");}


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE_FOURNISSSEUR"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUMERO_TELEPHONE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("OFFRE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("MODE_PAYMANT"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("CIN_EMP"));
     return model;
}
QSqlQueryModel *FOURNISSEUR::rechercher(QString rech)
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * from FOURNISSEUR where REFERENCE_FOURNISSEUR LIKE '"+rech+"%'");
    return model;
}
