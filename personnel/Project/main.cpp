#include <iostream>
using namespace std;
#include "Tag.h"
#include "Note.h"
#include "NoteManager.h"

int main()
{ NoteManager M;

Note N(1,"obj1","Des1","2020");
Note N1(2,"object","Des2","2022");
Tag T(2,"obj2","Des2","2021","Ahmed");
Tag T1(2,"obj2","Des2","2021","Ahmed");

M.ajouter(N);
M.ajouter(T);
M.ajouter(T1);
M.ajouter(N1);
M.supprimer(2);
M.afficher();
    return 0;
}
