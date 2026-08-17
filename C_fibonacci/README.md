# Fibonacci
El propósito es analizar el comportamiento de diferentes formas de calcular la sucesión de Fibonacci y 
observar cómo cambia el número de pasos y el tiempo de ejecución.

En esta práctica se utiliza una versión recursiva y una versión recursiva con memoización, 
con el objetivo de comparar el comportamiento de ambas soluciones.

---

## 1. Descripción del problema

La sucesión de Fibonacci es una secuencia de números donde cada valor se obtiene sumando los dos valores anteriores.

Los primeros valores de la sucesión son:

```text
0, 1, 1, 2, 3, 5, 8, 13, 21, ...
```

La sucesión se define como:

```text
F(0) = 0
F(1) = 1
F(n) = F(n-1) + F(n-2)
```

El problema consiste en calcular los valores de Fibonacci desde `F(0)` hasta `F(n)` utilizando diferentes formas de resolver el mismo problema.

Se implementaron las siguientes versiones:

- Fibonacci recursivo.
- Fibonacci recursivo con memoización.

El objetivo es observar cómo cambia el número de pasos y el tiempo de ejecución entre ambas versiones conforme aumenta `n`.

---

## 2. Algoritmos implementados

### Fibonacci recursivo

**Archivo:** "fibo.c"

La versión recursiva calcula `F(n)` realizando llamadas a:

```text
F(n-1)
F(n-2)
```

Las llamadas continúan hasta alcanzar los casos base:

```text
F(0) = 0
F(1) = 1
```

Al regresar de las llamadas recursivas, los resultados se suman hasta obtener el valor solicitado.

El problema de esta implementación es que algunos valores de Fibonacci se calculan repetidamente.

Por ejemplo, para calcular `F(5)` se necesita calcular `F(3)` más de una vez. Esta repetición aumenta rápidamente conforme aumenta `n`.


### Fibonacci con memoización

**Archivo:** "fibomemo.c"

La segunda versión utiliza recursión con **memoización**.

La memoización consiste en almacenar los valores de Fibonacci que ya fueron calculados.

Antes de calcular `F(n)`, el algoritmo verifica si el resultado se encuentra almacenado:

```c
if(F[n] >= 0){
    return F[n];
}
```

Si el valor ya existe, se retorna directamente y no se vuelve a realizar el cálculo.

Si todavía no ha sido calculado, se obtiene mediante:

```text
F(n) = F(n-1) + F(n-2)
```

y posteriormente se almacena para poder utilizarlo nuevamente.

De esta forma se evita repetir los mismos cálculos realizados por la versión recursiva.

---

## 3. Análisis de complejidad

| Algoritmo | Complejidad temporal |
|---|:---:|
| Fibonacci recursivo | `O(2ⁿ)` |
| Fibonacci con memoización | `O(n)` |

### Fibonacci recursivo

Para calcular `F(n)`, el algoritmo realiza dos llamadas recursivas:

```text
F(n-1)
F(n-2)
```

Cada una de estas llamadas puede generar nuevas llamadas recursivas hasta alcanzar los casos base.

Debido a que varios valores se calculan repetidamente, el número de llamadas aumenta de forma exponencial conforme aumenta `n`.

Por lo tanto, para este análisis se considera una complejidad temporal de:

```text
O(2ⁿ)
```

### Fibonacci con memoización

La versión con memoización almacena cada resultado calculado.

Los valores:

```text
F(0), F(1), F(2), ..., F(n)
```

se calculan y se almacenan para evitar volver a realizar el mismo cálculo.

Por esta razón, el crecimiento se reduce a:

```text
O(n)
```

---

## 4. Metodología experimental

Para analizar el comportamiento de ambas versiones se utilizan diferentes valores de `n`.

Los valores comienzan en:

```text
n = 10
```

y aumentan de 2 en 2 hasta:

```text
n = 100
```

Para cada valor de `n` se registran:

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

Los pasos:

Para ambas versiones se considera como un **paso** cada vez que se realiza una llamada a la función `fibo()`.

El contador se incrementa mediante:

```c
pasos++;
```

Por lo tanto, el número de pasos permite observar la cantidad de llamadas realizadas por cada versión.

---

## 5. Graficas
A partir de los resultados experimentales se generaron gráficas para observar el crecimiento de los algoritmos conforme aumenta el valor de `n`.

### Fibonacci recursivo: Conteo de Pasos

![Recursivo](recursivo_pasos.png)

### Fibonacci con memoización: Conteo de Pasos

![Memoización](memo_pasos.png)

### Fibonacci recursivo: Conteo de Tiempo

![Memoización](recursivo_tiempos.png)

### Fibonacci con memoizacion: Conteo de Tiempo

![Memoización](memo_tiempos.png)

---

## 6. Análisis de resultados

En la versión recursiva, el número de llamadas aumenta rápidamente conforme aumenta `n`, debido a que los mismos valores de Fibonacci se calculan varias veces.

Este comportamiento produce un crecimiento exponencial, consistente con la complejidad:

```text
O(2ⁿ)
```

En la versión con memoización, los resultados calculados se almacenan y se reutilizan cuando son necesarios nuevamente.

Esto evita repetir cálculos y reduce considerablemente el número de operaciones realizadas.

Por esta razón, se espera observar un crecimiento mucho menor en comparación con la versión recursiva, consistente con:

```text
O(n)
```

Las gráficas permiten observar la diferencia entre resolver el problema mediante recursión simple y utilizar memoización para evitar cálculos repetidos.

---

## 8. Conclusiones

La versión recursiva de Fibonacci permite resolver el problema directamente utilizando su definición matemática. Sin embargo, realiza una gran cantidad de cálculos repetidos, provocando que el número de operaciones aumente rápidamente conforme crece `n`.

La versión con memoización utiliza la misma idea recursiva, pero almacena los resultados calculados para reutilizarlos cuando se necesitan nuevamente.

De esta forma, la complejidad temporal se reduce de:

```text
O(2ⁿ)
```

a:

```text
O(n)
```

La comparación permite observar cómo la memoización puede mejorar el comportamiento de un algoritmo al evitar el cálculo repetido de los mismos subproblemas.

---

### Tecnologías utilizadas

- **Lenguaje:** C
- **Compilador:** GCC
- **Medición de tiempo:** `clock()`
- **Materia:** Análisis de Algoritmos