#include "picture.h"

picture::picture()
{

}

picture::picture(unsigned int _id, QString _name, QString _author, rat _rating,
                 QString _Nationality, Size _size):DataNode(_id,_name,_author,_rating)
{
    Nationality = _Nationality;
    size = _size;
}
