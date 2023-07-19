#ifndef DATANODE_H
#define DATANODE_H

#include <QMainWindow>

enum rat{
    unrated,general, adult, child
};

class DataNode
{
private:
    unsigned int ID;
    QString name;
    QString author;
    rat rating;
public:
    DataNode();

    DataNode(unsigned int _id,QString _name,QString _author,rat _rating);
    unsigned int get_id(){return ID;}
    QString get_name(){return name;}
    QString get_author(){return author;}
    rat get_rating(){return rating;}
};

#endif // DATANODE_H
