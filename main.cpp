// para correrlo en windows g++ -o main main.cpp  y ./main
#include <iostream>
using namespace std;
void MenuAtencionAlCliente();
void MenuGestionPrestamos();
void SubMenuTipoPrestamos();

int main() {
    int opcion;
    do {
        cout << "\nSeleccione un módulo " << endl;
        cout << "1. Atencion al cliente" << endl;
        cout << "2. Gestión de préstamos" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            cout << "Entrada no válida. Por favor, ingrese un número" << endl;
            continue; 
        }

        switch (opcion) {
            case 1:
                MenuAtencionAlCliente();
                break;
            case 2:
                MenuGestionPrestamos();
                break;
            case 3:
                cout << "Saliendo del programa" << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo" << endl;
        }

    } while (opcion != 3);

    return 0;
}

void MenuAtencionAlCliente() {
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