#include "cd.h"

CD::CD()
{

}

CD::CD(unsigned int _id, QString _name, QString _author, rat _rating,
       QString _producer, unsigned int _year, QString _time):DataNode(_id,_name,_author,_rating)
{
    producer = _producer;
    year = _year;
    time = _time;
}
