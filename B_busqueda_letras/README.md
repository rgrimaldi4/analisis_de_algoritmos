# Busqueda de cadenas de texto
propósito es analizar experimentalmente el comportamiento de un algoritmo de búsqueda de patrones dentro de una cadena de texto.

En esta práctica se utiliza el método de búsqueda ingenua (Naive String Matching) y se analiza cómo cambia el tiempo de ejecución conforme aumenta la longitud del patrón buscado.

---

## 1. Descripción del problema
El problema consiste en determinar las posiciones en las que un patrón aparece dentro de una cadena de texto.

Para realizar los experimentos se utilizan dos archivos:

- `letras_1000.txt`: contiene los caracteres utilizados para formar el patrón de búsqueda.
- `letras_100000.txt`: contiene el texto de **100 000 caracteres** sobre el cual se realiza la búsqueda.

El tamaño del texto permanece constante, mientras que la longitud del patrón aumenta progresivamente.

Los tamaños de patrón utilizados son:

```text
m = 10, 20, 30, ..., 1000
```

El objetivo es observar cómo afecta el incremento del tamaño del patrón al tiempo requerido para realizar la búsqueda.

---

## 2. Algoritmos implementados
### Búsqueda ingenua de patrones

El algoritmo coloca el patrón en cada posición posible del texto y compara sus caracteres uno por uno.

Para cada posición `i` del texto:

1. Se considera inicialmente que el patrón fue encontrado.
2. Se comparan los caracteres del patrón con los caracteres correspondientes del texto.
3. Si alguno de los caracteres es diferente, se marca que el patrón no coincide en esa posición.
4. El proceso continúa con la siguiente posición del texto.

En el programa, este comportamiento se realiza mediante dos ciclos anidados:

```c
for(int i=0; i<=100000-contador; i++){
    bool encontrado = true;

    for(int j=0; j<contador; j++){
        if(cadenaA[j] != cadenaB[i+j]){
            encontrado = false;
        }
    }
}
```

El ciclo externo recorre todas las posiciones donde puede comenzar el patrón y el ciclo interno compara los caracteres del patrón con el texto.

---

## 3. Análisis de complejidad
Sea:

```text
n = longitud del texto
m = longitud del patrón
```

El patrón puede comenzar aproximadamente en:

```text
n - m + 1
```

posiciones diferentes.

Para cada una de esas posiciones se comparan `m` caracteres.

Por lo tanto, el número de comparaciones es aproximadamente:

```text
(n - m + 1) · m
```

La complejidad temporal puede expresarse como:

```text
O(n · m)
```

### Comportamiento del experimento

En esta práctica:

```text
n = 100000
```

permanece constante y solamente aumenta `m`.

Por lo tanto:

```text
T(m) ≈ (100000 - m + 1) · m
```

Para los valores utilizados, de `m = 10` hasta `m = 1000`, se espera observar un crecimiento aproximadamente **lineal respecto al tamaño del patrón**, debido a que el tamaño del texto permanece constante.

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

## 7. Análisis de resultados

Teóricamente se espera observar diferencias importantes entre los algoritmos conforme aumenta el tamaño de entrada.

**Selección In-Place** y **Bubble Sort** presentan crecimiento cuadrático `O(n²)`. Por lo tanto, al aumentar `n`, el número de operaciones aumenta considerablemente.

**Merge Sort** presenta una complejidad `O(n log n)`, por lo que se espera que su crecimiento sea menor que el de los algoritmos cuadráticos cuando se utilizan entradas grandes.

**Permutation Sort** presenta el crecimiento más elevado de los algoritmos estudiados. Debido al número de permutaciones posibles, el incremento del tamaño de entrada provoca un aumento muy rápido del número de operaciones necesarias.

---

## 8. Conclusiones

La implementación de diferentes algoritmos para resolver un mismo problema permite observar que la estrategia utilizada tiene un efecto directo sobre la eficiencia computacional.

Los algoritmos cuadráticos, como Bubble Sort y el ordenamiento por selección In-Place, pueden funcionar adecuadamente para entradas pequeñas, pero su costo aumenta rápidamente conforme crece `n`.

Merge Sort utiliza la estrategia de divide y vencerás para reducir el crecimiento a `O(n log n)`, lo que teóricamente permite un mejor comportamiento para conjuntos de datos grandes.

Por otro lado, Permutation Sort presenta un crecimiento factorial y permite observar experimentalmente cómo un algoritmo puede volverse impráctico incluso con incrementos pequeños en el tamaño de entrada.

---

### Tecnologías utilizadas

- **Lenguaje:** C
- **Compilador:** GCC
- **Medición de tiempo:** `clock()`
- **Datos experimentales:** archivos CSV
- **Materia:** Análisis de Algoritmos