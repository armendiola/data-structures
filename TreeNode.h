#pragma once
#include "Node.h"

template <typename type>
class TreeNode :
	public Node<type>
{
public:
	TreeNode();
	TreeNode(type);
	~TreeNode();
	virtual TreeNode<type>* left();
	virtual TreeNode<type>* right();
	virtual void setLeft(TreeNode<type>*);
	virtual void setRight(TreeNode<type>*);
	friend std::ostream& operator<< (std::ostream& out, TreeNode& o){
		out << "|" << o.getData() << "|";
		return out;
	};

protected:
	TreeNode<type>* leftChild;
	TreeNode<type>* rightChild;
};

template <typename type>
TreeNode<type>::TreeNode() : Node(std::numeric_limits<type>::min()){
	leftChild = nullptr;
	rightChild = nullptr;
}

template <typename type>
TreeNode<type>::TreeNode(type d) : Node(d){
	leftChild = nullptr;
	rightChild = nullptr;
}

template <typename type>
TreeNode<type>::~TreeNode(){
	if (leftChild){
		leftChild->~TreeNode();
		leftChild = nullptr;
	}
	if (rightChild){
		rightChild->~TreeNode();
		rightChild = nullptr;
	}
}

template <typename type>
TreeNode<type>* TreeNode<type>::left(){
	return leftChild;
}

template <typename type>
TreeNode<type>* TreeNode<type>::right(){
	return rightChild;
}

template <typename type>
void TreeNode<type>::setLeft(TreeNode<type>* n){
	leftChild = n;
}

template <typename type>
void TreeNode<type>::setRight(TreeNode<type>* n){
	rightChild = n;
}