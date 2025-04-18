
#include "database.h"
#include "sqlite3.h"
#include <iostream>
#include <sstream>

sqlite3* db;

bool initDB(const std::string& dbName) {
    if (sqlite3_open(dbName.c_str(), &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << "\n";
        return false;
    }

    std::string sql = "CREATE TABLE IF NOT EXISTS expenses ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "category TEXT NOT NULL,"
                      "amount REAL NOT NULL,"
                      "date TEXT NOT NULL,"
                      "note TEXT);";

    char* errMsg = 0;
    if (sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << "\n";
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

bool addExpense(const std::string& category, double amount, const std::string& date, const std::string& note) {
    std::stringstream ss;
    ss << "INSERT INTO expenses (category, amount, date, note) VALUES (?, ?, ?, ?);";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, ss.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) return false;

    sqlite3_bind_text(stmt, 1, category.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, amount);
    sqlite3_bind_text(stmt, 3, date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, note.c_str(), -1, SQLITE_STATIC);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

void viewExpenses() {
    const char* sql = "SELECT * FROM expenses ORDER BY date DESC;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        std::cout << "ID | Category | Amount | Date | Note\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::cout << sqlite3_column_int(stmt, 0) << " | "
                      << sqlite3_column_text(stmt, 1) << " | "
                      << sqlite3_column_double(stmt, 2) << " | "
                      << sqlite3_column_text(stmt, 3) << " | "
                      << sqlite3_column_text(stmt, 4) << "\n";
        }
    }
    sqlite3_finalize(stmt); 
}

bool deleteExpense(int id) {
    std::string sql = "DELETE FROM expenses WHERE id = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_int(stmt, 1, id);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

void filterByCategory(const std::string& category) {
    std::string sql = "SELECT * FROM expenses WHERE category = ? ORDER BY date DESC;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, category.c_str(), -1, SQLITE_STATIC);
        std::cout << "ID | Category | Amount | Date | Note\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::cout << sqlite3_column_int(stmt, 0) << " | "
                      << sqlite3_column_text(stmt, 1) << " | "
                      << sqlite3_column_double(stmt, 2) << " | "
                      << sqlite3_column_text(stmt, 3) << " | "
                      << sqlite3_column_text(stmt, 4) << "\n";
        }
    }
    sqlite3_finalize(stmt);
}

void totalByCategory() {
    const char* sql = "SELECT category, SUM(amount) FROM expenses GROUP BY category;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        std::cout << "Category | Total\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::cout << sqlite3_column_text(stmt, 0) << " | "
                      << sqlite3_column_double(stmt, 1) << "\n";
        }
    }
    sqlite3_finalize(stmt);
}
