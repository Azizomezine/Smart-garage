#ifndef FORMATION_H
#define FORMATION_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class FOURNISSEUR
{public:
    FOURNISSEUR();
    FOURNISSEUR(QString,QString,QString,QString,QString,QString,QString);
    QString get_REFERENCE_FOURNISSEUR();
    QString get_NOM();
    QString get_PRENOM();
    QString get_NUMERO_TELEPHONE();
    QString get_OFFRE();
    QString get_MODE_PAIMENT();
    QString get_CIN_EMP();


    void  setREFERENCE_FOURNISSEUR(QString);
    void  setNOM(QString);
    void  setPRENOM(QString);
    void  setNUMERO_TELEPHONE(QString);
    void  setOFFRE(QString);
    void  setMODE_PAIMENT(QString);
    void  setCIN_EMP(QString);

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier(QString   ,QString  ,QString ,QString ,QString ,QString ,QString );
    QSqlQueryModel*  trier(QString);
    QSqlQueryModel * rechercher(QString);
    // QSqlQueryModel *tri();
    // bool modifierv2(QString);

private:
    QString REFERENCE_FOURNISSEUR ,NOM ,PRENOM ,NUMERO_TELEPHONE ,OFFRE ,MODE_PAIMENT ,CIN_EMP;
};

#endif // FORMATION_H
