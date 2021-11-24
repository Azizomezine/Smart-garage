#include "voiture.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

#include<QDebug>
#include<QSqlQuery>
#include<QTableView>
#include<QModelIndex>

voiture::voiture()
{

NOM="";
Modele="";
Categorie="";
Matricule="";
}

voiture::voiture(QString NOM,QString Modele,QString Categorie,QString Matricule)
{

this->NOM=NOM;
this->Modele=Modele;
this->Categorie=Categorie;
this->Matricule=Matricule;
}

//getters

QString voiture::get_NOM(){return NOM;}
QString voiture::get_Modele(){return Modele;}
QString voiture::get_Categorie(){return Categorie;}
QString voiture::get_Matricule(){return  Matricule;}

//setters

void  voiture::setNOM(QString NOM){this->NOM=NOM;}
void  voiture::setModele(QString Modele){this->Modele=Modele;}
void  voiture::setCategorie(QString Categorie){this->Categorie=Categorie;}
void  voiture::setMatricule( QString Matricule){this->Matricule=Matricule;}


bool voiture::ajouter()
{

QSqlQuery query;

query.prepare("INSERT INTO voiture (NOM, Modele,Categorie,  Matricule) "
                           "VALUES (:NOM,:Modele,:Categorie,:Matricule)");

query.bindValue(":NOM", NOM);
query.bindValue(":Modele", Modele);
query.bindValue(":Categorie", Categorie);
query.bindValue(":Matricule", Matricule);
 return query.exec();

}

bool voiture::supprimer(QString Matricule )
{
QSqlQuery query;
query.prepare("Delete from voiture where Matricule = :Matricule ");
query.bindValue(0, Matricule);
return    query.exec();
}

QSqlQueryModel* voiture::afficher(){
    QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM voiture");
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM de client"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Modele de voiture"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Categorie de voiture"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Matricule de voiture"));
    return model;
}


bool voiture::modifier(QString NOM,QString Modele,QString Categorie,QString Matricule)
{
    QSqlQuery query;

    query.prepare("UPDATE voiture SET NOM=:NOM, Modele=:Modele,Categorie=:Categorie,Matricule=:Matricule WHERE Matricule=:Matricule");

    query.bindValue(":NOM", NOM);
    query.bindValue(":Modele", Modele);
    query.bindValue(":Categorie", Categorie);
    query.bindValue(":Matricule", Matricule);

 return    query.exec();
}




QSqlQueryModel *voiture::tri(){

       QSqlQuery *q = new QSqlQuery();
       QSqlQueryModel *model = new QSqlQueryModel();
       q->prepare("SELECT * FROM VOITURE ORDER BY NOM ");
       q->exec();
       model->setQuery(*q);

       return model;
    }

    QSqlQueryModel *voiture::trid(){

       QSqlQuery *q = new QSqlQuery();
       QSqlQueryModel *model = new QSqlQueryModel();
       q->prepare("SELECT * FROM VOITURE ORDER BY NOM DESC");
       q->exec();
       model->setQuery(*q);

       return model;
    }


    QSqlQueryModel *voiture::rechercher(QString rech)
        {
            QSqlQueryModel * model= new QSqlQueryModel();

                model->setQuery("select * from VOITURE where Matricule LIKE '"+rech+"%'");
            return model;
        }















