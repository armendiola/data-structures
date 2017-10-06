#pragma once
#include "Node.h"

template<typename type>
class LinkedNode :
	public Node<type>
{
public:
	LinkedNode();
	LinkedNode(type);
	LinkedNode(type, LinkedNode<type>*);
	~LinkedNode();
	LinkedNode<type>* next();
	void setNext(LinkedNode<type>*);
	bool isSentinel();

protected:
	LinkedNode<type>* nextNode;
	type data;
	bool sentinel;
};

template<typename type>
LinkedNode<type>::LinkedNode(){
	nextNode = nullptr;
	sentinel = true;
}

template<typename type>
LinkedNode<type>::LinkedNode(type t) : Node(t){
	nextNode = nullptr;
	sentinel = false;
}

template<typename type>
LinkedNode<type>::LinkedNode(type t, LinkedNode<type>* n) : Node(t){
	nextNode = n;
	sentinel = false;
}

template<typename type>
LinkedNode<type>::~LinkedNode(){
	if (nextNode){
		nextNode->~LinkedNode();
		//delete nextNode;
		nextNode = nullptr;
	}
}

template<typename type>
LinkedNode<type>* LinkedNode<type>::next(){
	return nextNode;
}

template<typename type>
void LinkedNode<type>::setNext(LinkedNode<type>* n){
	nextNode = n;
}

template<typename type>
bool LinkedNode<type>::isSentinel(){
	return sentinel;
}