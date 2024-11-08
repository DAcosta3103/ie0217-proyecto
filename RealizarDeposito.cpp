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
        //sentencia SQL para actualizar el saldo
        const char* sqlUpdate = R"(
            UPDATE Cuentas
            SET Saldo = Saldo + ?
            WHERE IdCuenta = ?;
        )";
        //stmt (statement) puntero donde se va almacenar la sentencia SQL, db es la variable que abre la base de datos
        //sqlUpdate la sencuencia, -1 indica la longitud de la cadena SQL, &stmt es el punteero
        //que almacena la sentencia preparada, el nullptr indica que no se le van a pasar sentencias adicionales
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sqlUpdate, -1, &stmt, nullptr) != SQLITE_OK) {
            cerr << "Error al preparar la sentencia SQL: " << sqlite3_errmsg(db) << endl;
            return;
        }

        // se vinculan los valores para los parametros ? de de la sentencia
        sqlite3_bind_double(stmt, 1, monto); 
        sqlite3_bind_int(stmt, 2, IdCuenta);

        //esta funcion ejecuta la sentencia, en este caso actualiza la cuenta con el deposito
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Error al ejecutar la sentencia SQL: " << sqlite3_errmsg(db) << endl;
        } else {
            cout << "Depósito de " << monto << " realizado exitosamente en la cuenta " << IdCuenta << "!" << endl;
        }

        //libera los recursos del statement, liberando memoria
        sqlite3_finalize(stmt);  
    }

// exactamente la misma logica del realizar deposito, solo qjue en el saldo de la sentencia
//se le resta al saldo en lugar de sumar
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
            cout << "Retiro de " << monto << " realizado exitosamente desde la cuenta " << IdCuenta << "!" << endl;
        }

        sqlite3_finalize(stmt);  
    }


