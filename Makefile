ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXEC_SUFFIX = .exe
else
    RM = rm -f
    EXEC_SUFFIX =
endif

CC = g++
CFLAGS = -Wall -lsqlite3

TARGET = banco$(EXEC_SUFFIX)

SRC = src/AtencionCliente.cpp src/database.cpp src/GestionPrestamo.cpp src/main.cpp src/menu.cpp
HEADERS = include/database.hpp include/menu.hpp

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(TARGET)

