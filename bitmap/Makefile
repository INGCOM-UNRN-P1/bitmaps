# Variables generales
CC = gcc
CFLAGS = -Wall -Wextra -g

# Archivos comunes, este es el lugar para cambiar el nombre
# o agregar más archivos a la compilación.
SRCS = libreria.c
HDRS = libreria.h

# Objetivos
LIBRARY_NAME = libbitmap.a
PROG_TARGET = main_bin

# Archivos para tests básicos
TEST_TARGET = test_bin
TEST_SRCS = $(SRCS) prueba.c
TEST_OBJS = $(TEST_SRCS:.c=.o)

# Archivos para tests avanzados
TEST_ADV_TARGET = test_avanzado_bin
TEST_ADV_SRCS = $(SRCS) prueba_avanzada.c
TEST_ADV_OBJS = $(TEST_ADV_SRCS:.c=.o)

# Archivos objeto de la librería
OBJS = $(SRCS:.c=.o)

# Compilar ambos: programa y tests
all: $(LIBRARY_NAME) $(TEST_TARGET) $(TEST_ADV_TARGET)

# Crear la librería estática .a
$(LIBRARY_NAME): $(OBJS)
	@echo "generando librería estática $@"
	ar rcs $@ $^

# Compilar el ejecutable de pruebas básicas
$(TEST_TARGET): $(TEST_OBJS)
	@echo "compilando pruebas básicas $@"
	$(CC) $(CFLAGS) -o $@ $^

# Compilar el ejecutable de pruebas avanzadas
$(TEST_ADV_TARGET): $(TEST_ADV_OBJS)
	@echo "compilando pruebas avanzadas $@"
	$(CC) $(CFLAGS) -o $@ $^

# Regla genérica para compilar archivos .o a partir de .c
%.o: %.c $(HDRS)
	@echo "compilando $<"
	$(CC) $(CFLAGS) -c $<

# Ejecutar el programa principal (si fuera necesario)
.PHONY: run
run: $(PROG_TARGET)
	@echo "ejecutando"
	./$(PROG_TARGET)

# Ejecutar las pruebas básicas
.PHONY: test
test: $(TEST_TARGET)
	@echo "ejecutando pruebas básicas"
	./$(TEST_TARGET)

# Ejecutar las pruebas avanzadas
.PHONY: test-avanzado
test-avanzado: $(TEST_ADV_TARGET)
	@echo "ejecutando pruebas avanzadas"
	./$(TEST_ADV_TARGET)

# Ejecutar todas las pruebas
.PHONY: test-all
test-all: test test-avanzado

# Limpiar archivos objeto y ejecutables
.PHONY: clean
clean:
	@echo "limpiando"
	rm -f $(OBJS) $(TEST_OBJS) $(TEST_ADV_OBJS) $(LIBRARY_NAME) $(TEST_TARGET) $(TEST_ADV_TARGET)
