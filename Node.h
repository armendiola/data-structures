#pragma once
#include <cstddef>
#include <stdexcept>
#include <limits>
#include <iostream>
template<class type>
class Node
{
public:
	Node();
	Node(type);
	~Node();
	type getData();
	void setData(type);
	bool operator< (const Node& o) const;
	bool operator> (const Node& o) const;
	bool operator== (const Node& o) const;
	friend std::ostream& operator<< (std::ostream& out, Node& o){
		out << o.getData();
		return out;
	};


protected:
	type data;

};

template<class type>
Node<type>::Node(){
}

template<class type>
Node<type>::Node(type d){
	data = d;
}

template<class type>
Node<type>::~Node(){
}

template<class type>
type Node<type>::getData(){
	return data;
}

template<class type>
void Node<type>::setData(type d){
	data = d;
}
template<class type>
bool Node<type>::operator< (const Node& o) const{
	return data < o.data;
}
template<class type>
bool Node<type>::operator>(const Node& o) const{
	return data > o.data;
}
template<class type>
bool Node<type>::operator== (const Node& o) const{
	return data == o.data;
}