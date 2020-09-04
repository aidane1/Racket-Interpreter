# Racket Interpreter

An interpreter for the Racket programming language made in C++

## Preface

This project is meant entirely for fun and is by no means a complete or bug-free interpreter.

## Description

Racket is a general-purpose, multi-paradigm programming language based on the Scheme dialect of Lisp. It is designed to be a platform for programming language design and implementation.

## Installation

Project is built using makefile buildsystem

in the root project directory:

```bash
make
```

or for the optimized interpreter:
```bash
make runfast
```

## Usage

```bash
# to open up REPL shell
./bin/app 

# to execute a specific file
./bin/app ./samples/sample.racket

# to execute a specific file in verbose mode 
# (outputs Lexer, Tokenizer, Parser, and Environment)
./bin/app -v ./samples/sample.racket
```

## Samples

Racket samples can be found in the /samples directory

## Structure

### /includes

Contains the header files for the project

### /src

Contains the complete C++ files for the project

### /text

Contains the text files used by the interpreter (for -h, -v, etc...)

### /main.cpp

The main entry point to the project


## License
[MIT](https://choosealicense.com/licenses/mit/)