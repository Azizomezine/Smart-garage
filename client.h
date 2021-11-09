#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
class Client
{public:
    Client();
    Client(int ,QString ,QString ,QString ,int ,QString,QString );
    QString  get_REF();
    QString get_NOM();
    QString get_PRENOM();
    int get_CIN();
    int get_Numtel();
     QString get_ADRESSE_Email();
void  setADRESSE_Email( QString);
   void  setREF(QString);
    void  setNOM(QString);
    void  setPRENOM(QString);
    void  setCIN( int);
     QString get_Service();
     void setService(QString);
      void  setNumtel(int);


    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int);
QSqlQueryModel * rechercher(QString );
 QSqlQueryModel * tri();
private:
    QString NOM,PRENOM,ADRESSE_Email,SERVICE,REF;
    int CIN,Numtel;
};

#endif // CLIENT_H
