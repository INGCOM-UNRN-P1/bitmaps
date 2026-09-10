/**
 * Ejemplo de uso de la paleta de colores predefinida.
 * Crea una imagen que muestra todos los colores disponibles en la paleta.
 */

#include "../bitmap/libreria.h"
#include <stdio.h>

/**
 * Dibuja un cuadrado de color sólido en la imagen.
 *
 * @param bmp La imagen donde dibujar.
 * @param x_inicio Coordenada X del inicio del cuadrado.
 * @param y_inicio Coordenada Y del inicio del cuadrado.
 * @param tamaño Tamaño del lado del cuadrado.
 * @param color Color del cuadrado.
 *
 * @pre bmp no debe ser NULL.
 * @pre Las coordenadas y el tamaño deben estar dentro de los límites de la imagen.
 *
 * @returns true si se dibujó correctamente, false en caso de error.
 */
static bool dibujar_cuadrado(bmp_t *bmp, int x_inicio, int y_inicio, int tamaño, color_t color) {
    bool exito = true;
    
    for (int y = y_inicio; y < y_inicio + tamaño && exito; y++) {
        for (int x = x_inicio; x < x_inicio + tamaño && exito; x++) {
            coordenada_t coord = {x, y};
            if (!bmp_set_pixel(bmp, coord, color)) {
                exito = false;
            }
        }
    }
    
    return exito;
}

int main() {
    printf("Creando ejemplo de paleta de colores...\n");
    
    // Crear una imagen de 320x240 (4 columnas x 4 filas de cuadrados de 80x60)
    const int ancho = 320;
    const int alto = 240;
    const int cuadrados_por_fila = 4;
    const int cuadrados_por_columna = 4;
    const int tamaño_cuadrado_x = ancho / cuadrados_por_fila;
    const int tamaño_cuadrado_y = alto / cuadrados_por_columna;
    
    bmp_t *bmp = bmp_crear(ancho, alto);
    if (bmp == NULL) {
        fprintf(stderr, "Error al crear la imagen.\n");
        return 1;
    }
    
    // Array con todos los colores predefinidos
    color_t colores[] = {
        BMP_COLOR_NEGRO,       BMP_COLOR_BLANCO,      BMP_COLOR_ROJO,        BMP_COLOR_VERDE,
        BMP_COLOR_AZUL,        BMP_COLOR_AMARILLO,    BMP_COLOR_MAGENTA,     BMP_COLOR_CIAN,
        BMP_COLOR_GRIS_CLARO,  BMP_COLOR_GRIS_OSCURO, BMP_COLOR_NARANJA,     BMP_COLOR_PURPURA,
        BMP_COLOR_MARRON,      BMP_COLOR_ROSA,        BMP_COLOR_LIMA,        BMP_COLOR_TURQUESA
    };
    
    const char *nombres_colores[] = {
        "Negro",      "Blanco",      "Rojo",        "Verde",
        "Azul",       "Amarillo",    "Magenta",     "Cian",
        "Gris Claro", "Gris Oscuro", "Naranja",     "Purpura",
        "Marron",     "Rosa",        "Lima",        "Turquesa"
    };
    
    // Dibujar los cuadrados de colores
    for (int fila = 0; fila < cuadrados_por_columna; fila++) {
        for (int columna = 0; columna < cuadrados_por_fila; columna++) {
            int indice = fila * cuadrados_por_fila + columna;
            int x_inicio = columna * tamaño_cuadrado_x;
            int y_inicio = fila * tamaño_cuadrado_y;
            
            if (indice < 16) {
                printf("Dibujando cuadrado %s en posición (%d, %d)\n", 
                       nombres_colores[indice], x_inicio, y_inicio);
                
                if (!dibujar_cuadrado(bmp, x_inicio, y_inicio, 
                                     tamaño_cuadrado_x < tamaño_cuadrado_y ? tamaño_cuadrado_x : tamaño_cuadrado_y, 
                                     colores[indice])) {
                    printf("Error al dibujar cuadrado %s\n", nombres_colores[indice]);
                }
            }
        }
    }
    
    // Guardar la imagen
    const char *ruta = "paleta_colores.bmp";
    if (bmp_guardar(bmp, ruta)) {
        printf("¡Imagen de paleta de colores guardada en '%s'!\n", ruta);
        printf("La imagen muestra todos los colores predefinidos disponibles.\n");
    } else {
        fprintf(stderr, "Error al guardar la imagen.\n");
    }
    
    // Demostrar uso de funciones auxiliares de color
    printf("\nEjemplos de funciones auxiliares de color:\n");
    
    color_t mi_color = bmp_crear_color(128, 64, 192);
    printf("Color personalizado creado: RGB(%d, %d, %d)\n", 
           mi_color.r, mi_color.g, mi_color.b);
    
    printf("¿El color rojo es igual al color verde? %s\n", 
           bmp_colores_iguales(BMP_COLOR_ROJO, BMP_COLOR_VERDE) ? "Sí" : "No");
    printf("¿El color rojo es igual a sí mismo? %s\n", 
           bmp_colores_iguales(BMP_COLOR_ROJO, BMP_COLOR_ROJO) ? "Sí" : "No");
    
    bmp_destruir(bmp);
    
    return 0;
}