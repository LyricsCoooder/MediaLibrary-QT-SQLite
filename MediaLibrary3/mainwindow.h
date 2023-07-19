#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <data.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slotSelectChanged();

    void on_comboBox_datanode_currentTextChanged(const QString &arg1);

    void on_actionadd_triggered();

    void on_actionCD_triggered();

    void on_actionPic_triggered();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_tableWidget_cellEntered(int row, int column);

    void on_actionDel_triggered();

    void on_actionUpdate_triggered();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    DataBase DB;

};
#endif // MAINWINDOW_H
