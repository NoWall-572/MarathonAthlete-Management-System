#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>

namespace Ui {
class Signup;
}

class Signup : public QDialog
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr);
    ~Signup();

private slots:
    void on_btn_return_clicked();

    void on_btn_ok_clicked();

    void on_btn_ok_pressed();

private:
    Ui::Signup *ui;
};

#endif // SIGNUP_H
