#ifndef TABLE_H
#define TABLE_H

#include <QTableWidget>
#include <vector>
#include "book.h"
#include "cd.h"
#include "picture.h"

class Table
{
private:
    enum CellType{ctID=1000,ctName,ctAuthor,ctRating,ctPublisher,ctISBN,ctPages};
    enum FieldColNum{colID=0,colName,colAuthor,colRating,colPublisher,colISBN,colPages};

    QTableWidget *aim_table;
public:
    Table();
    Table(QTableWidget *t);
    void set_table_header(QStringList list);
    void set_table(std::vector<Book> books);
    void set_table(std::vector<CD> CDs);
    void set_table(std::vector<picture> pics);
};

#endif // TABLE_H
