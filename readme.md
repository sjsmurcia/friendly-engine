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

