#ifndef PERSONNEL_H
#define PERSONNEL_H
#include <QString>
#include <QSqlQueryModel>


class personnel
{public:
    personnel();
    personnel(int ,QString ,QString ,QString ,int ,QString);
    //getters
    int get_CIN_EMP();
    QString get_NOM();
    QString get_PRENOM();
    QString get_FONCTION();
    int get_SALAIRE();
    QString get_DATE();

    //setters
    void  setCIN_EMP( int);
    void  setNOM(QString);
    void  setPRENOM(QString);
    void  setFONCTION(QString);
    void  setSALAIRE( int);
    void  setDATE( QString);


    bool ajouter();
   QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier( int);
    QSqlQueryModel * recherche(QString);
    QSqlQueryModel * tri();
     QSqlQueryModel * tri2();

     QSqlQueryModel * presentcli();

private:
    QString NOM,PRENOM,FONCTION, DATE;
    int CIN_EMP,SALAIRE;
};

#endif // PERSONNEL_H
