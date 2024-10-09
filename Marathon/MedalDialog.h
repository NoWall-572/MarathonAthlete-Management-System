#ifndef MEDALDIALOG_H
#define MEDALDIALOG_H

#include <QDialog>

namespace Ui {
class MedalDialog;
}

class MedalDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MedalDialog(QWidget *parent = nullptr);
    ~MedalDialog();

private slots:
    void on_tabWidget_currentChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::MedalDialog *ui;
};

#endif // MEDALDIALOG_H
