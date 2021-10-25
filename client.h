#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQuery>

#include <QSqlQueryModel>
class Client
{public:
    Client();
    Client(int ,QString ,QString ,QString ,int ,QString );
    QString  get_REF();
    QString get_NOM();
    QString get_PRENOM();
    int get_CIN();
    int get_Numtel();
     QString get_ADRESSE_Email();
   void  setREF(QString);
    void  setNOM(QString);
    void  setPRENOM(QString);
    void  setCIN( int);
      void setADRESSE_Email(QString);
      void  setNumtel(int);


    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int);


private:
    QString NOM,PRENOM,ADRESSE_Email,REF;
    int CIN,Numtel;
};

#endif // CLIENT_H
