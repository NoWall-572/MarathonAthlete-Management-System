#ifndef OVER50DIALOG_H
#define OVER50DIALOG_H

#include <QDialog>

namespace Ui {
class Over50Dialog;
}

class Over50Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Over50Dialog(QWidget *parent = nullptr);
    ~Over50Dialog();

private:
    Ui::Over50Dialog *ui;
};

#endif // OVER50DIALOG_H
