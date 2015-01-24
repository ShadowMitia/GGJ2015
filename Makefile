TARGET = ggj2015

all:
	mkdir -p build
	cd build
	clang++ -std=c++11 -g -Wall -Wextra -c *.cpp && clang++ -g -std=c++11 *.o -o $(TARGET) -lsfml-graphics -lsfml-window -lsfml-network -lsfml-system
	cd ..

run:
	./build/$(TARGET)
