#ifndef PICTURE_H
#define PICTURE_H

#include "datanode.h"

struct Size
{
    unsigned int x;
    unsigned int y;
};

class picture:public DataNode
{
private:
    QString Nationality;
    Size size;
public:
    picture();
    picture(unsigned int _id,QString _name,QString _author,rat _rating
            ,QString _Nationality ,Size _size);
    QString get_nationality(){return Nationality;}
    Size get_size(){return size;}
};

#endif // PICTURE_H
