#include "../include/node.hpp"

int Node::counter = 256;

Node::Node(char carac, int frequency, Node * left, Node * right, Node * parent)
{
	this->id = counter++;
	this->carac = carac;
	this->frequency = frequency;
	this->left = left;
	this->right = right;
	this->parent = parent;
}

Node::Node(int id, char carac, int frequency, Node * left, Node * right, Node * parent)
{
	this->id = id;
	this->carac = carac;
	this->frequency = frequency;
	this->left = left;
	this->right = right;
	this->parent = parent;
}

Node::~Node(void){}

int Node::getId(void)
{
	return id;
}

char Node::getCarac(void)
{
	return carac;
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

void Node::setLeft(Node * n)
{
	this->left = n;
}

void Node::setRight(Node * n)
{
	this->right = n;
}

Node* Node::getParent(void)
{
	return parent;
}

void Node::setParent(Node * parent)
{
	this->parent = parent;
}

void Node::reduceFrequency(void)
{
	frequency = frequency - 1;
}

void Node::resetCounter(void)
{
	counter = 256;
}