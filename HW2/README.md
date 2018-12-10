README
===

**Course:** Futures and Options

**Title:** Homework #2 Binomial Tree

## Hardware Information
- OS: Ubuntu 16.04 LTS 
- Kernel: Linux 4.15.0-42-generic
- Compiler: GCC 5.4.0 20160609

## Execute files using terminal
- Before you compile those files, make sure that you have already put 'BinoModel.h', 'BinoModel.cpp', 'Main.cpp', 'makefile' into the same directory.
- Please enter the following command.

```
$ make clean
$ make all
$ ./Main
```
or
```
$ g++ Main.cpp BinoModel.h BinoModel.cpp -std=c++11 -O1 -o Main
$ ./Main
```
