#pragma once
#include "TreeNode.h"

enum Color{
	BLACK,
	RED,
	DOUBLE_BLACK,
	DOUBLE_RED
};

template <typename type>
class RedBlackTreeNode :
	public TreeNode<type>
{
public:
	RedBlackTreeNode();
	~RedBlackTreeNode();
	RedBlackTreeNode<type>* left();
	RedBlackTreeNode<type>* right();
	Color color();
	void setColor(Color);
	void flip();

protected:
	Color nodeColor;

};

template <typename type>
RedBlackTreeNode<type>::RedBlackTreeNode() : TreeNode(){
	nodeColor = RED;
}

template <typename type>
RedBlackTreeNode<type>::RedBlackTreeNode(type d) : TreeNode(d){
	nodeColor = RED;
}

template <typename type>
RedBlackTreeNode<type>::~RedBlackTreeNode(){
	nodeColor = BLACK;
}

template <typename type>
RedBlackTreeNode<type>* RedBlackTreeNode<type>::left(){
	return static_cast<RedBlackTreeNode<type>*>(leftChild);
}

template <typename type>
RedBlackTreeNode<type>* RedBlackTreeNode<type>::right(){
	return static_cast<RedBlackTreeNode<type>*>(rightChild);
}

template <typename type>
void RedBlackTreeNode<type>::setLeft(RedBlackTreeNode<type>* n){
	leftChild = n;
	modified = true;
}

template <typename type>
void RedBlackTreeNode<type>::setRight(RedBlackTreeNode<type>* n){
	rightChild = n;
	modified = true;
}

template <typename type>
Color RedBlackTreeNode<type>::color(){
	return nodeColor;
}

template <typename type>
void RedBlackTreeNode<type>::setColor(Color c){
	nodeColor = c;
}

template <typename type>
Color RedBlackTreeNode<type>::flip(){
	nodeColor = (nodeColor + 1) % 2;
}