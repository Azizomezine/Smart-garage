#include "NoteManager.h"
list<Note*>:: iterator NoteManager::rechercher(int c)
{
list<Note*>::iterator it=Ln.begin();
while(it!=Ln.end())
{
if((*it)->get_id()==c)
return it;
it++;
}
return Ln.end();
}


void NoteManager::ajouter(const Note &N)
{
 try {
 if(rechercher(N.get_id())!=Ln.end())
 {
     throw string("Note existe deja!");}
     else
     {
         Note * ptr=new Note(N);
         Ln.push_back(ptr);
     }

 }
 catch (const string & ch)
     {
         cerr<<ch<<endl;
     }
 }

void NoteManager::ajouter(const Tag &t)
{
 try {
 if(rechercher(t.get_id())!=Ln.end())
 {
     throw string("Tag existe deja!");}
     else
     {
         Note * ptr=new Tag(t);
         Ln.push_back(ptr);
     }

 }
 catch (const string & ch)
     {
         cerr<<ch<<endl;
     }
 }
void NoteManager::afficher()
{
   list<Note*>::iterator it;
    for(it=Ln.begin();it!=Ln.end();it++)
    {
        (*it)->afficher();
    }
}
void NoteManager::afficher(string d)
{
    list<Note*>::iterator it;
    for(it=Ln.begin();it!=Ln.end();it++)
    {
        if((*it)->get_date()==d)
        (*it)->afficher();
    }
}
void  NoteManager::supprimer(int id)
{
     list<Note*>::iterator it=rechercher(id);

     delete(*it);
     Ln.erase(it);//supprimer la case de la liste

}

NoteManager::~NoteManager()
{
    list<Note*>::iterator it;
    for(it=LN.begin();it=LN.end();i++)
    {
        delete (*it);
    }
}
void NoteManager::modifier(string ch)
{
    list<Note*>::iterator it =LN.begin();
    (*it) -> set_objet(ch);

}

