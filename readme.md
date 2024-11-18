# Algoritmo de Dispersion para llaves Numericas
1. Objetivo:
    - Crear un algoritmo propio que convierta una llave númerica en una posición dentro de una tabla con capacidad para 750 registros.
    - La Función de dispersion debe ser lo más eficiente posible para minimizar colisiones.
2. Estrategia:
    - Utilizar el operador '%' para asegurar que el resultado siempre esté rango válido (0 a 749).
3. Estructura del Código:
    - Definir una función hashNumerico() para generar la posición. 
    - Implementar una tabla hash usando un vector que almacene llaves. 
    - Permitir la inserción y busqueda de llaves.

3. 1. Paso 1 Crear la Funcion de dispersion para llaves Numéricas
    - Explicación de la Función hashNumerico()
    - Multiplicamos la llave por un número (en este caso, 3) y sumamos otro número (7) antes de aplicar el módulo.
    - El uso de multiplicación y suma agrega un poco más de aleatoriedad.
    - Finalmente, aplicamos módulo 750 para asegurarnos de que el resultado esté en el rango de 0 a 749.
3. 2. Paso 2: Implementar la Tabla Hash y Funciones de Inserción y Búsqueda
3. 3. Explicacion del codigo
    - Clase TablaHash:
    - Utiliza un vector de estructuras Entrada para almacenar llaves y un indicador (ocupado) que indica si la posición está ocupada.
    - Método insertar():
    - Calcula la posición usando la función hashNumerico().
    - Verifica si la posición ya está ocupada (manejo básico de colisiones).
    - Método buscar():
    - Verifica si una llave dada se encuentra en la posición calculada.
    - Método mostrarTabla():
    - Imprime todas las llaves almacenadas en la tabla hash.
    - Funcionalidades del Menú:
    - Permite al usuario insertar, buscar y mostrar el contenido de la tabla hash.
3. 4. Pruebas del Programa 
    - Ejecute el programa y pruebe las siguientes llaves
    - Insertar llaves 123, 456, 756
    - Buscar Llaves: Pruebe buscando llaves existentes y no existentes.
# Algoritmo de Dispersion Alfanumerico
1. Objetivo
    - Desarrollar un algoritmo de dispersión propio para llaves alfanuméricas (sin utilizar librerías, bibliotecas ni funciones de dispersión predefinidas). La tabla   hash debe tener una capacidad para 1100 registros.
2. Estrategia
    -Para las llaves alfanuméricas, necesitamos un algoritmo de dispersión que convierta una cadena de caracteres (string) en una posición dentro del rango de la tabla hash (0 a 1099).
    2. 1. Diseño del algoritmo de dispersion para llaves alfanumericas
    - Vamos a utilizar un enfoque común llamado Hashing Polinómico:
    - Iteramos sobre cada carácter de la cadena.
    - Asignamos un peso a cada carácter usando su valor ASCII.
    - Utilizamos un factor multiplicativo para aumentar la dispersión (por ejemplo, 31).
    - Aplicamos el módulo 1100 para asegurarnos de que el valor esté dentro del rango deseado (0 a 1099).
3. Explicacion del Algoritmo
    - factor = 31: Es un número primo que ayuda a distribuir mejor las cadenas (aunque puede ajustarse).
    - Para cada carácter en la cadena:
    - Multiplicamos el hash acumulado por factor y sumamos el valor ASCII del carácter.
    - Aplicamos el módulo 1100 para mantener el valor en el rango [0, 1099].