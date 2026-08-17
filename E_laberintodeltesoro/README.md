# Laberinto del Tesoro

El propósito es analizar el comportamiento de diferentes formas de resolver el problema del Laberinto del Tesoro y observar cómo cambia el número de pasos y el tiempo de ejecución.

En esta práctica se utiliza una versión recursiva, una versión recursiva con memoización y una versión iterativa, con el objetivo de comparar el comportamiento de las tres soluciones.

---

## 1. Descripción del problema

El problema del Laberinto del Tesoro consiste en encontrar el camino que permita acumular la mayor cantidad de tesoro dentro de una matriz.

Cada posición de la matriz contiene una cantidad de tesoro y para llegar a una posición se consideran los caminos que provienen desde arriba o desde la izquierda.

Para cada posición se selecciona el camino que permita acumular la mayor cantidad de tesoro.

El problema consiste en obtener el máximo tesoro acumulado desde la posición inicial:

```text
(0,0)
```

hasta la posición final:

```text
(n-1,n-1)
```

Se implementaron las siguientes versiones:

- Laberinto del Tesoro recursivo.
- Laberinto del Tesoro con memoización.
- Laberinto del Tesoro iterativo.

El objetivo es observar cómo cambia el número de pasos y el tiempo de ejecución entre las tres versiones conforme aumenta el tamaño de la matriz.

---

## 2. Algoritmos implementados

### Laberinto del Tesoro recursivo

**Archivo:** "laberintotesoro_.c"

La versión recursiva inicia desde la posición final de la matriz y realiza llamadas recursivas considerando dos posibles caminos:

```text
Arriba
Izquierda
```

Para cada posición se calculan ambos caminos y se selecciona el que permita acumular la mayor cantidad de tesoro.

```c
int arriba = LT_rec(i - 1, j);
int izquierda = LT_rec(i, j - 1);
```

Este proceso continúa hasta alcanzar la posición inicial `(0,0)`.

El problema de esta implementación es que algunos caminos y posiciones se calculan repetidamente, provocando que el número de llamadas aumente rápidamente conforme aumenta el tamaño de la matriz.

### Laberinto del Tesoro con memoización

**Archivo:** "laberintomemo.c"

La segunda versión utiliza recursión con **memoización**.

La memoización consiste en almacenar en una matriz los resultados que ya fueron calculados.

Antes de calcular nuevamente una posición, el algoritmo verifica si el resultado se encuentra almacenado:

```c
if (dp[i][j] != -1)
    return dp[i][j];
```

Si el resultado ya existe, se retorna directamente y no se vuelve a realizar el mismo cálculo.

De esta forma se evita repetir los mismos cálculos realizados por la versión recursiva.

Este enfoque corresponde a programación dinámica **Top-Down**.

### Laberinto del Tesoro iterativo

**Archivo:** "laberintoiterativa.c"

La tercera versión utiliza programación dinámica de forma iterativa.

Se utiliza una matriz `dp` donde cada posición almacena la cantidad máxima de tesoro que puede acumularse hasta esa posición.

El algoritmo recorre la matriz utilizando dos ciclos anidados.

Para cada posición se obtiene el valor acumulado desde arriba y desde la izquierda:

```c
int arriba = dp[i - 1][j];
int izquierda = dp[i][j - 1];
```

Posteriormente se selecciona el mayor y se suma el tesoro de la posición actual.

Este enfoque corresponde a programación dinámica **Bottom-Up** o tabulación.

---













## 3. Análisis de complejidad

| Algoritmo | Complejidad temporal |
|---|:---:|
| LCSS recursivo | `O(2^(n+m))` |
| LCSS con memoización | `O(n · m)` |
| LCSS iterativo | `O(n · m)` |

### LCSS recursivo

Cuando los caracteres no coinciden, el algoritmo realiza dos llamadas recursivas.

Estas llamadas pueden generar nuevas llamadas hasta alcanzar el final de alguna de las cadenas.

Además, algunos subproblemas se calculan repetidamente.

Por lo tanto, se considera una complejidad temporal de:

```text
O(2^(n+m))
```

### LCSS con memoización

La versión con memoización almacena los resultados correspondientes a cada combinación de posiciones `(i,j)`.

Como existen hasta `n · m` combinaciones posibles y cada una se calcula una sola vez, la complejidad se reduce a:

```text
O(n · m)
```

### LCSS iterativo

La versión iterativa utiliza dos ciclos anidados.

El primer ciclo recorre los `n` caracteres de una cadena y el segundo los `m` caracteres de la otra.

Por lo tanto, se realizan aproximadamente `n · m` operaciones:

```text
O(n · m)
```

---

## 4. Metodología experimental

Para analizar el comportamiento de las versiones se utilizan diferentes tamaños de cadenas.

Para cada tamaño se registran:

- Número de pasos.
- Tiempo de ejecución.

El tiempo se mide utilizando:

```c
clock()
```

y se convierte a segundos mediante:

```c
tiempo = (double)(tiempo_fin - tiempo_inicio) / CLOCKS_PER_SEC;
```

En la versión recursiva y con memoización se considera como un **paso** cada vez que se realiza una llamada a la función `LCSS()`.

El contador se incrementa mediante:

```c
pasos++;
```

En la versión iterativa se considera como un **paso** cada iteración realizada por los dos ciclos que recorren la matriz.

De esta forma, los resultados permiten comparar el crecimiento de las diferentes versiones.

---

## 5. Graficas

A partir de los resultados experimentales se generan gráficas para observar el crecimiento de los algoritmos conforme aumenta el tamaño de las cadenas.

### LCSS recursivo: Conteo de Pasos

![Recursivo](recursivo_pasos.png)

### LCSS recursivo: Conteo de Tiempos

![Recursivo](recursivo_tiempo.png)


### LCSS con memoización e iterativo: Conteo de Pasos

![Memoización](memo_iterativo_pasos.png)

### LCSS con memoización e iterativo: Conteo de Tiempos

![Memoización](memo_iterativa_tiempos.png)

---

## 6. Análisis de resultados

En la versión recursiva, el número de llamadas aumenta rápidamente conforme aumenta el tamaño de las cadenas, debido a que algunos subproblemas se calculan varias veces.

Este comportamiento produce un crecimiento exponencial, consistente con:

```text
O(2^(n+m))
```

En la versión con memoización, los resultados calculados se almacenan y se reutilizan cuando son necesarios nuevamente.

Esto evita repetir cálculos y reduce el crecimiento a:

```text
O(n · m)
```

La versión iterativa también presenta una complejidad:

```text
O(n · m)
```

debido a que utiliza dos ciclos anidados para recorrer las combinaciones de posiciones de ambas cadenas.

Las gráficas permiten observar la diferencia entre resolver LCSS mediante recursión simple y utilizar programación dinámica mediante memoización o tabulación.

---

## 7. Conclusiones

La versión recursiva de LCSS permite resolver el problema utilizando llamadas recursivas. Sin embargo, algunos subproblemas se calculan repetidamente, provocando que el número de operaciones aumente rápidamente conforme aumenta el tamaño de las cadenas.

La versión con memoización mantiene el enfoque recursivo, pero almacena los resultados calculados para evitar repetir los mismos subproblemas.

La versión iterativa utiliza una matriz para construir los resultados desde los casos más pequeños hasta obtener la solución final.

De esta forma, las versiones con programación dinámica reducen la complejidad temporal de un crecimiento exponencial a:

```text
O(n · m)
```

La comparación permite observar que la memoización e iterativa mejoran el comportamiento del algoritmo al evitar el cálculo repetido de los mismos subproblemas.

---

### Tecnologías utilizadas

- **Lenguaje:** C
- **Compilador:** GCC
- **Medición de tiempo:** `clock()`
- **Materia:** Análisis de Algoritmos