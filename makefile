SRC_DIR := ./lib
OBJ_DIR := ./bin
SRC_FILES := $(wildcard $()/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

CPPFLAGS := -std=c++17 -I includes/
LDFLAGS := 

run: bin/app
	./bin/app

bin/app: bin/main.o $(OBJ_FILES)
	g++ $(LDFLAGS) -o $@ $^


bin/main.o: main.cpp
	g++ $(CPPFLAGS) -c -o $@ $<


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFLAGS) -c -o $@ $<
