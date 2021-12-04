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
   QSqlQueryModel * rechercherclient(int cinc);

private:
    int cinc,pts;

};

#endif // CARTE_H
