#include "FindDialog.h"
#include "ui_FindDialog.h"
#include "showwindow.h"
#include "Athlete.h"

FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FindDialog)
{
    ui->setupUi(this);
    //设置无边框
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::on_pushButton_cancel_clicked()
{
    this->close();
    this->Index=100;
}


void FindDialog::on_comboBox_currentIndexChanged(int index=0)
{
    this->Index=index;

}


void FindDialog::on_pushButton_ok_clicked()
{
    if(this->Index==0)
    {
        finda.num=ui->lineEdit->text().toInt();

    }

    if(this->Index==1)
    {
        finda.name=ui->lineEdit->text();
    }

    if(this->Index==2)
    {
        finda.age=ui->lineEdit->text().toInt();
    }

    if(this->Index==3)
    {
        finda.country=ui->lineEdit->text();
    }
    this->close();
}

