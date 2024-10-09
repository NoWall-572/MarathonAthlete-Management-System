#include "showwindow.h"
#include "ui_showwindow.h"
#include "AthleteDatabase.h"
#include "FindDialog.h"
#include <QSqlQueryModel>
#include <QVariant>
#include <QTableView>
#include "MedalDialog.h"
#include "mainwindow.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include "over50dialog.h"

//居中
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







ShowWindow::ShowWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ShowWindow)
{
    ui->setupUi(this);
    //设置窗体透明
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    //设置无边框
    //this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);


    // 建立数据库连接
    if (createConnection())
    {
        // 创建表

        createAthletesTable();
        checkFilePermissions();


        // 显示运动员信息
        displayAthletes();
    }
    int index=ui->tabWidget->currentIndex();
    displayRecord(index, ui->tableView_record);

}

ShowWindow::~ShowWindow()
{
    delete ui;
}

//窗口大小改变
void ShowWindow::resizeEvent(QResizeEvent *event)
{
    //父类的保持
    QMainWindow::resizeEvent(event);

    int x = this->frameGeometry().width();
    int y = this->frameGeometry().height();

    //窗口改变大小的时候列表控件跟着改变
    ui->tabWidget->setGeometry(10,40,x-20,y-80);
}







void ShowWindow::displayAthletes()
{
    int currentTabIndex = ui->tabWidget->currentIndex();
    QSqlQueryModel *model = new QSqlQueryModel;
    if(currentTabIndex==0)
    {
        // 使用参数化查询，选择符合条件的运动员
        model->setQuery(QString("SELECT * FROM Athletes WHERE gender = '%1'").arg("男"));

        model->setHeaderData(0, Qt::Horizontal, tr("号码"));
        model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        model->setHeaderData(2, Qt::Horizontal, tr("年龄"));
        model->setHeaderData(3, Qt::Horizontal, tr("性别"));
        model->setHeaderData(4, Qt::Horizontal, tr("国家"));
        model->setHeaderData(5, Qt::Horizontal, tr("比赛用时"));
        model->setHeaderData(6, Qt::Horizontal, tr("时长"));
        model->setHeaderData(7, Qt::Horizontal, tr("排名"));
        model->setHeaderData(8, Qt::Horizontal, tr("备注"));
        ui->tableView_man->setModel(model);
        // 隐藏 gender 列
        ui->tableView_man->hideColumn(3);
        ui->tableView_man->hideColumn(6);

        // 创建自定义的居中委托
        CenterAlignDelegate *centerDelegate = new CenterAlignDelegate(ui->tableView_man);

        // 将居中委托应用到所有列
        ui->tableView_man->setItemDelegate(centerDelegate);
    }
    if(currentTabIndex==1)
    {
        // 使用参数化查询，选择符合条件的运动员
        model->setQuery(QString("SELECT * FROM Athletes WHERE gender = '%1'").arg("女"));

        model->setHeaderData(0, Qt::Horizontal, tr("号码"));
        model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        model->setHeaderData(2, Qt::Horizontal, tr("年龄"));
        model->setHeaderData(3, Qt::Horizontal, tr("性别"));
        model->setHeaderData(4, Qt::Horizontal, tr("国家"));
        model->setHeaderData(5, Qt::Horizontal, tr("比赛用时"));
        model->setHeaderData(6, Qt::Horizontal, tr("时长"));
        model->setHeaderData(7, Qt::Horizontal, tr("排名"));
        model->setHeaderData(8, Qt::Horizontal, tr("备注"));
        ui->tableView_woman->setModel(model);
        // 隐藏 gender 列
        ui->tableView_woman->hideColumn(3);
        ui->tableView_woman->hideColumn(6);

        // 创建自定义的居中委托
        CenterAlignDelegate *centerDelegate = new CenterAlignDelegate(ui->tableView_woman);

        // 将居中委托应用到所有列
        ui->tableView_woman->setItemDelegate(centerDelegate);
    }


}

void ShowWindow::displayAthletes_num(int num)
{
    int currentTabIndex = ui->tabWidget->currentIndex();
    QSqlQueryModel *model = new QSqlQueryModel;
    if(currentTabIndex==0)
    {
        // 使用参数化查询，选择符合条件的运动员
        model->setQuery(QString("SELECT * FROM Athletes WHERE num = %1 AND gender = '%2'").arg(num).arg("男"));

        model->setHeaderData(0, Qt::Horizontal, tr("号码"));
        model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        model->setHeaderData(2, Qt::Horizontal, tr("年龄"));
        model->setHeaderData(3, Qt::Horizontal, tr("性别"));
        model->setHeaderData(4, Qt::Horizontal, tr("国家"));
        model->setHeaderData(5, Qt::Horizontal, tr("比赛用时"));
        model->setHeaderData(6, Qt::Horizontal, tr("时长"));
        model->setHeaderData(7, Qt::Horizontal, tr("排名"));
        model->setHeaderData(8, Qt::Horizontal, tr("备注"));
        ui->tableView_man->setModel(model);
        // 隐藏 gender 列
        ui->tableView_man->hideColumn(3);
        ui->tableView_man->hideColumn(6);

        // 创建自定义的居中委托
        CenterAlignDelegate *centerDelegate = new CenterAlignDelegate(ui->tableView_man);

        // 将居中委托应用到所有列
        ui->tableView_man->setItemDelegate(centerDelegate);
    }
    if(currentTabIndex==1)
    {
        // 使用参数化查询，选择符合条件的运动员
        model->setQuery(QString("SELECT * FROM Athletes WHERE num = %1 AND gender = '%2'").arg(num).arg("女"));

        model->setHeaderData(0, Qt::Horizontal, tr("号码"));
        model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        model->setHeaderData(2, Qt::Horizontal, tr("年龄"));
        model->setHeaderData(3, Qt::Horizontal, tr("性别"));
        model->setHeaderData(4, Qt::Horizontal, tr("国家"));
        model->setHeaderData(5, Qt::Horizontal, tr("比赛用时"));
        model->setHeaderData(6, Qt::Horizontal, tr("时长"));
        model->setHeaderData(7, Qt::Horizontal, tr("排名"));
        model->setHeaderData(8, Qt::Horizontal, tr("备注"));
        ui->tableView_woman->setModel(model);
        // 隐藏 gender 列
        ui->tableView_woman->hideColumn(3);
        ui->tableView_woman->hideColumn(6);

        // 创建自定义的居中委托
        CenterAlignDelegate *centerDelegate = new CenterAlignDelegate(ui->tableView_woman);

        // 将居中委托应用到所有列
        ui->tableView_woman->setItemDelegate(centerDelegate);
    }
}

void ShowWindow::displayAthletes_name(const QString& name)
{
    int currentTabIndex = ui->tabWidget->currentIndex();
    QSqlQueryModel *model = new QSqlQueryModel;
    if(currentTabIndex==0)
    {
        // 使用参数化查询，选择符合条件的运动员
        model->setQuery(QString("SELECT * FROM Athletes WHERE name = '%1' AND gender = '%2'").arg(name).arg("男"));

        model->setHeaderData(0, Qt::Horizontal, tr("号码"));
        model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        model->setHeaderData(2, Qt::Horizontal, tr("年龄"));
        model->setHeaderData(3, Qt::Horizontal, tr("性别"));
        model->setHeaderData(4, Qt::Horizontal, tr("国家"));
        model->setHeaderData(5, Qt::Horizontal, tr("比赛用时"));
        model->setHeaderData(6, Qt::Horizontal, tr("时长"));
        model->setHeaderData(7, Qt::Horizontal, tr("排名"));
        model->setHeaderData(8, Qt::Horizontal, tr("备注"));
        ui->tableView_man->setModel(model);
        // 隐藏 gender 列
        ui->tableView_man->hideColumn(3);
        ui->tableView_man->hideColumn(6);

        // 创建自定义的居中委托
        CenterAlignDelegate *centerDelegate = new CenterAlignDelegate(ui->tableView_man);

        // 将居中委托应用到所有列
        ui->tableView_man->setItemDelegate(centerDelegate);
    }
    if(currentTabIndex==1)
    {
        // 使用参数化查询，选择符合条件的运动员
        model->setQuery(QString("SELECT * FROM Athletes WHERE name = '%1' AND gender = '%2'").arg(name).arg("女"));

        model->setHeaderData(0, Qt::Horizontal, tr("号码"));
        model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        model->setHeaderData(2, Qt::Horizontal, tr("年龄"));
        model->setHeaderData(3, Qt::Horizontal, tr("性别"));
        model->setHeaderData(4, Qt::Horizontal, tr("国家"));
        model->setHeaderData(5, Qt::Horizontal, tr("比赛用时"));
        model->setHeaderData(6, Qt::Horizontal, tr("时长"));
        model->setHeaderData(7, Qt::Horizontal, tr("排名"));
        model->setHeaderData(8, Qt::Horizontal, tr("备注"));
        ui->tableView_woman->setModel(model);
        // 隐藏 gender 列
        ui->tableView_woman->hideColumn(3);
        ui->tableView_woman->hideColumn(6);

        // 创建自定义的居中委托
        CenterAlignDelegate *centerDelegate = new CenterAlignDelegate(ui->tableView_woman);

        // 将居中委托应用到所有列
        ui->tableView_woman->setItemDelegate(centerDelegate);
    }
}

void ShowWindow::displayAthletes_gender(const QString& gender)
{
    int currentTabIndex = ui->tabWidget->currentIndex();
    QSqlQueryModel *model = new QSqlQueryModel;
    if(currentTabIndex==0)
    {
        // 使用参数化查询，选择符合条件的运动员
        model->setQuery(QString("SELECT * FROM Athletes WHERE gender = '%1' AND gender = '%2'").arg(gender).arg("男"));

        model->setHeaderData(0, Qt::Horizontal, tr("号码"));
        model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        model->setHeaderData(2, Qt::Horizontal, tr("年龄"));
        model->setHeaderData(3, Qt::Horizontal, tr("性别"));
        model->setHeaderData(4, Qt::Horizontal, tr("国家"));
        model->setHeaderData(5, Qt::Horizontal, tr("比赛用时"));
        model->setHeaderData(6, Qt::Horizontal, tr("时长"));
        model->setHeaderData(7, Qt::Horizontal, tr("排名"));
        model->setHeaderData(8, Qt::Horizontal, tr("备注"));
        ui->tableView_man->setModel(model);
        // 隐藏 gender 列
        ui->tableView_man->hideColumn(3);
        ui->tableView_man->hideColumn(6);

        // 创建自定义的居中委托
        CenterAlignDelegate *centerDelegate = new CenterAlignDelegate(ui->tableView_man);

        // 将居中委托应用到所有列
        ui->tableView_man->setItemDelegate(centerDelegate);
    }
    if(currentTabIndex==1)
    {
        // 使用参数化查询，选择符合条件的运动员
        model->setQuery(QString("SELECT * FROM Athletes WHERE gender = '%1' AND gender = '%2'").arg(gender).arg("女"));

        model->setHeaderData(0, Qt::Horizontal, tr("号码"));
        model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        model->setHeaderData(2, Qt::Horizontal, tr("年龄"));
        model->setHeaderData(3, Qt::Horizontal, tr("性别"));
        model->setHeaderData(4, Qt::Horizontal, tr("国家"));
        model->setHeaderData(5, Qt::Horizontal, tr("比赛用时"));
        model->setHeaderData(6, Qt::Horizontal, tr("时长"));
        model->setHeaderData(7, Qt::Horizontal, tr("排名"));
        model->setHeaderData(8, Qt::Horizontal, tr("备注"));
        ui->tableView_woman->setModel(model);
        // 隐藏 gender 列
        ui->tableView_woman->hideColumn(3);
        ui->tableView_woman->hideColumn(6);

        // 创建自定义的居中委托
        CenterAlignDelegate *centerDelegate = new CenterAlignDelegate(ui->tableView_woman);

        // 将居中委托应用到所有列
        ui->tableView_woman->setItemDelegate(centerDelegate);
    }
}

void ShowWindow::displayAthletes_country(const QString& country)
{
    int currentTabIndex = ui->tabWidget->currentIndex();
    QSqlQueryModel *model = new QSqlQueryModel;
    if(currentTabIndex==0)
    {
        // 使用参数化查询，选择符合条件的运动员
        model->setQuery(QString("SELECT * FROM Athletes WHERE country = '%1' AND gender = '%2'").arg(country).arg("男"));

        model->setHeaderData(0, Qt::Horizontal, tr("号码"));
        model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        model->setHeaderData(2, Qt::Horizontal, tr("年龄"));
        model->setHeaderData(3, Qt::Horizontal, tr("性别"));
        model->setHeaderData(4, Qt::Horizontal, tr("国家"));
        model->setHeaderData(5, Qt::Horizontal, tr("比赛用时"));
        model->setHeaderData(6, Qt::Horizontal, tr("时长"));
        model->setHeaderData(7, Qt::Horizontal, tr("排名"));
        model->setHeaderData(8, Qt::Horizontal, tr("备注"));
        ui->tableView_man->setModel(model);
        // 隐藏 gender 列
        ui->tableView_man->hideColumn(3);
        ui->tableView_man->hideColumn(6);

        // 创建自定义的居中委托
        CenterAlignDelegate *centerDelegate = new CenterAlignDelegate(ui->tableView_man);

        // 将居中委托应用到所有列
        ui->tableView_man->setItemDelegate(centerDelegate);
    }
    if(currentTabIndex==1)
    {
        // 使用参数化查询，选择符合条件的运动员
        model->setQuery(QString("SELECT * FROM Athletes WHERE country = '%1' AND gender = '%2'").arg(country).arg("女"));

        model->setHeaderData(0, Qt::Horizontal, tr("号码"));
        model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        model->setHeaderData(2, Qt::Horizontal, tr("年龄"));
        model->setHeaderData(3, Qt::Horizontal, tr("性别"));
        model->setHeaderData(4, Qt::Horizontal, tr("国家"));
        model->setHeaderData(5, Qt::Horizontal, tr("比赛用时"));
        model->setHeaderData(6, Qt::Horizontal, tr("时长"));
        model->setHeaderData(7, Qt::Horizontal, tr("排名"));
        model->setHeaderData(8, Qt::Horizontal, tr("备注"));
        ui->tableView_woman->setModel(model);
        // 隐藏 gender 列
        ui->tableView_woman->hideColumn(3);
        ui->tableView_woman->hideColumn(6);

        // 创建自定义的居中委托
        CenterAlignDelegate *centerDelegate = new CenterAlignDelegate(ui->tableView_woman);

        // 将居中委托应用到所有列
        ui->tableView_woman->setItemDelegate(centerDelegate);
    }
}


void ShowWindow::displayAthletes_age(int age)
{
    int currentTabIndex = ui->tabWidget->currentIndex();
    QSqlQueryModel *model = new QSqlQueryModel;
    if(currentTabIndex==0)
    {
        // 使用参数化查询，选择符合条件的运动员
        model->setQuery(QString("SELECT * FROM Athletes WHERE age = %1 AND gender = '%2'").arg(age).arg("男"));

        model->setHeaderData(0, Qt::Horizontal, tr("号码"));
        model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        model->setHeaderData(2, Qt::Horizontal, tr("年龄"));
        model->setHeaderData(3, Qt::Horizontal, tr("性别"));
        model->setHeaderData(4, Qt::Horizontal, tr("国家"));
        model->setHeaderData(5, Qt::Horizontal, tr("比赛用时"));
        model->setHeaderData(6, Qt::Horizontal, tr("时长"));
        model->setHeaderData(7, Qt::Horizontal, tr("排名"));
        model->setHeaderData(8, Qt::Horizontal, tr("备注"));
        ui->tableView_man->setModel(model);
        // 隐藏 gender 列
        ui->tableView_man->hideColumn(3);
        ui->tableView_man->hideColumn(6);

        // 创建自定义的居中委托
        CenterAlignDelegate *centerDelegate = new CenterAlignDelegate(ui->tableView_man);

        // 将居中委托应用到所有列
        ui->tableView_man->setItemDelegate(centerDelegate);

    }
    if(currentTabIndex==1)
    {
        // 使用参数化查询，选择符合条件的运动员
        model->setQuery(QString("SELECT * FROM Athletes WHERE age = %1 AND gender = '%2'").arg(age).arg("女"));
        model->setHeaderData(0, Qt::Horizontal, tr("号码"));
        model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        model->setHeaderData(2, Qt::Horizontal, tr("年龄"));
        model->setHeaderData(3, Qt::Horizontal, tr("性别"));
        model->setHeaderData(4, Qt::Horizontal, tr("国家"));
        model->setHeaderData(5, Qt::Horizontal, tr("比赛用时"));
        model->setHeaderData(6, Qt::Horizontal, tr("时长"));
        model->setHeaderData(7, Qt::Horizontal, tr("排名"));
        model->setHeaderData(8, Qt::Horizontal, tr("备注"));
        ui->tableView_woman->setModel(model);
        // 隐藏 gender 列
        ui->tableView_woman->hideColumn(3);
        ui->tableView_woman->hideColumn(6);

        // 创建自定义的居中委托
        CenterAlignDelegate *centerDelegate = new CenterAlignDelegate(ui->tableView_woman);

        // 将居中委托应用到所有列
        ui->tableView_woman->setItemDelegate(centerDelegate);
    }
}

void displayRecord(int index, QTableView *tableView)
{
    // 创建模型
    QStandardItemModel *model = new QStandardItemModel();

    // 设置表头
    model->setHorizontalHeaderLabels({"马拉松比赛记录"});

    if(index==0)
    {
        // 将全局变量 record 添加到模型中
        QStandardItem *item = new QStandardItem(malerecord.displaytime());
        model->appendRow(item);  // 添加到模型的第一行
    }
    if(index==1)
    {
        // 将全局变量 record 添加到模型中
        QStandardItem *item = new QStandardItem(femalerecord.displaytime());
        model->appendRow(item);  // 添加到模型的第一行
    }


    // 将模型绑定到 TableView
    tableView->setModel(model);

    // 调整列宽
    tableView->horizontalHeader()->setStretchLastSection(true);  // 自动扩展最后一列
    tableView->resizeColumnsToContents();
}

void ShowWindow::on_tabWidget_currentChanged(int)
{
    int index= ui->tabWidget->currentIndex();
    displayAthletes();
    displayRecord(index, ui->tableView_record);
}


void ShowWindow::on_actionfind_triggered()
{
    FindDialog *finddialog=new FindDialog(this);
    finddialog->exec();
    if(finddialog->Index==0)
    {
        displayAthletes_num(finddialog->finda.num);
    }

    if(finddialog->Index==1)
    {
        displayAthletes_name(finddialog->finda.name);
    }

    if(finddialog->Index==2)
    {
        displayAthletes_age(finddialog->finda.age);
    }

    if(finddialog->Index==3)
    {
        displayAthletes_country(finddialog->finda.country);
    }

    if(finddialog->Index==100)
    {
    }
}


void ShowWindow::on_actionrankboard_triggered()
{
    MedalDialog *medaldialog=new MedalDialog(this);
    medaldialog->show();
}


void ShowWindow::on_actionHomePage_triggered()
{
    MainWindow *mw=new MainWindow;
    this->close();
    mw->show();
}



void ShowWindow::on_actionold_triggered()
{
    Over50Dialog *olddlg =new Over50Dialog;
    olddlg -> show();
}

