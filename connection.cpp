#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");//l'attribut db sera intialise dans la methode createconnection()
bool test=false;
db.setDatabaseName("test-bd");//inserer le nom de la source de données ODBC
db.setUserName("aziz1");//inserer nom de l'utilisateur
db.setPassword("aziz1");//inserer mot de passe de cet utilisateur

if (db.open()) test=true;

    return  test;
}
void Connection::closeConnection(){db.close();}
