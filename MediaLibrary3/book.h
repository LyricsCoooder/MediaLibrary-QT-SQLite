#ifndef BOOK_H
#define BOOK_H

#include "datanode.h"

class Book:public DataNode
{
private:
    QString publisher;
    unsigned int ISBN;
    int num_pages;

public:
    Book();
    Book(unsigned int _id, QString _name, QString _author, rat _rating
         ,QString _publisher ,unsigned int _ISBN,int _num_pages);
    QString get_publisher(){return publisher;}
    unsigned int get_ISBN(){return ISBN;}
    int get_num_pages(){return num_pages;}

};

#endif // BOOK_H
