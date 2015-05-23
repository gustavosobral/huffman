#ifndef __NODE_H_INCLUDED__
#define __NODE_H_INCLUDED__

/**
 * \file node.hpp
 * \authors Gustavo Sobral, Francielly Cardoso
 * \date May 2015
 */

/** \brief Node abstraction for Huffman tree structure.
 * 
 * Hold the abstraction for the representation of one Node
 * on the Huffman tree algorithm. Its composed by unique integer id,
 * caracter if the node is a leaf node, frequency accumulated
 * and references for the left and right children nodes and for
 * the parent node.
 */
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

	/** \brief The class constructor.
	 *
	 * Initializes the carac and frequency with the passed values
	 * and sets the pointers left, right and parent with
	 * the passed pointers. In that way, the id is initialized
	 * using the static variable counter, which starts with 256.
	 */
	Node(char carac, int frequency, Node * left, Node * right, Node * parent);
	
	/** \brief The class constructor.
	 *
	 * Initializes the id, carac and frequency with the passed values
	 * and sets the pointers left, right and parent with
	 * the passed pointers.
	 */
	Node(int id, char carac, int frequency, Node * left, Node * right, Node * parent);

	/** \brief The class destructor.
	 */
	~Node(void);

	/** \brief Gets the node id value.
	 * \return The id value.
	 */
	int getId(void);
	
	/** \brief Gets the node carac value.
	 * \return The carac value.
	 */
	char getCarac(void);

	/** \brief Gets the node frequency value.
	 * \return The frequency value.
	 */
	int getFrequency(void);

	/** \brief Gets the pointer for the left children node.
	 * \return The pointer to left.
	 */
	Node* getLeft(void);

	/** \brief Gets the pointer for the right children node.
	 * \return The pointer to right.
	 */
	Node* getRight(void);
	
	/** \brief Gets the pointer for the parent node.
	 * \return The pointer to parent.
	 */
	Node* getParent(void);

	/** \brief Sets the left node.
	 * \param left Pointer to left node.
	 */
	void setLeft(Node * left);

	/** \brief Sets the right node.
	 * \param right Pointer to right node.
	 */
	void setRight(Node * right);	

	/** \brief Sets the parent node.
	 * \param parent Pointer to the parent.
	 */
	void setParent(Node * parent);
	
	/** \brief Reduce the node frequency by one.
	 */
	void reduceFrequency(void);

	/** \brief Reset the id counter to 256.
	 */
	static void resetCounter(void);
};

#endif