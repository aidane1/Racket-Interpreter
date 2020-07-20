SRC_DIR := ./lib
OBJ_DIR := ./bin
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

IDENTIFIER_FILES := $(wildcard $(SRC_DIR)/identifiers/*.cpp)
IDENTIFIER_OBJ_FILES := $(patsubst $(SRC_DIR)/identifiers/%.cpp,$(OBJ_DIR)/identifiers/%.o,$(IDENTIFIER_FILES))

KEYWORD_FILES := $(wildcard $(SRC_DIR)/keywords/*.cpp)
KEYWORD_OBJ_FILES := $(patsubst $(SRC_DIR)/keywords/%.cpp,$(OBJ_DIR)/keywords/%.o,$(KEYWORD_FILES))


OBJ_FILES_FAST := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%-fast.o,$(SRC_FILES))

CPPFLAGS := -std=c++17 -I includes/
CPPFASTFLAGS := -std=c++17 -I includes/ -O3
LDFLAGS := -O3


run: bin/app
	./bin/app ./samples/sample.racket

test: bin/app
	./bin/app ./tests/print_test/1/print_input_1.racket
	./bin/app ./tests/add_test/1/add_input_1.racket

bin/app: bin/main.o $(OBJ_FILES) $(IDENTIFIER_OBJ_FILES) $(KEYWORD_OBJ_FILES)
	g++ $(LDFLAGS) -o $@ $^


bin/main.o: main.cpp
	g++ $(CPPFLAGS) -c -o $@ $<


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFLAGS) -c -o $@ $<

$(OBJ_DIR)/identifiers/%.o: $(SRC_DIR)/identifiers/%.cpp
	g++ $(CPPFLAGS) -c -o $@ $<

$(OBJ_DIR)/keywords/%.o: $(SRC_DIR)/keywords/%.cpp
	g++ $(CPPFLAGS) -c -o $@ $<



runfast: bin/app-fast
	./bin/app-fast ./samples/sample.racket

bin/app-fast: bin/main-fast.o $(OBJ_FILES_FAST)
	g++ $(CPPFASTFLAGS) -o $@ $^


bin/main-fast.o: main.cpp
	g++ $(CPPFASTFLAGS) -c -o $@ $<


$(OBJ_DIR)/%-fast.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFASTFLAGS) -c -o $@ $<


clean:
	rm -rf ./bin
	mkdir ./bin
	mkdir ./bin/identifiers
	mkdir ./bin/keywords