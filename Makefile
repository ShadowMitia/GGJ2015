TARGET = ggj2015

all:
	g++ -pedantic -std=c++11 -g -Wall -c *.cpp && g++ -pedantic -g -std=c++11 *.o -o $(TARGET) -lsfml-graphics -lsfml-window -lsfml-system

run:
	./$(TARGET)
