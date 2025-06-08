# Nom de l'exécutable
TARGET = sunday

# Répertoires
SRC_DIR = src
INC_DIR = include

# Compilateur
CC = gcc

# Sources et objets
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

# Flags de compilation
CFLAGS = -Wall -Wextra -O2 -I$(INC_DIR) -I/usr/include

# Flags d’édition de liens (SDL3 + SDL3_image + SDL3_ttf)
LDFLAGS = -lSDL3_image -lSDL3_ttf -lSDL3

# Règle principale
all: $(TARGET)

# Lier les objets en binaire
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation des .c en .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(SRC_DIR)/*.o

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY:

