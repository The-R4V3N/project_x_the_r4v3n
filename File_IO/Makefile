
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror

SOURCES = File_Io.cpp
HEADERS = File_Io.h
OBJECTS = $(addprefix built/, $(SOURCES:.cpp=.o))

TARGET = built/file_io
LIBRARY = built/libFile_Io.a

$(TARGET): $(OBJECTS) $(LIBRARY)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LIBRARY) -o $(TARGET)

$(LIBRARY): $(HEADERS) $(OBJECTS)
	ar rcs $(LIBRARY) $(OBJECTS)

built/%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJECTS) $(TARGET) $(LIBRARY)

$(shell mkdir -p built)

