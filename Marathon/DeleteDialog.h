#ifndef DELETEDIALOG_H
#define DELETEDIALOG_H

#include <QDialog>
#include <Athlete.h>



namespace Ui {
class DeleteDialog;
}

class DeleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteDialog(QWidget *parent = nullptr);
    ~DeleteDialog();

    int num;

private slots:
    void on_pushButton_find_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_return_clicked();

private:
    Ui::DeleteDialog *ui;
};

#endif // DELETEDIALOG_H
