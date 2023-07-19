#include "dialogaddcd.h"
#include "ui_dialogaddcd.h"

DialogaddCD::DialogaddCD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogaddCD)
{
    ui->setupUi(this);
}

DialogaddCD::~DialogaddCD()
{
    delete ui;
}

CD DialogaddCD::new_cd()
{
    rat Rat = rat(ui->comboBox->currentIndex());

    CD Cd(ui->lineEdit_id->text().toInt(),
            ui->lineEdit_name->text(),
            ui->lineEdit_aut->text(),
            Rat,ui->lineEdit_pro->text(),
            ui->lineEdit_year->text().toInt(),
            ui->lineEdit_time->text());
    return Cd;
}

void DialogaddCD::set(QString _id, QString _name, QString _author, rat _rating, QString _producer, QString _year, QString _time)
{
    ui->lineEdit_time->setText(_time);
    ui->lineEdit_id->setText(_id);
    ui->lineEdit_name->setText(_name);
    ui->lineEdit_aut->setText(_author);
    ui->lineEdit_pro->setText(_producer);
    ui->lineEdit_year->setText(_year);
    ui->comboBox->setCurrentIndex(_rating);
    ui->pushButton->setText("Update");
}

void DialogaddCD::on_pushButton_clicked()
{
    accept();
}

