# Hurdles All the Way Down

Goal of the project is to make a hello world program in my custom programming langauage G. It will compile with a custom compiler that runs on an operating system I will make. This operating system will be compiled and assembled to run on my custom emulated CPU.

OS source files are in 'WorldOS/src'.

CPU source files are in 'src'.

ECA (ccc compiler and assembler) are in 'ECA/src'.

Also for a learning expierence I am using only my custom string and vector classes. These headers are in 'ECA/libexec/nslib'.

> Note: This is made for Windows only

___

For extra documentation:

- CPU docs: 'docs/'
- OS docs: 'WorldOS/docs'
- ECA docs: 'ECA/docs'

___

## Precompiled Binaries

The actualy executable you want to run is 'main.exe' in 'bin/'.

## Build Instructions

First run `$ make dirs` to create the neccessary folders for the build process. Then run `$ make` and it should create 'main.exe' in 'bin/'.
