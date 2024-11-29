#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <sqlite3.h>
#include <string>
#include <iostream>
using namespace std;
//definicion de la clae database y sus metodos para manipular la base de datos
class Database {
private:
//puntero que representa la base de datos y metodos privados para conectar y desconectar
    sqlite3* db;
    bool conectarDB(const string& nombreDB);
    void cerrarDB();

public:
    Database();
    ~Database();

    bool ejecutarSQL(const char *sql);
    void realizarDeposito(int IdCuenta,double monto, int IdCliente);
    void realizarRetiro(int IdCuenta,double monto, int IdCliente);
    void realizarTransferencia(int idCuentaOrigen, int idCuentaDestino, double monto, int IdCliente, int IdCuenta);
    void realizarPagoServicios(int idCuentaCliente, double monto, int IdCliente);
    void consultarTipoCambio();
    void comprarCDP(int idCliente, double monto, int plazo);
    void bloquearCuenta(int cuentaId);
    void verRegistroTransacciones();

    // Métodos para gestión de préstamos
    void consultarTiposPrestamos();
    void consultarFrecuenciaPagos(int IdPrestamo);
    void mostrarCuotasYDesglose();
    void actualizarSaldoPrestamo(double nuevoSaldo);
    void calcularIntereses(double IdPrestamo);
    void mostrarMetodosPago();
    void verInformacionPrestamo(int prestamoId);
    void generarReportePrestamo(int prestamoId);
};  

//uníca funcion que queda por fuera de la clase database
#endif // DATABASE_HPP
