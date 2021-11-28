#ifndef TAG_H
#define TAG_H
#include"Note.h"

class Tag: public Note
{
    public:
        Tag();
        Tag(int,string,string,string,string);
        void afficher();
        ~Tag();
    private:
        string nom;
};

#endif // TAG_H
