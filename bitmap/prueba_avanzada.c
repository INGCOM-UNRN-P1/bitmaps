#include "libreria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Contador global de pruebas
static int pruebas_ejecutadas = 0;
static int pruebas_exitosas = 0;

// Macros para facilitar las pruebas
#define ASSERT(condicion, mensaje) do { \
    pruebas_ejecutadas++; \
    if (condicion) { \
        pruebas_exitosas++; \
        printf("✓ %s\n", mensaje); \
    } else { \
        printf("✗ %s\n", mensaje); \
    } \
} while(0)

#define ASSERT_IGUAL_INT(esperado, actual, mensaje) do { \
    pruebas_ejecutadas++; \
    if ((esperado) == (actual)) { \
        pruebas_exitosas++; \
        printf("✓ %s (esperado: %d, actual: %d)\n", mensaje, esperado, actual); \
    } else { \
        printf("✗ %s (esperado: %d, actual: %d)\n", mensaje, esperado, actual); \
    } \
} while(0)

#define ASSERT_COLORES_IGUALES(esperado, actual, mensaje) do { \
    pruebas_ejecutadas++; \
    if (bmp_colores_iguales(esperado, actual)) { \
        pruebas_exitosas++; \
        printf("✓ %s\n", mensaje); \
    } else { \
        printf("✗ %s (esperado: RGB(%d,%d,%d), actual: RGB(%d,%d,%d))\n", \
               mensaje, esperado.r, esperado.g, esperado.b, \
               actual.r, actual.g, actual.b); \
    } \
} while(0)

void pruebas_paleta_colores() {
    printf("\n=== Pruebas de Paleta de Colores ===\n");
    
    // Verificar que los colores predefinidos tienen los valores correctos
    ASSERT_COLORES_IGUALES(bmp_crear_color(0, 0, 0), BMP_COLOR_NEGRO, 
                          "Color negro correcto");
    ASSERT_COLORES_IGUALES(bmp_crear_color(255, 255, 255), BMP_COLOR_BLANCO, 
                          "Color blanco correcto");
    ASSERT_COLORES_IGUALES(bmp_crear_color(255, 0, 0), BMP_COLOR_ROJO, 
                          "Color rojo correcto");
    ASSERT_COLORES_IGUALES(bmp_crear_color(0, 255, 0), BMP_COLOR_VERDE, 
                          "Color verde correcto");
    ASSERT_COLORES_IGUALES(bmp_crear_color(0, 0, 255), BMP_COLOR_AZUL, 
                          "Color azul correcto");
    ASSERT_COLORES_IGUALES(bmp_crear_color(255, 255, 0), BMP_COLOR_AMARILLO, 
                          "Color amarillo correcto");
    ASSERT_COLORES_IGUALES(bmp_crear_color(255, 0, 255), BMP_COLOR_MAGENTA, 
                          "Color magenta correcto");
    ASSERT_COLORES_IGUALES(bmp_crear_color(0, 255, 255), BMP_COLOR_CIAN, 
                          "Color cian correcto");
    
    // Probar la función de crear color
    color_t color_personalizado = bmp_crear_color(123, 45, 67);
    ASSERT_IGUAL_INT(123, color_personalizado.r, "Componente R de color personalizado");
    ASSERT_IGUAL_INT(45, color_personalizado.g, "Componente G de color personalizado");
    ASSERT_IGUAL_INT(67, color_personalizado.b, "Componente B de color personalizado");
    
    // Probar comparación de colores
    ASSERT(bmp_colores_iguales(BMP_COLOR_ROJO, BMP_COLOR_ROJO), 
           "Comparación de colores iguales (mismo color)");
    ASSERT(!bmp_colores_iguales(BMP_COLOR_ROJO, BMP_COLOR_AZUL), 
           "Comparación de colores diferentes");
}

void pruebas_casos_limite() {
    printf("\n=== Pruebas de Casos Límite ===\n");
    
    // Imagen 1x1
    bmp_t *bmp_mini = bmp_crear(1, 1);
    ASSERT(bmp_mini != NULL, "Crear imagen 1x1");
    ASSERT_IGUAL_INT(1, bmp_get_ancho(bmp_mini), "Ancho de imagen 1x1");
    ASSERT_IGUAL_INT(1, bmp_get_alto(bmp_mini), "Alto de imagen 1x1");
    
    coordenada_t coord_centro = {0, 0};
    ASSERT(bmp_set_pixel(bmp_mini, coord_centro, BMP_COLOR_ROJO), 
           "Set pixel en imagen 1x1");
    
    color_t color_leido;
    ASSERT(bmp_get_pixel(bmp_mini, coord_centro, &color_leido), 
           "Get pixel en imagen 1x1");
    ASSERT_COLORES_IGUALES(BMP_COLOR_ROJO, color_leido, 
                          "Color correcto en imagen 1x1");
    
    bmp_destruir(bmp_mini);
    
    // Dimensiones inválidas
    ASSERT(bmp_crear(0, 10) == NULL, "Crear imagen con ancho 0");
    ASSERT(bmp_crear(10, 0) == NULL, "Crear imagen con alto 0");
    ASSERT(bmp_crear(-1, 10) == NULL, "Crear imagen con ancho negativo");
    ASSERT(bmp_crear(10, -1) == NULL, "Crear imagen con alto negativo");
}

void pruebas_manejo_errores() {
    printf("\n=== Pruebas de Manejo de Errores ===\n");
    
    bmp_t *bmp = bmp_crear(5, 5);
    ASSERT(bmp != NULL, "Crear imagen para pruebas de error");
    
    // Coordenadas fuera de límites
    coordenada_t coord_invalida1 = {-1, 2};
    coordenada_t coord_invalida2 = {2, -1};
    coordenada_t coord_invalida3 = {5, 2}; // ancho es 5, máximo índice válido es 4
    coordenada_t coord_invalida4 = {2, 5}; // alto es 5, máximo índice válido es 4
    
    color_t color_temp;
    ASSERT(!bmp_set_pixel(bmp, coord_invalida1, BMP_COLOR_ROJO), 
           "Set pixel con X negativa falla");
    ASSERT(!bmp_set_pixel(bmp, coord_invalida2, BMP_COLOR_ROJO), 
           "Set pixel con Y negativa falla");
    ASSERT(!bmp_set_pixel(bmp, coord_invalida3, BMP_COLOR_ROJO), 
           "Set pixel con X fuera de límite falla");
    ASSERT(!bmp_set_pixel(bmp, coord_invalida4, BMP_COLOR_ROJO), 
           "Set pixel con Y fuera de límite falla");
    
    ASSERT(!bmp_get_pixel(bmp, coord_invalida1, &color_temp), 
           "Get pixel con X negativa falla");
    ASSERT(!bmp_get_pixel(bmp, coord_invalida2, &color_temp), 
           "Get pixel con Y negativa falla");
    ASSERT(!bmp_get_pixel(bmp, coord_invalida3, &color_temp), 
           "Get pixel con X fuera de límite falla");
    ASSERT(!bmp_get_pixel(bmp, coord_invalida4, &color_temp), 
           "Get pixel con Y fuera de límite falla");
    
    // Punteros nulos
    ASSERT(!bmp_get_pixel(NULL, coord_invalida1, &color_temp), 
           "Get pixel con BMP nulo falla");
    ASSERT(!bmp_get_pixel(bmp, coord_invalida1, NULL), 
           "Get pixel con puntero de color nulo falla");
    ASSERT(!bmp_set_pixel(NULL, coord_invalida1, BMP_COLOR_ROJO), 
           "Set pixel con BMP nulo falla");
    
    ASSERT_IGUAL_INT(0, bmp_get_ancho(NULL), "Get ancho con BMP nulo retorna 0");
    ASSERT_IGUAL_INT(0, bmp_get_alto(NULL), "Get alto con BMP nulo retorna 0");
    
    ASSERT(!bmp_guardar(NULL, "test.bmp"), "Guardar BMP nulo falla");
    ASSERT(!bmp_guardar(bmp, NULL), "Guardar con ruta nula falla");
    
    bmp_destruir(bmp);
    
    // Abrir archivo inexistente
    ASSERT(bmp_abrir("archivo_inexistente_12345.bmp") == NULL, 
           "Abrir archivo inexistente falla");
}

void pruebas_persistencia() {
    printf("\n=== Pruebas de Persistencia ===\n");
    
    const char *archivo_prueba = "test_persistencia.bmp";
    
    // Crear imagen con patrón conocido
    bmp_t *bmp_original = bmp_crear(3, 3);
    ASSERT(bmp_original != NULL, "Crear imagen para persistencia");
    
    // Llenar con patrón de colores
    coordenada_t coords[] = {{0,0}, {1,0}, {2,0}, {0,1}, {1,1}, {2,1}, {0,2}, {1,2}, {2,2}};
    color_t colores[] = {BMP_COLOR_ROJO, BMP_COLOR_VERDE, BMP_COLOR_AZUL,
                        BMP_COLOR_AMARILLO, BMP_COLOR_MAGENTA, BMP_COLOR_CIAN,
                        BMP_COLOR_BLANCO, BMP_COLOR_NEGRO, BMP_COLOR_GRIS_CLARO};
    
    for (int i = 0; i < 9; i++) {
        ASSERT(bmp_set_pixel(bmp_original, coords[i], colores[i]), 
               "Set pixel en patrón");
    }
    
    // Guardar imagen
    ASSERT(bmp_guardar(bmp_original, archivo_prueba), "Guardar imagen con patrón");
    
    // Cargar imagen
    bmp_t *bmp_cargada = bmp_abrir(archivo_prueba);
    ASSERT(bmp_cargada != NULL, "Cargar imagen guardada");
    
    if (bmp_cargada != NULL) {
        // Verificar dimensiones
        ASSERT_IGUAL_INT(3, bmp_get_ancho(bmp_cargada), "Ancho conservado tras persistencia");
        ASSERT_IGUAL_INT(3, bmp_get_alto(bmp_cargada), "Alto conservado tras persistencia");
        
        // Verificar colores
        for (int i = 0; i < 9; i++) {
            color_t color_leido;
            char mensaje[100];
            snprintf(mensaje, sizeof(mensaje), "Color %d conservado tras persistencia", i);
            
            if (bmp_get_pixel(bmp_cargada, coords[i], &color_leido)) {
                ASSERT_COLORES_IGUALES(colores[i], color_leido, mensaje);
            } else {
                ASSERT(false, mensaje);
            }
        }
    }
    
    bmp_destruir(bmp_original);
    bmp_destruir(bmp_cargada);
    
    // Limpiar archivo de prueba
    remove(archivo_prueba);
}

void pruebas_memoria() {
    printf("\n=== Pruebas de Gestión de Memoria ===\n");
    
    // Crear y destruir múltiples imágenes
    for (int i = 0; i < 10; i++) {
        bmp_t *bmp = bmp_crear(50, 50);
        ASSERT(bmp != NULL, "Crear imagen en bucle de memoria");
        bmp_destruir(bmp);
    }
    
    // Destruir imagen nula (no debe crashear)
    bmp_destruir(NULL);
    ASSERT(true, "Destruir BMP nulo no causa crash");
    
    // Crear imagen de tamaño significativo
    bmp_t *bmp_grande = bmp_crear(200, 200);
    ASSERT(bmp_grande != NULL, "Crear imagen grande (200x200)");
    
    if (bmp_grande != NULL) {
        // Llenar algunos píxeles para verificar que la memoria es válida
        coordenada_t esquinas[] = {{0,0}, {199,0}, {0,199}, {199,199}, {100,100}};
        for (int i = 0; i < 5; i++) {
            ASSERT(bmp_set_pixel(bmp_grande, esquinas[i], BMP_COLOR_AZUL), 
                   "Set pixel en imagen grande");
        }
    }
    
    bmp_destruir(bmp_grande);
}

void imprimir_resumen() {
    printf("\n" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "\n");
    printf("RESUMEN DE PRUEBAS\n");
    printf("=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "\n");
    printf("Pruebas ejecutadas: %d\n", pruebas_ejecutadas);
    printf("Pruebas exitosas:   %d\n", pruebas_exitosas);
    printf("Pruebas fallidas:   %d\n", pruebas_ejecutadas - pruebas_exitosas);
    
    if (pruebas_exitosas == pruebas_ejecutadas) {
        printf("\n🎉 ¡TODAS LAS PRUEBAS PASARON! 🎉\n");
    } else {
        printf("\n⚠️  Algunas pruebas fallaron. Revisar implementación.\n");
    }
    printf("=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "\n");
}

int main() {
    printf("SUITE DE PRUEBAS AVANZADA - libbitmap\n");
    printf("=====================================\n");
    
    pruebas_paleta_colores();
    pruebas_casos_limite();
    pruebas_manejo_errores();
    pruebas_persistencia();
    pruebas_memoria();
    
    imprimir_resumen();
    
    return (pruebas_exitosas == pruebas_ejecutadas) ? 0 : 1;
}