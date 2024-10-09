#include "DeleteDialog.h"
#include "ui_DeleteDialog.h"
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





DeleteDialog::DeleteDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DeleteDialog)
{
    ui->setupUi(this);
    //设置无边框
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);


}

DeleteDialog::~DeleteDialog()
{
    this->close();
    delete ui;
}

void DeleteDialog::on_pushButton_find_clicked()
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


void DeleteDialog::on_pushButton_del_clicked()
{
    num=ui->lineEdit->text().toInt();

    deleteAthlete(num);
    this->close();
}


void DeleteDialog::on_pushButton_return_clicked()
{
    this->close();
}

