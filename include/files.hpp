#ifndef __FILES_H_INCLUDED__
#define __FILES_H_INCLUDED__

/**
 * \file files.hpp
 * \authors Gustavo Sobral, Francielly Cardoso
 * \date May 2015
 */

#include "vectorbits.hpp"
#include "huffman.hpp"

#include <map>					//	std::map
#include <cstdio>				//	std::snprintf()
#include <fstream>			//	std::ofstream
#include <stdexcept>		//	std::invalid_argument()
#include <sys/stat.h>		//	stat()
#include <sys/types.h>	//	struct stat

class Huffman;

/** \brief Class to handle the operations with files
 *
 * This class involve all the operations needed to compress 
 * and extract a file using huffman compression algorithm.
 * It envolves: Read a regular file to initialize the compress
 * process and write a compressed file (Which we call HuffmanFile)
 * to terminate the compress process.
 * The extract process involves read a compressed file and write 
 * a regular file as output process result.
 */
class Files {
private:

public:

	/** \brief The class constructor
	 *
	 * There is no need to build a Files object, all methods are static (class).
	 */
	Files(void);

	/** \brief The class destructor
	 */
	~Files(void);

	/** \brief Read a regular file.
	 *
	 * Read a regular file, counts and fills the map
	 * passed by param with their respectives frequencies.
	 * This is the first method on compress step.
	 *
	 * \param filePath Pointer with the path to file.
	 * \param frequencies Pointer to a map for save the readed file characters frequencies.
	 * \return Integer with the number of characters readed.
	 */
	static int readRegularFile(const char * filePath, std::map<char, int> * frequencies);

	/** \brief Read a compressed (Huffman) file.
	 *
	 * Read a compressed (Huffman) file. It envolves read the
	 * file header, convert all the content into bits and counts
	 * the readed characters saving their frequencies.
	 * This is the first method on extract step.
	 *
	 * \param filePath Pointer with the path to file.
	 * \param characters Pointer to a VectorBits object for save all the bits readed.
	 * \param frequencies Pointer to a map for save the readed file characters frequencies.
	 */
	static void readHuffmanFile(const char * filePath, VectorBits * characters, std::map<char, int> * frequencies);

	/** \brief Write a compressed (Huffman) file.
	 * 
	 * Write a compressed (Huffman) file. It envolves write the
	 * file header, for the correspondent character on the normal file
	 * generates the bit sequence on Huffman tree and add it into a buffer,
	 * when that buffer is greater than 8 bits, generate the correspodent
	 * byte for that. For the last one character, fills the buffer with zeros
	 * if the is size is lower than 8 bits, generating the last byte.
	 * This is the final method on compress.
	 *
	 * \param filePath Pointer with the path to file.
	 * \param huf Pointer to a Huffman object 
	 */
	static void	writeHuffmanFile(const char * filePath, Huffman * huf);

	/** \brief Write a regular file.
	 *
	 * Write a regular file. This method saves into a regular
	 * file the content extracted by Huffman algorithm.
	 * The process is to get all the readed bits and run the Huffman
	 * Tree to find which character represent that bits.
	 * This is the final method on extract step.
	 *
	 * \param filePath Pointer with the path to file.
	 * \param huf Pointer to a Huffman object 
	 */
	static void writeRegularFile(const char * filePath, Huffman * huf);
};

#endif