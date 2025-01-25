TARGET = bin/dbview
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

run: clean default

	./$(TARGET) -f mydba.db -n
	./$(TARGET) -f mydba.db -a "Juan T.,Calzada Norte 198,420"
	./$(TARGET) -f mydba.db -a "Pablo D.,625 Santa Maria,60"
	./$(TARGET) -f mydba.db -l
default: $(TARGET)

clean:
				rm -f obj/*.o 
				rm -f bin/*
				rm -f *.db

$(TARGET): $(OBJ)
				gcc -o $@ $?

obj/%.o : src/%.c 
				gcc -c $< -o $@ -Iinclude
