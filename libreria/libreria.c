#include "libreria.h"
#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BMP_MAGIC 0x4D42
#define BITS_PER_PIXEL 24
#define COMPRESSION_BI_RGB 0

struct bmp {
    BITMAPFILEHEADER file_header;
    BITMAPINFOHEADER info_header;
    RGB *pixel_data;
};

static size_t calcular_padding(int ancho) {
    size_t padding = 0;
    if ((ancho * sizeof(RGB)) % 4 != 0) {
        padding = 4 - ((ancho * sizeof(RGB)) % 4);
    }
    return padding;
}

bmp_t *bmp_crear(int ancho, int alto) {
    bmp_t *bmp = NULL;
    bool error = false;

    if (ancho <= 0 || alto <= 0) {
        error = true;
    }

    if (!error) {
        bmp = malloc(sizeof(bmp_t));
        if (bmp == NULL) {
            error = true;
        }
    }

    if (!error) {
        size_t data_size = ancho * alto * sizeof(RGB);
        bmp->pixel_data = malloc(data_size);
        if (bmp->pixel_data == NULL) {
            free(bmp);
            bmp = NULL;
            error = true;
        }
    }

    if (!error) {
        memset(bmp->pixel_data, 0, ancho * alto * sizeof(RGB));

        size_t padding = calcular_padding(ancho);
        size_t image_size = (ancho * sizeof(RGB) + padding) * alto;

        bmp->file_header.bfType = BMP_MAGIC;
        bmp->file_header.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + image_size;
        bmp->file_header.bfReserved1 = 0;
        bmp->file_header.bfReserved2 = 0;
        bmp->file_header.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

        bmp->info_header.biSize = sizeof(BITMAPINFOHEADER);
        bmp->info_header.biWidth = ancho;
        bmp->info_header.biHeight = alto;
        bmp->info_header.biPlanes = 1;
        bmp->info_header.biBitCount = BITS_PER_PIXEL;
        bmp->info_header.biCompression = COMPRESSION_BI_RGB;
        bmp->info_header.biSizeImage = image_size;
        bmp->info_header.biXPelsPerMeter = 0;
        bmp->info_header.biYPelsPerMeter = 0;
        bmp->info_header.biClrUsed = 0;
        bmp->info_header.biClrImportant = 0;
    }

    return bmp;
}

bool bmp_guardar(const bmp_t *bmp, const char *ruta) {
    bool exito = true;
    FILE *archivo = NULL;

    if (bmp == NULL || ruta == NULL) {
        exito = false;
    }

    if (exito) {
        archivo = fopen(ruta, "wb");
        if (archivo == NULL) {
            exito = false;
        }
    }

    if (exito) {
        if (fwrite(&bmp->file_header, sizeof(BITMAPFILEHEADER), 1, archivo) != 1) {
            exito = false;
        }
    }

    if (exito) {
        if (fwrite(&bmp->info_header, sizeof(BITMAPINFOHEADER), 1, archivo) != 1) {
            exito = false;
        }
    }

    if (exito) {
        size_t padding = calcular_padding(bmp->info_header.biWidth);
        unsigned char padding_bytes[3] = {0, 0, 0};
        int ancho = bmp->info_header.biWidth;
        int alto = bmp->info_header.biHeight;

        for (int y = 0; y < alto; y++) {
            if (fwrite(&bmp->pixel_data[y * ancho], sizeof(RGB), ancho, archivo) != (size_t)ancho) {
                exito = false;
                break;
            }
            if (padding > 0) {
                if (fwrite(padding_bytes, 1, padding, archivo) != padding) {
                    exito = false;
                    break;
                }
            }
        }
    }

    if (archivo != NULL) {
        fclose(archivo);
    }

    return exito;
}

bmp_t *bmp_abrir(const char *ruta) {
    bmp_t *bmp = NULL;
    FILE *archivo = NULL;
    bool error = false;

    if (ruta == NULL) {
        error = true;
    }

    if (!error) {
        archivo = fopen(ruta, "rb");
        if (archivo == NULL) {
            error = true;
        }
    }

    if (!error) {
        bmp = malloc(sizeof(bmp_t));
        if (bmp == NULL) {
            error = true;
        }
    }

    if (!error) {
        if (fread(&bmp->file_header, sizeof(BITMAPFILEHEADER), 1, archivo) != 1) {
            error = true;
        }
    }

    if (!error) {
        if (bmp->file_header.bfType != BMP_MAGIC) {
            error = true;
        }
    }
    
    if (!error) {
        if (fread(&bmp->info_header, sizeof(BITMAPINFOHEADER), 1, archivo) != 1) {
            error = true;
        }
    }

    if (!error) {
        if (bmp->info_header.biCompression != COMPRESSION_BI_RGB || bmp->info_header.biBitCount != BITS_PER_PIXEL) {
            error = true;
        }
    }

    if (!error) {
        size_t data_size = bmp->info_header.biWidth * bmp->info_header.biHeight * sizeof(RGB);
        bmp->pixel_data = malloc(data_size);
        if (bmp->pixel_data == NULL) {
            error = true;
        }
    }

    if (!error) {
        fseek(archivo, bmp->file_header.bfOffBits, SEEK_SET);
        size_t padding = calcular_padding(bmp->info_header.biWidth);
        int ancho = bmp->info_header.biWidth;
        int alto = bmp->info_header.biHeight;

        for (int y = 0; y < alto; y++) {
            if (fread(&bmp->pixel_data[y * ancho], sizeof(RGB), ancho, archivo) != (size_t)ancho) {
                error = true;
                break;
            }
            if (fseek(archivo, padding, SEEK_CUR) != 0) {
                error = true;
                break;
            }
        }
    }

    if (error && bmp != NULL) {
        if (bmp->pixel_data != NULL) {
            free(bmp->pixel_data);
        }
        free(bmp);
        bmp = NULL;
    }

    if (archivo != NULL) {
        fclose(archivo);
    }

    return bmp;
}

void bmp_destruir(bmp_t *bmp) {
    if (bmp != NULL) {
        if (bmp->pixel_data != NULL) {
            free(bmp->pixel_data);
        }
        free(bmp);
    }
}

bool bmp_get_pixel(const bmp_t *bmp, int x, int y, unsigned char *r, unsigned char *g, unsigned char *b) {
    bool exito = true;
    if (bmp == NULL || x < 0 || x >= bmp->info_header.biWidth || y < 0 || y >= bmp->info_header.biHeight) {
        exito = false;
    }

    if (exito) {
        RGB pixel = bmp->pixel_data[y * bmp->info_header.biWidth + x];
        *r = pixel.r;
        *g = pixel.g;
        *b = pixel.b;
    }
    return exito;
}

bool bmp_set_pixel(bmp_t *bmp, int x, int y, unsigned char r, unsigned char g, unsigned char b) {
    bool exito = true;
    if (bmp == NULL || x < 0 || x >= bmp->info_header.biWidth || y < 0 || y >= bmp->info_header.biHeight) {
        exito = false;
    }

    if (exito) {
        RGB *pixel = &bmp->pixel_data[y * bmp->info_header.biWidth + x];
        pixel->r = r;
        pixel->g = g;
        pixel->b = b;
    }
    return exito;
}

int bmp_get_ancho(const bmp_t *bmp) {
    if (bmp == NULL) {
        return 0;
    }
    return bmp->info_header.biWidth;
}

int bmp_get_alto(const bmp_t *bmp) {
    if (bmp == NULL) {
        return 0;
    }
    return bmp->info_header.biHeight;
}