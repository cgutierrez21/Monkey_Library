#include <sqlite3.h>
#include <iostream>
#include <string>

int menu ();
int add_to_database (sqlite3 *db, int rc);
int print_database (sqlite3 *db, int rc);

int main () {
    bool remain_open = true;

    // Get home path
    const char *home = getenv("HOME");
    if (home == nullptr) {
        std::cerr << "Error getting home path" << std::endl;
        return 1;
    }
    std::string database_path = std::string(home) + "/Programming/Databases/book_database.db";
    
    // Open database
    sqlite3 *db;
    int rc = sqlite3_open(database_path.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << std::endl << std::endl;
        sqlite3_close(db);
        return 1;
    }
    else {
        std::cout << "Database open. Good to go!" << std::endl;
        std::cout << std::endl;
    }

    while (remain_open) {

        int action = menu();
        int result {10};
        switch (action) {
            case 1:
                result = add_to_database(db, rc);
                break;
            case 2:
                result = print_database(db, rc);
                break;
            default:
                remain_open = false;
                break;
        }

        switch (result) {
            case 0:
                switch (action) {
                    case 1:
                        std::cout << "\nSuccessful addition to database!\n" << std::endl;
                        break;
                    case 2:
                        std::cout << "\nFinished printing database!\n" << std::endl;
                        break;
                    default:
                        break;
                }
                break;
            case 1:
                return 1;
            case 2:
                return 2;
            default:
                break;
        }
    }

    sqlite3_close(db);

    return 0;
}

int menu (){
    // Menu
    std::cout << "1. Add to database" << std::endl;
    std::cout << "2. Print database" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Enter a number: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();
    return choice;
}

int add_to_database (sqlite3 *db, int rc) {
    // Adding to database
    std::string title{};
    std::string first_name{};
    std::string last_name{};
    float rating{0};

    std::cout << "Enter the title of the book: ";
    std::getline(std::cin, title);
    std::cout << "Enter the first name of the author: ";
    std::getline(std::cin, first_name);
    std::cout << "Enter the last name of the author: ";
    std::getline(std::cin, last_name);
    std::cout << "Enter the rating of the book: ";
    std::cin >> rating;

    // Prepare SQL statement
    const char *sql = "INSERT INTO books (title, first_name, last_name, rating) VALUES (?, ?, ?, ?);";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl << std::endl;
        sqlite3_close(db);
        return 1;
    }

    // Bind values to SQL statement
    sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, first_name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, last_name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 4, rating);

    // Execute SQL statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl << std::endl;
        sqlite3_close(db);
        return 2;
    }

    // Finalize
    sqlite3_finalize(stmt);

    return 0;
}

int print_database (sqlite3 *db, int rc) {
    // Printing database
    std::cout << "Printing database..." << std::endl;
    const char *sql = "SELECT * FROM books;";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl << std::endl;
        sqlite3_close(db);
        return 1;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int columncount = sqlite3_column_count(stmt);
        for (int i = 0; i < columncount; i++) {
            const char *columnName = sqlite3_column_name(stmt, i);
            if (std::string(columnName) == "title") {
                std::cout << sqlite3_column_text(stmt, i) << ": ";
            } else if ( std::string(columnName) == "last_name") {
                std::cout << sqlite3_column_text(stmt, i) << " | ";
            } else if ( std::string(columnName) == "rating") {
                std::cout << "Rating: " << sqlite3_column_double(stmt, i) << " ";
            } else {
                std::cout << sqlite3_column_text(stmt, i) << " ";
            }
        }
        std::cout << std::endl;
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl << std::endl;
        sqlite3_close(db);
        return 2;
    }

    sqlite3_finalize(stmt);

    return 0;
}
