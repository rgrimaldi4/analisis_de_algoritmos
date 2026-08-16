# 📊 Nombre del problema
El objetivo es implementar y analizar diferentes algoritmos de ordenamiento, comparando su comportamiento teórico con los resultados obtenidos experimentalmente.

En esta práctica se estudian algoritmos con diferentes estrategias y complejidades, con el objetivo de observar cómo aumenta el número de operaciones y el tiempo de ejecución conforme crece el tamaño de entrada.

---

## 1. 📌 Descripción del problema
El problema consiste en ordenar de menor a mayor un conjunto de números enteros inicialmente desordenados.

Los datos de entrada se obtienen de un archivo que contiene números desordenados. A partir de estos datos se construyen arreglos de diferentes tamaños para analizar el comportamiento de los algoritmos conforme aumenta el número de elementos n.

Se implementaron y analizaron los siguientes algoritmos:

Ordenamiento por selección in-place: borrado fisico y borrado logico
Bubble Sort.
Merge Sort.
Permutation Sort.

El propósito es comparar el crecimiento del número de pasos y del tiempo de ejecución de cada algoritmo, relacionando los resultados experimentales con su complejidad teórica.

---

## 2. ⚙️ Algoritmos implementados
El algoritmo busca el elemento mayor dentro de la parte no ordenada del arreglo.

Una vez localizado, intercambia dicho elemento con la última posición disponible. Después del intercambio, el límite de búsqueda se reduce en una posición y el proceso se repite hasta ordenar completamente el arreglo.

Esta implementación trabaja directamente sobre el arreglo original, por lo que no necesita construir un segundo arreglo para almacenar el resultado.

La práctica también contempla variantes de esta estrategia mediante borrado físico y borrado lógico.

### Algoritmo / Versión 1

Describir brevemente cómo funciona la primera implementación.

**Archivo:** `nombre_algoritmo_1.c`

### Algoritmo / Versión 2

Describir brevemente cómo funciona la segunda implementación.

**Archivo:** `nombre_algoritmo_2.c`

### Algoritmo / Versión 3

Describir brevemente cómo funciona la tercera implementación.

**Archivo:** `nombre_algoritmo_3.c`

---

## 3. 📈 Análisis de complejidad

Se analiza la complejidad temporal de cada una de las soluciones implementadas.

| Algoritmo | Complejidad temporal | Complejidad espacial |
|---|:---:|:---:|
| Versión 1 | `O(...)` | `O(...)` |
| Versión 2 | `O(...)` | `O(...)` |
| Versión 3 | `O(...)` | `O(...)` |

### Justificación

Explicar brevemente por qué cada algoritmo presenta dicha complejidad.

Por ejemplo:

> El algoritmo contiene dos ciclos anidados que dependen del tamaño de entrada `n`. Por cada iteración del primer ciclo, el segundo realiza aproximadamente `n` operaciones, produciendo un crecimiento cuadrático `O(n²)`.

---

## 4. 🧪 Metodología experimental

Para analizar el comportamiento de los algoritmos se realizaron experimentos utilizando diferentes tamaños de entrada.

Para cada tamaño de entrada se registraron:

- **Tamaño de entrada (`n`).**
- **Número de pasos realizados.**
- **Tiempo de ejecución.**

Cada prueba se realizó **30 veces**. Cuando corresponde, se eliminó el tiempo mayor y el tiempo menor, calculando el promedio con las **28 ejecuciones restantes**.

El tiempo promedio se calculó mediante:

```text
promedio = (suma_tiempos - tiempo_mayor - tiempo_menor) / 28
```

### Definición de paso

Para este problema se considera como un **paso**:

> [Indicar qué operación se está contando como paso.]

Los tamaños de entrada utilizados fueron:

```text
n = [...]
```

---

## 5. 📋 Resultados

Los resultados obtenidos durante los experimentos fueron almacenados en archivos `.csv` para su posterior análisis.

Ejemplo de los datos obtenidos:

| Tamaño `n` | Pasos | Tiempo promedio (s) |
|---:|---:|---:|
| 1000 | ... | ... |
| 2000 | ... | ... |
| 3000 | ... | ... |
| 4000 | ... | ... |
| ... | ... | ... |

Los resultados completos pueden consultarse en la carpeta:

```text
datos/
```

---

## 6. 📊 Gráficas

A partir de los resultados experimentales se generaron gráficas para observar el crecimiento de los algoritmos conforme aumenta el tamaño de entrada.

### Número de pasos

![Número de pasos](graficas/pasos.png)

### Tiempo de ejecución

![Tiempo de ejecución](graficas/tiempos.png)

### Comparación de algoritmos

Cuando existen diferentes soluciones para el mismo problema, se comparan sus resultados:

![Comparación de algoritmos](graficas/comparacion.png)

---

## 7. 🔎 Análisis de resultados

Analizar el comportamiento observado durante los experimentos.

Considerar:

- La forma de crecimiento de la gráfica.
- El crecimiento del número de pasos.
- El crecimiento del tiempo de ejecución.
- Las diferencias entre las implementaciones.
- La relación entre los resultados experimentales y la complejidad teórica.

Por ejemplo:

> Los resultados muestran que el número de pasos aumenta de forma cuadrática conforme crece el tamaño de entrada. La gráfica presenta una tendencia consistente con la complejidad teórica `O(n²)`.

> Los tiempos de ejecución presentan pequeñas variaciones entre experimentos debido a factores propios del sistema; sin embargo, la tendencia general coincide con el crecimiento observado en el número de pasos.

---

## 8. ✅ Conclusiones

Describir las principales conclusiones obtenidas después de realizar los experimentos.

Considerar:

- ¿Qué algoritmo presentó mejor comportamiento?
- ¿Cómo afecta el tamaño de entrada?
- ¿Coincide el comportamiento experimental con la complejidad teórica?
- ¿Qué ventajas o desventajas presenta cada solución?

---

### 🛠️ Tecnologías utilizadas

- **Lenguaje:** C
- **Compilador:** GCC
- **Medición de tiempo:** `clock()`
- **Datos experimentales:** CSV
- **Materia:** Análisis de Algoritmos