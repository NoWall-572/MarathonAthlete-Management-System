#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include "SignUpDialog.h"

namespace Ui
{
class EditWindow;
}

class EditWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditWindow(QWidget *parent = nullptr);
    ~EditWindow();
    virtual void resizeEvent(QResizeEvent *event) override;


private slots:
    void on_actionadd_triggered();

    void on_actiontime_triggered();

    void on_actionclear_triggered();

    void on_actiondelete_triggered();

    void on_actionexit_triggered();

    void on_actionlist_triggered();

private:
    Ui::EditWindow *ui;
};

void setupTableView(QTableView *tableView);

#endif // EDITWINDOW_H
