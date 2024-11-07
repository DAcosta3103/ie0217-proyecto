#include "database.hpp"
#include <sqlite3.h>
#include <string>
#include <iostream>
using namespace std;

bool Database::conectarDB(const string& nombreDB) {
if (sqlite3_open("banco.db", &db) == SQLITE_OK) {
    cout << "Conectado a la base de datos correctamente" << endl;
    return true;
} else {
    cerr << "Error al abrir la base de datos: " << sqlite3_errmsg(db) << endl;
    return false;
}
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);  // Cerrar la base de datos
        cout << "Base de datos cerrada correctamente" << endl;
    }
}

void Database::realizarDeposito(int IdCuenta, double monto) {
        const char* sqlUpdate = R"(
            UPDATE Cuentas
            SET Saldo = Saldo + ?
            WHERE IdCuenta = ?;
        )";

        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sqlUpdate, -1, &stmt, nullptr) != SQLITE_OK) {
            cerr << "Error al preparar la sentencia SQL: " << sqlite3_errmsg(db) << endl;
            return;
        }

        sqlite3_bind_double(stmt, 1, monto); 
        sqlite3_bind_int(stmt, 2, IdCuenta);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Error al ejecutar la sentencia SQL: " << sqlite3_errmsg(db) << endl;
        } else {
            cout << "Depósito de " << monto << " realizado exitosamente en la cuenta " << IdCuenta << "!" << endl;
        }

        sqlite3_finalize(stmt);  
    }

void Database::realizarRetiro(int IdCuenta, double monto) {
        const char* sqlUpdate = R"(
            UPDATE Cuentas
            SET Saldo = Saldo - ?
            WHERE IdCuenta = ?;
        )";

        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sqlUpdate, -1, &stmt, nullptr) != SQLITE_OK) {
            cerr << "Error al preparar la sentencia SQL: " << sqlite3_errmsg(db) << endl;
            return;
        }

        sqlite3_bind_double(stmt, 1, monto); 
        sqlite3_bind_int(stmt, 2, IdCuenta);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Error al ejecutar la sentencia SQL: " << sqlite3_errmsg(db) << endl;
        } else {
            cout << "Depósito de " << monto << " realizado exitosamente en la cuenta " << IdCuenta << "!" << endl;
        }

        sqlite3_finalize(stmt);  
    }


