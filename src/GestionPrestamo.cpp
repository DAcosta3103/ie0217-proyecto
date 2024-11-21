#include "../include/database.hpp"
#include "../include/menu.hpp"
#include <sqlite3.h>
#include <string>
#include <iostream>
using namespace std;

void Database::consultarTiposPrestamos() {
    SubMenuTipoPrestamos(); // el codigo de esto esta en menu.cpp
}


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

void Database::calcularIntereses(double montoPrestamo){}
