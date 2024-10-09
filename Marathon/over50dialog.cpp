#include "over50dialog.h"
#include "ui_over50dialog.h"
#include "AthleteDatabase.h"

Over50Dialog::Over50Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Over50Dialog)
{
    ui->setupUi(this);
    displayAthletesOver50(ui->tableView_man,ui->tableView_woman);
}

Over50Dialog::~Over50Dialog()
{
    delete ui;
}
