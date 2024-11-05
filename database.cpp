#include "database.hpp"
#include <sqlite3.h>
#include <string>
#include <iostream>
using namespace std;


bool Database::conectarDB(const string& nombreDB) {
if (sqlite3_open("banco.db", &db) == SQLITE_OK) {
    cout << "Conectado a la base de datos correctamente." << endl;
} else {
    cerr << "Error al abrir la base de datos: " << sqlite3_errmsg(db) << endl;
    return false;
}
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);  // Cerrar la base de datos
        cout << "Base de datos cerrada correctamente." << endl;
    }
}

bool Database::ejecutarSQL(const char* sql) {
    char* errorMessage = nullptr;
    int result = sqlite3_exec(db, sql, nullptr, nullptr, &errorMessage);
    if (result != SQLITE_OK) {
        cerr << "Error al ejecutar SQL: " << errorMessage << endl;
        sqlite3_free(errorMessage);  
        return false;
    }
    return true;
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
    if (ejecutarSQL(sqlCreateTables)) {
        cout << "Tabla 'cuentas' creada o ya existe." << endl;
    } else {
        cerr << "Error al crear la tabla 'cuentas'." << endl;
    }

}

