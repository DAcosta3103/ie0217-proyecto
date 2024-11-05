//  para correrlo en linux g++ -o banco main.cpp menu.cpp database.cpp -sqlite3
#include <iostream>
#include "menu.hpp"
#include "database.hpp"
using namespace std;

int main() {
    Database db;

    int opcion;
    do {
        cout << "\nSeleccione un módulo " << endl;
        cout << "1. Atencion al cliente" << endl;
        cout << "2. Gestión de préstamos" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        //bucle para evaluar si la entra es válida
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

