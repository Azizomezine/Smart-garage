#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test_bd");
db.setUserName("nour");//inserer nom de l'utilisateur
db.setPassword("nour");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
