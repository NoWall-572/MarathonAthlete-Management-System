#include "SignUpDialog.h"
#include "ui_SignUpDialog.h"
#include "AthleteDatabase.h"
#include <QGraphicsDropShadowEffect>
//#include <ctime>

SignUpDialog::SignUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpDialog)
{

    ui->setupUi(this); // 初始化UI

    //设置无边框
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    // 设置阴影效果
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(-3, 0);
    shadow->setBlurRadius(30);

    // 可以同时设置最大值和最小值
    ui->spinBox->setRange(0, 120);  // 等价于 setMinimum(0) 和 setMaximum(120)

    // 设置初始值
    ui->spinBox->setValue(18);  // 初始值设为 18


}

SignUpDialog::~SignUpDialog()
{
    delete ui;
}



QString    SignUpDialog::name()        //姓名
{
    return ui->lineEdit_name->text();
}



bool        SignUpDialog::sex()         //性别
{
    return ui->comboBox_sex->currentIndex();
}

QString    SignUpDialog::gender()       //性别
{
    if(this->sex()==0)
    {
        return "男";
    }
    if(this->sex()==1)
    {
        return "女";
    }
}

int        SignUpDialog::age()          //年龄
{
    return ui->spinBox->value();
}



QString    SignUpDialog::country()     //国别
{
    return ui->lineEdit_country->text();
}

//退出
void SignUpDialog::on_cancelButton_clicked()
{
    this->close();
}



void SignUpDialog::on_okButton_clicked()
{
    Athlete tempa;
    tempa.name   =this->name();
    tempa.age    =this->age();
    tempa.gender =this->gender();
    tempa.country=this->country();
    addAthlete(tempa);
    this->close();
    delete this;
}

