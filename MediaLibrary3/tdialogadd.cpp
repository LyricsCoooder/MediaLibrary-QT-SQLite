#include "tdialogadd.h"
#include "ui_tdialogadd.h"
#include "QLineEdit"
#include "QLabel"
#include "QVBoxLayout"
#include "QTimeEdit"

TDialogAdd::TDialogAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TDialogAdd)
{
    ui->setupUi(this);
}

TDialogAdd::~TDialogAdd()
{
    delete ui;
}

Book TDialogAdd::new_book()
{
    rat Rat = rat(ui->comboBox_rat->currentIndex());

    Book book(ui->lineEdit_id->text().toInt(),
              ui->lineEdit_name->text(),
              ui->lineEdit_author->text(),
              Rat,ui->lineEdit_pub->text(),
              ui->lineEdit_isbn->text().toInt(),
              ui->lineEdit_pag->text().toInt());
    return book;
}

void TDialogAdd::set(QString _id, QString _name, QString _author, rat _rating, QString _publisher, QString _ISBN, QString _num_pages)
{
    ui->lineEdit_isbn->setText(_ISBN);
    ui->lineEdit_id->setText(_id);
    ui->lineEdit_name->setText(_name);
    ui->lineEdit_author->setText(_author);
    ui->lineEdit_pag->setText(_num_pages);
    ui->lineEdit_pub->setText(_publisher);
    ui->comboBox_rat->setCurrentIndex(_rating);
    ui->pushButton_apply->setText("Update");
}


void TDialogAdd::on_pushButton_apply_clicked()
{
    accept();
}

