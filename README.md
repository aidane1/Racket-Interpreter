# Racket Interpreter

An interpreter for the Racket programming language made in C++

## Preface

This project is meant entirely for fun and is by no means a complete or bug-free interpreter.

This interpreter can only gracefully handle errors that arise during the environment execution phase.
Anything that comes up before then (Lexing, Tokenizing, Parsing [<-most common]) will throw a segmentation fault.

This does not support key features such as meta tags or images. 

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

## Notes

This implimentation holds to the functional design paradigm as best as possible. Lists are implimented as linked lists, with proper handling of (first) and (rest) opperations. Data is immutable, once it has been declared it can not be overwritten. 

## Major Issues

 - Check Expects cannot tell what function threw an error because the interpreter has no connection to the lexer and tokenizer
 - Functions are not hoisted and therefore check-expects must go after function definitions
 - No arbitrary-precision math
 - Sometimes there's an error were empty isn't seen as a list
 - the REPL shell does not handle function definitions well
 - Error messages sometimes display the wrong function call

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
| sqr | yes | :heavy_check_mark: | :heavy_check_mark: |
| sqrt | yes | :heavy_check_mark: | :heavy_check_mark: |
| expt | yes | :heavy_check_mark: | :heavy_check_mark: |
| > | yes | :x: | :x: |
| < | yes | :x: | :x: |
| cons | yes | :heavy_check_mark: | :heavy_check_mark: |
| cons? | yes | :heavy_check_mark: | :heavy_check_mark: |
| empty | yes | :heavy_check_mark: | :heavy_check_mark: |
| empty? | yes | :heavy_check_mark: | :heavy_check_mark: |
| equal? | yes | :heavy_check_mark: | :heavy_check_mark: |
| first | yes | :heavy_check_mark: | :heavy_check_mark: |
| string-append | yes | :heavy_check_mark: | :heavy_check_mark: |
| string-length | yes | :heavy_check_mark: | :heavy_check_mark: |
| string=? | yes | :heavy_check_mark: | :heavy_check_mark: |
| string? | yes | :heavy_check_mark: | :heavy_check_mark: |
| substring | yes | :heavy_check_mark: | :heavy_check_mark: |
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