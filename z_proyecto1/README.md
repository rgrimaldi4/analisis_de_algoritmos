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
<p>
Este programa recibe un archivo de texto como entrada, calcula la frecuencia de
cada símbolo, construye el árbol de Huffman y genera un archivo binario
comprimido.
</p>
