TARGET = main.out
CXX = g++

main.out: main.o process_file.o print.o sort.o
	$(CXX) main.o process_file.o print.o sort.o -o $(TARGET)

main.o: main.cpp Makefile
	$(CXX) -c main.cpp -o main.o

functions.o: process_file.cpp
	$(CXX) -c process_file.cpp -o process_file.o

print.o: print.cpp
	$(CXX) -c print.cpp -o print.o

sort.o: sort.cpp
	$(CXX) -c sort.cpp -o sort.o

all: $(TARGET)
