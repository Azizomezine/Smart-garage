#include "Tag.h"

Tag::Tag()
{
    //ctor
}


Tag::Tag(int in,string ob,string de,string da,string no):Note(in,ob,de,da)
{
    nom = no;
}

void Tag::afficher()
{
    Note::afficher();
    cout<<nom<<endl;
}

Tag::~Tag()
{
    //dtor
}
