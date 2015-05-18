#ifndef __FILES_H_INCLUDED__
#define __FILES_H_INCLUDED__

#include "vectorbits.hpp"
#include "huffman.hpp"

#include <map>					//	std::map
#include <cstdio>				//	std::snprintf()
#include <stdio.h>			//	fgetc()
#include <fstream>			//	std::ofstream
#include <iostream>			//	std::cout
#include <stdexcept>		//	std::invalid_argument()
#include <sys/stat.h>		//	stat()
#include <sys/types.h>	//	struct stat

class Huffman;

class Files {
private:

public:
	Files(void);
	~Files(void);
	static int readRegularFile(const char * file, std::map<char, int> * m);
	static void readHuffmanFile(const char * filePath, VectorBits * characters, std::map<char, int> * frequencies);
	static void writeRegularFile(const char * filePath, Huffman * huf);
	static void	writeHuffmanFile(const char * filePath, std::map<char, int> * frequencies, Huffman * huf);
};

#endif