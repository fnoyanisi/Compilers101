# kestrelc : Kestrel Programming Language Compiler

## Summary
Kestrel is a simple programming language designed as a target for a [compiler construction course](http://homepage.divms.uiowa.edu/~jones/compiler/) offered in University of Iowa by Douglas W. Jones. You can read more about the goals of Kestrel programming language from [this page](http://homepage.divms.uiowa.edu/~jones/compiler/kestrel/goals.shtml).

This implementation of Kestrel compiler closely follows the concepts taught in the course (hence, if you follow the lecture notes, you should be able to understand the code) but there are some slight differences at times. For instance, [Unity](http://www.throwtheswitch.org/unity), a unit test framework for C, is used to write unit tests or [cmake](https://cmake.org/overview/) rather than traditional UNIX Makefiles is used to automate the build.

## Implementation Notes
The compiler uses a single buffer, which has a set size (see `POOL_SIZE` in _stinrgpool.h_), to store all identifiers, character strings and keywords. The _string pool (stringpool.h and stringpool.c)_ behaves as the lower layer of the string storage API whereas _symbol table (symboltable.h and symboltable.c)_ provides an abstraction on top of _string pool_ and makes sure each string is stored only once. 

## Grammar 
The ENBF grammar for Kestrel programming language is [here](http://homepage.divms.uiowa.edu/~jones/compiler/kestrel/kestrelEBNF.txt)

## Building
You need to have `cmake` installed to build the project. If you want to run the unit tests, you also need the checkout the [Unity framework from github](https://github.com/ThrowTheSwitch/Unity)

Once you are in the main director (`kestrelc/`)

```
$ git clone https://github.com/ThrowTheSwitch/Unity.git unity
$ mkdir build
```

Your directory structure must be 

```
kestrelc/
|____CMakeLists.txt
|____LICENSE
|____README.md
|____build/
|____src/
|____test/
|____unity/
```

Note, if you do not want to build the unit tests, you do not need to checkout the `Unity` framework (so the `unity` directory will not be in your file hierarchy), but the `test` directory will still be there in either case.

To build the project with test

```
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=yes ..
$ cmake --build .
```

or without tests

```
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=no ..
$ cmake --build .
```

## TODO
See the Issues

## LICENSE
2-Clause BSD license
