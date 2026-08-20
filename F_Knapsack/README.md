# Knapsack Problem

El **Knapsack Problem (problema de la mochila)** consiste en seleccionar un conjunto de objetos, donde cada objeto tiene un **peso** y un **valor**, buscando obtener el mayor valor posible sin superar la capacidad máxima de la mochila.

En este experimento se implementaron diferentes enfoques para resolver el mismo problema y comparar su comportamiento:

- Recursivo.
- Fuerza bruta iterativa.
- Recursivo con memoización.
- Iterativo con programación dinámica.

Cada objeto se representa mediante la estructura:

```c
typedef struct{
    char objeto;
    int valor;
    int peso;
}Tobjeto;
```

Los valores y pesos de los objetos se generan de forma aleatoria. En todos los experimentos se utiliza una capacidad de mochila de `50`.

---

## 2. Algoritmos implementados

### Enfoque recursivo

La versión recursiva analiza dos posibilidades para cada objeto:

1. **Agregar el objeto**, si su peso no supera la capacidad disponible.
2. **Ignorar el objeto** y continuar con el siguiente.

```c
if(objetos[i].peso <= capacidadBolsa){
    valorAgregado = objetos[i].valor +
        maximizar(objetos, longitud, i+1,
        capacidadBolsa-objetos[i].peso);
}

int valorIngnorado =
    maximizar(objetos, longitud, i+1, capacidadBolsa);
```

Finalmente se selecciona el mayor valor entre ambas posibilidades.

Al no almacenar resultados previamente calculados, se vuelven a resolver subproblemas, provocando un crecimiento exponencial.

### Complejidad

```text
O(2^n)
```















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

De esta forma se evita repetir los mismos cálculos realizados, como en la versión recursiva.

Este enfoque corresponde a programación dinámica **Top-Down**.

### Laberinto del Tesoro iterativo

**Archivo:** "laberintoiterativa.c"

La tercera versión utiliza programación dinámica de forma iterativa.

Se utiliza una matriz, donde cada posición almacena la cantidad máxima de tesoro que puede acumularse hasta esa posición.

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
| Laberinto recursivo | `O(2^(n+n))` |
| Laberinto con memoización | `O(n*m)` |
| Laberinto iterativo | `O(n²)` |

### Laberinto del Tesoro recursivo

Para una posición de la matriz, el algoritmo puede realizar dos llamadas recursivas:

```text
Arriba
Izquierda
```

Cada una de estas llamadas puede generar nuevas llamadas hasta alcanzar los límites de la matriz.

Además, algunas posiciones se calculan repetidamente.

Por lo tanto, para una matriz de `n × n`, se considera una complejidad temporal de:

```text
O(2^(n+n))
```

Este crecimiento provoca que la versión recursiva deje de ser práctica para matrices grandes.

### Laberinto del Tesoro con memoización

La versión con memoización almacena el resultado correspondiente a cada posición `(i,j)`.

En una matriz de tamaño:

```text
n × n
```

existen `n²` posiciones posibles.

Cada posición se calcula y se almacena para evitar volver a realizar el mismo cálculo.

Por esta razón, el crecimiento se reduce a:

```text
O(n²)
```

### Laberinto del Tesoro iterativo

La versión iterativa utiliza dos ciclos anidados para recorrer la matriz:

```c
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
```

Ambos ciclos recorren hasta `n`.

Por lo tanto, se recorren las `n²` posiciones de la matriz y la complejidad temporal es:

```text
O(n²)
```

---


## 4. Metodología experimental

Para analizar el comportamiento de las tres versiones se utilizan diferentes tamaños de matrices.

Los valores de la matriz se generan de forma aleatoria utilizando valores entre `1` y `20`.

Se utiliza una semilla fija:

```c
srand(1);
```

para mantener los mismos valores durante los experimentos.

Para cada tamaño de matriz se registran:

- Máximo tesoro acumulado.
- Número de pasos o llamadas.
- Tiempo de ejecución.

El tiempo se mide utilizando:

```c
clock()
```

y se convierte a segundos mediante:

```c
tiempo = (double)(tiempo_fin - tiempo_inicio) / CLOCKS_PER_SEC;
```

En la versión recursiva y con memoización se considera como un **paso** cada vez que se realiza una llamada a la función correspondiente.

En la versión iterativa se considera como un **paso** cada posición de la matriz procesada por los ciclos.

De esta forma, los resultados permiten observar el crecimiento de cada versión conforme aumenta el tamaño de la matriz.

---

## 5. Graficas

A partir de los resultados experimentales se generan gráficas para observar el crecimiento de los algoritmos conforme aumenta el tamaño de la matriz.

### Laberinto recursivo: Conteo de Pasos

![Recursivo](recursivo_pasos.png)

### Laberinto con memoización e iterativo: Conteo de Pasos

![MemoRecursivo](memo_iterativ_pasos.png)

### Laberinto recursivo: Conteo de Tiempos

![Recursivo](recursivo_tiempos.png)

### Laberinto con memoización e iterativo: Conteo de Tiempos

![Memoización](memo_iterativo_tiempos.png)

---

## 6. Análisis de resultados

La versión recursiva del Laberinto del Tesoro permite encontrar el máximo tesoro acumulado considerando los posibles caminos desde arriba y desde la izquierda. 
Sin embargo, realiza cálculos repetidos, provocando que el número de operaciones aumente rápidamente conforme aumenta el tamaño de la matriz.

Este comportamiento produce un crecimiento exponencial, consistente con:

```text
O(2^(n+n))
```

La versión con memoización mantiene el enfoque recursivo, pero almacena los resultados calculados para reutilizarlos cuando se necesitan nuevamente.

Esto evita repetir cálculos y reduce el crecimiento a:

```text
O(n*m)
```

La versión iterativa utiliza una matriz para construir los resultados desde la posición inicial hasta obtener el máximo tesoro acumulado en la posición final.

La versión iterativa presenta una complejidad:

```text
O(n²)
```

De esta forma, las versiones con programación dinámica reducen considerablemente el número de cálculos realizados en comparación con la versión recursiva.

La comparación permite observar cómo la memoización y la tabulación mejoran el comportamiento del algoritmo al evitar el cálculo repetido de los mismos subproblemas.

---

### Tecnologías utilizadas

- **Lenguaje:** C
- **Compilador:** GCC
- **Medición de tiempo:** `clock()`
- **Materia:** Análisis de Algoritmos