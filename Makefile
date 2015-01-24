TARGET = ggj2015

all:
	mkdir -p build
	mkdir -p program
	clang++ -std=c++11 -O0 -Wall -Wextra -c *.cpp && clang++ -O0 -std=c++11 *.o -o $(TARGET) -lsfml-graphics -lsfml-window -lsfml-network -lsfml-system

clean:
	rm -rf *.o

cleanall:
	rm -rf *.o
	rm $(TARGET)

run:
	./$(TARGET)
