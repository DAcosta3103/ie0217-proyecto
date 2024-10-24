# ie0217-proyecto


## Base de datos
### Razones para utilizar SQLte
Para la implementación de la base de datos de este sistema bancario se va utilizar el motor SQLite, esto debido a su ligereza y ágilidad en operaciones de lectura y escritura, lo que lo hace una adecuada opción para contextos donde se necesite un movimiento de datos instantáneo como es el caso de un sistema bancario.

Además de esto es un motor ofrece las características que se le conocen como ACID (atomicity, consistency, isolation, durability), lo que significa que este motor asegura que todas o ninguna operación dentro de una transacción se va realizar (no deja una transacción a medias), ademas de que cada transacción va ser independiente de las demás, por lo que no van a afectar a otras operaciones y por ultimo que las operaciones realizadas no podrán deshacerse, evitando de esta forma errores o estados incompletos.

Por otro lado SQLite ofrece compatibiliad con múltiples plataformas y distintos lenguanges de programación, lo que hace posible poder integrarlo a entornos diferentes y a distintas tecnologías como lo puede ser aplicaciones móviles, web etc. Esta flexibilidad lo hace excelente para temas de un código escalable, ya que garantiza una fácil adaptación para futuras mejoras, actualizaciones, mantenimiento etc.

SQLite también es compatible con extensiones que permiten seguridad para la integridad de la base datos como cifradores o gestores de claves, ademas de poder ofrecer mecanismos de control de acceso. Extensiones como SQLCypher son compatibles con SQLite el cual proporciona cifrados avanzados a la base de datos bajo algoritmos, lo que asegura que los datos permanezcan seguros frente a accesos no autorizados.

### Estructura de la Base de datos.
Se proponen 5 tablas, Clientes, Cuentas, Préstamos, CDP y transacciones.

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
  * Interés DECIMAL() NOT NULL, (pocentaje)
  * Plazo INT NOT NULL, (en meses)
  * CuotaMensual DECIMAL() NOT NULL, 
  * Tipo ENUM (Hipotecario, Personal, Prendario) NOT NULL, 

* CDP: Almacena Información de los certificados de deposito a plazo de los clientes
  * IdCDP (PK) INT AUTO_INCREMENNT,
  * IdCliente (FK) INT NOT NULL, 
  * Monto DECIMAL() NOT NULL, 
  * TazaInterés DECIMAL() NOT NULL, (pocentaje)
  * Plazo INT NOT NULL, (en meses)
  * FechaInicio DATE NOT NULL,

* Transacciones: Funciona como registro de las transacciones realiadas a las cuentas.
  * IdTransacción (PK) INT AUTO_INCREMENT,
  * IdCliente (FK) INT NOT NULL,
  * Tipo ENUM (Deposito, Retiro, Transferencia, Abono) NOT NULL, 
  * Fecha TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

### Seguridad de la Base de Datos
Para la integridad de los datos finacieros de los clientes se propone lo siguiente

 * Cifrado de la base de datos, es posible con extensiones a SQLite como SQLCypher, el cual con algoritos de cifrado, garantiza que la información no va ser legible cin las claves correspondientes.

 * Controles de acceso robustos, con permisos estrictos a los directorios, limitando el poder de escribir, leer o ejectur solo para usuarios autotizados.

 * Utilización de archivos journal, implementados en SQLite, los cuales son archivos temporales, los cuales funcionan como respalda en el caso de que una transacción no se complete adecuadamente, permitiendo revertir los datos si se corrompen o debido a cualquier eventualidad.

 * Protección contra inyecciones SQL, haciendo un código SQL robusto con sentencias preparadas para evitar inyecciones SQL, evitando que las lineas ingresadas por personas malintenciondas se puedan interpretar como código SQL

### Generación de reportes de préstamos
Para generar reportes bancarios es necesario poder implementar el código en este caso en C++ y que este se conecte de manera adecuada a la base de datos, donde estan almacenados los registros.
El código recolecta por parte del usuario en la interfaz el número de ID del prestamo del cual se quiere generar el reporte. Una vez corroborado de que el ID del prestamo es existente, por medio de consultas SQL recolecta información de la base de datos, por medio de funciones se calculan las cuotas pagadas, el aporta al capital y los intereses pagados, por medio de extensiones o librerías es posible presentar estos datos en formato CSV o PDF, por último se pueden almacenar estos reportes en directorios específicos.