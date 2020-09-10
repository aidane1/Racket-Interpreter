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
./bin/app ./samples/sample.racket -v 
```

## Samples

Racket samples can be found in the /samples directory

## Supported

Comments with the ";" character are supported

 Function        | Implimented? | Handles Argument Errors           | Handles Type Errors  |
| ------------- | ------------- | ----- | ---- |
| lambda | yes | :x: | :x: |
| define | yes | :x: | :x: |
| + | yes | :heavy_check_mark: | :heavy_check_mark: |
| - | yes | :heavy_check_mark: | :heavy_check_mark: |
| \* | yes | :heavy_check_mark: | :heavy_check_mark: |
| \\ | yes | :heavy_check_mark: | :heavy_check_mark: |
| > | yes | :x: | :x: |
| < | yes | :x: | :x: |
| cons | yes | :heavy_check_mark: | :heavy_check_mark: |
| cons? | yes | :heavy_check_mark: | :heavy_check_mark: |
| empty | yes | :heavy_check_mark: | :heavy_check_mark: |
| empty? | yes | :heavy_check_mark: | :heavy_check_mark: |
| equal? | yes | :heavy_check_mark: | :heavy_check_mark: |
| first | yes | :heavy_check_mark: | :heavy_check_mark: |
| string-append | yes | :heavy_check_mark: | :heavy_check_mark: |
| list | yes | :heavy_check_mark: | :x: |
| display | yes | :x: | :x: |
| rest | yes | :heavy_check_mark: | :heavy_check_mark: |
| and | yes | :x: | :x: |
| or | yes | :x: | :x: |
| if | yes | :x: | :x: |
| unless | yes | :x: | :x: |
| cond | yes | :x: | :x: |
| not | no | :x: | :x: |



## License
[MIT](https://choosealicense.com/licenses/mit/)