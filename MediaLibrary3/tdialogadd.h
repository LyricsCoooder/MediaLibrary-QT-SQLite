#ifndef TDIALOGADD_H
#define TDIALOGADD_H

#include <QDialog>
#include "book.h"

class QLabel;
class QLineEdit;
class QTimeEdit;
class QVBoxLayout;

namespace Ui {
class TDialogAdd;
}

class TDialogAdd : public QDialog
{
    Q_OBJECT

public:
    explicit TDialogAdd(QWidget *parent = nullptr);
    ~TDialogAdd();
    Book new_book();
    void set(QString _id, QString _name, QString _author, rat _rating,
             QString _publisher, QString _ISBN, QString _num_pages);
private slots:

    void on_pushButton_apply_clicked();

private:
    Ui::TDialogAdd *ui;
};

#endif // TDIALOGADD_H
