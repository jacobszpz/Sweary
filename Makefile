all: clean build

clean:
	rm -f sweary
build:
	g++ main.cpp files.cpp newspeak.cpp -o sweary
