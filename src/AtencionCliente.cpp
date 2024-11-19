#include "../include/database.hpp"
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

   // Métodos para atención al cliente


void Database::realizarTransferencia(int idCuentaOrigen, int idCuentaDestino, double monto) {
        
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

    
    
void Database::realizarPagoServicios(int idCuentaCliente, double monto){

        // El monto se carga a una cuenta de servicios, propiedad del banco
        const int idCuentaServicios = 999; // ID ficticio de la cuenta de servicios

        // Se realiza un retiro de la cuenta
        realizarTransferencia(idCuentaCliente, idCuentaServicios, monto);

        cout << "Pago de servicios por " << monto << " realizado desde la cuenta del cliente " << idCuentaCliente << " hacia la cuenta de servicios " << idCuentaServicios << endl;
    }

void Database::consultarTipoCambio(){

        // Se manejará un tipo de cambio fijo, el cual para recordar buenas épocas, será $1 = 500 CRC (sujeto a cambios)
        cout << "El tipo de cambio actual es de 500 CRC por 1 USD." << endl;
    }


void Database::comprarCDP(int idCliente, double monto) {

        // Se setean valores predeterminados para el CDP
        const char* sqlInsertCDP = R"(
            INSERT INTO CDP (IdCliente, Monto, TazaInteres, Plazo, FechaInicio)
            VALUES (?, ?, 5.0, 12, date('now'));
        )";

        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sqlInsertCDP, -1, &stmt, nullptr) != SQLITE_OK) {
            cerr << "Error al preparar la sentencia SQL para comprar CDP: " << sqlite3_errmsg(db) << endl;
            return;
        }

        // Enlace de parámetros
        sqlite3_bind_int(stmt, 1, idCliente);
        sqlite3_bind_double(stmt, 2, monto);

        // Se maneja la lógica de compra
        /*
        Por implementar: Verificación de si el cliente tiene suficiente dinero en su cuenta
        */
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Error al ejecutar la compra de CDP: " << sqlite3_errmsg(db) << endl;
        } else {
            cout << "CDP comprado con éxito para el cliente " << idCliente << " por el monto de " << monto << endl;
        }
        sqlite3_finalize(stmt);
    }


void Database:: bloquearCuenta(int idCuenta) {
        
        const char* sqlUpdate = "UPDATE Cuentas SET Bloqueada = 1 WHERE IdCuenta = ?;"; // Se pone en 1 el indicador en la tabla SQL sobre el estado de bloqueo de la cuenta
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sqlUpdate, -1, &stmt, nullptr) != SQLITE_OK) {
            cerr << "Error al preparar la sentencia SQL para bloquear cuenta: " << sqlite3_errmsg(db) << endl;
            return;
        }

        sqlite3_bind_int(stmt, 1, idCuenta);

        // Se maneja la lógica del bloqueo de la cuenta
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Error al bloquear la cuenta " << idCuenta << ": " << sqlite3_errmsg(db) << endl;
        } else {
            cout << "Cuenta " << idCuenta << " bloqueada exitosamente." << endl;
        }
        sqlite3_finalize(stmt);
    }

void Database::desbloquearCuenta(int idCuenta) {
        
        const char* sqlUpdate = "UPDATE Cuentas SET Bloqueada = 0 WHERE IdCuenta = ?;"; // Se pone en 0 el indicador en la tabla SQL sobre el estado de bloqueo de la cuenta

        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sqlUpdate, -1, &stmt, nullptr) != SQLITE_OK) {
            cerr << "Error al preparar la sentencia SQL para desbloquear cuenta: " << sqlite3_errmsg(db) << endl;
            return;
        }

        sqlite3_bind_int(stmt, 1, idCuenta);

        // Se manejan los casos de éxito y error
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Error al desbloquear la cuenta " << idCuenta << ": " << sqlite3_errmsg(db) << endl;
        } else {
            cout << "Cuenta " << idCuenta << " desbloqueada exitosamente" << endl;
        }
        sqlite3_finalize(stmt);
        }

void Database::verRegistroTransacciones(){

        // Se seleccionan todos los campos de la tabla Transacciones
        const char* sqlSelect = "SELECT * FROM Transacciones;";

        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sqlSelect, -1, &stmt, nullptr) != SQLITE_OK) {
            cerr << "Error al preparar la consulta para ver el registro de transacciones: " << sqlite3_errmsg(db) << endl;
            return;
        }


        cout << "Registro de Transacciones:" << endl;
        cout << "----------------------------------------" << endl; // Línea para facilitar la revisión de la tabla en terminal
        // En este bucle, cada columna de la fila actual será extraída, esto para cada fila encontrada
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int idTransaccion = sqlite3_column_int(stmt, 0);
            int idCliente = sqlite3_column_int(stmt, 1);
            const unsigned char* tipo = sqlite3_column_text(stmt, 2);
            double monto = sqlite3_column_double(stmt, 3);
            const unsigned char* fecha = sqlite3_column_text(stmt, 4);

            cout << "ID Transacción: " << idTransaccion << " | Cliente: " << idCliente
                 << " | Tipo: " << tipo << " | Monto: " << monto << " | Fecha: " << fecha << endl;
        }
        cout << "----------------------------------------" << endl; // Línea para facilitar la revisión de la tabla en terminal

        sqlite3_finalize(stmt);

    }