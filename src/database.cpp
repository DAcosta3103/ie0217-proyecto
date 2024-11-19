#include "../include/database.hpp"
#include <sqlite3.h>
#include <string>
#include <iostream>
using namespace std;


//funcion para ejecutar las sentencias
bool Database::ejecutarSQL(const char* sql) {
     //varible para mensaje de error, el cual es generado por sqlite3_exec
    char* errorMessage = nullptr;

    //nullptr para funciones callback aqui no son necesarias
    // sql es la cadena de texto pasado por 
    //errorMessafge es generado por sqlite3_exec
    int result = sqlite3_exec(db, sql, nullptr, nullptr, &errorMessage);
    
    //manejo de error
    if (result != SQLITE_OK) {
        cerr << "Error al ejecutar SQL: " << errorMessage << endl;
        sqlite3_free(errorMessage);  
        return false;
    }
    return true;
}
    //puntero que almacena la sentencia de caracteres SQl para crear la tabla si no existe
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
        Bloqueada INT DEFAULT 0,  -- Para indicar si la cuenta está bloqueada
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
        Tipo TEXT CHECK(Tipo IN ('Hipotecario', 'Personal', 'Prendario')) NOT NULL,
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



Database::Database() {
    if (!conectarDB("banco.db")) {
        cerr << "Error al conectar a la base de datos" << endl;
        return;
    }


    //pasa el puntero con la sentencia SQL a sqlite3_exec para ejecutarlo y asi crear la tabla 
    //ejecuta la funcion y verifica si fue exitosa
    if (!ejecutarSQL(sqlCreateClientes)) {
        cerr << "Error al crear la tabla Clientes" << endl;
    }

    if (!ejecutarSQL(sqlCreateCuentas)) {
        cerr << "Error al crear la tabla Cuentas" << endl;
        }

    if (!ejecutarSQL(sqlCreateCDP)) {
        cerr << "Error al crear la tabla CDP" << endl;
    }

    if (!ejecutarSQL(sqlCreateCreditos)) {
        cerr << "Error al crear la tabla Creditos" << endl;
    }

    if (!ejecutarSQL(sqlCreateTransacciones)) {
        cerr << "Error al crear la tabla Transacciones" << endl;
    }
}
void Database::cerrarDB() {
    if (db) {
        sqlite3_close(db);  
        db = nullptr;  
}
}