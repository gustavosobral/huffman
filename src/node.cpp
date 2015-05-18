#include "../include/node.hpp"

Node::Node(int frequency)
{
	this->frequency = frequency;
}

Node::Node(char id, int frequency)
{
	this->id = id;
	this->frequency = frequency;
}

Node::Node(char id, int frequency, Node *left, Node *right)
{
	this->id = id;
	this->frequency = frequency;
	this->left = left;
	this->right = right;
}

Node::~Node(void){}

char Node::getId(void)
{
	return id;
}

int Node::getFrequency(void)
{
	return frequency;
}

Node* Node::getLeft(void)
{
	return left;
}

Node* Node::getRight(void)
{
	return right;
}

void Node::reduceFrequency(void)
{
	frequency = frequency - 1;
}