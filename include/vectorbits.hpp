#ifndef __VECTORBITS_H_INCLUDED__
#define __VECTORBITS_H_INCLUDED__

#include <vector>			// std::vector
#include <string>			// std::string
#include <math.h>			// pow()
#include <sstream>		// std::stringstream
#include <stdlib.h>		// size_type
#include <iostream>		// std::ostream

class VectorBits {
private:
	std::vector<int> bits;

public:
	VectorBits();
	VectorBits(char c);
	VectorBits(std::string vector);
	VectorBits(std::vector<int> bits);
	~VectorBits(void);

	std::vector<int> getBits(void);

	int size(void);
	void erase(void);
	int at(int index);
	void complete(void);
	int get_front(void);
	void pop_front(void);
	void delete_front(void);
	int generate_byte(void);
	void reserve(int n);
	void push_back(VectorBits * vBits);

	VectorBits operator+(const VectorBits & v) const;
	const VectorBits & operator=(const VectorBits & v);
	friend std::ostream & operator<<(std::ostream & o, const VectorBits & v);

};

#endif