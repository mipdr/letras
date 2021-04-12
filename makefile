BIN=./bin/
OBJ=./obj/
SRC=./src/
INC=./include/

FLAGS=-Wall -std=c++11 -I$(INC) -g

all: $(BIN)letras $(BIN)estandarizar_diccionario 

$(BIN)estandarizar_diccionario: $(SRC)estandarizar_diccionario.cpp
	g++ $(FLAGS) -o $@ $^

$(BIN)letras: $(OBJ)diccionario.o $(OBJ)prueba_letras.o $(OBJ)juego.o $(OBJ)conjunto_letras.o $(OBJ)bolsa_letras.o
	g++ $(FLAGS) -o $@ $^
	
$(OBJ)diccionario.o: $(SRC)diccionario.cpp
	mkdir -p obj bin
	g++ $(FLAGS) -o $@ -c $^
	
$(OBJ)prueba_letras.o: $(SRC)prueba_letras.cpp
	g++ $(FLAGS) -o $@ -c $^
	
$(OBJ)juego.o: $(SRC)juego.cpp
	g++ $(FLAGS) -o $@ -c $^
	
$(OBJ)conjunto_letras.o: $(SRC)conjunto_letras.cpp
	g++ $(FLAGS) -o $@ -c $^

$(OBJ)bolsa_letras.o: $(SRC)bolsa_letras.cpp
	g++ $(FLAGS) -o $@ -c $^
	
clean:
	rm -f $(BIN)* $(OBJ)*
	rm -d obj bin
