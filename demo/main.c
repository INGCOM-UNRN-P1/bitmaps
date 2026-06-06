#include "../bitmap/libreria.h"
#include <stdio.h>

/**
 * @brief Escala un valor de coordenada a un rango de 0-255 para un componente de color.
 *
 * @param valor_actual El valor actual de la coordenada (x o y).
 * @param max_dimension La dimensión máxima de la imagen (ancho o alto).
 *
 * @returns Un valor de unsigned char escalado entre 0 y 255.
 */
static unsigned char escalar_componente_color(int valor_actual, int max_dimension) {
    if (max_dimension == 0) {
        return 0;
    }
    return (unsigned char)((float)valor_actual / max_dimension * 255);
}

int main() {
    int ancho = 1920;
    int alto = 1080;

    bmp_t *bmp = bmp_crear(ancho, alto);
    if (bmp == NULL) {
        fprintf(stderr, "Error al crear la imagen BMP.\n");
        return 1;
    }

    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            coordenada_t coor = {x, y};
            color_t color = {
                escalar_componente_color(y, alto),
                escalar_componente_color(x, ancho),
                128
            };
            bmp_set_pixel(bmp, coor, color);
        }
    }

    for (int y = 0; y < alto; y++) {
        
            coordenada_t coor = {200, y};
            color_t color = {0,0,0};
            bmp_set_pixel(bmp, coor, color);
        
    }


    const char *ruta = "gradiente.bmp";
    if (bmp_guardar(bmp, ruta)) {
        printf("Imagen generada y guardada en '%s'\n", ruta);
    } else {
        fprintf(stderr, "Error al guardar la imagen BMP.\n");
    }

    bmp_destruir(bmp);

    return 0;
}