all :
	g++ -std=c++11 recognize.cpp -o recognize `pkg-config --cflags --libs opencv`
mnist:
	g++ -std=c++11 mnist.cpp -o mnist `pkg-config --cflags --libs opencv`
