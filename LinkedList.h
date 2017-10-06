#pragma once
#include "LinkedNode.h"

/*TODO:
//Figure out emplace
//Add operator= method
//Code remove_if and derivatives
//Add helper methods
//Make iterator a part of the class
//Setup tail sentinel?
//Fix copy/setHead/whatever function actually does that
*/

template<typename type>
class iterator{
public:
	iterator(LinkedNode<type>* n){
		node = n;
	}
	~iterator(){
		node = nullptr;
	}
	bool operator++(){ //pre-increment
		if (!node) return false;
		node = node->next();
		if (!node) return false;
		return true;
	}
	bool operator++(int){ //post-increment
		if (!node) return false;
		operator++();
		return true;
	}
	bool operator+= (std::size_t i){
		while (i-- > 0) if (!operator++()) return false;
		return true;
	}
	friend iterator<type> operator+ (iterator<type> lhs, const std::size_t& rhs){
		iterator<type> ret = iterator<type>(lhs.operator->());
		ret += rhs;
		return ret;
	}
	bool operator== (const iterator<type>& o) const{
		if (!o.operator->() || !node) return !o.operator->() && !node;
		return *(node) == *(o);
	}
	bool operator< (const iterator<type>& o) const{
		if (!o.operator->() || !node) return !o.operator->() && node;
		return *(node) < *(o);
	}
	bool operator> (const iterator<type>& o){ return o.operator<(*this); }
	bool operator<= (const iterator<type>& o){ return !(operator>(o)); }
	bool operator>= (const iterator<type>& o){ return !(operator<(o)); }
	LinkedNode<type>* operator->() const{
		return node;
	}
	LinkedNode<type>& operator*() const{
		return *node;
	}

protected:
	LinkedNode<type>* node;
};

template<typename type>
class LinkedList
{
public:
	//Constructors & Destructor
	LinkedList();
	LinkedList(type);
	LinkedList(LinkedNode<type>*);
	~LinkedList();

	//Iterator functions
	iterator<type> before_begin();
	iterator<type> begin();
	iterator<type> end();

	//Capacity functions
	int size();
	bool empty();

	//Element access
	LinkedNode<type>* head();
	LinkedNode<type>* tail();
	LinkedNode<type>* at(iterator<type>);
	LinkedNode<type>* at(std::size_t);

	//Modifiers
	void clear();
	iterator<type> insert(iterator<type>, LinkedNode<type>*);
	//iterator<type> emplace(iterator<type>, LinkedNode<type>*);
	LinkedNode<type>* remove(iterator<type>);
	iterator<type> erase(iterator<type>);
	void insert(LinkedNode<type>*, std::size_t);
	void insert(type, std::size_t);
	LinkedNode<type>* remove(std::size_t);
	void erase(std::size_t);
	void push_head(LinkedNode<type>*);
	void push_head(type);
	LinkedNode<type>* pop_head();
	void push_tail(LinkedNode<type>*);
	void push_tail(type);
	LinkedNode<type>* pop_tail();
	void copy(LinkedList<type>*);
	void unique();
	void merge(LinkedList<type>&);

	//List Operations
	void splice(iterator<type>, LinkedList<type>&);
	void splice(std::size_t, LinkedList<type>&);
	void reverse();
	void sort();
	void swap(LinkedList<type>&);
	void move();

	//Lookup
	int count(LinkedNode<type>*);
	LinkedNode<type>* find(type);

	//Operator Overloads
	bool operator+= (LinkedNode<type>* n){
		push_tail(n);
		return true;
	}
	friend std::ostream& operator<< (std::ostream& out, LinkedList& o){
		iterator<type> it = o.before_begin();
		while (++it){
			out << "|" << it->getData() << "|" << "->";
		}
		out << "|" << std::endl;
		return out;
	};
	void setHead(LinkedNode<type>*);
	LinkedNode<type>* prune(int);

protected:
	LinkedNode<type>* headNode;
	std::size_t curSize;
};

//Constructors & destructor
template<typename type>
LinkedList<type>::LinkedList(){
	headNode = new LinkedNode<type>();
	curSize = 0;
}

template<typename type>
LinkedList<type>::LinkedList(type d){
	LinkedNode<type>* n = new LinkedNode<type>(d);
	headNode = new LinkedNode<type>();
	headNode->setNext(n);
	curSize = 1;
}

template<typename type>
LinkedList<type>::LinkedList(LinkedNode<type>* n){
	headNode = new LinkedNode<type>();
	headNode->setNext(n);
	curSize = 1;
}

template<typename type>
LinkedList<type>::~LinkedList(){
	if (headNode){
		headNode->~LinkedNode<type>();
		headNode = nullptr;
	}
}

//Iterator functions

//Creates an iterator to the dummy head node
template<typename type>
iterator<type> LinkedList<type>::before_begin(){
	return iterator<type>(headNode);
}

//Creates an iterator to the first data node
template<typename type>
iterator<type> LinkedList<type>::begin(){
	iterator<type> it = iterator<type>(headNode);
	it++;
	return it;
}

//Creates an iterator to a nullptr, which represents the tail
template<typename type>
iterator<type> LinkedList<type>::end(){
	return iterator<type>(nullptr);
}

//Capacity functions

//Returns the size of the list
template<typename type>
int LinkedList<type>::size(){
	return curSize;
}

//Returns true if list is empty
template<typename type>
bool LinkedList<type>::empty(){
	return curSize == 0;
}

//Element access
template<typename type>
LinkedNode<type>* LinkedList<type>::head(){
	return headNode->next();
}

//Returns a pointer to the tail data node
template<typename type>
LinkedNode<type>* LinkedList<type>::tail(){
	return at(curSize - 1);
}

//Returns a pointer to the data node at the provided position
//it = iterator to desired data node
template<typename type>
LinkedNode<type>* LinkedList<type>::at(iterator<type> it){
	if (it == end()) throw std::out_of_range("position larger than list size");
	return it->next();
}

//Returns a pointer to the data node at the provided position
//pos = index of the desired data node
template<typename type>
LinkedNode<type>* LinkedList<type>::at(std::size_t pos){
	iterator<type> it = before_begin();
	it += pos;
	return at(it);
}

//Modifiers

//Inserts the given node after the iterator position.
//it	= iterator to desired insert position
//node	= node to be inserted
//returns incremented iterator, now referencing the inserted node
template<typename type>
iterator<type> LinkedList<type>::insert(iterator<type> it, LinkedNode<type>* node){
	if (it == end()) throw std::out_of_range("position larger than list size");
	node->setNext(it->next());
	it->setNext(node);
	it++;
	curSize++;
	return it;
}

//Removes the node after the iterator position.
//it	= iterator to the desired remove position
//Returns the removed node, iterator is unchanged
template<typename type>
LinkedNode<type>* LinkedList<type>::remove(iterator<type> it){
	if (it == end() || (it + 1) == end()) throw std::out_of_range("position larger than list size");
	LinkedNode<type>* rem = it->next();
	it->setNext(rem->next());
	rem->setNext(nullptr);
	curSize--;
	return rem;
}

//Erases the node after the iterator position.
//it	= iterator to the desired erase position
//Returns unchanged iterator, erased node is deconstructed.
template<typename type>
iterator<type> LinkedList<type>::erase(iterator<type> it){
	if (it == end() || (it + 1) == end()) throw std::out_of_range("position larger than list size");
	LinkedNode<type>* del = it->next();
	it->setNext(del->next());
	del->setNext(nullptr); //TODO revise?
	del->~LinkedNode();
	curSize--;
	return;
}

//Helper method for insert. Inserts node at indicated position.
//n		= node to be inserted
//pos	= position to be inserted at
template<typename type>
void LinkedList<type>::insert(LinkedNode<type>* n, std::size_t pos){
	iterator<type> it = before_begin();
	it += pos;
	insert(it, n);
}

//Helper method for insert. Creates a new node from the provided data and inserts it at the indicated position.
//d		= data to turn into the node to be inserted
//pos	= position to be inserted at
template<typename type>
void LinkedList<type>::insert(type d, std::size_t pos){
	LinkedNode<type>* ins = new LinkedNode<type>(d);
	insert(ins, pos);
}

//Helper method for remove. Removes the node at the indicated position.
//pos	= position of node to be removed
//Returns the removed node
template<typename type>
LinkedNode<type>* LinkedList<type>::remove(std::size_t pos){
	iterator<type> it = before_begin();
	it += pos;
	return remove(it);
}

//Helper method for erase. Erases the node at the indicated position. Erased node is deconstructed.
//pos	= position of node to be removed
template<typename type>
void LinkedList<type>::erase(std::size_t pos){
	iterator<type> it = before_begin();
	it += pos;
	return remove(it);
}

//Inserts the provided node at the front of the list, making it the head data node.
//n		= node to be inserted
template<typename type>
void LinkedList<type>::push_head(LinkedNode<type>* n){
	insert(n, 0);
}

//Helper method for push_head. Creates a new node from the provided data and inserts it at the front of the list, making it the new head data node.
//d		= data to turn into the node to be inserted
template<typename type>
void LinkedList<type>::push_head(type d){
	insert(d, 0);
}

//Removes the node at the front of the list, or the head data node.
//Returns the removed node
template<typename type>
LinkedNode<type>* LinkedList<type>::pop_head(){
	return remove(0);
}

//Inserts the provided node at the end of the list, making it the tail data node.
//n		= node to be inserted
template<typename type>
void LinkedList<type>::push_tail(LinkedNode<type>* n){
	insert(n, curSize);
}

//Helper method for push_tail. Creates a new node from the provided data and inserts it at the end of the list, making it the new tail data node.
//d		= data to turn into the node to be inserted
template<typename type>
void LinkedList<type>::push_tail(type d){
	insert(d, curSize);
}

//Removes the node at the end of the list, or the tail data node.
//Returns the removed node
template<typename type>
LinkedNode<type>* LinkedList<type>::pop_tail(){
	return remove(curSize - 1);
}

template<typename type>
void LinkedList<type>::copy(LinkedList<type>* o){
	if (headNode->next()) headNode->next()->~LinkedNode(); //TODO Reconsider this
	iterator<type> it = o->before_begin();
	headNode->setNext(it->next());
}

//Removes any duplicate nodes from a sorted list.
template<typename type>
void LinkedList<type>::unique(){
	iterator<type> it = before_begin();
	while (++it){
		if ((it + 1) == it) remove(it);
	}
}

//Merges the contents of the provided list
template<typename type>
void LinkedList<type>::merge(LinkedList<type>& o){
	iterator<type> it = before_begin();
	iterator<type> o_it = o.before_begin();
	while (o_it->next()){
		if ((o_it + 1) < (it + 1)) insert(it, o.remove(o_it));
		else it++;
	}
}

//List Operations

//Splices the list at the iterator position, placing nodes from after the splice at the end of the provided list.
//it	= iterator to splice location
//o		= list to store the spliced nodes
template<typename type>
void LinkedList<type>::splice(iterator<type> it, LinkedList<type>& o){ //TODO improve
	while (it->next()) o.push_tail(remove(it));
}

//Helper function for splice. Splices the list at the provided position, placing nodes from after the splice at the end of the provided list.
//pos	= index position of the splice location
//o		= list to store the spliced nodes
template<typename type>
void LinkedList<type>::splice(std::size_t pos, LinkedList<type>& o){
	iterator<type> it = before_begin();
	it += pos;
	splice(it, o);
}

//Reversed the contents of the list.
template<typename type>
void LinkedList<type>::reverse(){
	if (empty()) return;
	LinkedNode<type>* newHead = pop_tail();
	LinkedNode<type>* cur = newHead;
	while (!empty()){
		cur->setNext(pop_tail());
		cur = cur->next();
	}
	headNode->setNext(newHead);
}

//Sorts the list in ascending order through a merge sort
template<typename type>
void LinkedList<type>::sort(){
	if (curSize < 2) return;
	LinkedList<type> o = LinkedList<type>();
	splice(curSize / 2, o);
	sort();
	o.sort();
	merge(o);
}

//Swaps the contents of the list and the provided list
//o		= list to swap contents with
template<typename type>
void LinkedList<type>::swap(LinkedList<type>& o){
	iterator<type> it = before_begin();
	iterator<type> o_it = o.before_begin();
	headNode->setNext(o_it->next());
	o.setHead(it->next())
}

template<typename type>
void LinkedList<type>::setHead(LinkedNode<type>* n){ //TODO Remodel operator=
	if (headNode) headNode->~LinkedNode(); //Should I do this? Yes, except it breaks swap().
	headNode = n;
	curSize = 1;
	LinkedNode<type> temp = headNode;
	while (temp->next()){
		temp = temp->next();
		curSize++;
	}
}

template<typename type>
LinkedNode<type>* LinkedList<type>::prune(int pos){
	if (pos > curSize) return nullptr; //Throw error?
	LinkedNode<type>* ret = headNode;
	while (pos-- > 1){
		ret = ret->next();
	}
	LinkedNode<type> temp = ret;
	ret = ret->next();
	temp->setNext(nullptr);
	curSize = pos;
	return ret;
}

