#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include "Tag.h"
#include <list>

class NoteManager
{
    list<Note*>Ln;
    public:
        NoteManager(){};
         ~NoteManager();
list <Note*>::iterator rechercher(int);
void ajouter(const Note &);
void ajouter(const Tag &);
//Afficher la liste des notes ou tag
void afficher();
void afficher(string);
void supprimer(int);
};

#endif // NOTEMANAGER_H
