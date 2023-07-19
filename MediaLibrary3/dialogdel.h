#ifndef DIALOGDEL_H
#define DIALOGDEL_H

#include <QDialog>

namespace Ui {
class DialogDel;
}

class DialogDel : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDel(QWidget *parent = nullptr);
    ~DialogDel();

private:
    Ui::DialogDel *ui;
};

#endif // DIALOGDEL_H
