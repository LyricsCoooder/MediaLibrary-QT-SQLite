#include "datanode.h"

DataNode::DataNode()
{

}

DataNode::DataNode(unsigned int _id, QString _name, QString _author, rat _rating)
{
    ID = _id;
    name = _name;
    author =_author;
    rating = _rating;
}
