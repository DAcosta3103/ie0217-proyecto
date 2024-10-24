# ie0217-proyecto


### Base de datos
## Razones para utilizar SQLte
Para la implementación de la base de datos de este sistema bancario se va utilizar el motor SQLite, esto debido a su ligereza y ágilidad en operaciones de lectura y escritura, lo que lo hace una adecuada opción para contextos donde se necesite un movimiento de datos instantáneo como es el caso de un sistema bancario.

Además de esto es un motor ofrece las características que se le conocen como ACID (atomicity, consistency, isolation, durability), lo que significa que este motor asegura que todas o ninguna operación dentro de una transacción se va realizar (no deja una transacción a medias), ademas de que cada transacción va ser independiente de las demás, por lo que no van a afectar a otras operaciones y por ultimo que las operaciones realizadas no podrán deshacerse, evitando de esta forma errores o estados incompletos.

Por otro lado SQLite ofrece compatibiliad con múltiples plataformas y distintos lenguanges de programación, lo que hace posible poder integrarlo a entornos diferentes y a distintas tecnologías como lo puede ser aplicaciones móviles, web etc. Esta flexibilidad lo hace excelente para temas de un código escalable, ya que garantiza una fácil adaptación para futuras mejoras, actualizaciones, mantenimiento etc.

SQLite también es compatible con extensiones que permiten seguridad para la integridad de la base datos como cifradores o gestores de claves, ademas de poder ofrecer mecanismos de control de acceso. Extensiones como SQLCypher son compatibles con SQLite el cual proporciona cifrados avanzados a la base de datos bajo algoritmos, lo que asegura que los datos permanezcan seguros frente a accesos no autorizados.

## Estructura de la Base de datos.
Se proponen 5 tablas, Clientes, Cuentas, Préstamos, CDP y transacciones.

