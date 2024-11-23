//  para correrlo en linux g++ -o banco main.cpp menu.cpp database.cpp -sqlite3
#include <iostream>
#include "../include/menu.hpp"
#include "../include/database.hpp"
using namespace std;

int main() {
    //intanciacion de objeto para poder manipular la clase
   // Database db;
    Database db;
    int opcion;

    //blucle do while para el menu de modulos
    do {
        cout << "\nSeleccione un módulo " << endl;
        cout << "1. Atencion al cliente" << endl;
        cout << "2. Gestión de préstamos" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        //bucle para evaluar si la entra es válida, solo acepta interos ya que cin >> opcion;
        //continue ingora el resto del codigo para volver a iterar el bucle
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

