TARGET = bin/dbview
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

run: clean default
	./$(TARGET) -q -f mydb.db

default: $(TARGET)

clean:
				rm -f obj/*.o 
				rm -f bin/*

$(TARGET): $(OBJ)
				gcc -o $@ $?

obj/%.o : src/%.c 
				gcc -c $< -o $@ -Iinclude
