# Algoritmos de Ordenamiento
El objetivo es implementar y analizar diferentes algoritmos de ordenamiento, comparando su comportamiento teórico con los resultados obtenidos experimentalmente.

En esta práctica se estudian algoritmos con diferentes estrategias y complejidades, con el objetivo de observar cómo aumenta el número de operaciones y el tiempo de ejecución conforme crece el tamaño de entrada.

---

## 1. Descripción del problema
El problema consiste en ordenar de menor a mayor un conjunto de números enteros inicialmente desordenados.

Los datos de entrada se obtienen de un archivo que contiene números desordenados. A partir de estos datos se construyen arreglos de diferentes tamaños para analizar el comportamiento de los algoritmos conforme aumenta el número de elementos n.

Se implementaron y analizaron los siguientes algoritmos:

- **Ordenamiento por selección in-place: borrado fisico y borrado logico.
- **Bubble Sort.
- **Merge Sort.
- **Permutation Sort.

---

## 2. Algoritmos implementados

### Ordenamiento por selección In-Place
El algoritmo busca el elemento mayor dentro de la parte no ordenada del arreglo.

Una vez localizado, intercambia dicho elemento con la última posición disponible. Después del intercambio, el límite de búsqueda se reduce en una posición y el proceso se repite hasta ordenar completamente el arreglo. Esta implementación trabaja directamente sobre el arreglo original, por lo que no necesita construir un segundo arreglo para almacenar el resultado.

La práctica también contempla variantes de esta estrategia mediante borrado físico y borrado lógico.

<b>Borrado físico</b>
En esta versión, después de encontrar el elemento correspondiente, este se elimina físicamente del arreglo. Los elementos posteriores se desplazan una posición y el tamaño del arreglo disminuye.

**Archivo:** "inplace/ordenamiento.c"

<b>Borrado lógico</b>
En esta versión no se elimina físicamente el elemento. Después de seleccionar el mayor, su posición se marca para indicar que ya fue procesada. 

**Archivo:** "inplace/ordenamiento_bl.c"

### Bubble Sort
Bubble Sort recorre repetidamente el arreglo comparando elementos adyacentes.

Si dos elementos se encuentran en el orden incorrecto, se intercambian. Como resultado de cada recorrido, los elementos mayores se desplazan progresivamente hacia el final del arreglo.

Después de cada pasada se reduce la cantidad de elementos que necesitan ser comparados, ya que la parte final del arreglo se encuentra ordenada.

**Archivo:** "bubble_sort/order.c"

### Merge Sort
Merge Sort utiliza la estrategia de divide y vencerás.

El arreglo se divide recursivamente en dos partes hasta obtener subarreglos de un solo elemento. Posteriormente, durante el regreso de la recursión, los subarreglos se combinan mediante el proceso de merge.

Durante esta combinación se comparan los elementos de ambos subarreglos y se colocan ordenadamente en el arreglo resultante.

**Archivo:** "merge_sort/order.c"

### Permutation Sort

Permutation Sort genera diferentes permutaciones de los elementos del arreglo hasta encontrar un conjunto que se encuentre ordenado.

Después de generar una permutación, el algoritmo recorre el arreglo para verificar si los elementos están ordenados.

Este procedimiento puede requerir una gran cantidad de intentos conforme aumenta el tamaño de entrada, por lo que presenta un crecimiento considerablemente mayor que los otros algoritmos estudiados.

**Archivo:** "permutation_sort/order.c"

---

## 3. Análisis de complejidad

Se analiza la complejidad temporal de cada una de las soluciones implementadas.

| Algoritmo | Complejidad temporal |
|---|:---:|
| Selección In-Place | `O(n²)` |
| Bubble Sort | `O(n²)` |
| Merge Sort | `O(n log n)` |
| Permutation Sort | `O(n · n!)` |

#### Selección In-Place — `O(n²)`
El algoritmo utiliza dos ciclos anidados para ordenar el arreglo. El ciclo externo determina la parte del arreglo que todavía falta por ordenar, mientras que el ciclo interno recorre esa parte para buscar el elemento mayor.

En la primera iteración, el ciclo interno realiza aproximadamente n−1 comparaciones; en la siguiente, n−2; después n−3, y así sucesivamente:
El número aproximado de comparaciones es:
```text
(n - 1) + (n - 2) + (n - 3) + ... + 1
```

Esta suma corresponde a:
```text
n(n - 1) / 2
```

En el análisis asintótico se eliminan las constantes y los términos de menor crecimiento, por lo que domina:
```text
O(n²)
```

#### Bubble Sort — `O(n²)`

Bubble Sort utiliza dos ciclos anidados para realizar recorridos sucesivos sobre el arreglo. En cada pasada, el ciclo interno compara elementos adyacentes y los intercambia si están en el orden incorrecto.

Al terminar cada pasada, el elemento mayor de la parte no ordenada queda colocado en su posición final. Por esta razón, en cada nueva pasada se puede reducir en uno la cantidad de elementos que se recorren.

El número de comparaciones disminuye progresivamente:
```text
(n - 1) + (n - 2) + ... + 1
```

Por lo tanto, su complejidad temporal es:
```text
O(n²)
```

#### Merge Sort — `O(n log n)`

Merge Sort divide repetidamente el arreglo aproximadamente a la mitad hasta obtener subarreglos de un solo elemento. Como en cada división el tamaño del problema se reduce a la mitad, se generan aproximadamente:
```text
log₂(n)
```
niveles de recursión.

Al regresar de la recursión, los subarreglos se mezclan de forma ordenada. En cada nivel de recursión, el proceso de mezcla recorre en total los n elementos del arreglo.
Por lo tanto:
```text
n × log₂(n)
```

y su complejidad temporal es:
```text
O(n log n)
```

#### Permutation Sort — `O(n · n!)`
Permutation Sort genera diferentes permutaciones de los elementos del arreglo y comprueba cada una hasta encontrar una que esté ordenada.

Para `n` elementos existen:
```text
n!
```
permutaciones posibles.

Además, comprobar si una permutación está ordenada puede requerir recorrer hasta `n` elementos.
Por lo tanto, el crecimiento considerado para el análisis es:
```text
O(n · n!)
```

Este crecimiento factorial provoca que el algoritmo deje de ser práctico incluso para tamaños de entrada relativamente pequeños.

---

## 4. Metodología experimental
Para estudiar el comportamiento de los algoritmos se utilizaron conjuntos de datos con diferentes tamaños de entrada.

Para cada tamaño se registraron:

- **Tamaño de entrada (`n`).**
- **Número de pasos realizados.**
- **Tiempo de ejecución en segundos.**

En los algoritmos donde se realizaron 30 experimentos para cada tamaño de entrada, se descartaron el tiempo máximo y el tiempo mínimo para reducir el efecto de valores extremos.

El promedio se calculó utilizando las 28 mediciones restantes:

```text
promedio = (suma_tiempos - tiempo_mayor - tiempo_menor) / 28
```

El tiempo de ejecución fue medido en C utilizando:

```c
clock()
```

y convertido a segundos mediante:

```c
tiempo = (double)(fin_tiempo - inicio_tiempo) / CLOCKS_PER_SEC;
```

### Tamaños de entrada

Para los algoritmos capaces de trabajar con entradas grandes se utilizaron tamaños crecientes hasta llegar a:

```text
n = 100000
```

Permutation Sort requiere tamaños considerablemente menores debido a su rápido crecimiento.

---

## 5. Resultados

Los resultados experimentales obtenidos se almacenaron en archivos `.csv` para posteriormente calcular promedios y generar las gráficas correspondientes.

Para cada algoritmo se analizaron principalmente las siguientes variables:

| Tamaño `n` | Pasos | Tiempo promedio (s) |
|---:|---:|---:|
| ... | ... | ... |
| ... | ... | ... |
| ... | ... | ... |

Los resultados permiten comparar experimentalmente cómo aumenta el costo computacional de cada algoritmo conforme aumenta el tamaño de entrada.

---

## 6. Gráficas

A partir de los resultados experimentales se generaron gráficas para observar el crecimiento de los algoritmos conforme aumenta el tamaño de entrada.

![Gráficas](graficas.png)


![Permutation sort](permutation_sort.png)

---

## 7. 🔎 Análisis de resultados

Teóricamente se espera observar diferencias importantes entre los algoritmos conforme aumenta el tamaño de entrada.

**Selección In-Place** y **Bubble Sort** presentan crecimiento cuadrático `O(n²)`. Por lo tanto, al aumentar `n`, el número de operaciones aumenta considerablemente.

**Merge Sort** presenta una complejidad `O(n log n)`, por lo que se espera que su crecimiento sea menor que el de los algoritmos cuadráticos cuando se utilizan entradas grandes.

**Permutation Sort** presenta el crecimiento más elevado de los algoritmos estudiados. Debido al número de permutaciones posibles, el incremento del tamaño de entrada provoca un aumento muy rápido del número de operaciones necesarias.

Los resultados experimentales deberán contrastarse con estos comportamientos teóricos mediante las gráficas de pasos y tiempos obtenidas.
---

## 8. Conclusiones

La implementación de diferentes algoritmos para resolver un mismo problema permite observar que la estrategia utilizada tiene un efecto directo sobre la eficiencia computacional.

Los algoritmos cuadráticos, como Bubble Sort y el ordenamiento por selección In-Place, pueden funcionar adecuadamente para entradas pequeñas, pero su costo aumenta rápidamente conforme crece `n`.

Merge Sort utiliza la estrategia de divide y vencerás para reducir el crecimiento a `O(n log n)`, lo que teóricamente permite un mejor comportamiento para conjuntos de datos grandes.

Por otro lado, Permutation Sort presenta un crecimiento factorial y permite observar experimentalmente cómo un algoritmo puede volverse impráctico incluso con incrementos pequeños en el tamaño de entrada.

La comparación entre el análisis teórico, el número de pasos y los tiempos de ejecución permite comprender la importancia de la complejidad algorítmica al seleccionar una solución para un problema.

---

### Tecnologías utilizadas

- **Lenguaje:** C
- **Compilador:** GCC
- **Medición de tiempo:** `clock()`
- **Datos experimentales:** archivos CSV
- **Materia:** Análisis de Algoritmos