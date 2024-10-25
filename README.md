# ie0217-proyecto

## Requisitos funcionales de la base de datos
Ya que el cliente debe elegir entre las modalidades de atención al cliente o información sobre préstamos, hay que definir qué funciones tiene cada modalidad. A continuación se especifican los tipos de cuentas bancarias que los clientes pueden tener, así como la gestión de información sobre préstamos.
### Definición de operaciones bancarias para atención al cliente

El cliente será capaz de crear hasta dos cuentas de ahorro, donde cada una puede ser en dólares o colones. Las operaciones para esta modalidad son las siguientes:
- **Depósitos a la cuenta del cliente:** El cliente será capaz de abonar dinero a su(s) cuenta(s).
- **Retiros de la cuenta del cliente:** El cliente será capaz de retirar dinero desde una o ambas de sus cuentas.
- **Transferencia entre cuentas:** Un cliente será capaz de transferir dinero a la cuenta de otro cliente distinto.
- **Pago de servicios:** El cliente será capaz de realizar un pago para servicios básicos, como agua, luz o internet, cuyos montos estarán predefinidos.
- **Compra de CDP:** Cada cliente será capaz de realizar la compra de un Certificado de Depósito a Plazo (CDP), donde será capaz de elegir el plazo de tiempo en meses. También el cliente será informado de la tasa de interés correspondiente.
- **Tipo de cambio:** El cliente será capaz de revisar el tipo de cambio entre dólares y colones, el cual será un valor predefinido.
- **Bloqueo y desbloqueo de cuentas:** Cada cliente será capaz de bloquear su cuenta en caso de que sospeche fraude o robo, de manera que no se permitirán depósitos o retiros de la cuenta hasta que el cliente la desbloquee.
- **Ver registro de transacciones:** Cada cliente será capaz de revisar el registro de las transacciones realizadas desde su cuenta, como pagos, depósitos, retiros, etc.

### Gestión de Préstamos
Ahora bien, a continuación se describen las funciones del módulo referente a todo lo que tiene que ver con los préstamos bancarios:
**Tipos de Préstamos:** El sistema debe ofrecer opciones de préstamos, incluyendo:
- **Préstamos Personales:** Para uso general, con tasas de interés fijas.
- **Préstamos Hipotecarios:** A largo plazo, destinado a la compra de propiedades, con opciones de pago a plazos largos y tasas fijas.
- **Préstamos Prendarios:** Producto de financiación para la adquisición de bienes muebles registrables. Tiene una tasa de interés fija.

Ahora bien, para pagar los préstamos deben haber distintas **opciones de pago** para los clientes. A continuación se documentan configuraciones posibles para ver que el cliente se informe y poder pagar su préstamo: 
- **Frecuencia de Pago:** Opciones de pago mensual, trimestral, o anual, dependiendo de cuántos meses quiere pagar el cliente.
- **Cuotas y Desglose:** Cada cuota debe desglosarse en capital e interés para que el cliente vea cuánto se destina a la deuda principal y a intereses. Esta información se le desplegará al cliente en formato tabular.
- **Actualización del Saldo de Préstamo:** Cada pago debe reflejarse en el saldo del préstamo, actualizándose de acuerdo con el monto pagado.

También hay que definir el **Pago y Cálculo de Intereses**, lo cual es información importante para el cliente que consulta: 
- **Cálculo de Intereses:** Basado en el saldo pendiente, tasa de interés y período de tiempo restante. Con esta opción el cliente será capaz de ver cuánto deberá pagar en intereses.
- **Método de Pago:** Ya que el cobro del préstamo será mensual, el cliente será capaz de abonar una cantidad a su elección, de manera que puede pagar varios meses en una sola transacción, si así lo desea. Tras cada pago, el sistema actualizará el monto debido por el cliente.

Otras opciones importantes para la gestión de préstamos se detallan a continuación:
- **Ver tabla sobre información del préstamo:** Opción para que el cliente pueda revisar la información referente al préstamo que tenga, donde la información será desplegada en formato tabular. Esta opción va de la mano con la opción de **cuotas y desglose**. El cliente podrá ver los pagos restantes del préstamo, el interés que posee dicho préstamo, las cuotas restantes y las cuotas pagadas.
- **Préstamos en dólares o colones:** Esta opción permitirá al cliente realizar préstamos en el tipo de moneda deseado entre dólares y colones. Asimismo, el cliente podrá ver la tasa de interés, el plazo en meses y cuota mensual referente a su préstamo, lo cuál se manejará en la opción de **ver tabla sobre información del préstamo**.
 

### Identificación y Seguridad del Cliente
Ya que estamos trabajando con un sistema bancario, es necesario tomar en cuenta la importancia de la seguridad de los datos del cliente. Para esto, se definen el siguiente **método de autenticación** 
- **Nombre de Usuario y Contraseña:** Esquema básico para el manejo personal de una cuenta por cliente, el cual puede incluir requisitos de complejidad para la contraseña, como el uso de mayúsculas o carácteres numéricos. Es un método sencillo pero robusto, utilizado por los bancos estatales costarricenses, y apto para la inclusión en el código sin necesidad de utilizar aplicaciones terceras. Para mayor seguridad, la contraseña se guardará como un hash, y cada cliente será asignado un número del 0 al 999,999,999; donde dicho número para representar a los clientes se manejará internamente en el programa. Se utilizará la función hash _SHA-256_.



## Base de datos
### Razones para utilizar SQLite
Para la implementación de la base de datos de este sistema bancario se va utilizar el motor SQLite, esto debido a su ligereza y agilidad en operaciones de lectura y escritura, lo que lo hace una adecuada opción para contextos donde se necesite un movimiento de datos instantáneo como es el caso de un sistema bancario.

Además de esto, es un motor ofrece las características que se le conocen como ACID (atomicity, consistency, isolation, durability), lo que significa que este motor asegura que todas o ninguna operación dentro de una transacción se va realizar (no deja una transacción a medias), además de que cada transacción va a ser independiente de las demás, por lo que no van a afectar a otras operaciones; y por ultimo, que las operaciones realizadas no podrán deshacerse, evitando de esta forma errores o estados incompletos.

Por otro lado, SQLite ofrece compatibilidad con múltiples plataformas y distintos lenguages de programación, lo que hace posible poder integrarlo a entornos diferentes y a distintas tecnologías como lo puede ser aplicaciones móviles, web etc. Esta flexibilidad lo hace excelente para temas de un código escalable, ya que garantiza una fácil adaptación para futuras mejoras, actualizaciones, mantenimiento etc. 

SQLite también es compatible con extensiones que permiten seguridad para la integridad de la base datos como cifradores o gestores de claves, además de poder ofrecer mecanismos de control de acceso. Extensiones como SQLCypher son compatibles con SQLite el cual proporciona cifrados avanzados a la base de datos bajo algoritmos, lo que asegura que los datos permanezcan seguros frente a accesos no autorizados.


### Estructura de la Base de datos.
Para la estructura de la base de datos a realizar, se proponen 5 tablas: Clientes, Cuentas, Préstamos, CDP y transacciones.

* Clientes: Almacena la información básica de cada cliente
  * IdCliente (PK) INT AUTO_AUTOINCREMENT,
  * Cédula VARCHAR() UNIQUE NOT NULL,
  * Nombre  VARCHAR() NOT NULL,
  * Dirección TEXT, 
  * Teléfono INT, 
  * email  VARCHAR() UNIQUE,

* Cuentas: Cuentas bancarias asociadas a los clientes
  * IdCuenta (PK) INT AUTO_AUTOINCREMENT,
  * IdCliente (FK) INT NOT NULL, 
  * Tipo ENUM (colones, dólares) NOT NULL, .
  * Saldo DECIMAL() DEFAULT 0.00,

* Cuentas: Almacena información de las cuentas bancarias asociadas a los clientes
  * IdCuenta (PK) INT AUTO_AUTOINCREMENT,

* Créditos: Almacena información de los créditos asociados a los clientes
  * IdPréstamo (PK) INT AUTO_AUTOINCREMENT, 
  * IdCliente (FK) INT NOT NULL,
  * Monto DECIMAL() NOT NULL, 
  * Interés DECIMAL() NOT NULL, (porcentaje)
  * Plazo INT NOT NULL, (en meses)
  * CuotaMensual DECIMAL() NOT NULL, 
  * Tipo ENUM (Hipotecario, Personal, Prendario) NOT NULL, 

* CDP: Almacena Información de los certificados de depósito a plazo de los clientes
  * IdCDP (PK) INT AUTO_INCREMENNT,
  * IdCliente (FK) INT NOT NULL, 
  * Monto DECIMAL() NOT NULL, 
  * TazaInterés DECIMAL() NOT NULL, (porcentaje)
  * Plazo INT NOT NULL, (en meses)
  * FechaInicio DATE NOT NULL,

* Transacciones: Funciona como registro de las transacciones realizadas a las cuentas.
  * IdTransacción (PK) INT AUTO_INCREMENT,
  * IdCliente (FK) INT NOT NULL,
  * Tipo ENUM (Deposito, Retiro, Transferencia, Abono) NOT NULL, 
  * Fecha TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

### Seguridad de la Base de Datos
Para la integridad de los datos finacieros de los clientes se propone lo siguiente

 * Cifrado de la base de datos, es posible con extensiones a SQLite como SQLCypher, el cual con algoritos de cifrado, garantiza que la información no va ser legible cin las claves correspondientes.

 * Controles de acceso robustos, con permisos estrictos a los directorios, limitando el poder de escribir, leer o ejectur solo para usuarios autorizados.

 * Utilización de archivos journal, implementados en SQLite, los cuales son archivos temporales, los cuales funcionan como respaldo en el caso de que una transacción no se complete adecuadamente, permitiendo revertir los datos si se corrompen o debido a cualquier eventualidad.

 * Protección contra inyecciones SQL, haciendo un código SQL robusto con sentencias preparadas para evitar inyecciones SQL, evitando que las lineas ingresadas por personas malintencionadas se puedan interpretar como código SQL

### Generación de reportes de préstamos
Para generar reportes bancarios es necesario poder implementar el código, para el cual se utilizará el lenguaje C++, de manera que este se conecte de manera adecuada a la base de datos, donde están almacenados los registros.
El código recolecta por parte del usuario en la interfaz el número de ID del préstamo del cual se quiere generar el reporte. Una vez corroborado de que el ID del préstamo es existente, por medio de consultas SQL recolecta información de la base de datos, por medio de funciones se calculan las cuotas pagadas, el aporta al capital y los intereses pagados, por medio de extensiones o librerías como csv.h o libharu.h es posible presentar estos datos en formato CSV o PDF, por último se pueden almacenar estos reportes en directorios específicos.

### Automatización de pruebas
Para esto se pueden utilizar librerías como el framework de pruebas Google Test (gtest/gtest.h) en C++ para desarrollar pruebas automatizadas que validan las distintas funciones del sistema.
Entonces, luego de esta implementación, es necesario hacer distintas pruebas a las funciones del sistema para verificar su correcto funcionamiento. A continuación se tiene un ejemplo de cómo se vería una prueba para la función de depositar utilizando el framework de Google Test:\

```cpp
#include 1gtest/gtest.h1
#include 1mi_sistema_bancario.h1

// Prueba para la función de depósito
TEST(SistemaBancarioTest, DepositoIncrementaSaldo) {
    Cuenta cuenta;
    cuenta.depositar(100); // Depositar 100
    EXPECT_EQ(cuenta.getSaldo(), 100); // Verificar que el saldo sea 100
}
```

A continuación se listan los tipos de pruebas que serán necesarios:

**Pruebas de Integración con la Base de Datos:** 
- **Validación de Consultas SQL:** Verificar que las consultas SQL devuelvan resultados correctos para operaciones de préstamo. 
- **Pruebas de Conexión y Desconexión:** Confirmar que el sistema se conecte y desconecte de SQLite correctamente.

**Pruebas de Funcionalidades Clave:**  
- **Pruebas de Transacciones:** Validar depósitos, retiros, transferencias y pagos de servicios, asegurando que se registren en la base de datos. 
- **Pruebas de Seguridad y Autenticación:** Asegurar que solo usuarios autorizados puedan acceder mediante usuario y contraseña.

**Pruebas de Rendimiento:** 
- **Simulación de múltiples usuarios y transacciones simultáneas:** Asegurar que el sistema gestione cargas sin errores. 
- **Evaluación de respuesta ante grandes volúmenes de datos:** Identificar posibles cuellos de botella en la base de datos.

**Pruebas de Generación de Reportes:** 
- **Verificación de la Exactitud del Reporte:** Asegurar que los reportes generen la información correcta, con desglose de pagos en formato tabular.
- **Confirmación de Almacenamiento y Descarga:** Verificar que los reportes se almacenen correctamente y se puedan descargar en los formatos especificados.

**Pruebas de Frontera:** 
- **Saldo justo y operaciones límite:** Verifica el comportamiento del sistema al realizar transacciones con el saldo exacto o en el límite permitido. 
- **Máximos y mínimos de transacciones:** Asegura que el sistema maneje correctamente montos extremos dentro de los límites definidos.

**Pruebas de Error de Entrada:**  
- **ID de préstamo no existente:** Valida que el sistema maneje adecuadamente intentos de acceso a préstamos que no existen. 
- **Montos negativos y caracteres no válidos:** Prueba el sistema con datos no válidos en campos numéricos y verifica el manejo de errores.

**Pruebas de Manejo de Errores de Conexión:** 
- **Desconexión inesperada:** Simula la pérdida de conexión durante una transacción para asegurar que el sistema mantenga la integridad de los datos. 
- **Reintentos de conexión y consistencia:** Verifica que el sistema reintente la conexión sin corrupción de datos tras una reconexión exitosa.

**Pruebas de Seguridad Adicionales:**  
- **Acceso no autorizado:** Asegura que las cuentas y funciones no se accedan sin la autenticación adecuada. 
- **Cierre seguro de sesiones:** Verifica que al cerrar la sesión, no quede información residual accesible para futuros usuarios.

**Pruebas de Persistencia de Datos:** 
- **Validación de datos tras reinicio:** Asegura que los datos ingresados se mantengan intactos en la base de datos luego de reiniciar el sistema. 
- **Verificación de integridad tras operaciones sucesivas:** Confirma que transacciones consecutivas se reflejen correctamente en la base de datos.

**Pruebas de Concurrencia:** 
- **Operaciones simultáneas en múltiples cuentas:** Prueba la base de datos con varias transacciones en paralelo para verificar la gestión de concurrencia. 
- **Prevención de condiciones de carrera:** Asegura que no haya conflictos al acceder a datos compartidos por varias operaciones.

**Pruebas de Funcionalidad de Reportes para Distintas Condiciones:** 
- **Reporte sin transacciones:** Verifica que el sistema genere un reporte adecuado aun cuando no haya transacciones registradas. 
- **Reporte con cuotas pagadas y parciales:** Asegura que el desglose de cuotas en el reporte refleje correctamente los pagos realizados, pendientes y acumulados.

Al realizar todas estas pruebas se podrá validar el correcto funcionamiento del sistema. Sin embargo, cabe destacar que no todas las pruebas son fácilmente automatizables, como la prueba de frontera o error de entrada, pero se intentará automatizar todas las que sean posibles.


# Cronograma de Proyecto

## Fechas Importantes
- **Propuesta**: <span style="color:green">25 October 2024</span>  
- **Avance**: <span style="color:green">8 November 2024</span>  
- **Final**: <span style="color:green">26 November 2024</span>  

## Actividades

| **Periodo** | **Fecha**              | **Christian Tareas**                | **Diego Tareas**                 |
|-------------|------------------------|-------------------------------------|----------------------------------|
| Periodo 1   | 26 - 27 Oct            |   Investigación sobre base de datos, la conexión de este con el código implementado en C++, temas de seguridad con respecto a esta base de datos y la estructura que debe tener. Investigación sobre la generación de reportes y automatización de pruebas                                 | [ ]                              |
| **Entrega** | <span style="color:green">25 Oct</span> | [ ] Revisión y Entrega              | [ ] Revisión y Entrega            |
| Periodo 2   | 28 Oct - 3 Nov         | [ ]                                 | [ ]                              |
| Periodo 3   | 4 - 7 Nov              | [ ]                                 | [ ]                              |
| **Entrega** | <span style="color:green">8 Nov</span> | [ ] Revisión y Entrega              | [ ] Revisión y Entrega            |
| Periodo 4   | 9 - 10 Nov             | [ ]                                 | [ ]                              |
| Periodo 5   | 11 - 17 Nov            | [ ]                                 | [ ]                              |
| Periodo 6   | 18 - 24 Nov            | [ ]                                 | [ ]                              |
| Periodo 7   | 25 Nov                 | [ ]                                 | [ ]                              |
| **Entrega** | <span style="color:green">26 Nov</span> | [ ] Revisión y Entrega              | [ ] Revisión y Entrega            |
