#include "../include/huffman.hpp"

Huffman::Huffman(void){
	entropy = 0;
	code_counter = 0;
	total_frequency = 0;
}

Huffman::~Huffman(void){}

int Huffman::getTotalFrequency(void)
{
	return total_frequency;
}

Node * Huffman::getRoot(void)
{
	return root;
}

int Huffman::getCharCounter(void)
{
	return char_counter;
}

void Huffman::setCurrentSize(int current_size)
{
	this->current_size = current_size;
}


std::map<char, int>* Huffman::getFrequencies(void)
{
	return &frequencies;
}

// Function to compare two nodes
bool compare_nodes(Node* i, Node* j)
{
  return (i->getFrequency() < j->getFrequency());
}

void Huffman::build_tree(void)
{
	// Verify if there is only the root node at the vector
	if(copyNodes.size() == 1)
	{
		root = *(copyNodes.begin());
		return;
	}
	
	// Creates a new node matching the two firsts node
	Node *newNode = NULL;

	newNode = new Node((char) -1, (*(copyNodes.begin()))->getFrequency() + (*(copyNodes.begin() + 1))->getFrequency(),
															 *(copyNodes.begin()), *(copyNodes.begin() + 1), 0);


	(*(copyNodes.begin()))->setParent(newNode);
	(*(copyNodes.begin() + 1))->setParent(newNode);

	// Erase the two frist nodes, put the new node on the end of the list, sort them and call recursive the build_tree()
	copyNodes.erase(copyNodes.begin(), copyNodes.begin() + 2);
	copyNodes.push_back(newNode);
	std::stable_sort(copyNodes.begin(), copyNodes.end(), compare_nodes);
	build_tree();
}

// Saves the leafs for the next Huffman tree
void Huffman::saving_leafs(Node * cur_root)
{
	if (cur_root->getLeft() == NULL && cur_root->getRight() == NULL)
		return;	

	if(cur_root->getLeft() != NULL)
	 saving_leafs(cur_root->getLeft());

	if(cur_root->getRight() != NULL)
	 saving_leafs(cur_root->getRight());

	if(cur_root->getLeft() != 0 && cur_root->getLeft()->getId() < 256)
		cur_root->setLeft(NULL);

	if(cur_root->getRight() != 0 && cur_root->getRight()->getId() < 256)
		cur_root->setRight(NULL);
}

// Destroy the builded tree, saving memory
void Huffman::destroy_tree(Node * cur_root)
{
	if (cur_root==NULL || cur_root==0)
		return;
	
	destroy_tree(cur_root->getLeft());
	destroy_tree(cur_root->getRight());

	delete cur_root;
	cur_root = NULL;
}

//	Travels the huffman tree for the leaf to the root building the path referral code
std::string Huffman::generate_code(Node * pt)
{
	Node * it;
	std::string code = "";

	while(pt->getParent() != 0)
	{
		it = pt;
		pt = pt->getParent();
		if(pt->getLeft()->getId() == it->getId())
			code = code + "0";
		else code = code + "1";
	}
	std::reverse(code.begin(), code.end());
	return code;
}

char Huffman::discover_node(Node * pt, VectorBits * characters)
{
	// Verify if is a leaf node and stopping retrieving his 'id' If is not, goes to the left or right depending on the fron bit of 'characters'
	if(pt->getLeft() == 0 && pt->getRight() == 0)
	{
		return pt->getCarac();
	} else if(characters->get_front() == 0)
	{
		characters->delete_front();
		discover_node(pt->getLeft(), characters);
	} else if(characters->get_front() == 1)
	{
		characters->delete_front();
		discover_node(pt->getRight(), characters);
	}
}

void Huffman::compress(const char * filePath)
{
	double l; // average length

	// Reading the regular file to find this initial 'frequencies'
	std::clog << "# Reading file..." << std::endl;
	char_counter = Files::readRegularFile(filePath, &frequencies);

	std::clog << "# Generating huffman codes..." << std::endl;
	// Fill the 'nodes' vector and hashmap 'huffmanAdp'
	int id = 0;
	for(std::map<char, int>::iterator it = frequencies.begin(); it != frequencies.end(); it++)
	{
		Node *newNode = new Node(id++, it->first, it->second, 0, 0, 0);
		nodes.push_back(newNode);
		huffmanAdp[it->first] = newNode;
	}

	// Write the huffman compressed file using the 'frequencies' to write the header and this to use the huffman adaptative
	std::clog << "# Saving file..." << std::endl;
	Files::writeHuffmanFile(filePath, this);

	l = (double) (code_counter) / (char_counter);
	std::clog << "# Average lenght: " << l << std::endl;
	std::clog << "# Entropy: " << entropy << std::endl;
}

void Huffman::extract(const char * filePath)
{
	// Reads the compressed file keeping the readed 'characters' and their 'frequencies'
	std::clog << "# Reading file..." << std::endl;
	Files::readHuffmanFile(filePath, &characters, &frequencies);

	// It will generate the leaf (characters) nodes for the Huffman tree 
	std::clog << "# Generating characters..." << std::endl;
	int id = 0;
	for(std::map<char, int>::iterator it=frequencies.begin(); it!=frequencies.end(); it++)
	{
		Node *newNode = new Node(id++, it->first, it->second, 0, 0, 0);
		nodes.push_back(newNode);
		huffmanAdp[it->first] = newNode;
		total_frequency += it->second;
	}

	// Write the descompressed file using the 'descompressed' characters
	std::clog << "# Saving file..." << std::endl;
	Files::writeRegularFile(filePath, this);
}

// Build the VectorBits refered to char 'c' in adaptative algorithm way
VectorBits * Huffman::buildAdaptative(char c)
{
	std::string code;

	// Fills the copyNodes vector with the nodes to be matched 
	copyNodes = nodes;

	double P = (double) (huffmanAdp[c]->getFrequency()) / current_size;
	entropy += (log2(1/P))/char_counter;
	current_size--;

	// Sort the nodes by rising frequency. (Using stable_sort() instead of sort())
	std::stable_sort(copyNodes.begin(), copyNodes.end(), compare_nodes);

	// Match the nodes building the huffman tree and generate the code to the passed character 'c'
	Node::resetCounter();
	build_tree();
	
	code = generate_code(huffmanAdp[c]);

	// After the code is generated, the frequency refered to this character needs to be reduced
	huffmanAdp[c]->reduceFrequency();
	
	saving_leafs(root);
	destroy_tree(root);
	std::vector<Node*>().swap(copyNodes);

	return new VectorBits(code);
}

char Huffman::readAdaptative(void)
{
	char c;
	copyNodes = nodes;

	// Gets the total frequency to knows until what bits are valid symbols
	std::stable_sort(copyNodes.begin(), copyNodes.end(), compare_nodes);
	Node::resetCounter();
	build_tree();

	//	Run the vector of bits until find a valid character. Add this to the output vector of characters and decreased the refered frequency 
	c = discover_node(root, &characters);
	huffmanAdp[c]->reduceFrequency();

	saving_leafs(root);
	destroy_tree(root);
	std::vector<Node*>().swap(copyNodes);

	return c;
}