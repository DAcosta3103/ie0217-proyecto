#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <sqlite3.h>
#include <string>
#include <iostream>
using namespace std;

class Database {

private:
    sqlite3* db;
    bool conectarDB(const string& nombreDB);
    void cerrarDB();

public:
    Database();
    ~Database();
    
    bool ejecutarSQL(const char *sql);
    void realizarDeposito(int IdCuenta,double monto);
    void realizarRetiro(int IdCuenta,double monto);
    void realizarTransferencia(double monto);
    void realizarPagoServicios(double monto);
    void comprarCDP(double monto);
    void consultarTipoCambio();
    void bloquearCuenta(int cuentaId);
    void desbloquearCuenta(int cuentaId);
    void verRegistroTransacciones();

    // Métodos para gestión de préstamos
    void consultarTiposPrestamos();
    void consultarFrecuenciaPagos();
    void mostrarCuotasYDesglose();
    void actualizarSaldoPrestamo(double nuevoSaldo);
    void calcularIntereses(double montoPrestamo);
    void mostrarMetodosPago();
    void verInformacionPrestamo(int prestamoId);

};  
#endif // DATABASE_HPP
