#ifndef DIALOGADDCD_H
#define DIALOGADDCD_H

#include <QDialog>
#include "cd.h"

namespace Ui {
class DialogaddCD;
}

class DialogaddCD : public QDialog
{
    Q_OBJECT

public:
    explicit DialogaddCD(QWidget *parent = nullptr);
    ~DialogaddCD();
    CD new_cd();
    void set(QString _id, QString _name, QString _author, rat _rating,
            QString _producer ,QString _year ,QString _time);
private slots:
    void on_pushButton_clicked();

private:
    Ui::DialogaddCD *ui;
};

#endif // DIALOGADDCD_H
