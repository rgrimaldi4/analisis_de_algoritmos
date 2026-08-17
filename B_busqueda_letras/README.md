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
---

## 4. Metodología experimental
El texto utilizado para realizar las búsquedas tiene una longitud de:

```text
100000 caracteres
```

El tamaño del patrón comienza en:

```text
10 caracteres
```

y aumenta de 10 en 10 hasta alcanzar:

```text
1000 caracteres
```

Para cada tamaño de patrón se realizan **30 ejecuciones**.

En cada ejecución se registra el tiempo requerido para recorrer el texto y realizar las comparaciones.

Posteriormente se descartan el tiempo máximo y el tiempo mínimo  para reducir el efecto de valores extremos.

El promedio se obtiene utilizando las **28 ejecuciones restantes**:

```text
promedio = (suma_tiempos - tiempo_mayor - tiempo_menor) / 28
```

El tiempo se mide utilizando:

```c
clock()
```

y se convierte a segundos mediante:

```c
tiempo = (double)(fin_tiempo - inicio_tiempo) / CLOCKS_PER_SEC;
```
---

## 5. Resultados

Para cada tamaño de patrón se obtiene el tiempo promedio de ejecución.

Los resultados pueden organizarse de la siguiente manera:

| Longitud del patrón `m` | Tiempo promedio (s) |
|---:|---:|
| 10 | ... |
| 20 | ... |
| 30 | ... |
| 40 | ... |
| ... | ... |
| 1000 | ... |

El programa imprime un tiempo promedio por cada tamaño de patrón analizado.

---

## 6. Gráficas

A partir de los resultados experimentales se generaron gráficas para observar el crecimiento de los algoritmos conforme aumenta el tamaño de entrada.

![Graficas](graficas/busquedaletras.png)

---

## 7. Análisis de resultados

El algoritmo realiza una comparación del patrón en cada posición posible del texto.

Cuando aumenta la longitud del patrón, el ciclo interno debe realizar una mayor cantidad de comparaciones para cada posición analizada.

El número de operaciones está determinado por:

```text
(n - m + 1) · m
```

Debido a que durante los experimentos `n = 100000` permanece constante y `m` aumenta desde 10 hasta 1000, se espera que los tiempos presenten una tendencia aproximadamente lineal respecto al crecimiento del patrón.

---

## 8. Conclusiones
La búsqueda ingenua de patrones utiliza una estrategia sencilla basada en comparar directamente los caracteres del patrón con diferentes posiciones del texto.

Su complejidad depende tanto de la longitud del texto `n` como de la longitud del patrón `m`, obteniendo un crecimiento de:

```text
O(n · m)
```

En los experimentos realizados, el tamaño del texto permanece constante y únicamente aumenta la longitud del patrón. Por esta razón, el análisis experimental permite observar principalmente el efecto que tiene `m` sobre el tiempo de ejecución.

La práctica permite comprobar cómo el aumento del número de comparaciones influye directamente en el tiempo requerido para realizar una búsqueda.

---

### Tecnologías utilizadas

- **Lenguaje:** C
- **Compilador:** GCC
- **Medición de tiempo:** `clock()`
- **Datos experimentales:** archivos CSV
- **Materia:** Análisis de Algoritmos