#include "MedalDialog.h"
#include "ui_MedalDialog.h"
#include "AthleteDatabase.h"

MedalDialog::MedalDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MedalDialog)
{
    ui->setupUi(this);
    //设置无边框
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    int index =ui->tabWidget->currentIndex();

    if(index==0)
    {
        displayTop5Athletes(index, ui->tableView_mansingle);
    }
    if(index==1)
    {
        displayTop5Athletes(index, ui->tableView_womansingle);
    }
    if(index==2)
    {
        displayTop3CountriesInTableView(index, ui->tableView_manteam);
    }
    if(index==3)
    {
        displayTop3CountriesInTableView(index, ui->tableView_womanteam);
    }


}

MedalDialog::~MedalDialog()
{
    delete ui;
}

void MedalDialog::on_tabWidget_currentChanged(int index)
{

    if(index==0)
    {
        displayTop5Athletes(index, ui->tableView_mansingle);
    }
    if(index==1)
    {
        displayTop5Athletes(index, ui->tableView_womansingle);
    }
    if(index==2)
    {
        displayTop3CountriesInTableView(index, ui->tableView_manteam);
    }
    if(index==3)
    {
        displayTop3CountriesInTableView(index, ui->tableView_womanteam);
    }

}


void MedalDialog::on_pushButton_clicked()
{
    this->close();
}

