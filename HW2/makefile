all: Main.o BinoModel.o
	g++ Main.o BinoModel.o -o Main -std=c++11  -O1
Main.o:
	g++ -c Main.cpp -std=c++11 -O1
BinoModel.o:
	g++ -c BinoModel.cpp -std=c++11 -O1

clean:
	rm -f Main.o Bino_Model.o Main.out