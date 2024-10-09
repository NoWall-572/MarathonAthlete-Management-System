#ifndef SignUpDialog_H
#define SignUpDialog_H

#include <QDialog>

namespace Ui
{
class SignUpDialog;
}

class SignUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignUpDialog(QWidget *parent = nullptr);
    ~SignUpDialog();

    QString       name();          //姓名
    bool          sex();           //性别
    QString       gender();        //性别
    int           age();           //年龄
    QString       country();       //国别
private slots:
    void on_cancelButton_clicked();

    void on_okButton_clicked();

private:
    Ui::SignUpDialog *ui;
};



#endif // SignUpDialog_H
