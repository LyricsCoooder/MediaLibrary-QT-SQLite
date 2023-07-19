#ifndef CD_H
#define CD_H

#include "datanode.h"
#include "QTime"

class CD:public DataNode
{
private:
    QString producer;
    unsigned int year;
    QString time;
public:
    CD();
    CD(unsigned int _id,QString _name,QString _author,rat _rating
       ,QString _producer ,unsigned int _year ,QString _time);
    QString get_producer(){return producer;}
    unsigned int get_year(){return year;}
    QString get_time(){return time;}
};

#endif // CD_H
