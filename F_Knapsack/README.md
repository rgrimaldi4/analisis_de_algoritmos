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


### Enfoque de fuerza bruta iterativo

Esta versión genera y analiza todas las combinaciones posibles de objetos.

Para `n` objetos existen `2^n` combinaciones, ya que cada objeto puede estar incluido o no incluido en la mochila.


Por ejemplo, con 3 objetos `A`, `B`, `C` existen `2^3=8` combinaciones:

`{ }, {A}, {B}, {C}, {A,B}, {A,C}, {B,C}, {A,B,C}`

El algoritmo recorre cada combinación y calcula su peso y valor total. Si el peso no supera la capacidad de la mochila, compara su valor con el mejor encontrado hasta ese momento.


### Enfoque recursivo con memoización

Esta versión mantiene el funcionamiento recursivo, pero utiliza una matriz de memoización para almacenar los resultados ya calculados.

Cada estado depende de:

- El objeto actual `i`.
- La capacidad disponible de la mochila.

Antes de realizar nuevamente un cálculo, se verifica si el resultado ya se encuentra almacenado:

```c
if(memo[i][capacidadBolsa] != -1){
    return memo[i][capacidadBolsa];
}
```

Cuando se obtiene el mejor resultado, este se guarda en la matriz para poder reutilizarlo posteriormente.

La matriz se inicializa con `-1`, indicando que los estados todavía no han sido calculados.

De esta forma se evita repetir los mismos cálculos realizados una y otra vez.


### Enfoque iterativo con programación dinámica

La versión iterativa utiliza una tabla de programación dinámica de tamaño:

```text
(n + 1) × (W + 1)
```

La tabla se inicializa en `0` y se construye desde los problemas más pequeños hasta obtener la solución completa.

Para cada objeto y cada capacidad se comparan dos posibilidades:

```c
int valorAgregado = valorActual +
    tabla[i - 1][c - pesoActual];

int valorIgnorado =
    tabla[i - 1][c];
```

Se almacena en la posición actual el mayor de estos valores. Al terminar, `tabla[longitud][capacidadBolsa]` contiene el mejor valor que puede obtenerse sin superar la capacidad de la mochila.

Este enfoque corresponde a programación dinámica **bottom-up**, ya que inicia con los casos más pequeños y construye progresivamente la solución.

---

## 3. Análisis de complejidad

| Enfoque | Técnica | Complejidad temporal |
|---|---|---|
| Recursivo | Recursión | `O(2^n)` |
| Fuerza bruta | Iterativo / combinaciones | `O(n · 2^n)` |
| Recursivo con memoización | Programación dinámica Top-Down | `O(n · W)` |
| Iterativo | Programación dinámica Bottom-Up | `O(n · W)` |

Los enfoques recursivo y de fuerza bruta presentan un crecimiento exponencial debido a la cantidad de posibilidades que deben analizar.

En cambio, las versiones con programación dinámica aprovechan los resultados de subproblemas ya resueltos. La versión con memoización lo hace mediante un enfoque **Top-Down**, mientras que la versión iterativa construye la solución mediante **Bottom-Up**.

---

### 4. Metodología experimental

Para realizar las pruebas se generan objetos con:

```text
Valor: 1 a 20
Peso:  1 a 10
Capacidad de la mochila: 50
```

Los programas registran el número de pasos realizados y el tiempo de ejecución mediante `clock()`. Por cada tamaño de entrada se imprime:

```text
n, mejor valor, pasos, tiempo
```

Por ejemplo:

```text
10, valor, pasos, tiempo
15, valor, pasos, tiempo
20, valor, pasos, tiempo
...
```

En las implementaciones se utiliza `srand(1)`, permitiendo trabajar con una secuencia reproducible de valores generados por `rand()`.

---

## 5. Graficas

### Fuerza bruta y Recursivo: Conteo de tiempos

![Recursivo](tiempos_recursivos.png)

### Fuerza bruta y Recursivo: Conteo de pasos

![Recursivo](pasos_recursivos.png)

### Memoizacion recursivo y Memoizacion iterativo: Conteo de pasos

![Recursivo](memoizaciones.png)

---

### 6. Análisis de los resultados

### Análisis de tiempos

Los resultados muestran una diferencia clara entre los enfoques utilizados. Los algoritmos recursivo y de fuerza bruta iterativo presentan un crecimiento rápido en el tiempo de ejecución, relacionado con sus complejidades O(2ⁿ) y O(n · 2ⁿ), respectivamente.

En el enfoque recursivo, el tiempo aumenta hasta 307.581 segundos para n = 50, mientras que fuerza bruta alcanza 15.922 segundos para n = 25. Las gráficas muestran que los tiempos inicialmente son pequeños, pero aumentan de forma considerable conforme crece el número de objetos, comportamiento característico de los algoritmos con crecimiento exponencial.

Por otro lado, las versiones recursiva con memoización e iterativa, mantienen tiempos considerablemente bajos. Al aumentar la entrada hasta n = 1000, los tiempos registrados permanecen por debajo de 1 segundo. Esto muestra el beneficio de almacenar y reutilizar resultados previamente calculados, evitando gran parte del trabajo repetido presente en los enfoques sin memoizacion.

### Análisis de pasos

Los resultados muestran un crecimiento considerable en el número de pasos de los algoritmos recursivo y de fuerza bruta iterativo, relacionado con sus complejidades O(2ⁿ) y O(n · 2ⁿ), respectivamente. Conforme aumenta el número de objetos, la cantidad de operaciones necesarias crece rápidamente.

En el enfoque recursivo, este crecimiento se debe a que para cada objeto se consideran las posibilidades de incluirlo o no incluirlo. En fuerza bruta, se generan las 2ⁿ combinaciones posibles y se recorren los n objetos para evaluar el peso y valor de cada combinación. Esto provoca el crecimiento exponencial observado en las gráficas.

### Analisis de pasos con Memoizacion

Los resultados muestran que el número de pasos se reduce considerablemente al utilizar memoización, debido a que los resultados de los subproblemas se almacenan y se reutilizan cuando vuelven a ser necesarios. De esta forma, se evita realizar repetidamente los mismos cálculos presentes en el enfoque recursivo sin memoización.

Tanto la versión recursiva con memoización como la versión iterativa presentan un crecimiento mucho menor en comparación con los enfoques exponenciales. En estos casos, el número de operaciones depende principalmente de la cantidad de objetos y de la capacidad de la mochila, dando una complejidad de O(n · W), donde n representa el número de objetos y W la capacidad de la mochila.

Este comportamiento se refleja en los resultados experimentales, donde el número de pasos crece de manera más controlada conforme aumenta n. La eliminacion de cálculos repetidos permite trabajar con entradas considerablemente mayores, lo cual también explica los bajos tiempos de ejecución mencionados anteriormente.

---

### Tecnologías utilizadas

- **Lenguaje:** C
- **Compilador:** GCC
- **Medición de tiempo:** `clock()`
- **Materia:** Análisis de Algoritmos
