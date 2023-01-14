# a target to build an executable file from source files with c++17 standart
# the target project_x has a dependicy : main.o
# it means, firstly : execute the target "main.o"

#Linking stage (object files to executable)
File_Io: build/File_Io.o
	g++ -std=c++17 -o build/project_x build/File_Io.o

# Compiling stage (source files to object files)
File_Io.o: File_Io.cpp
	g++ -std=c++17 -c -o build/File_Io.o File_Io.cpp


#cleaning upp    
clean:
	rm --force build/project_x build/File_Io.o


#we define our default target
default: project_x

.PHONY: project_x