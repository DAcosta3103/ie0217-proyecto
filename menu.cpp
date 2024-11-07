#include <iostream>
#include "menu.hpp"
#include "database.hpp"
using namespace std;

void MenuAtencionAlCliente() {
    Database db;
    int subOpcion;
    do {
        cout << "\n Menú para atención al cliente, elija una opción" << endl;
        cout << "1. Depósitos a la cuenta" << endl;
        cout << "2. Retiros a la cuenta" << endl;
        cout << "3. Transferencia entre cuentas" << endl;
        cout << "4. Pago de servicios" << endl;
        cout << "5. Compra de CDP (Créditos de depósitos a plazo)" << endl;
        cout << "6. Consultar el tipo de cambio" << endl;
        cout << "7. Bloqueo o desbloqueo de cuentas" << endl;
        cout << "8. Ver el registro de transacciones" << endl;
        cout << "9. Regresar al menú principal" << endl;
        cout << "Seleccione una opción: ";
        cin >> subOpcion;

        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            cout << "Entrada no válida. Por favor, ingrese un número" << endl;
            continue; 
        }

        switch (subOpcion) {
            case 1:
            int IdCuenta;
            double monto;
            cout << "Ingrese el numero de identificion de la cuenta a la que quiere hacer el deposito: "<< endl;
            cin >> IdCuenta;
            cout << "Ingrese el monto a depositar: "<< endl;
            cin >> monto;

            db.realizarDeposito(IdCuenta, monto);
            break;

            case 2:
            cout << "Ingrese el numero de identificion de la cuenta a la que quiere hacer el retiro: "<< endl;
            cin >> IdCuenta;
            cout << "Ingrese el monto a retirar: "<< endl;
            cin >> monto;

            db.realizarRetiro(IdCuenta, monto);
            break;
            
            case 9:
                cout << "Regresando al menú de módulos" << endl;
                break;            
        }
    } while (subOpcion != 9); 
}

void MenuGestionPrestamos() {
    int subOpcion;
    do {
        cout << "\n Menú para le gestión de préstamos" << endl;
        cout << "1. Tipos de préstamos a solicitar" << endl;
        cout << "2. Consultar frecuencia de pagos" << endl;
        cout << "3. Cuotas y desgloce" << endl;
        cout << "4. Pago de servicios" << endl;
        cout << "5. Actualización del saldo de préstamo" << endl;
        cout << "6. Cálculo de intereses" << endl;
        cout << "7. Métodos de pago" << endl;
        cout << "8. Ver información de préstamo" << endl;
        cout << "9. Regresar al menú principal" << endl;
        cout << "Seleccione una opción: ";
        cin >> subOpcion;

        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            cout << "Entrada no válida. Por favor, ingrese un número" << endl;
            continue; 
        }

        switch (subOpcion) {
            case 1:
            SubMenuTipoPrestamos();
            break;

            case 9:
                cout << "Regresando al menú de módulos" << endl;
                break;            
        }
    } while (subOpcion != 9);
}

void SubMenuTipoPrestamos(){
    int subOpcion;

    do {
        cout << "\nElija una opción de préstamo" << endl;
        cout << "1. Préstamo personal" << endl;
        cout << "2. Préstamo prendario" << endl;
        cout << "3. Préstamo hipotecario" << endl;
        cout << "4. Regresar al menú de gestión de préstamos";
        cout << "\nSeleccione una opción: ";
        cin >> subOpcion;

        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            cout << "Entrada no válida. Por favor, ingrese un número" << endl;
            continue; 
        }
        
        switch (subOpcion){}




    } while (subOpcion =! 4);
}