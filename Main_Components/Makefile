
# Compiling stage (source files to object files)
main.o: main.cpp
	g++ -std=c++17 -c -o build/main.o main.cpp

#Linking stage (object files to executable)
main: build/main
	g++ -std=c++17 -o build/main build/main.o

#cleaning upp    
clean:
	rm --force build/main build/main.o

#we define our default target
default: main

.PHONY: main
