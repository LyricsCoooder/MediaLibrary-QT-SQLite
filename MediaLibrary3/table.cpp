#include "table.h"


Table::Table()
{

}

Table::Table(QTableWidget *t)
{
    aim_table = t;
}

void Table::set_table_header(QStringList list)
{
    aim_table->setColumnCount(list.count());
    for (int i = 0; i < aim_table->columnCount(); ++i)
    {
        QTableWidgetItem *header_item = new QTableWidgetItem(list.at(i));
        QFont font = header_item->font();
        font.setBold(true);
        font.setPointSize(11);
        header_item->setFont(font);
        aim_table->setHorizontalHeaderItem(i,header_item);
    }
}

void Table::set_table(std::vector<Book> books)
{
    aim_table->clearContents();
    int row_count = 0;
    aim_table->setRowCount(row_count);

    for(unsigned long long i = 0;i < books.size();i++)
    {
        row_count++;
        aim_table->setRowCount(row_count);

        QTableWidgetItem *item = new QTableWidgetItem(QString::number(books[i].get_id()), ctID);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        aim_table->setItem(i,colID,item);


        item = new QTableWidgetItem(books[i].get_name(),ctName);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        aim_table->setItem(i,colName,item);

        item = new QTableWidgetItem(books[i].get_author(),ctAuthor);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        aim_table->setItem(i,colAuthor,item);

        if(rat(books[i].get_rating()) == 0)
        {
            item = new QTableWidgetItem("Unrated",ctRating);
            item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            aim_table->setItem(i,colRating,item);
        }
        if(rat(books[i].get_rating()) == 1)
        {
            item = new QTableWidgetItem("General",ctRating);
            item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            aim_table->setItem(i,colRating,item);
        }
        if(rat(books[i].get_rating()) == 2)
        {
            item = new QTableWidgetItem("Adult",ctRating);
            item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            aim_table->setItem(i,colRating,item);
        }
        if(rat(books[i].get_rating()) == 3)
        {
            item = new QTableWidgetItem("Child",ctRating);
            item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            aim_table->setItem(i,colRating,item);
        }

        item = new QTableWidgetItem(books[i].get_publisher(),ctPublisher);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        aim_table->setItem(i,colPublisher,item);

        item = new QTableWidgetItem(QString::number(books[i].get_ISBN()),ctISBN);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        aim_table->setItem(i,colISBN,item);

        item = new QTableWidgetItem(QString::number(books[i].get_num_pages()),ctPages);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        aim_table->setItem(i,colPages,item);
    }
}

void Table::set_table(std::vector<CD> CDs)
{
    aim_table->clearContents();
    int row_count = 0;
    aim_table->setRowCount(row_count);
    for(unsigned long long i = 0;i < CDs.size();i++)
    {
        row_count++;
        aim_table->setRowCount(row_count);
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(CDs[i].get_id()), ctID);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        aim_table->setItem(i,colID,item);

        item = new QTableWidgetItem(CDs[i].get_name(),ctName);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        aim_table->setItem(i,colName,item);

        item = new QTableWidgetItem(CDs[i].get_author(),ctAuthor);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        aim_table->setItem(i,colAuthor,item);

        if(rat(CDs[i].get_rating()) == 0)
        {
            item = new QTableWidgetItem("Unrated",ctRating);
            item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            aim_table->setItem(i,colRating,item);
        }
        if(rat(CDs[i].get_rating()) == 1)
        {
            item = new QTableWidgetItem("General",ctRating);
            item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            aim_table->setItem(i,colRating,item);
        }
        if(rat(CDs[i].get_rating()) == 2)
        {
            item = new QTableWidgetItem("Adult",ctRating);
            item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            aim_table->setItem(i,colRating,item);
        }
        if(rat(CDs[i].get_rating()) == 3)
        {
            item = new QTableWidgetItem("Child",ctRating);
            item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            aim_table->setItem(i,colRating,item);
        }

        item = new QTableWidgetItem(CDs[i].get_producer(),1004);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        aim_table->setItem(i,4,item);

        item = new QTableWidgetItem(QString::number(CDs[i].get_year()),1005);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        aim_table->setItem(i,5,item);

        item = new QTableWidgetItem(CDs[i].get_time(),1006);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        aim_table->setItem(i,6,item);

    }
}

void Table::set_table(std::vector<picture> pics)
{
    aim_table->clearContents();
    int row_count = 0;
    aim_table->setRowCount(row_count);

    for(unsigned long long i = 0;i < pics.size();i++)
    {
        row_count++;
        aim_table->setRowCount(row_count);
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(pics[i].get_id()), ctID);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        aim_table->setItem(i,colID,item);

        item = new QTableWidgetItem(pics[i].get_name(),ctName);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        aim_table->setItem(i,colName,item);

        item = new QTableWidgetItem(pics[i].get_author(),ctAuthor);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        aim_table->setItem(i,colAuthor,item);

        if(rat(pics[i].get_rating()) == 0)
        {
            item = new QTableWidgetItem("Unrated",ctRating);
            item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            aim_table->setItem(i,colRating,item);
        }
        if(rat(pics[i].get_rating()) == 1)
        {
            item = new QTableWidgetItem("General",ctRating);
            item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            aim_table->setItem(i,colRating,item);
        }
        if(rat(pics[i].get_rating()) == 2)
        {
            item = new QTableWidgetItem("Adult",ctRating);
            item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            aim_table->setItem(i,colRating,item);
        }
        if(rat(pics[i].get_rating()) == 3)
        {
            item = new QTableWidgetItem("Child",ctRating);
            item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            aim_table->setItem(i,colRating,item);
        }

        item = new QTableWidgetItem(pics[i].get_nationality(),1004);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        aim_table->setItem(i,4,item);

        item = new QTableWidgetItem(QString::number(pics[i].get_size().x) + "cm x" +  QString::number(pics[i].get_size().y)+ "cm"
                                    ,1005);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        aim_table->setItem(i,5,item);
    }

}

