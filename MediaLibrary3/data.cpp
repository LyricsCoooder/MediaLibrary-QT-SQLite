#include "data.h"

DataBase::DataBase()
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("MediaLibrary.db");
    }
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        do_sql("CREATE TABLE Book (\
               id INT PRIMARY KEY NOT NULL,\
               name TEXT NOT NULL,\
               author TEXT NOT NULL,\
               rating INT NOT NULL,\
               publisher TEXT NOT NULL,\
               ISBN INT NOT NULL,\
               num_pages INT NOT NULL)");

        do_sql("CREATE TABLE CD (\
                id INT PRIMARY KEY NOT NULL,\
                name TEXT NOT NULL,\
                author TEXT NOT NULL,\
                rating INT NOT NULL,\
                producer TEXT NOT NULL,\
                year INT NOT NULL,\
                time TEXT NOT NULL)");

        do_sql("CREATE TABLE Picture (\
               id INT PRIMARY KEY NOT NULL,\
               name TEXT NOT NULL,\
               author TEXT NOT NULL,\
               rating INT NOT NULL,\
               nationality TEXT NOT NULL,\
               size_x INT NOT NULL,\
               size_y INT NOT NULL)");
    }
}

void DataBase::do_sql(QString sql)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare(sql);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to create table. " << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
}

void DataBase::add_CD(CD cd)
{
    QSqlQuery sqlQuery;

    sqlQuery.prepare("INSERT INTO CD VALUES(:id,:name,:author,:rating,:producer,:year,:time)");
    sqlQuery.bindValue(":id", cd.get_id());
    sqlQuery.bindValue(":name", cd.get_name());
    sqlQuery.bindValue(":author", cd.get_author());
    sqlQuery.bindValue(":rating", cd.get_rating());
    sqlQuery.bindValue(":producer", cd.get_producer());
    sqlQuery.bindValue(":year", cd.get_year());
    sqlQuery.bindValue(":time", cd.get_time());

    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to insert data. " << sqlQuery.lastError();
    }
    else
    {
        // do something
    }
}

void DataBase::add_Book(Book book)
{
    QSqlQuery sqlQuery;

    sqlQuery.prepare("INSERT INTO Book VALUES(:id,:name,:author,:rating,:publisher,:ISBN,:num_pages)");
    sqlQuery.bindValue(":id", book.get_id());
    sqlQuery.bindValue(":name", book.get_name());
    sqlQuery.bindValue(":author", book.get_author());
    sqlQuery.bindValue(":rating", book.get_rating());
    sqlQuery.bindValue(":publisher", book.get_publisher());
    sqlQuery.bindValue(":ISBN", book.get_ISBN());
    sqlQuery.bindValue(":num_pages", book.get_num_pages());

    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to insert data. " << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "OK";
        // do something
    }
}

void DataBase::add_Picture(picture pic)
{
    QSqlQuery sqlQuery;

    sqlQuery.prepare("INSERT INTO Picture VALUES(:id,:name,:author,:rating,:nationality,:size_x,:size_y)");
    sqlQuery.bindValue(":id", pic.get_id());
    sqlQuery.bindValue(":name", pic.get_name());
    sqlQuery.bindValue(":author", pic.get_author());
    sqlQuery.bindValue(":rating", pic.get_rating());
    sqlQuery.bindValue(":nationality", pic.get_nationality());
    sqlQuery.bindValue(":size_x", pic.get_size().x);
    sqlQuery.bindValue(":size_y", pic.get_size().y);

    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to insert data. " << sqlQuery.lastError();
    }
    else
    {
        // do something
    }
}

std::vector<Book> DataBase::get_all_book()
{
    QSqlQuery sqlQuery;
    std::vector<Book> temp_books;
    sqlQuery.exec("SELECT * FROM Book ORDER BY ID ASC");
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            auto id = sqlQuery.value(0).toInt();
            auto name = sqlQuery.value(1).toString();
            auto author = sqlQuery.value(2).toString();
            auto rating = sqlQuery.value(3).toInt();
            QString publisher = sqlQuery.value(4).toString();
            int ISBN = sqlQuery.value(5).toInt();
            int num_pages = sqlQuery.value(6).toInt();
            Book temp_book(id,name,author,rat(rating),publisher,ISBN,num_pages);
            temp_books.push_back(temp_book);
        }
    }
    return temp_books;
}

std::vector<CD> DataBase::get_all_CD()
{
    QSqlQuery sqlQuery;
    std::vector<CD> temp_CDs;
    sqlQuery.exec("SELECT * FROM CD ORDER BY ID ASC");
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            auto id = sqlQuery.value(0).toInt();
            auto name = sqlQuery.value(1).toString();
            auto author = sqlQuery.value(2).toString();
            auto rating = sqlQuery.value(3).toInt();
            auto producer = sqlQuery.value(4).toString();
            auto year = sqlQuery.value(5).toInt();
            auto time = sqlQuery.value(6).toString();
            CD temp_CD(id,name,author,rat(rating),producer,year,time);
            temp_CDs.push_back(temp_CD);
        }
    }
    return temp_CDs;
}

std::vector<picture> DataBase::get_all_picture()
{
    QSqlQuery sqlQuery;
    std::vector<picture> temp_pictures;
    sqlQuery.exec("SELECT * FROM Picture ORDER BY ID ASC");
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            auto id = sqlQuery.value(0).toInt();
            auto name = sqlQuery.value(1).toString();
            auto author = sqlQuery.value(2).toString();
            auto rating = sqlQuery.value(3).toInt();
            auto nationality = sqlQuery.value(4).toString();
            auto x = sqlQuery.value(5).toInt();
            auto y = sqlQuery.value(6).toInt();
            Size size;
            size.x = x;
            size.y = y;
            picture temp_picture(id,name,author,rat(rating),nationality,size);
            temp_pictures.push_back(temp_picture);
        }
    }
    return temp_pictures;
}

std::vector<Book> DataBase::get_all_book(int id)
{
    QSqlQuery sqlQuery;
    std::vector<Book> temp_books;
    QString SQL = "SELECT * FROM Book WHERE id GLOB '";
    sqlQuery.exec(SQL + QString::number(id) + "*' ORDER BY ID ASC");

    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            auto id = sqlQuery.value(0).toInt();
            auto name = sqlQuery.value(1).toString();
            auto author = sqlQuery.value(2).toString();
            auto rating = sqlQuery.value(3).toInt();
            QString publisher = sqlQuery.value(4).toString();
            int ISBN = sqlQuery.value(5).toInt();
            int num_pages = sqlQuery.value(6).toInt();
            Book temp_book(id,name,author,rat(rating),publisher,ISBN,num_pages);
            temp_books.push_back(temp_book);
        }
    }
    return temp_books;
}

std::vector<CD> DataBase::get_all_CD(int id)
{
    QSqlQuery sqlQuery;
    std::vector<CD> temp_CDs;

    QString SQL = "SELECT * FROM CD WHERE id GLOB '";
    sqlQuery.exec(SQL + QString::number(id) + "*' ORDER BY ID ASC");

    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            auto id = sqlQuery.value(0).toInt();
            auto name = sqlQuery.value(1).toString();
            auto author = sqlQuery.value(2).toString();
            auto rating = sqlQuery.value(3).toInt();
            auto producer = sqlQuery.value(4).toString();
            auto year = sqlQuery.value(5).toInt();
            auto time = sqlQuery.value(6).toString();
            CD temp_CD(id,name,author,rat(rating),producer,year,time);
            temp_CDs.push_back(temp_CD);
        }
    }
    return temp_CDs;
}

std::vector<picture> DataBase::get_all_picture(int id)
{
    QSqlQuery sqlQuery;
    std::vector<picture> temp_pictures;

    QString SQL = "SELECT * FROM Picture WHERE id GLOB '";
    sqlQuery.exec(SQL + QString::number(id) + "*' ORDER BY ID ASC");

    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            auto id = sqlQuery.value(0).toInt();
            auto name = sqlQuery.value(1).toString();
            auto author = sqlQuery.value(2).toString();
            auto rating = sqlQuery.value(3).toInt();
            auto nationality = sqlQuery.value(4).toString();
            auto x = sqlQuery.value(5).toInt();
            auto y = sqlQuery.value(6).toInt();
            Size size;
            size.x = x;
            size.y = y;
            picture temp_picture(id,name,author,rat(rating),nationality,size);
            temp_pictures.push_back(temp_picture);
        }
    }
    return temp_pictures;
}

std::vector<Book> DataBase::get_book_by_name(QString name)
{
    QSqlQuery sqlQuery;
    std::vector<Book> temp_books;
    QString SQL = "SELECT * FROM Book WHERE name GLOB '";
    sqlQuery.exec(SQL + name + "*' ORDER BY ID ASC");

    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            auto id = sqlQuery.value(0).toInt();
            auto name = sqlQuery.value(1).toString();
            auto author = sqlQuery.value(2).toString();
            auto rating = sqlQuery.value(3).toInt();
            QString publisher = sqlQuery.value(4).toString();
            int ISBN = sqlQuery.value(5).toInt();
            int num_pages = sqlQuery.value(6).toInt();
            Book temp_book(id,name,author,rat(rating),publisher,ISBN,num_pages);
            temp_books.push_back(temp_book);
        }
    }
    return temp_books;
}

std::vector<CD> DataBase::get_CD_by_name(QString name)
{
    QSqlQuery sqlQuery;
    std::vector<CD> temp_CDs;

    QString SQL = "SELECT * FROM CD WHERE name GLOB '";
    sqlQuery.exec(SQL + name + "*' ORDER BY ID ASC");

    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            auto id = sqlQuery.value(0).toInt();
            auto name = sqlQuery.value(1).toString();
            auto author = sqlQuery.value(2).toString();
            auto rating = sqlQuery.value(3).toInt();
            auto producer = sqlQuery.value(4).toString();
            auto year = sqlQuery.value(5).toInt();
            auto time = sqlQuery.value(6).toString();
            CD temp_CD(id,name,author,rat(rating),producer,year,time);
            temp_CDs.push_back(temp_CD);
        }
    }
    return temp_CDs;
}

std::vector<picture> DataBase::get_picture_by_name(QString name)
{
    QSqlQuery sqlQuery;
    std::vector<picture> temp_pictures;

    QString SQL = "SELECT * FROM Picture WHERE name GLOB '";
    sqlQuery.exec(SQL + name + "*' ORDER BY ID ASC");

    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            auto id = sqlQuery.value(0).toInt();
            auto name = sqlQuery.value(1).toString();
            auto author = sqlQuery.value(2).toString();
            auto rating = sqlQuery.value(3).toInt();
            auto nationality = sqlQuery.value(4).toString();
            auto x = sqlQuery.value(5).toInt();
            auto y = sqlQuery.value(6).toInt();
            Size size;
            size.x = x;
            size.y = y;
            picture temp_picture(id,name,author,rat(rating),nationality,size);
            temp_pictures.push_back(temp_picture);
        }
    }
    return temp_pictures;
}

std::vector<Book> DataBase::get_book_by_author(QString author)
{
    QSqlQuery sqlQuery;
    std::vector<Book> temp_books;
    QString SQL = "SELECT * FROM Book WHERE author GLOB '";
    sqlQuery.exec(SQL + author + "*' ORDER BY ID ASC");

    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            auto id = sqlQuery.value(0).toInt();
            auto name = sqlQuery.value(1).toString();
            auto author = sqlQuery.value(2).toString();
            auto rating = sqlQuery.value(3).toInt();
            QString publisher = sqlQuery.value(4).toString();
            int ISBN = sqlQuery.value(5).toInt();
            int num_pages = sqlQuery.value(6).toInt();
            Book temp_book(id,name,author,rat(rating),publisher,ISBN,num_pages);
            temp_books.push_back(temp_book);
        }
    }
    return temp_books;
}

std::vector<CD> DataBase::get_all_CD_by_author(QString author)
{
    QSqlQuery sqlQuery;
    std::vector<CD> temp_CDs;

    QString SQL = "SELECT * FROM CD WHERE author GLOB '";
    sqlQuery.exec(SQL + author + "*' ORDER BY ID ASC");

    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            auto id = sqlQuery.value(0).toInt();
            auto name = sqlQuery.value(1).toString();
            auto author = sqlQuery.value(2).toString();
            auto rating = sqlQuery.value(3).toInt();
            auto producer = sqlQuery.value(4).toString();
            auto year = sqlQuery.value(5).toInt();
            auto time = sqlQuery.value(6).toString();
            CD temp_CD(id,name,author,rat(rating),producer,year,time);
            temp_CDs.push_back(temp_CD);
        }
    }
    return temp_CDs;
}

std::vector<picture> DataBase::get_all_picture_by_author(QString author)
{
    QSqlQuery sqlQuery;
    std::vector<picture> temp_pictures;

    QString SQL = "SELECT * FROM Picture WHERE author GLOB '";
    sqlQuery.exec(SQL + author + "*' ORDER BY ID ASC");

    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            auto id = sqlQuery.value(0).toInt();
            auto name = sqlQuery.value(1).toString();
            auto author = sqlQuery.value(2).toString();
            auto rating = sqlQuery.value(3).toInt();
            auto nationality = sqlQuery.value(4).toString();
            auto x = sqlQuery.value(5).toInt();
            auto y = sqlQuery.value(6).toInt();
            Size size;
            size.x = x;
            size.y = y;
            picture temp_picture(id,name,author,rat(rating),nationality,size);
            temp_pictures.push_back(temp_picture);
        }
    }
    return temp_pictures;
}

void DataBase::delCD(int id)
{
    QSqlQuery sqlQuery;

    sqlQuery.exec(QString("DELETE FROM CD WHERE id = %1").arg(id));
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        qDebug()<<"deleted data success!";
    }
}

void DataBase::delpic(int id)
{
    QSqlQuery sqlQuery;
    sqlQuery.exec(QString("DELETE FROM Picture WHERE id = %1").arg(id));
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        qDebug()<<"deleted data success!";
    }
}

void DataBase::delbook(int id)
{
    QSqlQuery sqlQuery;
    sqlQuery.exec(QString("DELETE FROM Book WHERE id = %1").arg(id));
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        qDebug()<<"deleted data success!";
    }
}

DataBase::~DataBase()
{
    database.close();
}
