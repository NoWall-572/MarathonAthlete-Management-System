#ifndef SHOWWINDOW_H
#define SHOWWINDOW_H

#include <QMainWindow>
#include <QTableView>

namespace Ui {
class ShowWindow;
}

class ShowWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowWindow(QWidget *parent = nullptr);
    ~ShowWindow();
    virtual void resizeEvent(QResizeEvent *event) override;

    void displayAthletes();
    void displayAthletes_num(int);
    void displayAthletes_name(const QString&);
    void displayAthletes_age(int);
    void displayAthletes_gender(const QString&);
    void displayAthletes_country(const QString&);



private slots:

    void on_tabWidget_currentChanged(int index);

    void on_actionfind_triggered();

    void on_actionrankboard_triggered();

    void on_actionHomePage_triggered();

    void on_actionold_triggered();

private:
    Ui::ShowWindow *ui;

};

void displayRecord(int index, QTableView *tableView);


#endif // SHOWWINDOW_H
