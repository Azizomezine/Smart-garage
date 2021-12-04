#include <QSqlQueryModel>
#include "finance.h"


Finance::Finance()
{
 type_paiment="";id_client=0;prix=0;
}
Finance::Finance(int id_client,int prix , QString type_paiment)
{
    this->id_client=id_client;
    this->prix=prix;
    this->type_paiment=type_paiment;
}
void Finance::stat(QPieSeries *series)
{
    QSqlQuery q("select type_paiment,count(*) from gs_facture group by type_paiment");


        while(q.next())
        {series->append(q.value(0).toString()+": "+q.value(1).toString(),q.value(1).toInt());}


}
bool Finance::AjouterFacture()
{
QSqlQuery query;
QString res= QString::number(prix);
QString res1= QString::number(id_client);
query.prepare("INSERT INTO gs_facture (id_client,PRIX,type_paiment)" "VALUES (:idc, :ps,:tp)");
query.bindValue(":idc",res1);
query.bindValue(":ps",res);
query.bindValue(":tp",type_paiment);
return query.exec();
}
void Finance::promotion(int num,float prcnt)
{
    QString prc=QString::number(prcnt);
    QSqlQuery q;
    q.prepare("update gs_facture set prix=prix/"+prc+" where ID_CLIENT=:idc");
    q.bindValue(":idc",num);
    q.exec();
}
QSqlQueryModel* Finance:: AfficherFacture()
 {
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM gs_facture");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("id client"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("prix de service"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("type de paiment"));
         return model;
 }
bool Finance::SupprimerFacture(int Num)
 {
     QSqlQuery query;
     query.prepare("DELETE FROM gs_facture WHERE ID_CLIENT=:idc");
     query.bindValue(":idc",Num);
     return query.exec();
 }
QSqlQueryModel * Finance::chercher_id(QString N )
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM gs_facture WHERE code ='"+N+"' ;");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_client"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("prix"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("type_paiment"));

    return model ;
}
QSqlQueryModel * Finance::chercher_type(QString critere,QString N)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM gs_facture WHERE "+critere+" like '"+N+"%' ;");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_client"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("type_paiment"));
    return model ;
}
QSqlQueryModel * Finance::trier_type()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * FROM gs_facture ORDER BY type_paiement asc");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_client"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("type_paiment"));
    return model;
}
