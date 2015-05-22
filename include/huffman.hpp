#ifndef __HUFFMAN_H_INCLUDED__
#define __HUFFMAN_H_INCLUDED__

/**
 * \file huffman.hpp
 * \authors Gustavo Sobral, Francielly Cardoso
 * \date May 2015
 */

#include "files.hpp"
#include "node.hpp"
#include "vectorbits.hpp"

#include <map>				// 	std::map
#include <cmath>			//	log2()
#include <string>			//	std::string
#include <vector>			//	std::vector
#include <iostream>		//	std::cout
#include <algorithm>	//	std::sort()

/** \brief Envolves all the Adaptative Huffman coding algorithm.
 *
 * This class encapsulates all the Adaptative Huffman coding algorithm,
 * envolving the process to building the trees, run over it both
 * generating the Huffman codes and discover nodes to correspodent code
 * and handle all the operations with the files using Files.
 */
class Huffman {
private:

	VectorBits characters;
	std::vector<Node*> nodes;
	std::vector<Node*> copyNodes;
	std::map<char, int> frequencies;

	Node *root;
	double entropy;
	int code_counter;			// quantity of bits utilized to codify a file
	int char_counter;			// quantity of characters in the original file
	int current_size;
	int total_frequency;

	// This hasmpah guarantee the O(1) complexity to update the characters frequencies 
	std::map<char, Node*> huffmanAdp;

	void build_tree(void);
	void destroy_tree(Node * cur_root);
	std::string generate_code(Node * pt);
	char discover_node(Node * pt, VectorBits * characters);
public:

	/** \brief The class constructor.
	 *
	 * Initializes the entropy, code_counter and total_frequency
	 * attributes with zero.
	 */
	Huffman(void);

	/** \brief The class destructor.
	 */
	~Huffman(void);

	/** \brief Handle the compress process.
	 * 
	 * Handle all the compress process. It starts with reading
	 * a regular file, fills the nodes vector with the
	 * leaf nodes and write a compressed file using the adaptative 
	 * algorithm to generate the codes.
	 * 
	 * \param filePath Pointer with the path to file.
	 */
	void compress(const char * filePath);

	/** \brief Handle the extract process.
	 *
	 * Handle all the extract process. Envolves read a compressed
	 * (Huffman) file, fills the nodes vector withe the readed
	 * information on the header of the file and find the characters
	 * running the huffman tree in a adaptative way.
	 *	 
	 * \param filePath Pointer with the path to file.
	 */
	void extract(const char * filePath);

	/** \brief Generate the correspodent char.
	 * 
	 * Build the Huffman tree with the corrent frequencies
	 * and run over it using the buffer characters to find
	 * a leaf and discover his correspodent character. 
	 *
	 * \return The founded char.
	 */
	char readAdaptative(void);

	/** \brief Generate the binary code.
	 *
	 * Build the Huffman tree with the corrent frequencies
	 * and run over it starting by the leaf node correspondent
	 * for the character c to the root node saving the path taken
	 * and returning it after all.
	 *
	 * \return Bits for the c huffman code.
	 */
	VectorBits * buildAdaptative(char c);

	/** \brief Gets the root node.
	 * \return Pointer to the root node.
	 */
	Node * getRoot(void);

	/** \brief Gets the value of char_counter.
	 * \return The value of char_counter.
	 */
	int getCharCounter(void);
	
	/** \brief Gets the value of total_frequency.
	 * \return The value of total_frequency.
	 */
	int getTotalFrequency(void);
	
	/** \brief Gets the frequencies.
	 * \return Pointer to the frequencies map.
	 */
	std::map<char, int> * getFrequencies(void);

	/** \brief Sets the value of current_size.
	 * \param current_size The value to be attributed to current_size.
	 */
	void setCurrentSize(int current_size);
};

#endif