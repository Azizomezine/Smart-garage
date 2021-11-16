#ifndef CARTE_H
#define CARTE_H
#include <QString>
#include <QSqlQueryModel>

class Carte
{
public:
    Carte();
    Carte(int,int);

    int  getcinc();
    int getpts();


    void setcinc(int);
    void setpts(int);


    bool ajouterCarte();
    QSqlQueryModel* afficherCarte();
    bool supprimerCarte(int);
    bool modifierCarte(int);
    QSqlQueryModel* trierCarte();
    QSqlQueryModel* rechercherCarte(int);
    QSqlQueryModel* statistique();
private:
    int cinc,pts;
    QString expire;
};

#endif // CARTE_H
