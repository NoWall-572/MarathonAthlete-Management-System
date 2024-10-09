#include "SigninTimeDialog.h"
#include "ui_SigninTimeDialog.h"
#include "AthleteDatabase.h"
#include <QSqlQueryModel>
#include <QVariant>
#include <QTableView>
#include <QStyledItemDelegate>

class CenterAlignDelegate : public QStyledItemDelegate
{
public:
    explicit CenterAlignDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override
    {
        QStyledItemDelegate::initStyleOption(option, index);

        // 设置居中对齐
        option->displayAlignment = Qt::AlignCenter;
    }
};





SigninTimeDialog::SigninTimeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SigninTimeDialog)
{
    ui->setupUi(this);

    //设置无边框
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);


    // 可以同时设置最大值和最小值
    ui->spinBox_h->setRange(0, 23);  // 等价于 setMinimum(0) 和 setMaximum(24)

    // 设置初始值
    ui->spinBox_h->setValue(23);  // 初始值设为 24

    // 可以同时设置最大值和最小值
    ui->spinBox_m->setRange(0, 59);  // 等价于 setMinimum(0) 和 setMaximum(59)

    // 设置初始值
    ui->spinBox_m->setValue(0);  // 初始值设为 0

    // 可以同时设置最大值和最小值
    ui->spinBox_s->setRange(0, 59);  // 等价于 setMinimum(0) 和 setMaximum(59)

    // 设置初始值
    ui->spinBox_s->setValue(0);  // 初始值设为 0

}

SigninTimeDialog::~SigninTimeDialog()
{
    delete ui;
}

void SigninTimeDialog::on_pushButton_cancel_clicked()
{
    this->close();
}


void SigninTimeDialog::on_pushButton_ok_clicked()
{
    num=ui->lineEdit->text().toInt();
    hour=ui->spinBox_h->value();
    minute=ui->spinBox_m->value();
    second=ui->spinBox_s->value();
    updateAthletetime(num, hour, minute, second);
    this->close();

}


void SigninTimeDialog::on_pushButton_clicked()
{
    num=0;
    num=ui->lineEdit->text().toInt();
    QSqlQueryModel *model = new QSqlQueryModel;
        // 使用参数化查询，选择符合条件的运动员
        model->setQuery(QString("SELECT * FROM Athletes WHERE num = %1").arg(num));
        model->setHeaderData(0, Qt::Horizontal, tr("号码"));
        model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        model->setHeaderData(2, Qt::Horizontal, tr("年龄"));
        model->setHeaderData(3, Qt::Horizontal, tr("性别"));
        model->setHeaderData(4, Qt::Horizontal, tr("国家"));




        ui->tableView->setModel(model);
        // 设置 QTableView 为可编辑的模式
        ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);


        ui->tableView->hideColumn(5);
        ui->tableView->hideColumn(6);
        ui->tableView->hideColumn(7);
        ui->tableView->setColumnWidth(0, 50);
        ui->tableView->setColumnWidth(1, 150);
        ui->tableView->setColumnWidth(2, 50);
        ui->tableView->setColumnWidth(3, 50);
        ui->tableView->setColumnWidth(4, 150);

        // 创建自定义的居中委托
        CenterAlignDelegate *centerDelegate = new CenterAlignDelegate(ui->tableView);

        // 将居中委托应用到所有列
        ui->tableView->setItemDelegate(centerDelegate);

}


void SigninTimeDialog::on_lineEdit_returnPressed()
{
    num=0;
    num=ui->lineEdit->text().toInt();
    QSqlQueryModel *model = new QSqlQueryModel;
    // 使用参数化查询，选择符合条件的运动员
    model->setQuery(QString("SELECT * FROM Athletes WHERE num = %1").arg(num));
    model->setHeaderData(0, Qt::Horizontal, tr("号码"));
    model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
    model->setHeaderData(2, Qt::Horizontal, tr("年龄"));
    model->setHeaderData(3, Qt::Horizontal, tr("性别"));
    model->setHeaderData(4, Qt::Horizontal, tr("国家"));




    ui->tableView->setModel(model);
    // 设置 QTableView 为可编辑的模式
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);


    ui->tableView->hideColumn(5);
    ui->tableView->hideColumn(6);
    ui->tableView->hideColumn(7);
    ui->tableView->setColumnWidth(0, 50);
    ui->tableView->setColumnWidth(1, 150);
    ui->tableView->setColumnWidth(2, 50);
    ui->tableView->setColumnWidth(3, 50);
    ui->tableView->setColumnWidth(4, 150);

    // 创建自定义的居中委托
    CenterAlignDelegate *centerDelegate = new CenterAlignDelegate(ui->tableView);

    // 将居中委托应用到所有列
    ui->tableView->setItemDelegate(centerDelegate);
}

