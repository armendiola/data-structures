#pragma once
#include "TreeNode.h"

template <typename type>
class AVLTreeNode :
	public Node<type>
{
public:
	AVLTreeNode();
	AVLTreeNode(type);
	~AVLTreeNode();
	AVLTreeNode<type>* left();
	AVLTreeNode<type>* right();
	int balance();
	void setLeft(AVLTreeNode<type>*);
	void setRight(AVLTreeNode<type>*);
	friend std::ostream& operator<< (std::ostream& out, AVLTreeNode& o){
		out << "|" << o.getData() << "|";
		return out;
	};

	static std::size_t height(AVLTreeNode<type>*);

protected:
	AVLTreeNode<type>* leftChild;
	AVLTreeNode<type>* rightChild;
	int subBalance;
};

template <typename type>
AVLTreeNode<type>::AVLTreeNode() : Node(std::numeric_limits<type>::min()){
	leftChild = nullptr;
	rightChild = nullptr;
}

template <typename type>
AVLTreeNode<type>::AVLTreeNode(type d) : Node(d){
	leftChild = nullptr;
	rightChild = nullptr;
}

template <typename type>
AVLTreeNode<type>::~AVLTreeNode(){
	if (leftChild){
		leftChild->~AVLTreeNode();
		leftChild = nullptr;
	}
	if (rightChild){
		rightChild->~AVLTreeNode();
		rightChild = nullptr;
	}
}

template <typename type>
AVLTreeNode<type>* AVLTreeNode<type>::left(){
	return leftChild;
}

template <typename type>
AVLTreeNode<type>* AVLTreeNode<type>::right(){
	return rightChild;
}

template <typename type>
int AVLTreeNode<type>::balance(){
	return subBalance;
}

template <typename type>
void AVLTreeNode<type>::setLeft(AVLTreeNode<type>* n){
	leftChild = n;
	subBalance = AVLTreeNode::height(rightChild) - AVLTreeNode::height(leftChild);
}

template <typename type>
void AVLTreeNode<type>::setRight(AVLTreeNode<type>* n){
	rightChild = n;
	subBalance = AVLTreeNode::height(rightChild) - AVLTreeNode::height(leftChild);
}

template <typename type>
std::size_t AVLTreeNode<type>::height(AVLTreeNode<type>* n){
	if (!n) return 0;
	else if (n->balance() > 0) return AVLTreeNode::height(n->right()) + 1;
	else return AVLTreeNode::height(n->left()) + 1;
}