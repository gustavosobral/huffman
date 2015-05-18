#ifndef __NODE_H_INCLUDED__
#define __NODE_H_INCLUDED__

class Node {
private:
	char id;
	int frequency;		// Max of 4.294.967.296 = 4.2 GB (2.1 GB)
	Node *left;
	Node *right;
public:
	Node(int frequency);
	Node(char id, int frequency);
	Node(char id, int frequency, Node *left, Node *right);
	~Node(void);

	char getId(void);
	int getFrequency(void);
	Node* getLeft(void);
	Node* getRight(void);

	void reduceFrequency(void);
};

#endif