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

<strong><p>Forma de ejecutar los programas:</p></strong>
<pre><code>codifica mensaje.txt mensaje.cod</code></pre>    
<pre><code>decodifica mensaje.cod</code></pre>    


<hr>
<h2><mark>Programa: <code>codifica.c</code></mark></h2>
<p>Este programa hace lo siguiente</p>
<ol>
    <li>Recibe un archivo de texto como entrada</li>
    <li>Calcula la frecuencia de cada símbolo</li>
    <li>Construye el árbol de Huffman</li>
    <li>Genera un archivo binario comprimido</li>
</ol>


<p>
    <strong>1. Datos de entrada.</strong><br>
    <code>codifica.c</code> recibe por linea de comandos el nombre del archivo de texto de entrada y el nombre que tendrá el archivo comprimido.
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
    Salida: árbol de Huffman correspondiente a los caracteres usados en el documento.
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
    Entrada: Matriz de codigos binarios de Huffnam (CBH) y archivo de texto original<br>
    1. Abrir el archivo original en modo lectura.<br>
    2. Crear y abrir el archivo comprimido en modo binario/escritura.<br>
    3. Se escribe el encabezado del archivo comprimido, el cual se conforma de: </br>
    <pre><code> numero_de_simbolos|tamaño_del_mensaje|carac|frec|carac|frec...carac|frec</code></pre>
    4. Se lee el archivo original carácter por carácter, por cada carácter se obtiene su código binario de la matriz de códigos.<br>
    5. Los bits del código Huffman se van agrupando en bytes.<br>
    6. Cuando se completa un byte, este se escribe en el archivo comprimido.<br>
    7. Si al final sobran bits que no completan un byte, se rellenan con ceros y se escribe el último byte.<br>
    Salida: archivo comprimido
</p>
</blockquote>

<hr>

<h2><mark>Programa: <code>decodifica.c</code></mark></h2>

<p>Este programa hace lo siguiente</p>
<ol>
    <li>Recibe el archivo comprimido de entrada</li>
    <li>Se lee el encabezado y se crea y ordena la cola de prioridad</li>
    <li>Construye el árbol de Huffman</li>
    <li>Decodifica el mensaje e imprime el texto original en la consola</li>
</ol>

<p>
    <strong>1. Construir el árbol de Huffman</strong><br>
    Para decodificar se tiene que construir el arbol de Huffman.<br>
    El árbol se crea a partir de los caracteres y sus frecuencias, tal informacio esta contenida en el encabezado del archivo comprimido.<br>
</p>
<blockquote>
<p>
    <strong>Funcionamiento general:</strong><br>
    Entrada: archivo comprimido.<br>
    1. Se lee el encabezado del archivo comprimido.<br>
    2. Se lee cada caracter y su frecuencia<br>
    3. Se crea un nodo hoja con el carácter y su frecuencia, y se inserta en la cola de prioridad.<br>
    4. La cola de prioridad se ordena de menor a mayor según la frecuencia. La complejidad temporal del ordenamiento es cuadrática <code>O(n²)</code>.<br>
    5. Una vez que la cola de prioridad está completa y ordenada, se ejecuta el algoritmo de Huffman (mismo que se describió anteriormente).<br>
    6. En esta punto esta listo el árbol de Huffman<br>
    Salida: árbol de Huffman reconstruido.
</p>
</blockquote>


<p>
    <strong>2. Decodificar el mensaje.</strong><br>
    Una vez reconstruido el árbol de Huffman, se lee el mensaje comprimido bit por bit.<br>
    Cada bit leído permite recorrer el árbol desde la raíz hasta llegar a una hoja, donde se encuentra el carácter original.
</p>

<blockquote>
<p>
    <strong>Funcionamiento general:</strong><br>
    Entrada: archivo comprimido y árbol de Huffman reconstruido.<br>
    1. Se inicializa un apuntador en la raíz del árbol de Huffman.<br>
    2. Se lee el archivo comprimido byte por byte.<br>
    3. Por cada byte leído, se extraen sus bits de izquierda a derecha.<br>
    4. Si el bit leído es <code>0</code>, se avanza hacia el hijo izquierdo del árbol.<br>
    5. Si el bit leído es <code>1</code>, se avanza hacia el hijo derecho del árbol.<br>
    6. Cuando se llega a un nodo hoja, se imprime en la consola el carácter almacenado en ese nodo.<br>
    7. Después de imprimir el carácter, el apuntador regresa a la raíz del árbol para continuar decodificando el siguiente carácter.<br>
    8. El proceso se repite hasta imprimir la cantidad total de caracteres indicada en el encabezado.<br>
    Salida: texto original impreso en la consola.
</p>
</blockquote>


