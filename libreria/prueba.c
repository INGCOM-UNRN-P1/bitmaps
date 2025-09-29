#include "libreria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para remove

void prueba_crear_destruir() {
    printf("--- Prueba Crear y Destruir ---\n");
    bmp_t *bmp = bmp_crear(10, 10);
    if (bmp != NULL) {
        printf("Crear: OK\n");
    } else {
        printf("Crear: FAIL\n");
    }
    bmp_destruir(bmp);
    printf("Destruir: OK\n");
}

void prueba_guardar_abrir() {
    printf("--- Prueba Guardar y Abrir ---\n");
    const char *ruta = "prueba.bmp";
    bmp_t *bmp_original = bmp_crear(20, 30);
    bool guardado = bmp_guardar(bmp_original, ruta);
    if (guardado) {
        printf("Guardar: OK\n");
    } else {
        printf("Guardar: FAIL\n");
    }

    bmp_t *bmp_leido = bmp_abrir(ruta);
    if (bmp_leido != NULL) {
        printf("Abrir: OK\n");
    } else {
        printf("Abrir: FAIL\n");
    }

    if (bmp_get_ancho(bmp_original) == 20 && bmp_get_alto(bmp_original) == 30) {
         printf("Dimensiones Originales: OK\n");
    } else {
         printf("Dimensiones Originales: FAIL\n");
    }

    if (bmp_get_ancho(bmp_leido) == 20 && bmp_get_alto(bmp_leido) == 30) {
         printf("Dimensiones Leidas: OK\n");
    } else {
         printf("Dimensiones Leidas: FAIL\n");
    }

    bmp_destruir(bmp_original);
    bmp_destruir(bmp_leido);
    remove(ruta);
}

void prueba_set_get_pixel() {
    printf("--- Prueba Set y Get Pixel ---\n");
    const char *ruta = "pixel_test.bmp";
    bmp_t *bmp = bmp_crear(5, 5);

    bmp_set_pixel(bmp, 2, 3, 255, 0, 0); // Píxel rojo en (2, 3)

    bool guardado = bmp_guardar(bmp, ruta);
    if (!guardado) {
        printf("Guardar para prueba de píxel: FAIL\n");
        bmp_destruir(bmp);
        return;
    }

    bmp_t *bmp_leido = bmp_abrir(ruta);
    if (bmp_leido == NULL) {
        printf("Abrir para prueba de píxel: FAIL\n");
        bmp_destruir(bmp);
        remove(ruta);
        return;
    }

    unsigned char r, g, b;
    bool leido = bmp_get_pixel(bmp_leido, 2, 3, &r, &g, &b);

    if (leido && r == 255 && g == 0 && b == 0) {
        printf("Get/Set Pixel: OK\n");
    } else {
        printf("Get/Set Pixel: FAIL (r=%d, g=%d, b=%d)\n", r, g, b);
    }

    bmp_destruir(bmp);
    bmp_destruir(bmp_leido);
    remove(ruta);
}

int main() {
    prueba_crear_destruir();
    printf("\n");
    prueba_guardar_abrir();
    printf("\n");
    prueba_set_get_pixel();
    printf("\n");

    return 0;
}
