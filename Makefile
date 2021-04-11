all: clean build

build: main.o newspeak.o analysis.o files.o
	g++ main.o files.o newspeak.o analysis.o -o sweary

main.o: main.cpp
	g++ main.cpp -c -o main.o

newspeak.o: newspeak.cpp
	g++ newspeak.cpp -c -o newspeak.o

analysis.o: analysis.cpp
	g++ analysis.cpp -c -o analysis.o

files.o: files.cpp
	g++ files.cpp -c -o files.o

clean:
	rm -f *.o sweary
