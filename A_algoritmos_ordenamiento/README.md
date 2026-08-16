# 📊 Nombre del problema

Práctica desarrollada para la materia **Análisis de Algoritmos**, cuyo propósito es implementar, experimentar y analizar diferentes algoritmos o estrategias para resolver un problema, comparando su comportamiento teórico con los resultados obtenidos experimentalmente.

---

## 1. 📌 Descripción del problema

Describir brevemente el problema que se desea resolver.

Incluir:

- ¿En qué consiste el problema?
- ¿Qué datos recibe?
- ¿Qué resultado debe obtener?
- ¿Qué versiones o algoritmos se utilizaron para resolverlo?

---

## 2. ⚙️ Algoritmos implementados

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