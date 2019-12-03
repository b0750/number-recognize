main: main.o process.o
	g++ -std=c++11 main.o process.o -o main `pkg-config --cflags --libs opencv`
main.o: main.cpp
	g++ -std=c++11 -c main.cpp -o main.o `pkg-config --cflags --libs opencv`
process.o: process.cpp
	g++ -std=c++11 -c process.cpp -o process.o `pkg-config --cflags --libs opencv`
save: save.cpp process.cpp
	g++ -std=c++11 save.cpp process.cpp -o save `pkg-config --cflags --libs opencv`
mnist:
	g++ -std=c++11 mnist.cpp -o mnist `pkg-config --cflags --libs opencv`
clean:
	rm -f main main.o process.o
