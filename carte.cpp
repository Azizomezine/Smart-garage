#include "carte.h"
#include "client.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
Carte::Carte()
{
    cinc=0;
    pts=0;


}

Carte::Carte(int cinc,int pts)
{
    this->cinc=cinc;
    this->pts=pts;


}

int  Carte::getcinc(){return cinc;};
int Carte::getpts(){return pts;};



void Carte::setcinc(int cinc){this->cinc=cinc;};
void Carte::setpts(int pts){this->pts=pts;};


bool Carte::ajouterCarte()
{
    QSqlQuery query;
    QString cinc_string= QString::number(cinc);
    QString pts_string= QString::number(pts);

          query.prepare("INSERT INTO carte (CIN,PTS) "
                        "VALUES (:CIN, :PTS)");
          query.bindValue(0, cinc_string);
          query.bindValue(1, pts_string);


          return query.exec();
}

bool Carte::supprimerCarte(int cinc)
{
    QSqlQuery query;

          query.prepare("DELETE FROM CARTE WHERE CIN=:CIN");
          query.bindValue(":CIN", cinc);
          return query.exec();

}

QSqlQueryModel* Carte::afficherCarte()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM carte");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Pts"));
    return model;
}

bool Carte::modifierCarte(int cinc)
{
    QString cinc_string=QString::number(cinc);
    QString pts_string=QString::number(pts);
    QSqlQuery query;
    query.prepare("UPDATE carte SET CIN=:CIN, pts=:pts WHERE CIN=:CIN");
    query.bindValue(":CIN", cinc_string);
    query.bindValue(":pts", pts_string);


    return query.exec();
}
QSqlQueryModel * Carte::rechercherclient(int cinc)
{
    QSqlQueryModel * model= new QSqlQueryModel();
      QString cinc_string=QString::number(cinc);
    model->setQuery("select * from carte where CIN like '%"+cinc_string+"%' ");
        return model;
}

