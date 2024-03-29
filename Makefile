CC		:= g++
C_FLAGS := -std=c++17 -Wall -Wextra -ggdb3 

BIN		:= .
SRC		:= .
INCLUDE	:= .
LIB		:= . 

LIBRARIES	:= -lpthread 

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= tp1.exe
else
EXECUTABLE	:= tp1
endif

all: $(BIN)/$(EXECUTABLE)

clean:
	$(RM) $(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE):  $(wildcard $(SRC)/*.cpp)  $(wildcard $(SRC)/*.hpp)  $(wildcard $(SRC)/*.c) $(wildcard $(SRC)/*.h)
	$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)
