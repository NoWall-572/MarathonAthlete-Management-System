#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include "Athlete.h"


namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = nullptr);
    ~FindDialog();
    Athlete finda;
    int Index;
private slots:
    void on_pushButton_cancel_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_ok_clicked();

private:
    Ui::FindDialog *ui;
};

#endif // FINDDIALOG_H
