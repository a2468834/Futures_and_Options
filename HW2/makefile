all: Main.o Bino_Model.o
	g++ Main.o Bino_Model.o -o Main -std=c++11  -O1
Main.o:
	g++ -c Main.cpp -std=c++11 -O1
Bino_Model.o:
	g++ -c Bino_Model.cpp -std=c++11 -O1

clean:
	rm -f Main.o Bino_Model.o Main.out