#pragma once
#include "Node.h"

template<typename type>
class DoubleLinkedNode :
	public Node<type>
{
public:
	DoubleLinkedNode();
	DoubleLinkedNode(type);
	DoubleLinkedNode(type, DoubleLinkedNode<type>*);
	DoubleLinkedNode(type, DoubleLinkedNode<type>*, DoubleLinkedNode<type>*);
	~DoubleLinkedNode();
	DoubleLinkedNode<type>* next();
	DoubleLinkedNode<type>* prev();
	void setNext(DoubleLinkedNode<type>*);
	void setPrev(DoubleLinkedNode<type>*);
	bool isSentinel();
	bool operator==(const DoubleLinkedNode<type>& o) const{
		if (sentinel || o.sentinel){
			if (!prevNode) return !o.prevNode;
			if (!nextNode) return !o.nextNode;
		}
		return data == o.data;
	}
	friend std::ostream& operator<< (std::ostream& out, DoubleLinkedNode& o){
		out << o.getData();
		return out;
	};
protected:
	DoubleLinkedNode<type>* nextNode;
	DoubleLinkedNode<type>* prevNode;
	bool sentinel;
};

template<typename type>
DoubleLinkedNode<type>::DoubleLinkedNode() : Node(std::numeric_limits<type>::max()){
	nextNode = nullptr;
	prevNode = nullptr;
	sentinel = true;
}

template<typename type>
DoubleLinkedNode<type>::DoubleLinkedNode(type t) : Node(t){
	nextNode = nullptr;
	sentinel = false;
}

template<typename type>
DoubleLinkedNode<type>::DoubleLinkedNode(type t, DoubleLinkedNode<type>* n) : Node(t){
	nextNode = n;
	prevNode = nullptr;
	sentinel = false;
}

template<typename type>
DoubleLinkedNode<type>::DoubleLinkedNode(type t, DoubleLinkedNode<type>* n, DoubleLinkedNode<type>* p) : Node(t){
	nextNode = n;
	prevNode = p;
	sentinel = false;
}

template<typename type>
DoubleLinkedNode<type>::~DoubleLinkedNode(){
	if (nextNode){
		nextNode->~DoubleLinkedNode();
		nextNode = nullptr;
	}
	if (prevNode) prevNode = nullptr;
}

template<typename type>
DoubleLinkedNode<type>* DoubleLinkedNode<type>::next(){
	return nextNode;
}

template<typename type>
DoubleLinkedNode<type>* DoubleLinkedNode<type>::prev(){
	return prevNode;
}

template<typename type>
void DoubleLinkedNode<type>::setNext(DoubleLinkedNode<type>* n){
	nextNode = n;
}

template<typename type>
void DoubleLinkedNode<type>::setPrev(DoubleLinkedNode<type>* n){
	prevNode = n;
}

template<typename type>
bool DoubleLinkedNode<type>::isSentinel(){
	return sentinel;
}
