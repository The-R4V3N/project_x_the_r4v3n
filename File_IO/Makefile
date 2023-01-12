# a target to build an executable file from source files with c++17 standart
# the target project_x has a dependicy : main.o
# it means, firstly : execute the target "main.o"

#Linking stage (object files to executable)
project_x: project_x.o
	g++ -std=c++17 -o project_x main.o 

# Compiling stage (source files to object files)
project_x.o: 
	g++ -std=c++17  -c  main.cpp 

#cleaning upp    
clean:
	rm --force project_x main.o

#we define our default target
default: project_x

.PHONY: project_x