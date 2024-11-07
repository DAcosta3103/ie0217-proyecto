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

Database::Database() {
    if (!conectarDB("banco.db")) {
        cerr << "Error al conectar a la base de datos" << endl;
        return;
    }

    // SQL para crear la tabla Clientes
    const char* sqlCreateClientes = R"(
    CREATE TABLE IF NOT EXISTS Clientes (
        IdCliente INTEGER PRIMARY KEY AUTOINCREMENT,
        Cedula VARCHAR(20) UNIQUE NOT NULL,
        Nombre VARCHAR(100) NOT NULL,
        Direccion TEXT,
        Telefono INT,
        Email VARCHAR(100) UNIQUE
    );
    )";

    // SQL para crear la tabla Cuentas
    const char* sqlCreateCuentas = R"(
    CREATE TABLE IF NOT EXISTS Cuentas (
        IdCuenta INTEGER PRIMARY KEY AUTOINCREMENT,
        IdCliente INT NOT NULL,
        Tipo TEXT CHECK(Tipo IN ('colones', 'dolares')) NOT NULL,
        Saldo DECIMAL(10, 2) DEFAULT 0.00,
        FOREIGN KEY(IdCliente) REFERENCES Clientes(IdCliente)
    );
    )";

    const char* sqlCreateCreditos = R"(
    CREATE TABLE IF NOT EXISTS Creditos (
        IdPrestamo INTEGER PRIMARY KEY AUTOINCREMENT,
        IdCliente INT NOT NULL,
        Monto DECIMAL (10,2) NOT NULL,
        Plazo INT NOT NULL,
        CuotaMensual DECIMAL (10,2) NOT NULL,
        Tipo EXT CHECK(Tipo IN ('Hipotecario', 'Personal', 'Prendario')) NOT NULL,
        FOREIGN KEY(IdCliente) REFERENCES Clientes(IdCliente)
    );
    )";

    const char* sqlCreateCDP = R"(
    CREATE TABLE IF NOT EXISTS CDP (
        IdCDP INTEGER PRIMARY KEY AUTOINCREMENT,
        IdCliente INT NOT NULL,
        Monto DECIMAL (10,2) NOT NULL,
        TazaInteres DECIMAL (10,2) NOT NULL,
        Plazo INT NOT NULL,
        FechaInicio DATE NOT NULL,
        FOREIGN KEY(IdCliente) REFERENCES Clientes(IdCliente)
    );
    )";

    const char* sqlCreateTransacciones = R"(
    CREATE TABLE IF NOT EXISTS Transacciones (
        IdTransaccion INTEGER PRIMARY KEY AUTOINCREMENT,
        IdCliente INT NOT NULL,
        Tipo TEXT CHECK(Tipo IN ('Deposito', 'Retiro', 'Transferencia','Abono')) NOT NULL,
        FOREIGN KEY(IdCliente) REFERENCES Clientes(IdCliente)
    );
    )";


    if (ejecutarSQL(sqlCreateClientes)) {
        cout << "Tabla Clientes creada o ya existe" << endl;
    } else {
        cerr << "Error al crear la tabla Clientes" << endl;
    }


    if (ejecutarSQL(sqlCreateCuentas)) {
        cout << "Tabla Cuentas creada o ya existe" << endl;
    } else {
        cerr << "Error al crear la tabla Cuentas" << endl;
    }

    if (ejecutarSQL(sqlCreateCDP)) {
        cout << "Tabla CDP creada o ya existe" << endl;
    } else {
        cerr << "Error al crear la tabla CDP" << endl;
    }

    if (ejecutarSQL(sqlCreateCreditos)) {
        cout << "Tabla Creditos creada o ya existe" << endl;
    } else {
        cerr << "Error al crear la tabla Creditos" << endl;
    }

        if (ejecutarSQL(sqlCreateTransacciones)) {
        cout << "Tabla Transacciones creada o ya existe" << endl;
    } else {
        cerr << "Error al crear la tabla Transacciones" << endl;
    }


}

