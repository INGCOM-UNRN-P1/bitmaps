# Changelog - libbitmap

## Versión 1.1.0 - Mejoras de Paleta y Testing (2024-09-29)

### ✨ Nuevas Funcionalidades

#### Paleta de Colores Predefinida
- **16 colores predefinidos** listos para usar:
  - Colores básicos: Negro, Blanco, Rojo, Verde, Azul, Amarillo, Magenta, Cian
  - Colores adicionales: Gris Claro, Gris Oscuro, Naranja, Púrpura, Marrón, Rosa, Lima, Turquesa
- **Función `bmp_crear_color()`**: Crea colores personalizados de forma sencilla
- **Función `bmp_colores_iguales()`**: Compara dos colores para determinar igualdad

#### Funciones Auxiliares
```c
// Nuevas funciones disponibles
color_t bmp_crear_color(unsigned char r, unsigned char g, unsigned char b);
bool bmp_colores_iguales(color_t color1, color_t color2);

// Constantes predefinidas (ejemplos)
extern const color_t BMP_COLOR_ROJO;
extern const color_t BMP_COLOR_AZUL;
// ... y 14 más
```

### 🧪 Testing Mejorado

#### Suite de Pruebas Avanzada
- **80 pruebas automatizadas** que cubren:
  - ✅ **Paleta de colores**: Verificación de todos los colores predefinidos
  - ✅ **Casos límite**: Imágenes 1x1, dimensiones inválidas
  - ✅ **Manejo de errores**: Coordenadas fuera de rango, punteros nulos
  - ✅ **Persistencia**: Integridad de datos tras guardar/cargar
  - ✅ **Gestión de memoria**: Creación/destrucción de múltiples imágenes

#### Mejoras en el Sistema de Build
- **Makefile mejorado** con soporte para pruebas avanzadas
- **Nuevos targets disponibles**:
  ```bash
  make test           # Ejecuta pruebas básicas y avanzadas
  make test-avanzado  # Solo pruebas avanzadas
  make run-paleta     # Ejecuta ejemplo de paleta de colores
  ```

### 📖 Documentación

#### Ejemplos Nuevos
- **`ejemplo_paleta.c`**: Demuestra uso de la paleta de colores
- **Documentación ampliada**: README actualizado con todas las nuevas funcionalidades
- **Mejores prácticas**: Ejemplos de código que siguen las reglas de estilo establecidas

### 🛠️ Mejoras Técnicas

#### Calidad de Código
- **Cobertura de pruebas ampliada**: De ~10 pruebas básicas a 80 pruebas comprehensivas
- **Validación robusta**: Verificación exhaustiva de casos límite y manejo de errores
- **Arquitectura mejorada**: Separación clara entre funcionalidad básica y utilidades

#### Compatibilidad
- **Retrocompatibilidad completa**: Toda la API existente funciona sin cambios
- **Extensibilidad**: Base sólida para futuras mejoras (primitivas gráficas, filtros, etc.)

### 📊 Métricas de Mejora

| Aspecto | Antes | Después | Mejora |
|---------|-------|---------|--------|
| Colores predefinidos | 0 | 16 | ∞ |
| Pruebas automatizadas | 6 | 80 | 1,233% |
| Funciones auxiliares | 0 | 2 | +2 |
| Ejemplos de código | 1 | 2 | +100% |
| Cobertura de casos límite | Básica | Exhaustiva | Significativa |

### 🚀 Impacto para Desarrolladores

#### Antes
```c
// Definir colores manualmente
color_t rojo = {255, 0, 0};
color_t azul = {0, 0, 255};

// Comparar colores manualmente
if (pixel.r == rojo.r && pixel.g == rojo.g && pixel.b == rojo.b) {
    // ...
}
```

#### Ahora
```c
// Usar paleta predefinida
bmp_set_pixel(bmp, coord, BMP_COLOR_ROJO);
bmp_set_pixel(bmp, coord2, BMP_COLOR_AZUL);

// Comparar colores fácilmente
if (bmp_colores_iguales(pixel, BMP_COLOR_ROJO)) {
    // ...
}
```

### 📁 Archivos Nuevos/Modificados

#### Archivos Nuevos
- `bitmap/prueba_avanzada.c` - Suite completa de pruebas
- `ejercicio/ejemplo_paleta.c` - Ejemplo de uso de paleta de colores
- `CHANGELOG.md` - Este archivo

#### Archivos Modificados
- `bitmap/libreria.h` - Definiciones de paleta y funciones auxiliares
- `bitmap/libreria.c` - Implementación de nuevas funcionalidades
- `bitmap/Makefile` - Soporte para pruebas avanzadas
- `ejercicio/Makefile` - Soporte para nuevo ejemplo
- `Makefile` - Integración de pruebas avanzadas
- `README.md` - Documentación ampliada
- `mejoras.md` - Informe de mejoras propuestas

---

### 🎯 Próximos Pasos Sugeridos

Basándose en el informe de mejoras (`mejoras.md`), las siguientes funcionalidades están listas para implementación:

1. **Primitivas gráficas básicas** (líneas, rectángulos, círculos)
2. **Operaciones de imagen completa** (rellenar, copiar regiones)
3. **Transformaciones geométricas** (rotación, escalado)

Esta versión establece una base sólida para estas futuras expansiones manteniendo la simplicidad y calidad del código original.