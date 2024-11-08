#include "database.hpp"
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

Database::Database() {
    if (!conectarDB("banco.db")) {
        cerr << "Error al conectar a la base de datos" << endl;
        return;
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


    // Métodos para atención al cliente


    void realizarTransferencia(int idCuentaOrigen, int idCuentaDestino, double monto) {
        
        // Verifica el saldo suficiente en la cuenta origen
        const char* sqlSelect = "SELECT Saldo FROM Cuentas WHERE IdCuenta = ?";
        sqlite3_stmt* stmtSelect;
        if (sqlite3_prepare_v2(db, sqlSelect, -1, &stmtSelect, nullptr) != SQLITE_OK) {
            cerr << "Error al preparar la consulta de saldo: " << sqlite3_errmsg(db) << endl;   
            return;
        }

        sqlite3_bind_int(stmtSelect, 1, idCuentaOrigen);
        double saldoOrigen = 0;

        if (sqlite3_step(stmtSelect) == SQLITE_ROW) {
            saldoOrigen = sqlite3_column_double(stmtSelect, 0);
        } else {
            cerr << "Error al obtener el saldo de la cuenta origen " << idCuentaOrigen << endl;
            sqlite3_finalize(stmtSelect);
            return;
        }
        sqlite3_finalize(stmtSelect);

        // Verifica si hay saldo suficiente
        if (saldoOrigen < monto) {
            cerr << "Saldo insuficiente en la cuenta de origen " << idCuentaOrigen << endl;
            return;
        }

        // Inicia la transferencia si el saldo es suficiente
        realizarRetiro(idCuentaOrigen, monto);
        realizarDeposito(idCuentaDestino, monto);
        cout << "Transferencia de " << monto << " realizada de cuenta " << idCuentaOrigen << " a cuenta " << idCuentaDestino << endl;
    }   

    void realizarPagoServicios(int idCuentaCliente, double monto){

        // El monto se carga a una cuenta de servicios, propiedad del banco
        const int idCuentaServicios = 999; // ID ficticio de la cuenta de servicios

        // Se realiza un retiro de la cuenta
        realizarTransferencia(idCuentaCliente, idCuentaServicios, monto);

        cout << "Pago de servicios por " << monto << " realizado desde la cuenta del cliente " << idCuentaCliente << " hacia la cuenta de servicios " << idCuentaServicios << endl;
    }

    void consultarTipoCambio(){

        // Se manejará un tipo de cambio fijo, el cual para recordar buenas épocas, será $1 = 500 CRC (sujeto a cambios)
        cout << "El tipo de cambio actual es de 500 CRC por 1 USD." << endl;
    }

    }
    // Fin de la clase Database




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


