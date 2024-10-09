#include "editwindow.h"
#include "ui_editwindow.h"
#include <QTableView>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include "AthleteDatabase.h"
#include <QVBoxLayout>
#include "SigninTimeDialog.h"
#include "DeleteDialog.h"
#include "mainwindow.h"
#include "listdialog.h"


EditWindow::EditWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EditWindow)
{

    ui->setupUi(this);


    // 建立数据库连接
    if (createConnection())
    {
        // 创建表

        createAthletesTable();
        checkFilePermissions();




        // 显示运动员信息
        setupTableView(ui->tableView);

    }

}


EditWindow::~EditWindow()
{
    delete ui;
}

//窗口大小改变
void EditWindow::resizeEvent(QResizeEvent *event)
{
    //父类的保持
    QMainWindow::resizeEvent(event);

    int x = this->frameGeometry().width();
    int y = this->frameGeometry().height();

    //窗口改变大小的时候列表控件跟着改变
    ui->tableView->setGeometry(10,10,x-20,y-10);
}

//登记
void EditWindow::on_actionadd_triggered()
{
    SignUpDialog *signupdialog = new SignUpDialog(this);
    signupdialog->exec();
    setupTableView(ui->tableView);
}


void EditWindow::on_actiontime_triggered()
{
    SigninTimeDialog *sitdialog = new SigninTimeDialog(this);
    sitdialog->exec();
    setupTableView(ui->tableView);

}


void EditWindow::on_actionclear_triggered()
{
    renewAthletesTable();
    setupTableView(ui->tableView);
}


void EditWindow::on_actiondelete_triggered()
{
    DeleteDialog *deletedialog = new DeleteDialog(this);
    deletedialog->exec();
    setupTableView(ui->tableView);
}


void EditWindow::on_actionexit_triggered()
{

    this->close();
    MainWindow *mw=new MainWindow;
    mw->show();
}


void EditWindow::on_actionlist_triggered()
{
    ListDialog *listdialog=new ListDialog;
    listdialog->show();


}

