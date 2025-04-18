# 💸 C++ Expense Tracker

A lightweight **Expense Tracker** application built in **C++**, utilizing **MySQL** for data storage. This project demonstrates how C++ can be integrated with MySQL for basic CRUD operations to manage income and expense records.

---

## 🚀 Features

- 📌 Add new expenses (category, amount, date, note)
- 📄 View all expenses sorted by date
- ❌ Delete an expense by ID
- 🔍 Filter expenses by category
- 📊 View total expenses grouped by category

---

## 🛠️ Requirements

- C++ compiler (e.g., g++)
- [SQLite3](https://www.sqlite.org/index.html) development library installed

---

## 🔧 Setup & Compilation

### Linux/macOS:

```bash
g++ main.cpp database.cpp -lsqlite3 -o ExpenseTracker
./ExpenseTracker

==== Expense Tracker ====
1. Add Expense
2. View Expenses
3. Delete Expense
4. Filter by Category
5. Total Expense by Category
6. Exit
Choose an option:

💡 Example
Category: Food
Amount: 150
Date (YYYY-MM-DD): 2025-04-18
Note: Lunch at restaurant

✅ Expense added!

📚 Learnings
Working with SQLite in C++

Preparing and executing SQL statements with sqlite3

Handling user input and output via terminal

Modularizing code with headers and source files

📌 Todo
Add file export (CSV/JSON)

Implement monthly/yearly filters

Add user authentication for multi-user support


