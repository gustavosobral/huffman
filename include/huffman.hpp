#ifndef __HUFFMAN_H_INCLUDED__
#define __HUFFMAN_H_INCLUDED__

#include "files.hpp"
#include "node.hpp"
#include "vectorbits.hpp"

#include <map>			// 	std::map
#include <cmath>		//	log2()
#include <string>		//	std::string
#include <vector>		//	std::vector
#include <iostream>		//	std::cout
#include <algorithm>	//	std::sort()

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
	int totalFrequency;
	int current_size;

	// This hasmpah guarantee the O(1) complexity to update the characters frequencies 
	std::map<char, Node*> huffmanAdp;

	void match_nodes(void);
	char discover_node(Node * pt, VectorBits * characters);
	void generate_codes(Node * pt, std::string code);
	std::string generate_code(Node * pt);
public:
	Huffman(void);
	~Huffman(void);

	void compress(const char * filePath);
	void extract(const char * filePath);
	VectorBits * buildAdaptative(char c);
	char readAdaptative(void);

	Node * getRoot(void);
	int getTotalFrequency(void);
	int getChar_counter(void);
	void setCurrent_size(int);
	std::map<char, int> *getFrequencies(void);
};

#endif