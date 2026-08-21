# Dijkstra

## 1. Descripción

El algoritmo de **Dijkstra** permite encontrar las distancias mínimas desde un vértice inicial hacia los demás vértices de un grafo con pesos.

En este trabajo se implementaron dos enfoques para resolver el mismo problema:

- **Dijkstra con arreglo de distancias**.
- **Dijkstra con cola de prioridad**.

Ambas implementaciones utilizan una **matriz de adyacencia** para representar el grafo y comienzan desde el vértice 0. La diferencia principal se encuentra en la forma de seleccionar el siguiente vértice con menor distancia.

---

## 2. Algoritmos implementados

### Dijkstra con arreglo de distancias

Esta implementación utiliza tres arreglos principales:

- **dist**: almacena la menor distancia conocida desde el vértice inicial hasta cada vértice.
- **parent**: almacena el padre de cada vértice dentro del camino encontrado.
- **visitados**: indica si un vértice ya fue procesado.

Inicialmente, las distancias se establecen en infinito y la distancia del vértice inicial se establece en 0.

Para seleccionar el siguiente vértice, la función **extractMin** recorre el arreglo de distancias y busca el vértice no visitado que tenga la menor distancia.

Una vez seleccionado, se recorren sus vértices adyacentes. Para cada uno se calcula la distancia acumulada desde el origen y, si esta distancia es menor que la almacenada anteriormente, se actualizan su distancia y su padre.

Al finalizar, se imprime para cada vértice su padre y la distancia mínima encontrada desde el vértice inicial. 
---

### Dijkstra con cola de prioridad

Esta implementación utiliza los arreglos **dist**, **parent** y **visitados**, además de una **cola de prioridad** para almacenar los vértices pendientes.

La cola se organiza utilizando un **min-heap**, donde los vértices son comparados de acuerdo con la distancia almacenada en **dist**.

En cada iteración se extrae un vértice de la cola y posteriormente se reorganiza el heap mediante **min_heapify**.

Después se recorren los vértices adyacentes y se calcula la distancia acumulada. Si se encuentra una distancia menor, se actualizan **dist** y **parent**, y se reorganiza nuevamente el heap de acuerdo con las nuevas distancias.

Al finalizar, también se imprime para cada vértice su padre y la distancia mínima encontrada desde el vértice inicial. 
---

## 3. Análisis de complejidad

### Dijkstra con arreglo de distancias

La función **extractMin** recorre los n vértices para encontrar el vértice no visitado con menor distancia.

Además, cada vez que se selecciona un vértice se recorre una fila de la matriz de adyacencia para buscar sus conexiones.

Como este proceso se realiza para los n vértices, la complejidad de esta implementación es:

**O(n²)**
aqui
---

### Dijkstra con cola de prioridad

Esta implementación utiliza un **min-heap** para organizar los vértices de acuerdo con sus distancias.
x
La operación **`ExtractMin`** permite extraer el vértice con la menor distancia y despues se reorganiza el heap mediante **`min_heapify`**. 

Como un heap es un árbol binario completo, su altura crece de forma logarítmica respecto al número de vértices, es decir, **`O(log n)`**. Por lo tanto, en el peor caso min_heapify puede recorrer desde la raíz hasta una hoja, dando a ExtractMin una complejidad:

**O(log n)**

Cuando en la relajación se encuentra una distancia menor para un vértice, se utiliza **`DecreaseKey`** para actualizar su posición dentro del heap. Gracias al arreglo de posiciones, el vértice puede localizarse directamente y desplazarse hacia arriba en el heap, por lo que esta operación también tiene una complejidad de:

**O(log n)**

Y por cada vértice extraído se recorre una fila completa de la matriz de adyacencia para buscar sus conexiones. En el peor caso, se procesan `n` vértices y para cada uno se revisan hasta `n` posibles adyacentes.

Considerando que dentro de este recorrido puede ejecutarse `DecreaseKey`, el crecimiento en el peor caso es:

**n*n * log V**

Por lo tanto, la complejidad considerada para esta implementación es:

**O(n^2 log n)**

---

## 4. Funcionamiento

Para comprobar el funcionamiento de los algoritmos se utiliza un grafo almacenado en el archivo **grafo.csv** y representado mediante una matriz de adyacencia.

En ambas implementaciones se utilizan 5 vértices y se toma el vértice 0 como punto inicial:

**dijkstra(G, n_vertices, 0, 0);**

Los algoritmos calculan las distancias desde este vértice hacia los demás vértices del grafo. 
---

## 5. Datos de salida

Al finalizar la ejecución, los dos algoritmos muestran para cada vértice:

- **Vértice:** vértice correspondiente.
- **Padre:** vértice desde el cual se obtuvo la menor distancia.
- **Distancia:** distancia mínima encontrada desde el vértice inicial.

La salida permite observar los padres seleccionados por Dijkstra y las distancias mínimas obtenidas desde el vértice 0 hacia los demás vértices.

---

## 6. Comparación de los enfoques

Los dos algoritmos resuelven el mismo problema y utilizan una matriz de adyacencia, pero se diferencian principalmente en la forma de seleccionar el siguiente vértice.

La primera implementación utiliza un **arreglo de distancias** y realiza una búsqueda lineal para encontrar el vértice con menor distancia.

La segunda implementación utiliza una **cola de prioridad basada en un min-heap**, buscando mantener los vértices organizados de acuerdo con sus distancias.

De esta forma, ambas implementaciones permiten observar diferentes maneras de realizar la selección del siguiente vértice dentro del algoritmo de Dijkstra.

### Tecnologías utilizadas

- **Lenguaje:** C
- **Compilador:** GCC
- **Representación del grafo:** Matriz de adyacencia
- **Materia:** Análisis de Algoritmos