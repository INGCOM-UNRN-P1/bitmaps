#include "../libreria/libreria.h"
#include <stdio.h>

int main() {
    int ancho = 256;
    int alto = 1024;

    bmp_t *bmp = bmp_crear(ancho, alto);
    if (bmp == NULL) {
        fprintf(stderr, "Error al crear la imagen BMP.\n");
        return 1;
    }

    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            unsigned char r = x;
            unsigned char g = y;
            unsigned char b = 0;
            bmp_set_pixel(bmp, x, y, r, g, b);
        }
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
