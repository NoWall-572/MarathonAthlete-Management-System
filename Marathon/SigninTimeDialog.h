#ifndef SIGNINTIMEDIALOG_H
#define SIGNINTIMEDIALOG_H

#include <QDialog>

namespace Ui {
class SigninTimeDialog;
}

class SigninTimeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SigninTimeDialog(QWidget *parent = nullptr);
    ~SigninTimeDialog();

private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_ok_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_returnPressed();

private:
    Ui::SigninTimeDialog *ui;
    int num;
    int hour=0;
    int minute=0;
    int second=0;
};

#endif // SIGNINTIMEDIALOG_H
