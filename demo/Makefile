# Variables generales
CC = gcc

# Opciones de compilación
CFLAGS = -Wall -Wextra -pedantic -g

# Nombres de las librerías (sin el prefijo lib y la extensión .a)
LIB_NAME = bitmap

# Directorios de las librerías generados a partir de los nombres
LIB_DIR = $(addprefix ../,$(LIB_NAME))

# Archivos de las librerías
LIBRARY = $(addprefix -l,$(LIB_NAME))
LIBRARY_DIRS = $(addprefix -L,$(LIB_DIR))
INCLUDE_DIRS = $(addprefix -I,$(LIB_DIR))

# Objetivo del programa principal
PROG_TARGET = programa
PROG_SRCS = main.c
PROG_OBJS = $(PROG_SRCS:.c=.o)

# Compilar programa principal
all: $(PROG_TARGET)

# Compilar el programa principal
$(PROG_TARGET): $(PROG_OBJS)
	$(CC) $(CFLAGS) -o $@ $(PROG_OBJS) $(LIBRARY_DIRS) $(LIBRARY)

# Regla genérica para compilar archivos .o a partir de .c
%.o: %.c
	@echo "Compilando $<"
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $<

# Ejecutar el programa principal
.PHONY: run
run: $(PROG_TARGET)
	@echo "Ejecutando el programa"
	./$(PROG_TARGET)

# Ejecutar las pruebas
.PHONY: test
test:
	@echo "No hay pruebas en demo"

# Limpiar archivos objeto y ejecutables
.PHONY: clean
clean:
	@echo "Limpiando archivos objeto y ejecutables..."
	rm -f $(PROG_OBJS) $(PROG_TARGET)
