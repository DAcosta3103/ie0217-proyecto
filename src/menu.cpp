#include <iostream>
#include "../include/menu.hpp"
#include "../include/database.hpp"

using namespace std;

void MenuAtencionAlCliente() {
    Database db;
    int subOpcion;
    int opcionSubmenu;
    int idCliente;
    int IdCliente;
    int IdCuenta;
    int idCuenta;
    int idCuentaDestino;
    int idCuentaOrigen;
    int idCuentaCliente;
    double monto;
    int plazo;
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

            db.realizarDeposito(IdCuenta, monto, IdCliente);
            break;

            case 2:
            cout << "Ingrese el numero de identificion de la cuenta a la que quiere hacer el retiro: ";
            cin >> IdCuenta;
            cout << "Ingrese el monto a retirar: ";
            cin >> monto;

            db.realizarRetiro( IdCuenta, monto,  IdCliente);
            break;

            case 3:
            cout << "Ingrese el numero de identificion de la cuenta de origen de los fondos: ";
            cin >> idCuentaOrigen;
            cout << "Ingrese el numero de identificion de la cuenta destino para la tranferencia: ";
            cin >> idCuentaDestino;
            cout << "Ingrese el monto a transferir: ";
            cin >> monto;

            db.realizarTransferencia(idCuentaOrigen, idCuentaDestino,monto,IdCliente, IdCliente);
            break;
            case 4:
            do {
                    cout << "\nCentro de pago de servicios:\n";
                    cout << "1. Agua y luz\n";
                    cout << "2. Marchamo\n";
                    cout << "3. Internet\n";
                    cout << "4. Impuesto municipal\n";
                    cout << "5. Regresar al menú anterior" << endl;
                    cout << "Seleccione una opción del submenú: ";
                    cin >> opcionSubmenu;

                    switch (opcionSubmenu) {
                        case 1:

                        cout << "Ingrese el numero de identificion de la cuenta de origen de los fondos: ";
                        cin >> idCuentaCliente;  
                        cout << "Ingrese el monto a cancelar: ";
                        cin >> monto;
                        db.realizarPagoServicios(idCuentaCliente,monto, IdCliente);
                            break;
                           
                        case 2:
                        cout << "Ingrese el numero de identificion de la cuenta de origen de los fondos: ";
                        cin >> idCuentaCliente;  
                        cout << "Ingrese el monto a cancelar: ";
                        cin >> monto;
                        db.realizarPagoServicios(idCuentaCliente,monto, IdCliente);
                            break;

                        case 3:
                        cout << "Ingrese el numero de identificion de la cuenta de origen de los fondos: ";
                        cin >> idCuentaCliente;  
                        cout << "Ingrese el monto a cancelar: ";
                        cin >> monto;
                        db.realizarPagoServicios(idCuentaCliente,monto, IdCliente);
                            break;
                        case 4:
                        cout << "Ingrese el numero de identificion de la cuenta de origen de los fondos: ";
                        cin >> idCuentaCliente;  
                        cout << "Ingrese el monto a cancelar: ";
                        cin >> monto;
                        db.realizarPagoServicios(idCuentaCliente,monto, IdCliente);
                            break;
                    }
                } while (opcionSubmenu != 5);
                break;
            break;
            case 5:
                db.comprarCDP(idCliente, monto, plazo);
            break;
            case 6:
            db.consultarTipoCambio();
            break;

            case 7:
            db.bloquearCuenta(idCuenta);
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
    Database db;
    int IdPrestamo;
    int subOpcion;
    double nuevoSaldo;
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

            case 2:
            db.consultarFrecuenciaPagos(IdPrestamo);
            break;

            case 3:
            db.mostrarCuotasYDesglose();

            case 4:
            db.actualizarSaldoPrestamo(nuevoSaldo);

            case 5:
            db.calcularIntereses(IdPrestamo);

            case 6:
            db.mostrarMetodosPago();

            case 7:
            db.verInformacionPrestamo(IdPrestamo);

            case 8:
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
                do{
                    cout<<"1. Guía de préstamo personal"<<endl;
                    cout<<"2. Requisitos para préstamo personal"<<endl;
                    cout<<"3. Regresar al menú anterior";
                    cout<< "\nSeleccione una opción: ";
                    cin >> subOpcion;
                    
                    if (cin.fail()) {
                    cin.clear(); 
                    cin.ignore(1000, '\n'); 
                    cout << "Entrada no válida. Por favor, ingrese un número" << endl;
                    continue; 
                }
                        switch (subOpcion) {
                            case 1:
                                cout << "\nGuía de préstamo personal" << endl;
                                cout << "Orientación para el trámite y formalización del cŕedito personal.\n";
                                cout << "  • Paso 1: Analizar la nacesidad del cliente y las circunstancias del cŕedito\n";
                                cout << "  • Paso 2: Definir las posibilidades económicas del cliente\n"; 
                                cout << "  • Paso 3: Enviar la solicitud y adjuntar la documentación requerida\n";
                                cout << "  • Paso 4: Asignar un ejectivo del banco al cliente para evaluar la solicitud y determinar la aprovación del cŕedito\n";
                            break;

                            case 2:
                                cout << "\nRequisitos" << endl;
                                cout << "Documentación del cliente:\n";
                                cout << "  • Formulario de solicitud del cŕedito personal firmado por el solicitante\n";
                                cout << "  • Fotocopia legible del documento de identificación\n";
                                cout << "  • Constancia salarial o declaración de ingresos\n";
                                cout << "  • Comprobante de domicilio (recibo de servicios públicos reciente)\n";

                                cout << "\nRequisitos adicionales\n";
                                cout << "  • Historial crediticio\n";
                                cout << "  • Documentos adicionales si el trabajador es trabajador independiente\n";

                            break;
                            case 3:
                                cout << "\nRegresando al menú anterior." << endl;
                                break;
                            default:
                                cout << "\nOpción no válida. Por favor, intente de nuevo." << endl;
                            break;
                            }
                        } while (subOpcion != 3); 
 
                break;

            case 2:
                cout << "\nHas seleccionado el Préstamo prendario." << endl;
                do{
                    cout<<"1. Guía de préstamo prendario"<<endl;
                    cout<<"2. Requisitos para préstamo prendario"<<endl;
                    cout<<"3. Regresar al menú anterior";
                    cout<< "\nSeleccione una opción: ";
                    cin >> subOpcion;
                    
                    if (cin.fail()) {
                    cin.clear(); 
                    cin.ignore(1000, '\n'); 
                    cout << "Entrada no válida. Por favor, ingrese un número" << endl;
                    continue; 
                }
                        switch (subOpcion) {
                            case 1:
                                cout << "\nGuía de préstamo prendario" << endl;
                                cout << "Orientación para el trámite y formalización del cŕedito prendario.\n";
                                cout << "  • Paso 1: Analizar la nacesidad del cliente y las circunstancias del cŕedito\n";
                                cout << "  • Paso 2: Definir los bienes muebles a ofrecer como garantía\n";
                                cout << "  • Paso 3: Valorar el bien mueble y definir el monto máximo del cŕedito\n";
                                cout << "  • Paso 4: Enviar la solicitud y asignar un ejectivo del banco al cliente para revisar la documentación y llevar a cabo el crédito\n";
                            break;

                            case 2:
                                cout << "\nRequisitos" << endl;
                                cout << "Documentación del cliente:\n";
                                cout << "  • Formulario del cliente firmado por el deudor y el co-deudor\n";
                                cout << "  • Solicitud del cŕedito prendario\n";
                                cout << "  • Fotocopia legible del documento de identificación\n";
                                cout << "  • Constancia salarial o declaración de ingresos\n";

                                cout << "\nRequisitos de garantía\n";
                                cout << "  • Factura del bien mueble ofrecido como garantía\n";
                                cout << "  • Certificación de propiedad del bien\n";
                                cout << "  • Avalúo técnico del bien\n";
                                cout << "  • Documentos adicionales según las políticas del banco\n";

                            break;
                            case 3:
                                cout << "\nRegresando al menú anterior." << endl;
                                break;
                            default:
                                cout << "\nOpción no válida. Por favor, intente de nuevo." << endl;
                            break;
                            }
                        } while (subOpcion != 3); 
 
                break;

            case 3:
                cout << "\nHas seleccionado el Préstamo hipotecario." << endl;
                do{
                    cout<<"\n1. Guía de préstamo hipotecario"<<endl;
                    cout<<"2. Requisitos para préstamo hipotecario"<<endl;
                    cout<<"3. Regresar al menú anterior";
                    cout<< "\nSeleccione una opción: ";
                    cin >> subOpcion;
                    
                    if (cin.fail()) {
                    cin.clear(); 
                    cin.ignore(1000, '\n'); 
                    cout << "Entrada no válida. Por favor, ingrese un número" << endl;
                    continue; 
                }
                        switch (subOpcion) {
                            case 1:
                                cout << "\nGuía de préstamo hipoteario" << endl;
                                cout << "Orientación para el trámite y formalización del cŕedito de vivienda.\n";
                                cout << "  • Paso 1: Seleccionar un plan acorde al proyecto de vivienda\n";
                                cout << "  • Paso 2: Definair posibilidades económicas del cliente\n";
                                cout << "  • Paso 3: Iniciar el trámite del crédito\n";
                                cout << "  • Paso 4: Enviar la solicitud y asignar un ejectivo del banco al cliente para revisar la documentación y llevar a cabo el crédito\n";
                            break;

                            case 2:
                                cout << "\nRequisitos" << endl;
                                cout << "Documentación del cliente:\n";
                                cout << "  • Formulario del cliente firmado por el deudor y el co-deudor\n";
                                cout << "  • Solicitud del cŕedito hipotecario\n";
                                cout << "  • Fotocopia legible del documento de identificación\n";
                                cout << "  • Constancia salarial y copia de orden patronal\n";

                                cout << "\nRequisitos de garantía\n";
                                cout << "  • Copia de plano plano catastro, planos constructivos\n";
                                cout << "  • Estudio registral\n";
                                cout << "  • Certificación de impuetos al día\n";
                                cout << "  • Constancia salarial y copia de orden patronal\n";
                                cout << "  • Avalúo de la propiedad a hipotecar\n";

                            break;

                            case 3:
                                cout << "\nRegresando al menú anterior." << endl;
                            break;
                            default:
                                cout << "\nOpción no válida. Por favor, intente de nuevo." << endl;
                            break;
                            }
                        } while (subOpcion != 3); 
 
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

