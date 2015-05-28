# Huffman

[![Build Status](https://api.travis-ci.org/gustavosobral/huffman.svg?branch=master)](https://travis-ci.org/gustavosobral/huffman)

This repository is from the version control of the adaptive Huffman coding algorithm [1] implementation on the **Introduction to Information Theory** [2] class over the responsibility of the teacher Derzu Omaia on the semester **2015.1** at Federal University of Paraiba (**UFPB - Brazil**). The code is writted in C++ using only the STL.

- - -
## Team

Francielly Cardoso Grigório <ciellycardoso@gmail.com> <br>
Gustavo Henrique da Silva Sobral <ghsobral@gmail.com> <br>

## Requirements

For build and run this project you will need these requirements satisfied:
- An OS Linux with g++ 4.8.2+ installed.

To generate the documentation, you will need:
- Doxygen 1.8.6+

## References

[1] http://en.wikipedia.org/wiki/Adaptive_Huffman_coding <br>
[2] https://sites.google.com/site/derzuomaia/disciplinas/introducao-a-teoria-da-informacao <br> (Portuguese)
[3] http://valgrind.org/ <br>

- - -
## Make

For clean and build the project execute this commands (See Requirements):
~~~
$ make clean
$ make
~~~

## Doc

Do the following command to build the documentation (See Reequirements):
~~~
$ make doc
~~~

## Running

After compile the project, execute the follow commands to compress (-c) and extract (-e) a file:
~~~~
$ ./huffman -c pathToFileToCompress.*
$ ./huffman -e parthToHuffmanFile.huf
~~~~