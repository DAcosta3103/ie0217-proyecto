#include "../include/database.hpp"
#include "../include/menu.hpp"
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <string.h>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

/**
 * @brief Función para consultar los tipos de préstamos disponibles en el banco
 */
void Database::consultarTiposPrestamos() {
    SubMenuTipoPrestamos(); /// el codigo de esto esta en menu.cpp
}


/**
 * @brief Función para mostrar las cuentas y desglose 
 * 
 * Se muestran los detalles de cada préstamo
 */
void Database::consultarFrecuenciaPagos(int IdPrestamo) {
    if (IdPrestamo <= 0) {
        cout << "\nConsultar frecuencia de pagos" << endl;
        cout << "Ingrese el ID del préstamo del cual quiere consultar la frecuencia de pagos: ";
        cin >> IdPrestamo;
        if (cin.fail() || IdPrestamo <= 0) {
            cerr << "ID inválido. Por favor, intente de nuevo." << endl;
            cin.clear(); 
            cin.ignore(); 
            return;
        }
    }

    string sqlQuery = "SELECT Frecuencia FROM Creditos WHERE IdPrestamo = " + to_string(IdPrestamo) + ";";

    sqlite3_stmt* stmt;


    int result = sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << endl;
        return;
    }


    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* frecuencia = sqlite3_column_text(stmt, 0); 
        cout << "La frecuencia de pagos para el préstamo con ID " << IdPrestamo
             << " es " << (frecuencia ? reinterpret_cast<const char*>(frecuencia) : "No disponible") << endl;
    } else {
        cerr << "No hay prestamos registrados con el ID " << IdPrestamo << endl;
    }

    sqlite3_finalize(stmt);
}

/**
 * @brief Función para calcular los intereses
 * 
 * Los intereses calculados pueden referirse a un tipo de préstamo en específico, o bien a un CDP
 * @param IdPrestamo 
 */
void Database::calcularIntereses(double IdPrestamo) {
    int opcion;
    
    do {
        cout << "\nCalculadora de intereses" << endl;
        cout << "1. Calcular intereses de un prestamo" << endl;
        cout << "2. Calcular intereses de un certificado a deposito (CDP)" << endl;
        cout << "3. Regresar al menu anterior" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        /// Verificar si la entrada es válida
        if (cin.fail()) {
            cin.clear();  /// Limpiar el error
            cin.ignore(1000, '\n');  /// Ignorar la entrada incorrecta
            cout << "Entrada no válida. Por favor, ingrese un número" << endl;
            continue;
        }

        switch (opcion) {
        case 1: {
            cout << "Ingrese el ID del préstamo para consultar: ";
            cin >> IdPrestamo;

            const char* sql = R"(
                SELECT Monto, TasaInteres, CuotasPagadas, Frecuencia
                FROM Creditos
                WHERE IdPrestamo = ?;
            )";

            sqlite3_stmt* stmt;
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
                cerr << "Error preparando la consulta: " << sqlite3_errmsg(db) << endl;
                break;
            }

            sqlite3_bind_int(stmt, 1, IdPrestamo);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                double monto = sqlite3_column_double(stmt, 0);
                double tasaInteres = sqlite3_column_double(stmt, 1);
                int cuotasPagadas = sqlite3_column_int(stmt, 2);
                const char* frecuencia = (const char*)sqlite3_column_text(stmt, 3);

                int cuotasPorAnio = 0;
                if (strcmp(frecuencia, "Quincenal") == 0)
                    cuotasPorAnio = 24;
                else if (strcmp(frecuencia, "Mensual") == 0)
                    cuotasPorAnio = 12;
                else if (strcmp(frecuencia, "Trimestral") == 0)
                    cuotasPorAnio = 4;
                else if (strcmp(frecuencia, "Anual") == 0)
                    cuotasPorAnio = 1;

                if (cuotasPorAnio == 0) {
                    cerr << "Error: Frecuencia inválida en el registro del crédito." << endl;
                    sqlite3_finalize(stmt);
                    break;
                }


                double tasaPorPeriodo = (tasaInteres / 100.0) / cuotasPorAnio;


                double tiempo = static_cast<double>(cuotasPagadas) / cuotasPorAnio;


                double montoFinal = monto * pow(1 + tasaPorPeriodo, cuotasPorAnio * tiempo);

                double interesAcumulado = montoFinal - monto;

                cout << "\n--- Resumen del Crédito ---" << endl;
                cout << "ID del Préstamo: " << IdPrestamo << endl;
                cout << "Monto: " << monto << endl;
                cout << "Tasa de Interés: " << tasaInteres << "%" << endl;
                cout << "Cuotas Pagadas: " << cuotasPagadas << endl;
                cout << "Frecuencia: " << frecuencia << endl;
                cout << "Interés Acumulado: " << interesAcumulado << endl;

            } else {
                cout << "No existe el préstamo con el ID ingresado." << endl;
            }

            sqlite3_finalize(stmt);
            break;
            }

        case 2:
            /// Lógica para calcular los intereses de un certificado a depósito
            double monto;
            int plazo;
            double interesCDP;
            cout << "Favor tener en cuenta que el banco maneja una tasa de interés del 1%." << endl;

            cout << "Ingrese el monto que desea depositar: ";
            cin >> monto;

            cout << "ingrese el plazo, en meses, que durará el depósito: ";
            cin >> plazo;

            interesCDP = (monto*plazo*0.01)/365;
            
            cout << "El interés generado por un CDP con los parámetros especificados es de " << interesCDP << "colones" << endl;
            break;
        case 3:
            cout << "Regresando al menú anterior." << endl;
            break;
        default:
            cout << "Opción no válida. Intente de nuevo" << endl;
            break;
        }

    } while (opcion != 3);  /// El bucle se repite hasta que la opción sea 3 (salir)
}


/**
 * @brief Función para mostrar las cuentas y desglose 
 * 
 * Se muestran los detalles de cada préstamo
 */
void Database::mostrarCuotasYDesglose() {
    /// Consulta SQL para obtener todos los préstamos con sus detalles
    const char* sqlQuery = R"(
        SELECT IdPrestamo, IdCliente, Monto, Cuota, CuotasPagadas, Plazo, TasaInteres, Tipo, Moneda
        FROM Creditos;
    )";

    sqlite3_stmt* stmt;
    /// Preparar la sentencia SQL
    if (sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error al preparar la consulta de préstamos: " << sqlite3_errmsg(db) << endl;
        return;
    }

    cout << "\n--- Desglose de Préstamos ---" << endl;
    /// Iterar por cada préstamo en la base de datos
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int idPrestamo = sqlite3_column_int(stmt, 0);
        int idCliente = sqlite3_column_int(stmt, 1);
        double monto = sqlite3_column_double(stmt, 2);
        double cuota = sqlite3_column_double(stmt, 3);
        int cuotasPagadas = sqlite3_column_int(stmt, 4);
        int plazo = sqlite3_column_int(stmt, 5);
        double tasaInteres = sqlite3_column_double(stmt, 6);
        const char* tipo = (const char*)sqlite3_column_text(stmt, 7);
        const char* moneda = (const char*)sqlite3_column_text(stmt, 8);

        /// Formatear y mostrar detalles de cada préstamo
        cout << "Préstamo ID: " << idPrestamo << endl;
        cout << "Cliente ID: " << idCliente << endl;
        cout << "Tipo: " << tipo << endl;
        cout << "Monto: " << monto << " " << moneda << endl;
        cout << "Cuota Mensual: " << cuota << endl;
        cout << "Cuotas Pagadas: " << cuotasPagadas << "/" << plazo << endl;
        cout << "Tasa de Interés: " << tasaInteres << "%" << endl;
        cout << "------------------------" << endl;
    }

    sqlite3_finalize(stmt);
}

/**
 * @brief Función para realizar abonos a un préstamo
 * 
 * @param nuevoSaldo Monto a abonar del préstamo
 */
void Database::actualizarSaldoPrestamo(double nuevoSaldo) {
    /// Verificar que el nuevo saldo sea válido
    if (nuevoSaldo < 0) {
        cerr << "Error: El saldo del préstamo no puede ser negativo." << endl;
        return;
    }

    /// Consulta para actualizar el saldo de un préstamo
    const char* sqlUpdate = R"(
        UPDATE Creditos 
        SET Monto = ? 
        WHERE IdPrestamo = (
            SELECT MAX(IdPrestamo) 
            FROM Creditos
        );
    )";

    sqlite3_stmt* stmt;
    /// Preparar la sentencia SQL
    if (sqlite3_prepare_v2(db, sqlUpdate, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error al preparar la actualización del saldo: " << sqlite3_errmsg(db) << endl;
        return;
    }

    /// Vincular el nuevo saldo
    sqlite3_bind_double(stmt, 1, nuevoSaldo);

    /// Ejecutar la actualización
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Error al actualizar el saldo del préstamo: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "Saldo del préstamo actualizado exitosamente a " << nuevoSaldo << endl;
    }

    sqlite3_finalize(stmt);
}

/**
 * @brief Función para mostrar los métodos de pago para préstamos
 * 
 */
void Database::mostrarMetodosPago() {
    /// Definir métodos de pago predeterminados
    const char* metodosPago[] = {
        "Transferencia Bancaria", 
        "Pago en Ventanilla", 
        "Débito Automático", 
        "Pago en Línea"
    };

    cout << "\n--- Métodos de Pago Disponibles ---" << endl;
    /// Mostrar cada método de pago
    for (int i = 0; i < 4; ++i) {
        cout << i+1 << ". " << metodosPago[i] << endl;
    }
}

/**
 * @brief Función para ver la información referente a un préstamo en específico
 * 
 * @param prestamoId Número de identificación del préstamo a consultar
 */
void Database::verInformacionPrestamo(int prestamoId) {
    ///int prestamoId;

    /// Pedir al usuario el ID del préstamo
    cout << "Ingrese el ID del préstamo que desea consultar: ";
    cin >> prestamoId;

    /// Consulta SQL para obtener información detallada de un préstamo específico
    const char* sqlQuery = R"(
        SELECT 
            c.IdPrestamo, 
            c.IdCliente, 
            cl.Nombre, 
            c.Monto, 
            c.Frecuencia, 
            c.Plazo, 
            c.Cuota, 
            c.CuotasPagadas, 
            c.TasaInteres, 
            c.Tipo, 
            c.Moneda
        FROM Creditos c
        JOIN Clientes cl ON c.IdCliente = cl.IdCliente
        WHERE c.IdPrestamo = ?;
    )";

    sqlite3_stmt* stmt;

    /// Preparar la sentencia SQL
    if (sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error al preparar la consulta de información del préstamo: " << sqlite3_errmsg(db) << endl;
        return;
    }

    /// Vincular el ID de préstamo ingresado por el usuario
    sqlite3_bind_int(stmt, 1, prestamoId);

    /// Verificar si se encontró el préstamo
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        /// Extraer información del préstamo
        int idPrestamo = sqlite3_column_int(stmt, 0);
        int idCliente = sqlite3_column_int(stmt, 1);
        const char* nombreCliente = (const char*)sqlite3_column_text(stmt, 2);
        double monto = sqlite3_column_double(stmt, 3);
        const char* frecuencia = (const char*)sqlite3_column_text(stmt, 4);
        int plazo = sqlite3_column_int(stmt, 5);
        double cuota = sqlite3_column_double(stmt, 6);
        int cuotasPagadas = sqlite3_column_int(stmt, 7);
        double tasaInteres = sqlite3_column_double(stmt, 8);
        const char* tipo = (const char*)sqlite3_column_text(stmt, 9);
        const char* moneda = (const char*)sqlite3_column_text(stmt, 10);

        /// Mostrar información detallada del préstamo
        cout << "\n--- Detalles del Préstamo ---" << endl;
        cout << "ID Préstamo: " << idPrestamo << endl;
        cout << "Cliente: " << nombreCliente << " (ID: " << idCliente << ")" << endl;
        cout << "Tipo de Préstamo: " << tipo << endl;
        cout << "Monto: " << monto << " " << moneda << endl;
        cout << "Frecuencia de Pago: " << frecuencia << endl;
        cout << "Plazo Total: " << plazo << " cuotas" << endl;
        cout << "Cuotas Pagadas: " << cuotasPagadas << endl;
        cout << "Cuota Mensual: " << cuota << endl;
        cout << "Tasa de Interés: " << tasaInteres << "%" << endl;

        /// Calcular y mostrar saldo pendiente
        double saldoPendiente = monto - (cuotasPagadas * cuota);
        cout << "Saldo Pendiente: " << saldoPendiente << " " << moneda << endl;
    } else {
        /// Mostrar mensaje si no se encuentra el préstamo
        cout << "No se encontró préstamo con ID " << prestamoId << endl;
    }

    /// Liberar recursos de la consulta preparada
    sqlite3_finalize(stmt);
}

/**
 * @brief Función para generar un reporte de un préstamo en específico
 * 
 * @param prestamoId Número de identificación del préstamo a consultar
 */
void Database::generarReportePrestamo(int prestamoId) {
    /// Consulta SQL para obtener detalles completos del préstamo con información del cliente
    const char* sqlQuery = R"(
        SELECT 
            c.IdPrestamo,     
            cl.Nombre,        
            c.Monto,             
            c.TasaInteres,    
            c.Plazo,             
            c.Cuota,             
            c.CuotasPagadas,     
            c.Frecuencia,     
            c.Moneda          
        FROM Creditos c
        JOIN Clientes cl ON c.IdCliente = cl.IdCliente
        WHERE c.IdPrestamo = ?;
    )";

    sqlite3_stmt* stmt;

    /// Preparar la sentencia SQL
    if (sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error al preparar la consulta de reporte de préstamo: " << sqlite3_errmsg(db) << endl;
        return;
    }

    /// Vincular el ID de préstamo a la consulta
    sqlite3_bind_int(stmt, 1, prestamoId);

    /// Verificar si se encontró el préstamo
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        /// Extraer información del préstamo
        int idPrestamo = sqlite3_column_int(stmt, 0);
        const char* nombreCliente = (const char*)sqlite3_column_text(stmt, 1);
        double montoInicial = sqlite3_column_double(stmt, 2);
        double tasaInteres = sqlite3_column_double(stmt, 3);
        int plazoTotal = sqlite3_column_int(stmt, 4);
        double cuotaMensual = sqlite3_column_double(stmt, 5);
        int cuotasPagadas = sqlite3_column_int(stmt, 6);
        
        /// Convertir frecuencia a string para comparación segura
        string frecuencia((const char*)sqlite3_column_text(stmt, 7));
        const char* moneda = (const char*)sqlite3_column_text(stmt, 8);

        /// Generar nombre de archivo de reporte único
        string nombreArchivo = "reporte_prestamo_" + to_string(idPrestamo) + ".txt";
        
        /// Abrir archivo de reporte
        ofstream reporteArchivo(nombreArchivo);
        
        /// Verificar si se pudo crear el archivo
        if (!reporteArchivo.is_open()) {
            cerr << "Error al crear el archivo de reporte." << endl;
            sqlite3_finalize(stmt);
            return;
        }

        /// Calcular factor de periodicidad según la frecuencia de pago
        double factorPeriodicidad = (frecuencia == "Mensual" ? 12.0 : 
                                     frecuencia == "Trimestral" ? 4.0 : 
                                     frecuencia == "Anual" ? 1.0 : 24.0);

        /// Calcular tasa de interés por periodo
        double tasaPeriodo = (tasaInteres / 100.0) / factorPeriodicidad;

        /// Encabezado del reporte
        reporteArchivo << "===== REPORTE DETALLADO DE PRÉSTAMO =====" << endl;
        reporteArchivo << "ID Préstamo: " << idPrestamo << endl;
        reporteArchivo << "Cliente: " << nombreCliente << endl;
        reporteArchivo << "Monto Inicial: " << montoInicial << " " << moneda << endl;
        reporteArchivo << "Tasa de Interés: " << tasaInteres << "%" << endl;
        reporteArchivo << "Plazo Total: " << plazoTotal << " cuotas" << endl;
        reporteArchivo << "Frecuencia de Pago: " << frecuencia << endl;
        reporteArchivo << "Cuota: " << cuotaMensual << " " << moneda << endl;
        reporteArchivo << endl;

        /// Tabla de amortización detallada
        reporteArchivo << "=== TABLA DE AMORTIZACIÓN ===" << endl;
        reporteArchivo << left 
                       << setw(10) << "Cuota #" 
                       << setw(15) << "Capital" 
                       << setw(15) << "Intereses" 
                       << setw(15) << "Saldo Restante" 
                       << endl;
        reporteArchivo << string(55, '-') << endl;

        /// Variables para cálculo de amortización
        double saldoRestante = montoInicial;
        double totalCapital = 0.0;
        double totalIntereses = 0.0;

        /// Generar tabla de amortización
        for (int i = 1; i <= cuotasPagadas; ++i) {
            /// Calcular intereses de la cuota actual
            double interes = saldoRestante * tasaPeriodo;
            
            /// Calcular abono a capital
            double capital = cuotaMensual - interes;
            
            /// Actualizar saldo restante
            saldoRestante -= capital;
            
            /// Acumular totales
            totalCapital += capital;
            totalIntereses += interes;

            /// Escribir línea en el reporte
            reporteArchivo << left 
                           << setw(10) << i 
                           << setw(15) << fixed << setprecision(2) << capital 
                           << setw(15) << interes 
                           << setw(15) << max(0.0, saldoRestante)  /// Evitar saldos negativos 
                           << endl;
        }

        /// Resumen final
        reporteArchivo << endl;
        reporteArchivo << "=== RESUMEN ===" << endl;
        reporteArchivo << "Cuotas Pagadas: " << cuotasPagadas << " de " << plazoTotal << endl;
        reporteArchivo << "Total Pagado en Capital: " << fixed << setprecision(2) << totalCapital << " " << moneda << endl;
        reporteArchivo << "Total Pagado en Intereses: " << fixed << setprecision(2) << totalIntereses << " " << moneda << endl;
        
        /// Cerrar archivo
        reporteArchivo.close();
        
        /// Confirmar generación de reporte
        cout << "Reporte generado exitosamente en " << nombreArchivo << endl;
    } else {
        /// Mensaje si no se encuentra el préstamo
        cout << "No se encontró préstamo con ID " << prestamoId << endl;
    }

    /// Liberar recursos de la consulta
    sqlite3_finalize(stmt);
}