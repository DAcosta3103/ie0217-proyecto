#include "database.hpp"
#include <sqlite3.h>
#include <string>
#include <iostream>
using namespace std;


bool Database::conectarDB(const string& nombreDB) {
    if (sqlite3_open(nombreDB.c_str(), &db) == SQLITE_OK) {
        return true;
    } else {
        cerr << "Error al abrir la base de datos: " << sqlite3_errmsg(db) << endl;
        return false;
    }
}

Database::Database(){
    if (!conectarDB("banco.db")) {
        cerr << "Error al conectar a la base de datos." << endl;
        return;
    }

    const char* sqlCreateTables = R"(
    CREATE TABLE IF NOT EXISTS cuentas (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        saldo REAL DEFAULT 0,
        bloqueada INTEGER DEFAULT 0
    );
)";

}