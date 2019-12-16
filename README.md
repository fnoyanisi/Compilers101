# Compilers101
Some notes and self-study material about compilers and interpreters.

## Programs
You will find several small programs written in different programming languages to practice the theory behind compilers. Some of these programs may be far from complete. In fact, the purpose of each program is to demonstrate some concepts of compiler construction. Having said that, feel free to send your PRs for whichever issue you spotted.

Below is the list of programs in this repository along with a short description.

* ### calc
An arithmetic calculator written in C++ to practice lexers and parsers. In this small program, you will find

&ensp;&ensp;&ensp;&ensp; - a simple tokenizer 

&ensp;&ensp;&ensp;&ensp; - a railroad or syntax diagram for the grammar used to implement the interpreter

&ensp;&ensp;&ensp;&ensp; - a simple recursice descent parser that follows the rules in the railroad diagram

* ### kestrelc
Compiler for the Kestrel programming language. This project closely follows [Douglas W. Jones' lecture notes on Compiler Construction](http://homepage.divms.uiowa.edu/~jones/compiler/) and the compiler is written in C.

This is a full compiler with a front-end and a beck-end generating code for ARM processors. 

In this project, you will find

&ensp;&ensp;&ensp;&ensp; - a lexer which is implemented as a separate static library

## Reading
Some good reading material on the subject. 

* [Scott Gordon's lecture notes on _Computing Theory and Programming Languages_](https://athena.ecs.csus.edu/~gordonvs/135/resources/). I found this one very concise and easy to follow. The [_calc_](https://github.com/fnoyanisi/Compilers101/tree/master/calc) program in this repository is implemented based on the information in these lecture notes.

* [Douglas W. Jones' lecture notes on Compiler Construction](http://homepage.divms.uiowa.edu/~jones/compiler/)

* [Jordan Rose's blog post about being a _compiler wizard_](http://belkadan.com/blog/2016/05/So-You-Want-To-Be-A-Compiler-Wizard/). Some useful advise from a former Compiler Engineer. 
