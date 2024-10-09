#include "listdialog.h"
#include "ui_listdialog.h"
#include "AthleteDatabase.h"

ListDialog::ListDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ListDialog)
{
    ui->setupUi(this);
    int index=ui->tabWidget->currentIndex();
    if(index==0)
    {
        displayAthleteList(index, ui->tableView_man);
    }
    if(index==1)
    {
        displayAthleteList(index, ui->tableView_woman);
    }
}

ListDialog::~ListDialog()
{
    delete ui;
}

void ListDialog::on_tabWidget_currentChanged(int index)
{
    if(index==0)
    {
        displayAthleteList(index, ui->tableView_man);
    }
    if(index==1)
    {
        displayAthleteList(index, ui->tableView_woman);
    }
}

