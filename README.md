# `libbitmap` - Creacion de archivos gráficos

Esta librería facilita la creación de imágenes `.bmp` sin compresión que, terminan siendo,
una matríz de pixeles. Pero, con todo el funcionamiento interno expuesto en el repositorio
es posible ver e inspeccionar que pasa por adentro.

> [!WARNING]  
> Ojo que las imágenes no tienen compresión. Es muy (pero muy) facil crear un archivo supermasivo.
> Para que tengan una idea, 1920x1080 es mas o menos 6,2Mb

## Objetivos del Makefile

1. `make` compila el `main.c` y `prueba.c`.
2. `make run` ejecuta `main.c`.
3. `make test` ejecuta `prueba.c`.
4. `make clean` limpia los compilados e intermedios.
5. `make librerias` compila todas las librerías.
6. `make ejercicio` compila el código principal

Recuerden no enviar al repositorio los compilados (`.exe`) e intermedios (`.o`/`.a`), para ello usen `make clean` en la
raíz del proyecto.

## Ideas

Sobre esta libreria, que expone únicamente la imagen de a pixel, se puede construir de todo.
Mostrar texto, tomar 'sprites' de un archivo, dibujar, y, eventualmente, generar imagenes con
algun tipo de compresión.

Es solo el comienzo :-D

## Manual de `libbitmap` (BMP)

Esta librería proporciona funcionalidades para la creación, apertura, manipulación y guardado de imágenes BMP sin compresión (formato de 24 bits por píxel).

### Compilación y Enlazado

Para compilar la librería, navegue al directorio `libreria` y ejecute `make`:

```bash
cd libreria
make
```

Esto generará el archivo de librería estática `liblibreria.a`. Para enlazar su proyecto con esta librería, debe incluir el archivo de cabecera `libreria.h` y especificar la librería en su comando de compilación. Por ejemplo:

```bash
gcc -o mi_programa mi_programa.c -L./libreria -llibreria
```

### Tipos de Datos

La librería define los siguientes tipos de datos para facilitar la manipulación de imágenes:

*   **`bmp_t`**: Estructura opaca que representa una imagen BMP. Todas las operaciones se realizan a través de punteros a este tipo.

*   **`coordenada_t`**:
    ```c
    typedef struct {
        int x;
        int y;
    } coordenada_t;
    ```
    Representa una coordenada (x, y) en la imagen.

*   **`color_t`**:
    ```c
    typedef struct {
        unsigned char r;
        unsigned char g;
        unsigned char b;
    } color_t;
    ```
    Representa un color RGB, donde `r`, `g` y `b` son los componentes rojo, verde y azul respectivamente, con valores entre 0 y 255.

### Funciones de la Librería

A continuación se detallan las funciones públicas disponibles en la librería:

#### `bmp_crear`

```c
bmp_t *bmp_crear(int ancho, int alto);
```
Crea una nueva imagen BMP en memoria.
*   `ancho`: El ancho de la imagen en píxeles.
*   `alto`: El alto de la imagen en píxeles.
*   **Retorna**: Un puntero a una nueva estructura `bmp_t` si la creación fue exitosa, o `NULL` si no se pudo asignar memoria o las dimensiones son inválidas. El llamador es responsable de liberar la memoria utilizando `bmp_destruir()`.

#### `bmp_guardar`

```c
bool bmp_guardar(const bmp_t *bmp, const char *ruta);
```
Guarda una imagen BMP en un archivo.
*   `bmp`: Un puntero a la estructura `bmp_t` que se desea guardar.
*   `ruta`: La ruta del archivo donde se guardará la imagen.
*   **Retorna**: `true` si la imagen se guardó correctamente, `false` en caso de error.

#### `bmp_abrir`

```c
bmp_t *bmp_abrir(const char *ruta);
```
Abre una imagen BMP desde un archivo.
*   `ruta`: La ruta del archivo BMP que se desea abrir.
*   **Retorna**: Un puntero a una nueva estructura `bmp_t` si la apertura fue exitosa, o `NULL` si ocurre un error. El llamador es responsable de liberar la memoria utilizando `bmp_destruir()`.

#### `bmp_destruir`

```c
void bmp_destruir(bmp_t *bmp);
```
Libera la memoria asociada a una imagen BMP.
*   `bmp`: Puntero a la estructura `bmp_t` a destruir. Si es `NULL`, la función no hace nada.

#### `bmp_get_pixel`

```c
bool bmp_get_pixel(const bmp_t *bmp, coordenada_t coor, color_t *color);
```
Obtiene el color de un píxel específico de la imagen.
*   `bmp`: Puntero a la imagen.
*   `coor`: Coordenada del píxel.
*   `color`: Puntero para almacenar el color.
*   **Retorna**: `true` si se pudo obtener el color del píxel, `false` si las coordenadas están fuera de los límites de la imagen.

#### `bmp_set_pixel`

```c
bool bmp_set_pixel(bmp_t *bmp, coordenada_t coor, color_t color);
```
Establece el color de un píxel específico de la imagen.
*   `bmp`: Puntero a la imagen.
*   `coor`: Coordenada del píxel.
*   `color`: Color a establecer.
*   **Retorna**: `true` si se pudo establecer el color del píxel, `false` si las coordenadas están fuera de los límites de la imagen.

#### `bmp_get_ancho`

```c
int bmp_get_ancho(const bmp_t *bmp);
```
Obtiene el ancho de una imagen BMP.
*   `bmp`: Puntero a la imagen.
*   **Retorna**: El ancho de la imagen en píxeles.

#### `bmp_get_alto`

```c
int bmp_get_alto(const bmp_t *bmp);
```
Obtiene el alto de una imagen BMP.
*   `bmp`: Puntero a la imagen.
*   **Retorna**: El alto de la imagen en píxeles.

### Ejemplo de Uso

Consulte el archivo `ejercicio/main.c` para un ejemplo de cómo utilizar la librería para crear una imagen con un gradiente de color.
