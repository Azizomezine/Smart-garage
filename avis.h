#ifndef AVIS_H
#define AVIS_H
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>

class avis
{
public:
    avis();
    avis(QString,QString,QString );
    QString  get_REF();
    QString get_TYPE();
   void  setREF(QString);
    void  setTYPE(QString);
    QString get_Avis();
   void  setAvis(QString);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier(QString);
QSqlQueryModel * rechercher(QString );
 QSqlQueryModel * tri();
private:
    QString Avis,ref_avis,type_avis;
};

#endif // AVIS_H
