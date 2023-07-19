#ifndef DIALOGADDPIC_H
#define DIALOGADDPIC_H

#include <QDialog>
#include "picture.h"

namespace Ui {
class Dialogaddpic;
}

class Dialogaddpic : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogaddpic(QWidget *parent = nullptr);
    ~Dialogaddpic();
    picture new_pic();
    void set(QString _id,QString _name,QString _author,rat _rating
             ,QString _Nationality ,Size _size);
private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialogaddpic *ui;
};

#endif // DIALOGADDPIC_H
