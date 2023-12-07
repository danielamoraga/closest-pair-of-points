# closest-pair-of-points
Solving closest pair of points problem with two algorithms: "sweep line" and a randomized algorithm.

### Profesores:
- Benjamín Bustos
- Gonzalo Navarro

### Estudiantes
- Gonzalo Cisternas
- Javiera Jiménez
- Daniela Moraga

### Requerimientos
* C++
* Compilador

En caso de no tener esto, seguir los pasos de [esta página](https://code.visualstudio.com/docs/cpp/config-mingw).

### Archivos importantes
Los archivos **sweep-line.hpp** y **randomized.hpp** contienen los algoritmos correspondientes para retornar el par de puntos más cercanos y su distancia correspondiente. Las instrucciones de generación de puntos y las iteraciones para probar cada algoritmo se encuentran en el archivo **main.cpp**, que además crea archivos de texto con los resultados con los cuales posteriormente se generan los gráficos de visualización.

### Paso a paso
Una vez que se tienen los requerimientos, basta con ejecutar **main.cpp**, lo cual creará puntos de valores aleatorios entre 0 y 1, partiendo por una cantidad de desde 5 millones de puntos sobre la cual repetirá cada algoritmo 100 veces, y luego volverá a hacerlo con un paso de 5 millones de puntos hasta llegar a 50 millones. Para cada cantidad de puntos, se irá guardando el tiempo que demoró cada algoritmo en archivos de texto "resultados_5000000.txt, resultados_10000000.txt, etc." dentro de la carpeta **/results**, para luego poder utilizar estos datos para generar visualizaciones gráficas de las diferencias temporales entre ambos algoritmos.
