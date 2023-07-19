#include "dialogaddpic.h"
#include "ui_dialogaddpic.h"

Dialogaddpic::Dialogaddpic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogaddpic)
{
    ui->setupUi(this);
}

Dialogaddpic::~Dialogaddpic()
{
    delete ui;
}

picture Dialogaddpic::new_pic()
{
    rat Rat = rat(ui->comboBox->currentIndex());
    Size size;
    size.x = ui->lineEdit_Len->text().toInt();
    size.y = ui->lineEdit_WId->text().toInt();
    picture pic(ui->lineEdit_id->text().toInt(),
              ui->lineEdit_name->text(),
              ui->lineEdit_Aut->text(),
              Rat,ui->lineEdit_Nation->text(),
              size);
    return pic;
}

void Dialogaddpic::set(QString _id, QString _name, QString _author, rat _rating, QString _Nationality, Size _size)
{
    ui->lineEdit_WId->setText(QString::number(_size.x));
    ui->lineEdit_id->setText(_id);
    ui->lineEdit_name->setText(_name);
    ui->lineEdit_Aut->setText(_author);
    ui->lineEdit_Nation->setText(_Nationality);
    ui->lineEdit_Len->setText(QString::number(_size.y));
    ui->comboBox->setCurrentIndex(_rating);
    ui->pushButton->setText("Update");
}

void Dialogaddpic::on_pushButton_clicked()
{
    accept();
}

