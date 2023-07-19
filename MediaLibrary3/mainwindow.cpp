#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "table.h"
#include "tdialogadd.h"
#include "dialogaddcd.h"
#include "dialogaddpic.h"
#include "QMouseEvent"
#include "dialogdel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->toolBar->setStyleSheet("QToolBar { background-color: light; }");
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setStyleSheet("selection-background-color:lightblue;");
    ui->tableWidget->verticalHeader()->setVisible(false); //设置垂直头不可见
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑

    connect(ui->tableWidget,SIGNAL(itemSelectionChanged()),
            this,SLOT(slotSelectChanged()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotSelectChanged()
{
    if(ui->tableWidget->selectedItems().size() > 0 && ui->tableWidget->selectedItems().size() < 8)
    {
        ui->actionDel->setEnabled(true);
        ui->actionUpdate->setEnabled(true);
    }
    else
    {
        ui->actionDel->setEnabled(false);
        ui->actionUpdate->setEnabled(false);
    }
}


void MainWindow::on_comboBox_datanode_currentTextChanged(const QString &arg1)
{
    ui->lineEdit->setText("");
    if(arg1 == "Book"){
        Table table(ui->tableWidget);
        QStringList header_text;
        header_text << "ID" << "Name" << "Author" << "Rating" << "Publisher" << "ISBN" << "Pages";
        table.set_table_header(header_text);
        table.set_table(DB.get_all_book());
    }
    if(arg1 == "CD"){
        Table table(ui->tableWidget);
        QStringList header_text;
        header_text << "ID" << "Name" << "Author" << "Rating" << "producer" << "Year" << "Time";
        table.set_table_header(header_text);
        table.set_table(DB.get_all_CD());
    }
    if(arg1 == "Picture"){
        Table table(ui->tableWidget);
        QStringList header_text;
        header_text << "ID" << "Name" << "Author" << "Rating" << "Nationality" << "Size";
        table.set_table_header(header_text);
        table.set_table(DB.get_all_picture());
    }
}

void MainWindow::on_actionadd_triggered()
{
    TDialogAdd *add_data = new TDialogAdd(this);
    add_data->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    add_data->setWindowTitle("Add new book");

    int ret = add_data->exec();
    if(ret == QDialog::Accepted)
    {
        DB.add_Book(add_data->new_book());
        Table table(ui->tableWidget);
    }

    ui->comboBox_datanode->setCurrentIndex(0);
    Table(ui->tableWidget).set_table(DB.get_all_book());
    delete add_data;
}


void MainWindow::on_actionCD_triggered()
{
    DialogaddCD *add_data = new DialogaddCD(this);
    add_data->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    add_data->setWindowTitle("Add new CD");

    int ret = add_data->exec();
    if(ret == QDialog::Accepted)
    {
        DB.add_CD(add_data->new_cd());
        Table table(ui->tableWidget);
    }

    ui->comboBox_datanode->setCurrentIndex(2);
    Table(ui->tableWidget).set_table(DB.get_all_CD());
    delete add_data;
}


void MainWindow::on_actionPic_triggered()
{
    Dialogaddpic *add_data = new Dialogaddpic(this);
    add_data->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    add_data->setWindowTitle("Add new picture");

    int ret = add_data->exec();
    if(ret == QDialog::Accepted)
    {
        DB.add_Picture(add_data->new_pic());
        Table table(ui->tableWidget);
    }

    ui->comboBox_datanode->setCurrentIndex(1);
    Table(ui->tableWidget).set_table(DB.get_all_picture());
    delete add_data;
}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->lineEdit->setText("");
    if(arg1 == "ID"){
        ui->lineEdit->setPlaceholderText("Search by ID");
    }
    if(arg1 == "Name"){
        ui->lineEdit->setPlaceholderText("Search by Name");
    }
    if(arg1 == "Author"){
        ui->lineEdit->setPlaceholderText("Search by Author");
    }
}

void MainWindow::on_tableWidget_cellEntered(int row, int column)
{
    QString state = ui->comboBox_datanode->currentText();
    QSqlQuery query;
    QTableWidgetItem *item_now = ui->tableWidget->item(row,column);
    QTableWidgetItem *item_id = ui->tableWidget->item(row,0);
    if(state == "book")
    {
        query.exec(QString(R"(UPDATE Book SET Name=%2 WHERE ID='%1';)")
                       .arg(item_id->text().toInt()).arg(item_now->text()));

    }

}


void MainWindow::on_actionDel_triggered()
{
    DialogDel *Del = new DialogDel(this);
    Del->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    Del->setWindowTitle("DEl");

    int ret = Del->exec();
    if(ret == QDialog::Accepted)
    {
        int id = ui->tableWidget->selectedItems().at(0)->text().toInt();
        if(ui->comboBox_datanode->currentText() == "Picture")
        {
            DB.delpic(id);
            Table(ui->tableWidget).set_table(DB.get_all_picture());
        }
        if(ui->comboBox_datanode->currentText() == "CD")
        {
            DB.delCD(id);
            Table(ui->tableWidget).set_table(DB.get_all_CD());
        }
        if(ui->comboBox_datanode->currentText() == "Book")
        {
            DB.delbook(id);
            Table(ui->tableWidget).set_table(DB.get_all_book());
        }
    }
    ui->lineEdit->setText("");
    delete Del;
}

void MainWindow::on_actionUpdate_triggered()
{
    int id = ui->tableWidget->selectedItems().at(0)->text().toInt();
    if(ui->comboBox_datanode->currentText() == "Picture")
    {
        Dialogaddpic *add_data = new Dialogaddpic(this);
        add_data->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
        add_data->setWindowTitle("Update");

        QString str = ui->tableWidget->selectedItems().at(5)->text();
        QString strx;
        QString stry;
        for(int i = 0;i < str.size();i++)
        {
            if(str[i] == 'x')
            {
                strx = str.mid(0,i - 3);
                stry = str.mid(i + 1,str.size() - i-3);
                break;
            }
        }
        Size size;
        size.x = strx.toInt();
        size.y = stry.toInt();
        add_data->set(ui->tableWidget->selectedItems().at(0)->text(),
                      ui->tableWidget->selectedItems().at(1)->text(),
                      ui->tableWidget->selectedItems().at(2)->text(),
                      rat(ui->tableWidget->selectedItems().at(3)->text().toInt()),
                      ui->tableWidget->selectedItems().at(4)->text(),
                      size);

        int ret = add_data->exec();
        if(ret == QDialog::Accepted)
        {
            DB.delpic(id);
            DB.add_Picture(add_data->new_pic());
            Table table(ui->tableWidget);
            Table(ui->tableWidget).set_table(DB.get_all_picture());
        }
        delete add_data;
    }
    if(ui->comboBox_datanode->currentText() == "CD")
    {
        DialogaddCD *add_data = new DialogaddCD(this);
        add_data->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
        add_data->setWindowTitle("Update");
        add_data->set(ui->tableWidget->selectedItems().at(0)->text(),
                      ui->tableWidget->selectedItems().at(1)->text(),
                      ui->tableWidget->selectedItems().at(2)->text(),
                      rat(ui->tableWidget->selectedItems().at(3)->text().toInt()),
                      ui->tableWidget->selectedItems().at(4)->text(),
                      ui->tableWidget->selectedItems().at(5)->text(),
                      ui->tableWidget->selectedItems().at(6)->text());
        int ret = add_data->exec();
        if(ret == QDialog::Accepted)
        {
            DB.delCD(id);
            DB.add_CD(add_data->new_cd());
            Table table(ui->tableWidget);
            Table(ui->tableWidget).set_table(DB.get_all_CD());
        }
        delete add_data;
    }
    if(ui->comboBox_datanode->currentText() == "Book")
    {
        TDialogAdd *add_data = new TDialogAdd(this);
        add_data->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
        add_data->setWindowTitle("Update");
        add_data->set(ui->tableWidget->selectedItems().at(0)->text(),
                      ui->tableWidget->selectedItems().at(1)->text(),
                      ui->tableWidget->selectedItems().at(2)->text(),
                      rat(ui->tableWidget->selectedItems().at(3)->text().toInt()),
                      ui->tableWidget->selectedItems().at(4)->text(),
                      ui->tableWidget->selectedItems().at(5)->text(),
                      ui->tableWidget->selectedItems().at(6)->text());
        int ret = add_data->exec();
        if(ret == QDialog::Accepted)
        {
            DB.delbook(id);
            DB.add_Book(add_data->new_book());
            Table table(ui->tableWidget);
            Table(ui->tableWidget).set_table(DB.get_all_book());
        }
        delete add_data;
    }
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    Table table(ui->tableWidget);
    if(ui->comboBox_datanode->currentText() == "Picture")
    {
        if(ui->comboBox->currentText() == "ID"){

            if(arg1 == "")
            {
                Table(ui->tableWidget).set_table(DB.get_all_picture());
            }
            else
            {
                Table(ui->tableWidget).set_table(DB.get_all_picture(ui->lineEdit->text().toInt()));
            }
        }
        if(ui->comboBox->currentText() == "Name"){
            if(arg1 == "")
            {
                Table(ui->tableWidget).set_table(DB.get_all_picture());
            }
            else
            {
                Table(ui->tableWidget).set_table(DB.get_picture_by_name(ui->lineEdit->text()));
            }
        }
        if(ui->comboBox->currentText()== "Author"){
            if(arg1 == "")
            {
                Table(ui->tableWidget).set_table(DB.get_all_picture());
            }
            else
            {
                Table(ui->tableWidget).set_table(DB.get_all_picture_by_author(ui->lineEdit->text()));
            }
        }
    }
    if(ui->comboBox_datanode->currentText() == "CD")
    {
        if(ui->comboBox->currentText()== "ID"){
            if(arg1 == "")
            {
                Table(ui->tableWidget).set_table(DB.get_all_CD());
            }
            else
            {
                Table(ui->tableWidget).set_table(DB.get_all_CD(ui->lineEdit->text().toInt()));
            }
        }
        if(ui->comboBox->currentText()== "Name"){
            if(arg1 == "")
            {
                Table(ui->tableWidget).set_table(DB.get_all_CD());
            }
            else
            {
                Table(ui->tableWidget).set_table(DB.get_CD_by_name(ui->lineEdit->text()));
            }
        }
        if(ui->comboBox->currentText() == "Author"){
            if(arg1 == "")
            {
                Table(ui->tableWidget).set_table(DB.get_all_CD());
            }
            else
            {
                Table(ui->tableWidget).set_table(DB.get_all_CD_by_author(ui->lineEdit->text()));
            }
        }
    }
    if(ui->comboBox_datanode->currentText() == "Book")
    {
        if(ui->comboBox->currentText() == "ID"){
            if(arg1 == "")
            {
                Table(ui->tableWidget).set_table(DB.get_all_book());
            }
            else
            {
                Table(ui->tableWidget).set_table(DB.get_all_book(ui->lineEdit->text().toInt()));
            }
        }
        if(ui->comboBox->currentText() == "Name"){
            if(arg1 == "")
            {
                Table(ui->tableWidget).set_table(DB.get_all_book());
            }
            else
            {
                Table(ui->tableWidget).set_table(DB.get_book_by_name(ui->lineEdit->text()));
            }
        }
        if(ui->comboBox->currentText() == "Author"){
            if(arg1 == "")
            {
                Table(ui->tableWidget).set_table(DB.get_all_book());
            }
            else
            {
                Table(ui->tableWidget).set_table(DB.get_book_by_author(ui->lineEdit->text()));
            }
        }
    }

}

