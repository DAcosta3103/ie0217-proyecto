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
void Database::realizarDeposito(int IdCuenta, double monto, int IdCliente) {
    // Sentencia SQL para actualizar el saldo de la cuenta
    const char* sqlUpdate = R"(
        UPDATE Cuentas
        SET Saldo = Saldo + ?
        WHERE IdCuenta = ?;
    )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sqlUpdate, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error al preparar la sentencia SQL para actualizar el saldo: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_double(stmt, 1, monto); 
    sqlite3_bind_int(stmt, 2, IdCuenta);

    // Ejecutamos la sentencia para actualizar el saldo
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Error al ejecutar la sentencia SQL: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    } else {
        cout << "Depósito de " << monto << " realizado exitosamente en la cuenta " << IdCuenta << "!" << endl;
    }

    sqlite3_finalize(stmt);  // Liberamos los recursos del statement

    // **Paso 1: Buscar el IdCliente vinculado a la IdCuenta**
    const char* sqlSelectCliente = R"(
        SELECT IdCliente FROM Cuentas WHERE IdCuenta = ?;
    )";

    sqlite3_stmt* stmtSelectCliente;
    if (sqlite3_prepare_v2(db, sqlSelectCliente, -1, &stmtSelectCliente, nullptr) != SQLITE_OK) {
        cerr << "Error al preparar la consulta SQL para obtener IdCliente: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_int(stmtSelectCliente, 1, IdCuenta);

    int IdClienteVinculado = -1;  // Variable para almacenar el IdCliente
    if (sqlite3_step(stmtSelectCliente) == SQLITE_ROW) {
        IdClienteVinculado = sqlite3_column_int(stmtSelectCliente, 0);
    } else {
        cerr << "No se encontró el IdCliente para la cuenta " << IdCuenta << endl;
        sqlite3_finalize(stmtSelectCliente);
        return;
    }

    sqlite3_finalize(stmtSelectCliente);  // Liberamos los recursos del statement

    // ahora para registrar la transaccion
    const char* sqlInsertTransaccion = R"(
        INSERT INTO Transacciones (IdCliente, Tipo, Monto, Fecha)
        VALUES (?, 'Deposito', ?, date('now'));
    )";

    sqlite3_stmt* stmtTransaccion;
    if (sqlite3_prepare_v2(db, sqlInsertTransaccion, -1, &stmtTransaccion, nullptr) != SQLITE_OK) {
        cerr << "Error al preparar la sentencia SQL para insertar la transacción: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_int(stmtTransaccion, 1, IdClienteVinculado);  // Usamos el IdCliente vinculado
    sqlite3_bind_double(stmtTransaccion, 2, monto);  // Monto de la transacción

    // Ejecutamos la inserción de la transacción
    if (sqlite3_step(stmtTransaccion) != SQLITE_DONE) {
        cerr << "Error al registrar la transacción en la tabla: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "Transacción registrada exitosamente en la tabla Transacciones." << endl;
    }

    sqlite3_finalize(stmtTransaccion);  // Liberamos los recursos del statement
}


// exactamente la misma logica del realizar deposito, solo que en el saldo de la sentencia
//se le resta al saldo en lugar de sumar
void Database::realizarRetiro(int IdCuenta, double monto, int IdCliente) {
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

       // Buscar el IdCliente vinculado a la IdCuenta
    const char* sqlSelectCliente = R"(
        SELECT IdCliente FROM Cuentas WHERE IdCuenta = ?;
    )";

    sqlite3_stmt* stmtSelectCliente;
    if (sqlite3_prepare_v2(db, sqlSelectCliente, -1, &stmtSelectCliente, nullptr) != SQLITE_OK) {
        cerr << "Error al preparar la consulta SQL para obtener IdCliente: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_int(stmtSelectCliente, 1, IdCuenta);

    int IdClienteVinculado = -1;  // Variable para almacenar el IdCliente
    if (sqlite3_step(stmtSelectCliente) == SQLITE_ROW) {
        IdClienteVinculado = sqlite3_column_int(stmtSelectCliente, 0);
    } else {
        cerr << "No se encontró el IdCliente para la cuenta " << IdCuenta << endl;
        sqlite3_finalize(stmtSelectCliente);
        return;
    }

    sqlite3_finalize(stmtSelectCliente);  // Liberamos los recursos del statement

    // ahora para registrar la transaccion
    const char* sqlInsertTransaccion = R"(
        INSERT INTO Transacciones (IdCliente, Tipo, Monto, Fecha)
        VALUES (?, 'Retiro', ?, date('now'));
    )";

    sqlite3_stmt* stmtTransaccion;
    if (sqlite3_prepare_v2(db, sqlInsertTransaccion, -1, &stmtTransaccion, nullptr) != SQLITE_OK) {
        cerr << "Error al preparar la sentencia SQL para insertar la transacción: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_int(stmtTransaccion, 1, IdClienteVinculado);  
    sqlite3_bind_double(stmtTransaccion, 2, monto);  

  
    if (sqlite3_step(stmtTransaccion) != SQLITE_DONE) {
        cerr << "Error al registrar la transacción en la tabla: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "Transacción registrada exitosamente en la tabla Transacciones." << endl;
    }

    sqlite3_finalize(stmtTransaccion);  // Liberamos los recursos del statement
    }

// Métodos para atención al cliente


void Database::realizarTransferencia(int idCuentaOrigen, int idCuentaDestino, double monto, int IdCliente, int IdCuenta) {
        
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
        realizarRetiro(idCuentaOrigen, monto,IdCuenta);
        realizarDeposito(idCuentaDestino, monto, IdCliente);
        cout << "Transferencia de " << monto << " realizada de cuenta " << idCuentaOrigen << " a cuenta " << idCuentaDestino << endl;

        //Buscar el IdCliente vinculado a la IdCuenta
    const char* sqlSelectCliente = R"(
        SELECT IdCliente FROM Cuentas WHERE IdCuenta = ?;
    )";

    sqlite3_stmt* stmtSelectCliente;
    if (sqlite3_prepare_v2(db, sqlSelectCliente, -1, &stmtSelectCliente, nullptr) != SQLITE_OK) {
        cerr << "Error al preparar la consulta SQL para obtener IdCliente: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_int(stmtSelectCliente, 1, IdCuenta);

    int IdClienteVinculado = -1;  // Variable para almacenar el IdCliente
    if (sqlite3_step(stmtSelectCliente) == SQLITE_ROW) {
        IdClienteVinculado = sqlite3_column_int(stmtSelectCliente, 0);
    } else {
        cerr << "No se encontró el IdCliente para la cuenta " << IdCuenta << endl;
        sqlite3_finalize(stmtSelectCliente);
        return;
    }

    sqlite3_finalize(stmtSelectCliente);  // Liberamos los recursos del statement

    // ahora para registrar la transaccion
    const char* sqlInsertTransaccion = R"(
        INSERT INTO Transacciones (IdCliente, Tipo, Monto, Fecha)
        VALUES (?, 'Deposito', ?, date('now'));
    )";

    sqlite3_stmt* stmtTransaccion;
    if (sqlite3_prepare_v2(db, sqlInsertTransaccion, -1, &stmtTransaccion, nullptr) != SQLITE_OK) {
        cerr << "Error al preparar la sentencia SQL para insertar la transacción: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_int(stmtTransaccion, 1, IdClienteVinculado);  // Usamos el IdCliente vinculado
    sqlite3_bind_double(stmtTransaccion, 2, monto);  // Monto de la transacción

    // Ejecutamos la inserción de la transacción
    if (sqlite3_step(stmtTransaccion) != SQLITE_DONE) {
        cerr << "Error al registrar la transacción en la tabla: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "Transacción registrada exitosamente en la tabla Transacciones." << endl;
    }

    sqlite3_finalize(stmtTransaccion);  // Liberamos los recursos del statement
    }   

    
    
void Database::realizarPagoServicios(int idCuentaCliente, double monto, int IdCliente) {

    const int idCuentaServicios = 999;
    int idCuentaOrigen = idCuentaCliente;  
    int idCuentaDestino = idCuentaServicios;

    realizarTransferencia(idCuentaOrigen, idCuentaDestino, monto, IdCliente, idCuentaServicios);

    cout << "\nPago de servicios por " << monto << " realizado desde la cuenta del cliente " 
         << idCuentaCliente << " hacia la cuenta de servicios " << idCuentaServicios << endl;
}



void Database::consultarTipoCambio(){

        // Se manejará un tipo de cambio fijo, el cual para recordar buenas épocas, será $1 = 500 CRC (sujeto a cambios)
        cout << "El tipo de cambio actual es de 500 CRC por 1 USD." << endl;
    }


void Database::comprarCDP(int idCliente, double monto, int plazo) {

    double interes;

    cout << "Ingrese el ID del cliente: ";
    cin >> idCliente;

    cout << "Ingrese el monto a invertir: ";
    cin >> monto;

    cout << "Ingrese el plazo en meses: ";
    cin >> plazo;

    interes = (monto*plazo*0.01)/365;

    // se maneja una tasa de interés de 1%
    const char* sqlInsertCDP = R"(
        INSERT INTO CDP (IdCliente, Monto, TasaInteres, Plazo, FechaInicio)
        VALUES (?, ?, 1.0, ?, date('now'));    
    )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sqlInsertCDP, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error al preparar la sentencia SQL para comprar CDP: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // Enlace de parámetros
    sqlite3_bind_int(stmt, 1, idCliente);
    sqlite3_bind_double(stmt, 2, monto);
    sqlite3_bind_int(stmt, 3, plazo);

    // Se maneja la lógica de compra
    /*
    Por implementar: Verificación de si el cliente tiene suficiente dinero en su cuenta
    */
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Error al ejecutar la compra de CDP: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "CDP comprado con éxito para el cliente " << idCliente << " por el monto de " << monto << " con un plazo de " << plazo << " meses." << endl;
        cout << "El interés que generará será de " << interes << "colones" << endl;
    }
    sqlite3_finalize(stmt);
}

void Database::bloquearCuenta(int idCuenta) {
    cout << "Ingrese el ID de la cuenta que desea bloquear o desbloquear: ";
    cin >> idCuenta;

    // Primero, verificamos el estado actual de la cuenta
    const char* sqlCheckStatus = "SELECT Bloqueada FROM Cuentas WHERE IdCuenta = ?;";
    sqlite3_stmt* stmtCheck;
    if (sqlite3_prepare_v2(db, sqlCheckStatus, -1, &stmtCheck, nullptr) != SQLITE_OK) {
        cerr << "Error al preparar la sentencia SQL para verificar el estado de la cuenta: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_int(stmtCheck, 1, idCuenta);

    int bloqueada = -1;
    if (sqlite3_step(stmtCheck) == SQLITE_ROW) {
        bloqueada = sqlite3_column_int(stmtCheck, 0);  // Obtener el estado de la cuenta
    }

    sqlite3_finalize(stmtCheck);

    // Verificamos si encontramos la cuenta
    if (bloqueada == -1) {
        cerr << "Cuenta no encontrada con el ID: " << idCuenta << endl;
        return;
    }

    // Definimos la lógica para bloquear o desbloquear la cuenta
    const char* sqlUpdate = nullptr;
    if (bloqueada == 1) {
        // Si la cuenta está bloqueada, la desbloqueamos (Bloqueada = 0)
        sqlUpdate = "UPDATE Cuentas SET Bloqueada = 0 WHERE IdCuenta = ?;";
        cout << "Cuenta con ID " << idCuenta<<" desbloqueada" << endl;
    } else {
        // Si la cuenta no está bloqueada, la bloqueamos (Bloqueada = 1)
        sqlUpdate = "UPDATE Cuentas SET Bloqueada = 1 WHERE IdCuenta = ?;";
        cout << "Cuenta con ID " << idCuenta<<" bloqueada" << endl;
    }

    sqlite3_stmt* stmtUpdate;
    if (sqlite3_prepare_v2(db, sqlUpdate, -1, &stmtUpdate, nullptr) != SQLITE_OK) {
        cerr << "Error al preparar la sentencia SQL para actualizar el estado de la cuenta: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_int(stmtUpdate, 1, idCuenta);

    // Ejecutamos la actualización
    if (sqlite3_step(stmtUpdate) != SQLITE_DONE) {
        cerr << "Error al actualizar la cuenta " << idCuenta << ": " << sqlite3_errmsg(db) << endl;
    }
    sqlite3_finalize(stmtUpdate);
}


void Database::verRegistroTransacciones() {
    
    const char* sqlSelect = "SELECT IdTransaccion, IdCliente, Tipo, Monto, Fecha FROM Transacciones;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sqlSelect, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error al preparar la consulta para ver el registro de transacciones: " << sqlite3_errmsg(db) << endl;
        return;
    }

    cout << "Registro de Transacciones:" << endl;
    cout << "----------------------------------------" << endl;

    // En este bucle, cada columna de la fila actual será extraída, esto para cada fila encontrada
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int idTransaccion = sqlite3_column_int(stmt, 0);
        int idCliente = sqlite3_column_int(stmt, 1);
        const unsigned char* tipo = sqlite3_column_text(stmt, 2);
        int monto = sqlite3_column_int(stmt, 3);  
        const char* fecha = (const char*) sqlite3_column_text(stmt, 4);  

        cout << "ID Transacción: " << idTransaccion << " | Cliente: " << idCliente
             << " | Tipo: " << tipo << " | Monto: " << monto << " | Fecha: " << fecha << endl;
    }
    cout << "----------------------------------------" << endl;

    sqlite3_finalize(stmt);
}
