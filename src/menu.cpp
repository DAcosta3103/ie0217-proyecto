#include <iostream>
#include "../include/menu.hpp"
#include "../include/database.hpp"
using namespace std;

void MenuAtencionAlCliente() {
    Database db;
    int subOpcion;
    int opcionSubmenu;
    int IdCuenta;
    int idCuentaDestino;
    int idCuentaOrigen;
    int idCuentaCliente;
    double monto;
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
            cout << "Ingrese el numero de identificion de la cuenta a la que quiere hacer el deposito: ";
            cin >> IdCuenta;
            cout << "Ingrese el monto a depositar: ";
            cin >> monto;

            db.realizarDeposito(IdCuenta, monto);
            break;

            case 2:
            cout << "Ingrese el numero de identificion de la cuenta a la que quiere hacer el retiro: ";
            cin >> IdCuenta;
            cout << "Ingrese el monto a retirar: ";
            cin >> monto;

            db.realizarRetiro(IdCuenta, monto);
            break;

            case 3:
            cout << "Ingrese el numero de identificion de la cuenta de origen de los fondos: ";
            cin >> idCuentaOrigen;
            cout << "Ingrese el numero de identificion de la cuenta destino para la tranferencia: ";
            cin >> idCuentaDestino;
            cout << "Ingrese el monto a transferir: ";
            cin >> monto;

            db.realizarTransferencia(idCuentaOrigen, idCuentaDestino,monto);
            break;
            case 4:
            do {
                    cout << "\nCentro de pago de servicios:\n";
                    cout << "1. Agua y luz\n";
                    cout << "2. Marchamo\n";
                    cout << "3. Internet\n";
                    cout << "4. Impuesto municipal\n";
                    cout << "Seleccione una opción del submenú: ";
                    cin >> opcionSubmenu;

                    switch (opcionSubmenu) {
                        case 1:

                        cout << "Ingrese el numero de identificion de la cuenta de origen de los fondos: ";
                        cin >> idCuentaCliente;  
                        cout << "Ingrese el monto a cancelar: ";
                        cin >> monto;
                        db.realizarPagoServicios(idCuentaCliente,monto);
                            break;
                           
                        case 2:
                        cout << "Ingrese el numero de identificion de la cuenta de origen de los fondos: ";
                        cin >> idCuentaCliente;  
                        cout << "Ingrese el monto a cancelar: ";
                        cin >> monto;
                        db.realizarPagoServicios(idCuentaCliente,monto);
                            break;

                        case 3:
                        cout << "Ingrese el numero de identificion de la cuenta de origen de los fondos: ";
                        cin >> idCuentaCliente;  
                        cout << "Ingrese el monto a cancelar: ";
                        cin >> monto;
                        db.realizarPagoServicios(idCuentaCliente,monto);
                            break;
                        case 4:
                        cout << "Ingrese el numero de identificion de la cuenta de origen de los fondos: ";
                        cin >> idCuentaCliente;  
                        cout << "Ingrese el monto a cancelar: ";
                        cin >> monto;
                        db.realizarPagoServicios(idCuentaCliente,monto);
                            break;

                        default:
                            cout << "Ingrese una opcion valida para el pago de servicios" << endl;
                    }
                } while (opcionSubmenu != 4);
                break;
            break;
            case 5:
            //falta implementar
            break;
            case 6:
            db.consultarTipoCambio();
            break;

            case 7:
            //falta implementar
            break;

            case 8:
            db.verRegistroTransacciones();
            break;
            
            case 9:
                cout << "Regresando al menú de módulos" << endl;
                break;            
        }
    } while (subOpcion != 9); 
}

void MenuGestionPrestamos() {
    int subOpcion;
    Database db;
    do {
        cout << "\n Menú para le gestión de préstamos" << endl;
        cout << "1. Tipos de préstamos a solicitar" << endl;
        cout << "2. Consultar frecuencia de pagos" << endl;
        cout << "3. Cuotas y desgloce" << endl;
        cout << "4. Actualización del saldo de préstamo" << endl;
        cout << "5. Cálculo de intereses" << endl;
        cout << "6. Métodos de pago" << endl;
        cout << "7. Ver información de préstamo" << endl;
        cout << "8. Regresar al menú principal" << endl;
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
            db.consultarTiposPrestamos();
            break;

            case 9:
                cout << "Regresando al menú de módulos" << endl;
                break;            
        }
    } while (subOpcion != 8);
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
        
        switch (subOpcion) {
            case 1:
                cout << "\nHas seleccionado el Préstamo personal." << endl;
                
                break;

            case 2:
                cout << "\nHas seleccionado el Préstamo prendario." << endl;
            
                break;

            case 3:
                cout << "\nHas seleccionado el Préstamo hipotecario." << endl;
                
                break;

            case 4:
                cout << "\nRegresando al menú de gestión de préstamos..." << endl;
                break;

            default:
                cout << "\nOpción no válida. Por favor, intente de nuevo." << endl;
                break;
        }
    } while (subOpcion != 4); // Continúa mostrando el menú hasta que el usuario seleccione la opción 4
}

