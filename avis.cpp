#include "avis.h"

avis::avis()
{
    ref_avis="";
    type_avis="";
    Avis="";
}
avis::avis(QString ref_avis,QString type_avis,QString Avis)
{
  this->ref_avis=ref_avis;
  this->type_avis=type_avis;
    this->Avis=Avis;
}
QString avis::get_REF(){return   ref_avis;}
QString avis::get_TYPE(){return type_avis;}
QString avis::get_Avis(){return  Avis;}
void avis::setREF(QString ref_avis ){this->ref_avis=ref_avis;}
void  avis::setTYPE(QString type_avis){this->type_avis=type_avis;}
void avis::setAvis(QString Avis) {this->Avis=Avis;}
 bool avis::ajouter()
 {
     QSqlQuery query;


     query.prepare("INSERT INTO AVIS (REF_AVIS,TYPE_AVIS, AVIS) "
                         "VALUES (:REF_AVIS, :TYPE_AVIS, :AVIS)");
     query.bindValue(":REF_AVIS", ref_avis);
     query.bindValue(":TYPE_AVIS",type_avis);
  query.bindValue(":AVIS",Avis);
       return query.exec();
 }
 QSqlQueryModel *avis::afficher()
 {QSqlQueryModel * model= new QSqlQueryModel();

 model->setQuery("select * from AVIS");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("REF_AVIS"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE_AVIS"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("AVIS "));


     return model;
 }

bool avis::supprimer(QString ref_avis )
 {
 QSqlQuery query;
 query.prepare("Delete from AVIS where REF_AVIS = :ref_avis ");
 query.bindValue(":ref_avis", ref_avis);
 return    query.exec();
 }
bool avis::modifier(QString ref_avis)
{
    QSqlQuery query;
    query.prepare("UPDATE AVIS SET REF_AVIS=REF_AVIS,TYPE_AVIS=:TYPE_AVIS,AVIS=:AVIS WHERE REF_AVIS=:REF_AVIS");
    query.bindValue(":REF_AVIS", ref_avis);
    query.bindValue(":TYPE_AVIS",type_avis);
 query.bindValue(":AVIS",Avis);
    return    query.exec();

}
QSqlQueryModel * avis::rechercher(QString rech)
{
    QSqlQueryModel * model= new QSqlQueryModel();
        QString recher="select *  from AVIS where REF_AVIS like '%"+rech+"%'or TYPE_AVIS like '%"+rech+"%'or AVIS like '%"+rech+"%'";
        model->setQuery(recher);
        return model;
}
