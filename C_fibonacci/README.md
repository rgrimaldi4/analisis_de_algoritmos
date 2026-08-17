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
