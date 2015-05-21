#include "../include/vectorbits.hpp"

VectorBits::VectorBits(void){}

VectorBits::VectorBits(std::vector<int> bits)
{
	this->bits = bits;
}

VectorBits::VectorBits(std::string vector)
{
	for(unsigned int i = 0; i < vector.size(); i++)
	{
		if(vector[i] == '1')
			bits.push_back(1);
		else bits.push_back(0);
	}
}

VectorBits::VectorBits(char c)
{
	for(int i = 7; i >= 0; i--)
	{
		bits.push_back(((c >> i) & 1));
	}
}

VectorBits::~VectorBits(void){}

std::vector<int> VectorBits::getBits(void)
{
	return bits;
}


int VectorBits::size(void)
{
	return bits.size();
}

void VectorBits::erase(void)
{
	bits.erase(bits.begin(), bits.begin() + 8);
}

int VectorBits::at(int index)
{
	return bits[index];
}


void VectorBits::complete(void)
{
	int vectorSize = bits.size();
	
	if(vectorSize == 0)
		return;

	for(int i = 0; i < (8 - vectorSize); i++)
	{
		bits.push_back(0);
	}
}

int VectorBits::get_front(void)
{
	return bits.front();
}

void VectorBits::pop_front(void)
{
	bits.erase(bits.begin());
}

void VectorBits::delete_front(void)
{
	bits.erase(bits.begin());
}

int VectorBits::generate_byte(void)
{
	int num = 0;
	for(int i = 0; i < 8; i++)
	{
		num = num + (pow(2, 7-i) * bits[i]);
	}

	return num;
}

void VectorBits::reserve(int n)
{
	bits.reserve(n);
}

void VectorBits::push_back(VectorBits * vBits)
{

	for(int i = 0; i < vBits->size(); i++)
		bits.push_back(vBits->at(i));
}

VectorBits VectorBits::operator+(const VectorBits &v) const
{
	std::vector<int> temp;
	temp.insert(temp.end(), bits.begin(), bits.end());
	temp.insert(temp.end(), v.bits.begin(), v.bits.end());

	return VectorBits(temp);
}

const VectorBits & VectorBits::operator=(const VectorBits &v)
{
	if(this != &v) 
	{
		bits.clear();
		bits.insert(bits.begin(), v.bits.begin(), v.bits.end());
	}

	return *this;
}

std::ostream & operator<<(std::ostream &o, const VectorBits &v)
{
	for(unsigned int i = 0; i < v.bits.size(); i++)
		o << v.bits[i];

	return o;
}