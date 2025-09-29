#ifndef LIBRERIA_H
#define LIBRERIA_H

#include <stdbool.h>
#include <stddef.h>

// ============================================================================
// TIPOS DE DATOS
// ============================================================================

/**
 * @typedef bmp_t
 * @brief Estructura opaca para representar una imagen BMP.
 *
 * Encapsula los encabezados y los datos de píxeles de una imagen BMP.
 * La manipulación de esta estructura se realiza a través de las funciones
 * proporcionadas por la biblioteca.
 */
typedef struct bmp bmp_t;

/**
 * @typedef coordenada_t
 * @brief Estructura para representar una coordenada (x, y).
 */
typedef struct {
    int x;
    int y;
} coordenada_t;

/**
 * @typedef color_t
 * @brief Estructura para representar un color RGB.
 */
typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} color_t;


// ============================================================================
// FUNCIONES PÚBLICAS
// ============================================================================

/**
 * @brief Crea una nueva imagen BMP en memoria.
 *
 * @param ancho El ancho de la imagen en píxeles.
 * @param alto El alto de la imagen en píxeles.
 *
 * @pre El ancho y el alto deben ser mayores que cero.
 *
 * @returns Un puntero a una nueva estructura bmp_t si la creación fue exitosa,
 *          o NULL si no se pudo asignar memoria o las dimensiones son
 *          inválidas. El llamador es responsable de liberar la memoria
 *          utilizando bmp_destruir().
 *
 * @post Si la creación es exitosa, la imagen está inicializada con un fondo
 *       negro (todos los píxeles en 0,0,0).
 */
bmp_t *bmp_crear(int ancho, int alto);

/**
 * @brief Guarda una imagen BMP en un archivo.
 *
 * @param bmp Un puntero a la estructura bmp_t que se desea guardar.
 * @param ruta La ruta del archivo donde se guardará la imagen.
 *
 * @pre El puntero bmp no debe ser NULL.
 * @pre La ruta no debe ser NULL y debe ser una ruta de archivo válida.
 *
 * @returns true si la imagen se guardó correctamente, false en caso de error
 *          (por ejemplo, no se pudo abrir el archivo para escritura).
 *
 * @post El archivo en la ruta especificada contiene la imagen BMP.
 */
bool bmp_guardar(const bmp_t *bmp, const char *ruta);

/**
 * @brief Abre una imagen BMP desde un archivo.
 *
 * @param ruta La ruta del archivo BMP que se desea abrir.
 *
 * @pre La ruta no debe ser NULL y debe apuntar a un archivo BMP válido y sin
 *      compresión.
 *
 * @returns Un puntero a una nueva estructura bmp_t si la apertura fue exitosa,
 *          o NULL si ocurre un error (ej. el archivo no existe, no es un BMP
 *          válido, o no se puede asignar memoria). El llamador es responsable
 *          de liberar la memoria utilizando bmp_destruir().
 *
 * @post Si la apertura es exitosa, la estructura bmp_t contiene los datos
 *       de la imagen leída del archivo.
 */
bmp_t *bmp_abrir(const char *ruta);

/**
 * @brief Libera la memoria asociada a una imagen BMP.
 *
 * @param bmp Puntero a la estructura bmp_t a destruir. Si es NULL, la función
 *            no hace nada.
 *
 * @post Toda la memoria asignada para la estructura bmp_t y sus datos de
 *       píxeles es liberada. El puntero bmp ya no es válido.
 */
void bmp_destruir(bmp_t *bmp);

/**
 * @brief Obtiene el color de un píxel específico de la imagen.
 *
 * @param bmp Puntero a la imagen.
 * @param coor Coordenada del píxel.
 * @param color Puntero para almacenar el color.
 *
 * @pre El puntero bmp no debe ser NULL.
 * @pre Las coordenadas deben estar dentro de los límites de la imagen.
 * @pre El puntero color no debe ser NULL.
 *
 * @returns true si se pudo obtener el color del píxel, false si las
 *          coordenadas están fuera de los límites de la imagen.
 */
bool bmp_get_pixel(const bmp_t *bmp, coordenada_t coor, color_t *color);

/**
 * @brief Establece el color de un píxel específico de la imagen.
 *
 * @param bmp Puntero a la imagen.
 * @param coor Coordenada del píxel.
 * @param color Color a establecer.
 *
 * @pre El puntero bmp no debe ser NULL.
 * @pre Las coordenadas deben estar dentro de los límites de la imagen.
 *
 * @returns true si se pudo establecer el color del píxel, false si las
 *          coordenadas están fuera de los límites de la imagen.
 *
 * @post El píxel en las coordenadas de la imagen se actualiza con el
 *       nuevo color.
 */
bool bmp_set_pixel(bmp_t *bmp, coordenada_t coor, color_t color);

/**
 * @brief Obtiene el ancho de una imagen BMP.
 *
 * @param bmp Puntero a la imagen.
 *
 * @pre El puntero bmp no debe ser NULL.
 *
 * @returns El ancho de la imagen en píxeles.
 */
int bmp_get_ancho(const bmp_t *bmp);

/**
 * @brief Obtiene el alto de una imagen BMP.
 *
 * @param bmp Puntero a la imagen.
 *
 * @pre El puntero bmp no debe ser NULL.
 *
 * @returns El alto de la imagen en píxeles.
 */
int bmp_get_alto(const bmp_t *bmp);


#endif // LIBRERIA_H
