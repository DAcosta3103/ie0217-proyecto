#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <sqlite3.h>
#include <string>
#include <iostream>
using namespace std;
//definicion de la clae database y sus metodos para manipular la base de datos

/**
 * @brief Clase para la base de datos
 */
class Database {
private:
//puntero que representa la base de datos y metodos privados para conectar y desconectar
    sqlite3* db;
    /** 
    * @brief Funcion para conectar la base de datos
    * @param nombreDB Nombre para la base de datos
    * @return True si esta conectada
    */ 
    bool conectarDB(const string& nombreDB);

    /**
     * @brief Funcion para cerrar la base de datos
     * 
     */
    void cerrarDB();

public:
    /**
     * @brief Construtor para la clase Database
     * 
     */
    Database();

    /**
     * @brief Destructor para la clase Database
     * 
     */
    ~Database();

    /**
     * @brief Funcion para ejecutar las sentencias SQL en el script
     * 
     * @param sql 
     * @return true 
     * @return false 
     */
    bool ejecutarSQL(const char *sql);

    /**
     * @brief Funcion para realizar depositos a una cuenta
     * 
     * @param IdCuenta Número de identificacion de la cuenta
     * @param monto Monto a depositar
     * @param IdCliente Número de identificación del cliente
     */
    void realizarDeposito(int IdCuenta,double monto, int IdCliente);

    /**
     * @brief Funcion para realizar retiros desde una cuenta
     * 
     * @param IdCuenta Número de identificacion de la cuenta 
     * @param monto Monto a depositar
     * @param IdCliente Número de identificación del cliente
     */
    void realizarRetiro(int IdCuenta,double monto, int IdCliente);

    /**
     * @brief Funcion para realizar transferencias entre cuentas
     * 
     * @param idCuentaOrigen Número de identificación de la cuenta de origen
     * @param idCuentaDestino Número de identificación de la cuenta a recibir el dinero
     * @param IdCuenta Número de identificacion de la cuenta
     * @param monto Monto a depositar
     * @param IdCliente Número de identificación del cliente
     */
    void realizarTransferencia(int idCuentaOrigen, int idCuentaDestino, double monto, int IdCliente, int IdCuenta);

    /**
     * @brief Funcion para pagar distintos servicios básicos
     * 
     * @param idCuentaCliente Número de identificación de la cuenta del cliente
     * @param monto Monto a pagar
     * @param IdCliente Número de identificación del cliente
     */
    void realizarPagoServicios(int idCuentaCliente, double monto, int IdCliente);

    /**
     * @brief Funcion para consultar el tipo de cambio
     * 
     * Brinda la conversión de dólares a colones
     */
    void consultarTipoCambio();

    /**
     * @brief Funcion para comprar Certificados de Depósito a Plazo (CDPs)
     * 
     * @param idCliente Número de identificación del cliente
     * @param monto Monto a depositar
     * @param plazo Plazo, en meses, del depósito
     */
    void comprarCDP(int idCliente, double monto, int plazo);

    /**
     * @brief Funcion para bloquear una cuenta
     * 
     * En caso de sospecha de fraude, es posible bloquear la cuenta por razones de seguridad
     * 
     * @param cuentaId Número de identificación de la cuenta
     */
    void bloquearCuenta(int cuentaId);

    /**
     * @brief Función para ver el registro de transacciones realizadas
     * 
     */
    void verRegistroTransacciones();

    // -------------------Métodos para gestión de préstamos -----------------

    /**
     * @brief Función para consultar los tipos de préstamos disponibles en el banco
     */
    void consultarTiposPrestamos();
    
    /**
     * @brief Función para consultar la frecuencia de pagos de un préstamo en específico
     * 
     * @param IdPrestamo Número de identificación del préstamo a consultar
     */
    void consultarFrecuenciaPagos(int IdPrestamo);

    /**
     * @brief Función para mostrar las cuentas y desglose 
     * 
     * Se muestran los detalles de cada préstamo
     */
    void mostrarCuotasYDesglose();

    /**
     * @brief Función para realizar abonos a un préstamo
     * 
     * @param nuevoSaldo Monto a abonar del préstamo
     */
    void actualizarSaldoPrestamo(double nuevoSaldo);

    /**
     * @brief Función para calcular los intereses
     * 
     * Los intereses calculados pueden referirse a un tipo de préstamo en específico, o bien a un CDP
     * @param IdPrestamo 
     */
    void calcularIntereses(double IdPrestamo);

    /**
     * @brief Función para mostrar los métodos de pago para préstamos
     * 
     */
    void mostrarMetodosPago();

    /**
     * @brief Función para ver la información referente a un préstamo en específico
     * 
     * @param prestamoId Número de identificación del préstamo a consultar
     */
    void verInformacionPrestamo(int prestamoId);

    /**
     * @brief Función para generar un reporte de un préstamo en específico
     * 
     * @param prestamoId Número de identificación del préstamo a consultar
     */
    void generarReportePrestamo(int prestamoId);
};  


#endif // DATABASE_HPP
