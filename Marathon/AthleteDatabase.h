#ifndef ATHLETEDATABASE_H
#define ATHLETEDATABASE_H

#include <QString>
#include "Athlete.h"
#include <QTableView>
#include <QStyledItemDelegate>
#include <QSqlTableModel>

extern Match_time malerecord;
extern Match_time femalerecord;




// 声明函数
void checkFilePermissions();
bool createConnection();
void closeDatabaseConnection();
void resetDatabaseConnection();
bool createAthletesTable();
bool renewAthletesTable();
bool addAthlete(const Athlete);
void setupTableView(QTableView *tableView);
bool updateAthletetime(int num, int h, int m, int s);
void updateAthleteRank();
bool deleteAthlete(int num);
void displayTop3CountriesInTableView(int index, QTableView *tableView);
void displayTop5Athletes(int index, QTableView *tableView);
void displayAthleteList(int index, QTableView *tableView);
void updateRecords(QSqlTableModel *model);
void displayAthletesOver50(QTableView *maleTableView, QTableView *femaleTableView);

#endif // ATHLETEDATABASE_H
