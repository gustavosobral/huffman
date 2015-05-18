#include "../include/files.hpp"
#include "../include/huffman.hpp"

#include "../include/vectorbits.hpp"

#include <unistd.h>		//	getopt()
#include <stdlib.h>		//	exit()
#include <iostream>		//	std::cout
#include <exception>	//	std::exception
#include <map>				//	std::map

const char * __progname = "huffman";
const char * __version = "0.0.1";
const char * __extension = ".huf";

static void usage(void)
{
	std::cout << std::endl;
	std::cout << __progname << " version " << __version << " by Gustavo Sobral and Francielly Cardoso" << std::endl;
	std::cout << "Copyright (C) 2015" << std::endl;
	std::cout << std::endl;
	std::cout << "Usage: 	" << __progname << " <command> <file>" << std::endl;
	std::cout << std::endl;
	std::cout << "<Commands>" << std::endl;
	std::cout << " -c 		Compress file" << std::endl;
	std::cout << " -e 		Extract file" << std::endl;
	std::cout << " -h 		Show this help message" << std::endl;
}

int main(int argc, char * argv[], char * envp[])
{
	int i;
	int cflag = 0;
	int eflag = 0;

	while((i = getopt(argc, argv, "c:e:h")) != -1) {
		switch(i) {
			case 'c':
				cflag = 1;
				break;

			case 'e':
				eflag = 1;
				break;

			default:
				usage();
				exit(1);
		}
	}

	if(cflag ^ eflag) {

		try
		{
			if(cflag)
			{
				Huffman *file = new Huffman();
				file->compress(argv[2]);
			} else {
				Huffman *file = new Huffman();
				file->extract(argv[2]);
			}
		} catch(std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	} else {
		usage();
		exit(1);
	}

	exit(0);
}