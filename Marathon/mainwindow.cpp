#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signup.h"
#include "showwindow.h"
#include "editwindow.h"

#include <QGraphicsDropShadowEffect>

QString passwd;
QString Currentname;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置窗体透明
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    //设置无边框
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    //实例阴影shadow
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    //设置阴影距离
    shadow->setOffset(-3, 0);
    //设置阴影颜色
    shadow->setColor(QColor("#888888"));
    //设置阴影圆角
    shadow->setBlurRadius(30);


    sqlite_Init();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void sqlite_Init()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("user.db");
    if(!db.open())
    {
        qDebug()<<"open error";
    }
    //create excle
    QString createsql=QString("create table if not exists user(id integer primary key autoincrement,"
                        "username ntext unique not NULL,"
                        "password ntext not NULL)");
    QSqlQuery query;
    if(!query.exec(createsql))
    {
        qDebug()<<"table create error";
    }
    else
    {
        qDebug()<<"table create success";
    }
}


//关闭
void MainWindow::on_pushButton_clicked()
{
    this->close();
}


//登录
void MainWindow::on_btn_signin_clicked()
{
    sqlite_Init();
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    QString sql=QString("select * from user where username='%1' and password='%2'")
            .arg(username).arg(password);
    //创建执行语句对象
    QSqlQuery query(sql);
    //判断执行结果
    if(!query.next())
    {
        qDebug()<<"Login error";
        QMessageBox::information(this,"登录认证","登录失败,账户或者密码错误");

    }
    else
    {
        Currentname = ui->lineEdit_username->text();
        qDebug()<<"Login success";
        QMessageBox::information(this,"登录认证","登录成功");

        EditWindow *ew = new EditWindow;
        ew->show();
        this->close();
    }
}


//访客界面
void MainWindow::on_pushButton_tourist_clicked()
{
    ShowWindow *sw = new ShowWindow;
    sw->show();
    this->close();
}


//注册
void MainWindow::on_btn_signup_clicked()
{
    this->close();
    Signup *s = new Signup;
    s->show();

}

//鼠标按下
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    last = event->globalPos();
}

//鼠标移动
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->globalX() - last.x(); //
    int dy = event->globalY() - last.y();

    last = event->globalPos();
    move(x()+dx, y()+dy);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    int dx = event->globalX() - last.x();
    int dy = event->globalY() - last.y();
    move(x()+dx, y()+dy);
}



