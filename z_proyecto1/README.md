<h1>Compresión de archivos de texto con el algoritmo de Huffman</h1>
<p>
Este proyecto comprime archivos de texto que contienen únicamente caracteres
ASCII permitidos por el alfabeto definido en el programa.
</p>
<p><strong>Alfabeto permitido (55 símbolos):</strong></p>
<ul>
    <li>Letras minúsculas: <code>a-z</code></li>
    <li>Letras mayúsculas: <code>A-Z</code></li>
    <li>Punto (<code>.</code>)</li>
    <li>Coma (<code>,</code>)</li>
    <li>Espacio en blanco</li>
</ul>
<p><strong>Restricciones:</strong></p>
<ul>
    <li>No se permiten acentos.</li>
    <li>No se permite la letra <code>ñ</code>.</li>
</ul>



<h2>Programas del proyecto</h2>
<p>El proyecto consta de dos programas.</p>
<ul>
    <li><strong>codifica.c</strong> – Comprime un archivo de texto utilizando el algoritmo de Huffman.</li>
    <li><strong>decodifica.c</strong> – Descomprime el mensaje original a partir del archivo comprimido.</li>
</ul>
<hr>
<h2>Programa: <code>codifica.c</code></h2>
<p>Este programa hace lo siguiente</p>
<ol>
    <li>Recibe un archivo de texto como entrada</li>
    <li>Calcula la frecuencia de cada símbolo</li>
    <li>Construye el árbol de Huffman</li>
    <li>Genera un archivo binario comprimido</li>
</ol>


<p>
    <strong>1. Datos de entrada.</strong><br>
    <code>codifica.c</code> recibe por linea de comandos el nombre del archivo de texto de entrada y el nombre que tendrá el archivo comprimido, como se muestra en el siguiente ejemplo:
    <pre><code>codifica.c mensaje.txt mensaje.cod</code></pre>
</p>


<p>
    <strong>2. Conteo de frecuencias.</strong><br>
    Para contar las frecuencias se utiliza un vector de longitud 128, donde cada posición corresponde a un código ASCII entre 0 y 127.<br> 
    De esta forma, es posible acceder e incrementar la frecuencia de cualquier carácter en tiempo constante <code>O(1)</code>.<br>
</p>
<blockquote>
<p style="padding-left: 40px;">
    <strong>Funcionamiento general:</strong><br>
    1. Se marcan con <code>-1</code> todas las posiciones del vector de frecuencias.<br>
    2. Los 55 caracteres admitidos se inicializan en <code>0</code>.<br>
    3. Se lee el archivo a comprimir carácter por carácter y, por cada carácter leído, se incrementa en <code>1</code> la posición correspondiente del vector de frecuencias.<br>
    Salida: Vector de frecuencias de cada caracter usado en el documento.
</p>
</blockquote>


<p>
    <strong>3. Construir el árbol de Huffman.</strong><br>
    Para esto, se utilizó un vector de apuntadores, donde cada posición apunta a un nodo.<br>
    El vector funciona como una cola de prioridad, y cada nodo representa un carácter y su frecuencia.<br>
    Las estructuras del vector y de los nodos se muestran a continuación.
</p>
<pre><code>
    typedef struct nodo {
        int caracter;
        int frecuencia;
        struct nodo *izq;
        struct nodo *der;
    } Tnodo;
    
    typedef struct {
        Tnodo **caracteres;
        int tamanio;
    } TnodoCola;
</code></pre>
<blockquote>
<p style="padding-left: 40px;">
    <strong>Funcionamiento general:</strong><br>
    Entrada: Vector de frecuencias.<br>
    1. Por cada carácter con frecuencia mayor que <code>0</code>, se crea un nodo hoja que almacena el carácter y su frecuencia, y se inserta en el vector de apuntadores (cola de prioridad).<br>
    2. La cola se ordena de menor a mayor según la frecuencia. La complejidad temporal de ordenamiento es cuadratica <code>O(n²)</code>.<br>
    3. Cuando la cola esta completa y ordenada, se ejecuta el algoritmo Huffman, que hace lo siguiente.<br>
    4. Si existen mas de un nodo en la cola de prioridad, se extraen los dos nodos con menor frecuencia.<br>
    5. Se crea un nuevo nodo padre cuya frecuencia es la suma de las frecuencias de ambos nodos.<br>
    6. El nodo con menor frecuencia se enlaza como hijo izquierdo y el otro como hijo derecho.<br>
    7. El nuevo nodo se inserta de nuevo en la cola de prioridad y esta se reordena. La inserción tiene una complejidad temporal <code>O(n²)</code> debido al reordenamiento<br>
    8. El proceso se repite hasta que solo queda un nodo, el cual corresponde a la raíz del árbol de Huffman.<br>
    Salida: Arbol de Huffman correspondiente a los caracteres usados en el documento.
</p>
</blockquote>


<p>
<strong>4. Genera un archivo binario comprimido.</strong><br>
Para codificar cada carácter, primero se generaron los códigos binarios correspondientes a cada carácter usado en el documento.<br>
Esto se hizo a partir del árbol de Huffman y se utilizó una matriz de tamaño <code>128 x 56</code>.<br>
Cada fila representa un carácter ASCII posible, y en cada columna se guarda un bit del código Huffman: <code>0</code> o <code>1</code>
</p>
<blockquote>
<p style="padding-left: 40px;">
    <strong>Funcionamiento general:</strong><br>
    Entrada: Codigos binarios de Huffnam y archivo de texto original<br>
    1. Abrir el archivo original en modo lectura.<br>
    2. Crear y abrir el archivo comprimido en modo binario/escritura
    3. Se escribe el encabezado del archivo comprimido, incluyendo la información necesaria para reconstruir el árbol de Huffman.<br>
</p>
</blockquote>



