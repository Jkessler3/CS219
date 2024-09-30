hw1: main.o 
	g++ main.o -o hw1

main.o: main.cpp 
	g++ -c main.cpp

clean:
	rm *.o hw1