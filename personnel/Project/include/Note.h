#ifndef NOTE_H
#define NOTE_H

#include<string>
#include<iostream>

using namespace std;

class Note
{
    public:
        Note();
       Note(int,string,string,string);
       modifier(string );
     virtual   ~Note();
       virtual void afficher();
        int get_id() const {return id;}
        string get_obj(){return obj;}
        string get_descr(){return descr;}
        string  get_date(){return date;}
    private:
        int id;
        string obj,descr,date;
        //set_objet(string ch}{objet=ch};

};

#endif // NOTE_H
