
#ifndef DATABASE_H
#define DATABASE_H

#include <string>

bool initDB(const std::string& dbName);
bool addExpense(const std::string& category, double amount, const std::string& date, const std::string& note);
void viewExpenses();
bool deleteExpense(int id);
void filterByCategory(const std::string& category);
void totalByCategory();

#endif
