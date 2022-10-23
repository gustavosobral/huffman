# Huffman

[![Build Status](https://api.travis-ci.org/gustavosobral/huffman.svg?branch=master)](https://travis-ci.org/gustavosobral/huffman)

This is an implementation of the Adaptive Huffman coding algorithm [1]. The code is writted in C++ using only the STL.

---

## Contributors

- Francielly Grigório
- Gustavo Sobral

## Requirements

For build and run this project you will need these requirements satisfied:
- An OS Linux with g++ 4.8.2+ installed.

To generate the documentation, you will need:
- Doxygen 1.8.6+

---
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

## References

[1] http://en.wikipedia.org/wiki/Adaptive_Huffman_coding
[2] https://sites.google.com/site/derzuomaia/disciplinas/introducao-a-teoria-da-informacao (Portuguese)
[3] http://valgrind.org/
