#include "AthleteDatabase.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QFile>
#include <QDebug>
#include <QTableView>
#include <QSqlTableModel>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QItemDelegate>
#include <QStandardItemModel>
#include <QCheckBox>
#include <QApplication>
#include <QComboBox>
#include <QObject>
#include "genderdelegate.h"

Match_time malerecord(2,1,9);
Match_time femalerecord(1,4,51);










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

//只读
class ReadOnlyDelegate : public QItemDelegate
{

public:
    explicit ReadOnlyDelegate(QObject *parent = nullptr) : QItemDelegate(parent) {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        // 返回空指针，表示此列不可编辑
        return nullptr;
    }
};

//居中只读
class ReadOnlyCenterDelegate : public QStyledItemDelegate
{

public:
    explicit ReadOnlyCenterDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    // 设置单元格为不可编辑
    QWidget *createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const override
    {
        // 返回空指针，表示此单元格不可编辑
        return nullptr;
    }

    // 设置居中显示
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        // 调用父类的 paint 方法前设置居中
        QStyleOptionViewItem opt = option;
        opt.displayAlignment = Qt::AlignCenter;  // 设置文本居中
        QStyledItemDelegate::paint(painter, opt, index);
    }
};







void checkFilePermissions()
{
    QFile dbFile("Athletes.db");
    if (dbFile.exists()) {
        if (dbFile.permissions() & QFile::ReadOwner && dbFile.permissions() & QFile::WriteOwner) {
            qDebug() << "File has read and write permissions.";
        } else {
            qDebug() << "File does not have read and/or write permissions.";
        }
    } else {
        qDebug() << "File does not exist.";
    }
}


bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Athletes.db");

    if (!db.open())
    {
        qDebug() << "Error: Could not connect to database." << db.lastError();
        return false;
    }
    return true;
}

void closeDatabaseConnection()
{
    // 获取数据库连接
    QSqlDatabase db = QSqlDatabase::database();

    if (db.isOpen())
    {
        // 关闭数据库连接
        db.close();
    }

    // 移除数据库连接
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);  // 移除默认连接
    qDebug() << "Database connection removed.";
}

void resetDatabaseConnection()
{
    // 关闭并移除之前的数据库连接
    closeDatabaseConnection();

    // 重新创建一个新的数据库连接
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Athletes.db");

    if (!db.open()) {
        qDebug() << "Error: Could not connect to database." << db.lastError();
    } else {
        qDebug() << "Database connection re-established.";
    }
}



bool createAthletesTable()
{
    QSqlQuery query;


    QString createTableQuery = "CREATE TABLE IF NOT EXISTS Athletes ("
                               "num INTEGER PRIMARY KEY AUTOINCREMENT, "
                               "name TEXT, "
                               "age INTEGER, "
                               "gender TEXT,"
                               "country TEXT,"
                               "matchtime TEXT,"
                               "timevalue INTEGER,"
                               "rank INTEGER,"
                               "note TEXT)";
    if (!query.exec(createTableQuery))
    {
        qDebug() << "Error: Could not create table." << query.lastError();
        return false;
    }

    return true;
}

bool renewAthletesTable()
{
    QSqlQuery query;

    // 删除旧表（如果有）************************************************
    query.exec("DROP TABLE IF EXISTS Athletes");

    QString createTableQuery = "CREATE TABLE IF NOT EXISTS Athletes ("
                               "num INTEGER PRIMARY KEY AUTOINCREMENT, "
                               "name TEXT, "
                               "age INTEGER, "
                               "gender TEXT,"
                               "country TEXT,"
                               "matchtime TEXT,"
                               "timevalue INTEGER,"
                               "rank INTEGER,"
                               "note TEXT)";
    if (!query.exec(createTableQuery))
    {
        qDebug() << "Error: Could not create table." << query.lastError();
        return false;
    }

    return true;
}


bool addAthlete(const Athlete a)
{
    QSqlQuery query;

    query.prepare("INSERT OR REPLACE INTO Athletes (name, age, gender, country, matchtime, timevalue, rank, note) "
                  "VALUES (:name, :age, :gender, :country, :matchtime, :timevalue, :rank, :note)");
    //query.bindValue(":num", num);
    query.bindValue(":name", a.name);
    query.bindValue(":age", a.age);
    query.bindValue(":gender", a.gender);
    query.bindValue(":country", a.country);
    query.bindValue(":matchtime", a.mtime.displaytime());
    query.bindValue(":timevalue", a.mtime.value());
    query.bindValue(":rank", a.rank);
    query.bindValue(":note", a.note);
/*
    QString insert_sql=QString("INSERT OR REPLACE INTO Athletes values(?,?,?,?)");
    query.prepare(insert_sql);
    query.addBindValue(a.name);
    query.addBindValue(a.age);
    query.addBindValue(a.gender);
    query.addBindValue(a.country);
*/
    qDebug() << "Inserting athlete: name=" << a.name
             << "age=" << a.age
             << "gender=" << a.gender
             << "country=" << a.country;


    if (!query.exec())
    {
        qDebug() << "Error: Could not insert athlete."
                 << query.lastError().text()   // 错误的文本描述
                 << query.lastError().driverText();  // 数据库驱动错误
        return false;
    }
    else
    {
        qDebug()<<"Insert success";
    }
    return true;
}


void setupTableView(QTableView *tableView)
{
    // 创建数据库连接
    if (!createConnection())
    {
        return;
    }

    // 创建 QSqlTableModel 并绑定到 QTableView
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("Athletes");  // 绑定 Athletes 表
    model->setEditStrategy(QSqlTableModel::OnFieldChange);  // 当用户修改某个字段时，立刻更新数据库

    // 设置排序
    updateAthleteRank();

    // 设置表头显示名称
    model->setHeaderData(0, Qt::Horizontal, "号码");
    model->setHeaderData(1, Qt::Horizontal, "姓名");
    model->setHeaderData(2, Qt::Horizontal, "年龄");
    model->setHeaderData(3, Qt::Horizontal, "性别");
    model->setHeaderData(4, Qt::Horizontal, "国家");
    model->setHeaderData(5, Qt::Horizontal, "比赛用时");
    model->setHeaderData(6, Qt::Horizontal, "用时");
    model->setHeaderData(7, Qt::Horizontal, "排名");
    model->setHeaderData(8, Qt::Horizontal, "备注");

    // 按 timevalue 排序
    model->setSort(7, Qt::AscendingOrder);  // 假设 timevalue 列是第 6 列

    model->select();  // 重新选择数据并显示*******

    // 将模型绑定到 QTableView
    tableView->setModel(model);


    updateRecords(model);

    // 设置 QTableView 为可编辑的模式
    tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    // 设置性别列的委托为 GenderDelegate (假设性别是第 3 列)
    GenderDelegate *genderDelegate = new GenderDelegate(tableView);
    tableView->setItemDelegateForColumn(3, genderDelegate);  // 设置第 3 列（性别）为 QComboBox

    // 自动调整列宽
    //tableView->resizeColumnsToContents();

    tableView->setColumnWidth(0, 70); // 设置第 1 列（ID 列）宽度为 70 像素
    tableView->setColumnWidth(1, 200); // 设置第 2 列（姓名）宽度为 200 像素
    tableView->setColumnWidth(2, 80);  // 设置第 3 列（年龄）宽度为 80 像素
    tableView->setColumnWidth(3, 70);  // 设置第 4 列（性别）宽度为 70 像素
    tableView->setColumnWidth(4, 150); // 设置第 5 列（国家）宽度为 150 像素
    tableView->setColumnWidth(5, 200); // 设置第 6 列（时间）宽度为 200 像素
    tableView->setColumnWidth(6, 70);  // 设置第 7 列宽度为 70 像素
    tableView->setColumnWidth(7, 70);  // 设置第 8 列（排名）宽度为 70 像素
    tableView->setColumnWidth(8, 80);



    tableView->hideColumn(6);

    // 调整列宽模式（例如 ResizeToContents 或 Fixed）
    //tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);  // 让姓名列自适应

    // 创建自定义的居中委托
    CenterAlignDelegate *centerDelegate = new CenterAlignDelegate(tableView);

    // 将居中委托应用到所有列
    tableView->setItemDelegate(centerDelegate);

    // 创建自定义委托，应用居中且不可编辑
    ReadOnlyCenterDelegate *readOnlyCenterDelegate = new ReadOnlyCenterDelegate(tableView);

    // 设置自定义委托到需要的列
    tableView->setItemDelegateForColumn(5, readOnlyCenterDelegate);
    tableView->setItemDelegateForColumn(6, readOnlyCenterDelegate);
    tableView->setItemDelegateForColumn(7, readOnlyCenterDelegate);
    tableView->setItemDelegateForColumn(8, readOnlyCenterDelegate);
    // 设置自定义委托到 gender 列 (第 3 列)
    //GenderDelegate *genderDelegate = new GenderDelegate(tableView);
    //tableView->setItemDelegateForColumn(3, genderDelegate);  // 将性别列设置为使用 GenderDelegate
}


bool updateAthletetime(int num, int h, int m, int s)
{
    QSqlQuery query;
    Match_time temptime(h,m,s);

    query.prepare("UPDATE Athletes SET matchtime = :matchtime, timevalue = :timevalue WHERE num = :num");

    query.bindValue(":matchtime", temptime.displaytime());
    query.bindValue(":timevalue", temptime.value());
    query.bindValue(":num", num);

    if (!query.exec())
    {
        qDebug() << "Error updating athlete age:" << query.lastError().text();
        return false;
    }

    return true;
}

void updateAthleteRank()
{
    QSqlQuery query;

    // 使用 RANK() 函数来确保相同 timevalue 的运动员获得相同排名
    QString updateRankSql = R"(
        WITH RankedAthletes AS (
            SELECT num, gender, RANK() OVER(PARTITION BY gender ORDER BY timevalue ASC) AS rank
            FROM Athletes
        )
        UPDATE Athletes
        SET rank = (SELECT rank FROM RankedAthletes WHERE Athletes.num = RankedAthletes.num);
    )";

    // 打印 SQL 查询进行调试
    qDebug() << "Executing SQL: " << updateRankSql;

    // 执行 SQL 更新查询
    if (!query.exec(updateRankSql))
    {
        qDebug() << "Error updating athlete rank:" << query.lastError().text();
    }
    else
    {
        qDebug() << "Athlete ranks updated successfully!";
    }
}

//删除
bool deleteAthlete(int num)
{
    QSqlQuery query;

    // 准备删除语句
    query.prepare("DELETE FROM Athletes WHERE num = :num");
    query.bindValue(":num", num);  // 绑定要删除的运动员编号

    // 执行删除操作
    if (!query.exec())
    {
        qDebug() << "Error deleting athlete:" << query.lastError().text();
        return false;
    }

    qDebug() << "Athlete with num" << num << "deleted successfully.";
    return true;
}

//团体成绩计算
void displayTop3CountriesInTableView(int index, QTableView *tableView)
{

    QSqlQuery query;
    if(index==2)
    {
    // SQL 查询：选取男性前三名国家的前三名运动员姓名和比赛用时
    QString top3SumSql = R"(
        WITH RankedAthletes AS (
            SELECT num, name, country, gender, matchtime, timevalue,
                   ROW_NUMBER() OVER (PARTITION BY country, gender ORDER BY timevalue ASC) AS rank
            FROM Athletes
        ),
        CountryTimeSums AS (
            SELECT country, gender, SUM(timevalue) AS total_timevalue
            FROM RankedAthletes
            WHERE rank <= 3
            GROUP BY country, gender
        ),
        TopCountries AS (
            SELECT country, gender, total_timevalue
            FROM CountryTimeSums
            WHERE gender = '男'
            ORDER BY total_timevalue ASC
            LIMIT 3
        )
        SELECT RankedAthletes.name, RankedAthletes.country, RankedAthletes.matchtime, RankedAthletes.timevalue
        FROM RankedAthletes
        JOIN TopCountries ON RankedAthletes.country = TopCountries.country
        WHERE RankedAthletes.rank <= 3 AND RankedAthletes.gender = '男'
        ORDER BY TopCountries.total_timevalue ASC, RankedAthletes.country, RankedAthletes.rank;
    )";


    // 执行查询
    if (!query.exec(top3SumSql))
    {
        qDebug() << "Error calculating top 3 timevalue sum:" << query.lastError().text();
        return;
    }





    }

    if(index==3)
    {
        // SQL 查询：选取女性前三名国家的前三名运动员姓名和比赛用时
        QString top3SumSql = R"(
        WITH RankedAthletes AS (
            SELECT num, name, country, gender, matchtime, timevalue,
                   ROW_NUMBER() OVER (PARTITION BY country, gender ORDER BY timevalue ASC) AS rank
            FROM Athletes
        ),
        CountryTimeSums AS (
            SELECT country, gender, SUM(timevalue) AS total_timevalue
            FROM RankedAthletes
            WHERE rank <= 3
            GROUP BY country, gender
        ),
        TopCountries AS (
            SELECT country, gender, total_timevalue
            FROM CountryTimeSums
            WHERE gender = '女'
            ORDER BY total_timevalue ASC
            LIMIT 3
        )
        SELECT RankedAthletes.name, RankedAthletes.country, RankedAthletes.matchtime, RankedAthletes.timevalue
        FROM RankedAthletes
        JOIN TopCountries ON RankedAthletes.country = TopCountries.country
        WHERE RankedAthletes.rank <= 3 AND RankedAthletes.gender = '女'
        ORDER BY TopCountries.total_timevalue ASC, RankedAthletes.country, RankedAthletes.rank;
    )";


        // 执行查询
        if (!query.exec(top3SumSql))
        {
            qDebug() << "Error calculating top 3 timevalue sum:" << query.lastError().text();
            return;
        }
    }
        // 创建 QStandardItemModel，用于显示结果
        QStandardItemModel *model = new QStandardItemModel();

        // 设置表头，隐藏性别列
        model->setHorizontalHeaderLabels(QStringList() << "国家" << "运动员姓名" << "比赛用时");

        // 将查询结果添加到模型中
        int row = 0;
        while (query.next())
        {
            QString name = query.value(0).toString();      // 运动员姓名
            QString country = query.value(1).toString();   // 国家
            QString matchtime = query.value(2).toString();  // 比赛用时

            // 添加每一行到模型
            model->setItem(row, 0, new QStandardItem(country));     // 国家
            model->setItem(row, 1, new QStandardItem(name));        // 姓名
            model->setItem(row, 2, new QStandardItem(matchtime)); // 用时

            row++;  // 行号增加
        }

        // 将模型绑定到 QTableView
        tableView->setModel(model);

        // 调整列宽
        //tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableView->setColumnWidth(0, 150);
        tableView->setColumnWidth(1, 160);
        tableView->setColumnWidth(2, 270);
        // 创建自定义委托，应用居中且不可编辑
        ReadOnlyCenterDelegate *readOnlyCenterDelegate = new ReadOnlyCenterDelegate(tableView);

        // 设置自定义委托到需要的列
        tableView->setItemDelegateForColumn(0, readOnlyCenterDelegate);
        tableView->setItemDelegateForColumn(1, readOnlyCenterDelegate);
        tableView->setItemDelegateForColumn(2, readOnlyCenterDelegate);





}

//个人成绩展示
void displayTop5Athletes(int index, QTableView *tableView)
{

    QSqlQuery query;
    if(index==0)
    {

        // SQL 查询：获取男性运动员中排名前五及并列的号码、姓名、国家和比赛用时
        QString top5MaleSql = R"(
        SELECT num, name, country, matchtime, rank, note
        FROM Athletes
        WHERE gender = '男' AND rank <= 5
        ORDER BY rank ASC;
    )";

    // 执行查询
    if (!query.exec(top5MaleSql))
    {
        qDebug() << "Error fetching top 5 male athletes:" << query.lastError().text();
        return;
    }
    }

    if(index==1)
    {

        // SQL 查询：获取女性运动员中排名前五及并列的号码、姓名、国家和比赛用时
        QString top5FemaleSql = R"(
        SELECT num, name, country, matchtime, rank, note
        FROM Athletes
        WHERE gender = '女' AND rank <= 5
        ORDER BY rank ASC;
    )";

        // 执行查询
        if (!query.exec(top5FemaleSql))
        {
            qDebug() << "Error fetching top 5 female athletes:" << query.lastError().text();
            return;
        }
    }



    // 创建 QStandardItemModel，用于显示结果
    QStandardItemModel *model = new QStandardItemModel();

    // 设置表头
    model->setHorizontalHeaderLabels(QStringList() << "号码" << "运动员姓名" << "国家" << "比赛用时" << "排名" << "备注");

    // 将查询结果添加到模型中
    int row = 0;
    while (query.next())
    {
        int num = query.value(0).toInt();               // 运动员号码
        QString name = query.value(1).toString();       // 运动员姓名
        QString country = query.value(2).toString();    // 国家
        QString matchtime = query.value(3).toString();   // 比赛用时
        int rank = query.value(4).toInt();
        QString note =query.value(5).toString();

        // 添加每一行到模型
        model->setItem(row, 0, new QStandardItem(QString::number(num)));  // 号码
        model->setItem(row, 1, new QStandardItem(name));                  // 姓名
        model->setItem(row, 2, new QStandardItem(country));               // 国家
        model->setItem(row, 3, new QStandardItem(matchtime));             // 用时
        model->setItem(row, 4, new QStandardItem(QString::number(rank)));
        model->setItem(row, 5, new QStandardItem(note));
        row++;  // 行号增加
    }

    // 将模型绑定到 QTableView
    tableView->setModel(model);

    // 调整列宽
    tableView->setColumnWidth(0, 70);  // 号码
    tableView->setColumnWidth(1, 120); // 姓名
    tableView->setColumnWidth(2, 110); // 国家
    tableView->setColumnWidth(3, 160); // 用时
    tableView->setColumnWidth(4, 50);
    tableView->setColumnWidth(5, 80);
    // 创建自定义委托，应用居中且不可编辑（如果需要）
    ReadOnlyCenterDelegate *readOnlyCenterDelegate = new ReadOnlyCenterDelegate(tableView);

    // 设置自定义委托到需要的列
    tableView->setItemDelegateForColumn(0, readOnlyCenterDelegate);  // 号码
    tableView->setItemDelegateForColumn(1, readOnlyCenterDelegate);  // 姓名
    tableView->setItemDelegateForColumn(2, readOnlyCenterDelegate);  // 国家
    tableView->setItemDelegateForColumn(3, readOnlyCenterDelegate);  // 用时
    tableView->setItemDelegateForColumn(4, readOnlyCenterDelegate);
    tableView->setItemDelegateForColumn(5, readOnlyCenterDelegate);
}


//展示报名表
void displayAthleteList(int index, QTableView *tableView)
{


    // 创建数据库连接
    if (!createConnection())
    {
        qDebug() << "Error: Unable to establish a database connection.";
        return;
    }

    // 创建 QSqlTableModel 并绑定到 QTableView
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("Athletes");  // 绑定 Athletes 表


    if(index==0)
    {
    // 设置过滤条件，只显示性别为 "Male" 的运动员
        model->setFilter("gender = '男'");  // 这里假设 "gender" 是数据库中的列名
    }
    if(index==1)
    {
        model->setFilter("gender = '女'");
    }


    // 手动提交模式
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    // 选择数据
    model->select();  // 重新选择数据并加载

    // 设置表头显示名称
    model->setHeaderData(0, Qt::Horizontal, "号码");
    model->setHeaderData(1, Qt::Horizontal, "运动员姓名");

    model->setHeaderData(4, Qt::Horizontal, "国家");

    // 将模型绑定到 QTableView
    tableView->setModel(model);

    // 禁用表格的编辑功能
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 创建自定义的居中委托
    CenterAlignDelegate *centerDelegate = new CenterAlignDelegate(tableView);

    // 将居中委托应用到所有列
    tableView->setItemDelegate(centerDelegate);

    // 自动调整列宽
    tableView->setColumnWidth(0, 120);  // 设置第 1 列（号码）宽度为 70 像素
    tableView->setColumnWidth(1, 210); // 设置第 2 列（姓名）宽度为 150 像素
    tableView->setColumnWidth(3, 70);  // 设置第 3 列（性别）宽度为 70 像素
    tableView->setColumnWidth(4, 200); // 设置第 4 列（国家）宽度为 120 像素

    // 隐藏不需要显示的列
    tableView->hideColumn(2); // 隐藏年龄
    tableView->hideColumn(3);
    tableView->hideColumn(5); // 隐藏比赛用时
    tableView->hideColumn(6); // 隐藏用时
    tableView->hideColumn(7); // 隐藏排名
}


void updateRecords(QSqlTableModel *model)
{
    // 遍历模型中的所有运动员数据
    for (int row = 0; row < model->rowCount(); ++row)
    {
        QString gender = model->data(model->index(row, 3)).toString();  // 性别列
        double timeValue = model->data(model->index(row, 6)).toInt();  // 比赛用时列
        QString athleteName = model->data(model->index(row, 1)).toString();  // 运动员姓名列

        // 根据性别进行判断，男子与女子分开处理
        if (gender == "男")
        {
            // 如果男子的比赛时间小于当前的男子比赛记录，打破纪录
            if (timeValue < malerecord.value())
            {
                malerecord.fromSeconds(timeValue);  // 更新男子记录
                qDebug() << "New male record broken by" << athleteName << "with time" << timeValue;

                // 更新该运动员的破纪录状态，假设有一列用于标记破纪录状态
                model->setData(model->index(row, 8), "RECORD!");  // 假设第 8 列是用于标记破纪录的
            }
        }
        else if (gender == "女")
        {
            // 如果女子的比赛时间小于当前的女子比赛记录，打破纪录
            if (timeValue < femalerecord.value())
            {
                femalerecord.fromSeconds(timeValue);  // 更新女子记录
                qDebug() << "New female record broken by" << athleteName << "with time" << timeValue;

                // 更新该运动员的破纪录状态
                model->setData(model->index(row, 8), "RECORD!");  // 假设第 8 列是用于标记破纪录的
            }
        }
    }

    // 提交更新到数据库
    if (!model->submitAll())
    {
        qDebug() << "Error while submitting the data: " << model->lastError();
    }
}

void displayAthletesOver50(QTableView *maleTableView, QTableView *femaleTableView)
{
    // 创建数据库连接
    if (!createConnection()) {
        qDebug() << "Error: Unable to establish a database connection.";
        return;
    }

    // 男性运动员模型
    QSqlTableModel *maleModel = new QSqlTableModel;
    maleModel->setTable("Athletes");  // 绑定 Athletes 表
    // 设置过滤条件，筛选50岁以上的男性运动员
    maleModel->setFilter("gender = '男' AND age > 50");
    maleModel->select();  // 加载数据

    // 设置男性表头显示名称
    maleModel->setHeaderData(0, Qt::Horizontal, "号码");
    maleModel->setHeaderData(1, Qt::Horizontal, "姓名");
    maleModel->setHeaderData(2, Qt::Horizontal, "年龄");
    maleModel->setHeaderData(3, Qt::Horizontal, "性别");
    maleModel->setHeaderData(4, Qt::Horizontal, "国家");
    maleModel->setHeaderData(5, Qt::Horizontal, "比赛用时");
    maleModel->setHeaderData(6, Qt::Horizontal, "比赛用时");
    maleModel->setHeaderData(7, Qt::Horizontal, "排名");          // 新增排名列
    maleModel->setHeaderData(8, Qt::Horizontal, "是否破纪录");   // 新增是否破纪录列

    // 将男性运动员模型绑定到 QTableView
    maleTableView->setModel(maleModel);

    // 自动调整列宽
    maleTableView->setColumnWidth(0, 30);  // 设置第 1 列（号码）宽度为 70 像素
    maleTableView->setColumnWidth(1, 90); // 设置第 2 列（姓名）宽度为 150 像素
    maleTableView->setColumnWidth(2, 40);  // 设置第 3 列（年龄）宽度为 80 像素
    maleTableView->setColumnWidth(3, 30);  // 设置第 4 列（性别）宽度为 70 像素
    maleTableView->setColumnWidth(4, 60); // 设置第 5 列（国家）宽度为 150 像素
    maleTableView->setColumnWidth(5, 120); // 设置第 6 列（比赛用时）宽度为 120 像素
    maleTableView->setColumnWidth(6, 70);
    maleTableView->setColumnWidth(7, 40);  // 设置第 7 列（排名）宽度为 70 像素
    maleTableView->setColumnWidth(8, 100); // 设置第 8 列（是否破纪录）宽度为 100 像素
    maleTableView->hideColumn(6);

    // 女性运动员模型
    QSqlTableModel *femaleModel = new QSqlTableModel;
    femaleModel->setTable("Athletes");  // 绑定 Athletes 表
    // 设置过滤条件，筛选50岁以上的女性运动员
    femaleModel->setFilter("gender = '女' AND age > 50");
    femaleModel->select();  // 加载数据

    // 设置女性表头显示名称
    femaleModel->setHeaderData(0, Qt::Horizontal, "号码");
    femaleModel->setHeaderData(1, Qt::Horizontal, "姓名");
    femaleModel->setHeaderData(2, Qt::Horizontal, "年龄");
    femaleModel->setHeaderData(3, Qt::Horizontal, "性别");
    femaleModel->setHeaderData(4, Qt::Horizontal, "国家");
    femaleModel->setHeaderData(5, Qt::Horizontal, "比赛用时");
    femaleModel->setHeaderData(6, Qt::Horizontal, "比赛用时");
    femaleModel->setHeaderData(7, Qt::Horizontal, "排名");          // 新增排名列
    femaleModel->setHeaderData(8, Qt::Horizontal, "是否破纪录");   // 新增是否破纪录列

    // 将女性运动员模型绑定到 QTableView
    femaleTableView->setModel(femaleModel);

    // 自动调整列宽
    femaleTableView->setColumnWidth(0, 30);  // 设置第 1 列（号码）宽度为 70 像素
    femaleTableView->setColumnWidth(1, 90); // 设置第 2 列（姓名）宽度为 150 像素
    femaleTableView->setColumnWidth(2, 40);  // 设置第 3 列（年龄）宽度为 80 像素
    femaleTableView->setColumnWidth(3, 30);  // 设置第 4 列（性别）宽度为 70 像素
    femaleTableView->setColumnWidth(4, 60); // 设置第 5 列（国家）宽度为 150 像素
    femaleTableView->setColumnWidth(5, 120); // 设置第 6 列（比赛用时）宽度为 120 像素
    femaleTableView->setColumnWidth(6, 70);
    femaleTableView->setColumnWidth(7, 40);  // 设置第 7 列（排名）宽度为 70 像素
    femaleTableView->setColumnWidth(8, 100); // 设置第 8 列（是否破纪录）宽度为 100 像素
    femaleTableView->hideColumn(6);
}


