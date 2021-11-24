#ifndef PERSONNEL_H
#define PERSONNEL_H
#include <QString>
#include <QSqlQueryModel>
#include<QSqlQuery>


#include <QtCharts/QBarSet>





class voiture
{public:
    voiture();
    voiture(QString ,QString ,QString ,QString);
    //getters

    QString get_NOM();
    QString get_Modele();
    QString get_Categorie();
    QString get_Matricule();
    //setters

    void  setNOM(QString);
    void  setModele(QString);
    void  setCategorie(QString);
    void  setMatricule( QString);

    //Crud
    bool ajouter();
    QSqlQueryModel * afficher();
    bool modifier( QString ,QString ,QString ,QString);
    QSqlQueryModel * rechercher(QString);
    bool supprimer(QString);
    QSqlQueryModel *tri();
     QSqlQueryModel * trid();


    //metier

private:
    QString NOM,Modele,Categorie,Matricule;

};

#endif // PERSONNEL_H
