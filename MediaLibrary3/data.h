#ifndef DATA_H
#define DATA_H

#include <vector>
#include "cd.h"
#include "book.h"
#include "picture.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class DataBase
{
private:
    QSqlDatabase database;

public:
    DataBase();
    void do_sql(QString sql);
    void add_CD(CD cd);
    void add_Book(Book book);
    void add_Picture(picture pic);

    std::vector<Book> get_all_book();
    std::vector<CD> get_all_CD();
    std::vector<picture> get_all_picture();

    std::vector<Book> get_all_book(int id);
    std::vector<CD> get_all_CD(int id);
    std::vector<picture> get_all_picture(int id);

    std::vector<Book> get_book_by_name(QString name);
    std::vector<CD> get_CD_by_name(QString name);
    std::vector<picture> get_picture_by_name(QString name);

    std::vector<Book> get_book_by_author(QString author);
    std::vector<CD> get_all_CD_by_author(QString author);
    std::vector<picture> get_all_picture_by_author(QString author);

    void delCD(int id);
    void delpic(int id);
    void delbook(int id);

    ~DataBase();
};

#endif // DATA_H
