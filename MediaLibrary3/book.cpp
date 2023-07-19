#include "book.h"

Book::Book()
{

}

Book::Book(unsigned int _id, QString _name, QString _author, rat _rating,
           QString _publisher, unsigned int _ISBN, int _num_pages):DataNode(_id,_name,_author,_rating)
{
    publisher = _publisher;
    ISBN = _ISBN;
    num_pages = _num_pages;
}
