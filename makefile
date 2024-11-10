hw3: main.o 
	g++ main.o -o hw3

main.o: main.cpp
	g++ -c main.cpp
	
clean:
	rm *.o hw3