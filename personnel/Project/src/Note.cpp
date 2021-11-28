#include "Note.h"

Note::Note()
{
    //ctor
}

Note::Note(int in,string ob,string de,string da)
{
    id=in;
    obj=ob;
    descr=de;
    date = da;
}

void Note::afficher()
{
    cout<<id<<" "<<obj<<" "<<descr<<" "<<date<<endl;
}

Note::~Note()
{
    //dtor
}

