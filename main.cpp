
#include <iostream>
#include "database.h"

int main() {
    std::string dbName = "expenses.db";
    if (!initDB(dbName)) {
        std::cerr << "Failed to initialize the database.\n";
        return 1;
    }

    int choice;
    while (true) {
        std::cout << "\n==== Expense Tracker ====\n";
        std::cout << "1. Add Expense\n";
        std::cout << "2. View Expenses\n";
        std::cout << "3. Delete Expense\n";
        std::cout << "4. Filter by Category\n";
        std::cout << "5. Total Expense by Category\n";
        std::cout << "6. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string category, date, note;
            double amount;
            std::cin.ignore();
            std::cout << "Category: ";
            std::getline(std::cin, category);
            std::cout << "Amount: ";
            std::cin >> amount;
            std::cin.ignore();
            std::cout << "Date (YYYY-MM-DD): ";
            std::getline(std::cin, date);
            std::cout << "Note: ";
            std::getline(std::cin, note);

            if (addExpense(category, amount, date, note))
                std::cout << "Expense added!\n";
            else
                std::cout << "Error adding expense.\n";
        } else if (choice == 2) {
            viewExpenses();
        } else if (choice == 3) {
            int id;
            std::cout << "Enter ID to delete: ";
            std::cin >> id;
            if (deleteExpense(id))
                std::cout << "Expense deleted.\n";
            else
                std::cout << "Failed to delete expense.\n";
        } else if (choice == 4) {
            std::string category;
            std::cin.ignore();
            std::cout << "Enter category to filter: ";
            std::getline(std::cin, category);
            filterByCategory(category);
        } else if (choice == 5) {
            totalByCategory();
        } else if (choice == 6) {
            break;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}
