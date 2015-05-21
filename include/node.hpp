#ifndef __NODE_H_INCLUDED__
#define __NODE_H_INCLUDED__

class Node {
private:
	static int counter;

	int id;
	char carac;
	int frequency;		// Max of 4.294.967.296 = 4.2 GB (2.1 GB)
	Node *left;
	Node *right;
	Node *parent;
public:
	Node(char carac, int frequency, Node * left, Node * right, Node * parent);
	Node(int id, char carac, int frequency, Node * left, Node * right, Node * parent);
	~Node(void);

	int getId(void);
	char getCarac(void);
	int getFrequency(void);
	Node* getLeft(void);
	Node* getRight(void);
	Node* getParent(void);

	void setParent(Node * parent);
	
	void reduceFrequency(void);
	static void resetCounter(void);
};

#endif