#pragma once
#include "DoubleLinkedNode.h"

/*TODO:
//Figure out reverse iterators
//Figure out emplace
//Add operator= method
//Code remove_if and derivatives
//Add helper methods
//Make iterator a part of the class
//Fix copy/setHead/whatever function actually does that
*/

template<typename type>
class iterator{
public:
	iterator(){
	}
	iterator(DoubleLinkedNode<type>* n){
		node = n;
	}
	~iterator(){
		node = nullptr;
	}
	bool operator++(){ //pre-increment
		if (!(node->next())) return false;
		node = node->next();
		if (!(node->next())) return false;
		return true;
	}
	bool operator--(){ //pre-decrement
		if (!(node->prev())) return false;
		node = node->prev();
		if (!(node->prev())) return false;
		return true;
	}
	bool operator++(int){ //post-increment
		if (!(node->next())) return false;
		operator++();
		return true;
	}
	bool operator--(int){ //post-decrement
		if (!(node->prev())) return false;
		operator--();
		return true;
	}
	bool operator+= (std::size_t i){
		while (i-- > 0) if (!operator++()) return false;
		return true;
	}
	bool operator-= (std::size_t i){
		while (i-- > 0) if (!operator--()) return false;
		return true;
	}
	friend iterator<type> operator+ (iterator<type> lhs, const std::size_t& rhs){
		iterator<type> ret = iterator<type>(lhs.operator->());
		ret += rhs;
		return ret;
	}
	friend iterator<type> operator- (iterator<type> lhs, const std::size_t& rhs){
		iterator<type> ret = iterator<type>(lhs.operator->());
		ret -= rhs;
		return ret;
	}
	bool operator== (const iterator<type>& o) const{
		if (!o.operator->() || !node) return !o.operator->() && !node;
		return *(node) == *(o);
	}
	bool operator!= (const iterator<type>& o) const{
		return !(operator==(o));
	}
	bool operator< (const iterator<type>& o) const{
		if (!o.operator->() || !node) return !o.operator->() && node;
		return *(node) < *(o);
	}
	bool operator> (const iterator<type>& o){ return o.operator<(*this); }
	bool operator<= (const iterator<type>& o){ return !(operator>(o)); }
	bool operator>= (const iterator<type>& o){ return !(operator<(o)); }
	DoubleLinkedNode<type>* operator->() const{
		return node;
	}
	DoubleLinkedNode<type>& operator*() const{
		return *node;
	}

protected:
	DoubleLinkedNode<type>* node;
};

template<class type>
class DoubleLinkedList
{
public:
	//Constructors & Destructor
	DoubleLinkedList();
	DoubleLinkedList(type);
	DoubleLinkedList(DoubleLinkedNode<type>*);
	~DoubleLinkedList();

	//Iterator functions
	iterator<type> before_begin();
	iterator<type> begin();
	iterator<type> end();
	iterator<type> rbefore_begin();
	iterator<type> rbegin();
	iterator<type> rend();

	//Capacity functions
	int size();
	bool empty();

	//Element Access
	DoubleLinkedNode<type>* head();
	DoubleLinkedNode<type>* tail();
	DoubleLinkedNode<type>* at(iterator<type>);
	DoubleLinkedNode<type>* at(std::size_t);

	//Modifiers
	void clear();
	iterator<type> insert(iterator<type>, DoubleLinkedNode<type>*);
	//iterator<type> emplace(iterator<type>, DoubleLinkedNode<type>*);
	DoubleLinkedNode<type>* remove(iterator<type>);
	iterator<type> erase(iterator<type>);
	void insert(DoubleLinkedNode<type>*, std::size_t);
	void insert(type, std::size_t);
	DoubleLinkedNode<type>* remove(std::size_t);
	void erase(std::size_t);
	void push_head(DoubleLinkedNode<type>*);
	void push_head(type);
	DoubleLinkedNode<type>* pop_head();
	void push_tail(DoubleLinkedNode<type>*);
	void push_tail(type);
	DoubleLinkedNode<type>* pop_tail();
	void copy(DoubleLinkedList<type>*);
	void unique();
	void merge(DoubleLinkedList<type>&);

	//List Operations
	void splice(iterator<type>, DoubleLinkedList<type>&);
	void splice(std::size_t, DoubleLinkedList<type>&);
	void reverse();
	void sort();
	void swap(DoubleLinkedList<type>&);
	void move();

	//Lookup
	int count(DoubleLinkedNode<type>*);
	DoubleLinkedNode<type>* find(type);

	//Operator Overloads
	bool operator+= (DoubleLinkedNode<type>* n){
		push_tail(n);
		return true;
	}
	friend std::ostream& operator<< (std::ostream& out, DoubleLinkedList& o){
		iterator<type> it = o.before_begin();
		out << "|<->";
		while (++it){
			out << "|" << it->getData() << "|" << "<->";
		}
		out << "|" << std::endl;
		return out;
	};

	void setHead(DoubleLinkedNode<type>*);
	void add(DoubleLinkedNode<type>*);
	bool insert(DoubleLinkedNode<type>*, int);
	DoubleLinkedNode<type>* get(int);
	DoubleLinkedNode<type>* getFirst();
	DoubleLinkedNode<type>* getLast();
	DoubleLinkedNode<type>* remove(int);
	DoubleLinkedNode<type>* removeFirst();
	DoubleLinkedNode<type>* removeLast();
	DoubleLinkedNode<type>* prune(int);

protected:
	DoubleLinkedNode<type>* headNode;
	DoubleLinkedNode<type>* tailNode;
	std::size_t curSize;
};

//Constructors & destructor
template<typename type>
DoubleLinkedList<type>::DoubleLinkedList(){
	headNode = new DoubleLinkedNode<type>();
	tailNode = new DoubleLinkedNode<type>();
	headNode->setNext(tailNode);
	tailNode->setPrev(headNode);
	curSize = 0;
}

template<typename type>
DoubleLinkedList<type>::DoubleLinkedList(type d){
	DoubleLinkedNode<type>* n = new DoubleLinkedNode<type>(d);
	headNode = new DoubleLinkedNode<type>();
	headNode->setNext(n);
	n->setPrev(headNode);
	tailNode = new DoubleLinkedNode<type>();
	n->setNext(tailNode);
	tailNode->setPrev(n);
	curSize = 1;
}

template<typename type>
DoubleLinkedList<type>::DoubleLinkedList(DoubleLinkedNode<type>* n){
	headNode = new DoubleLinkedNode<type>();
	headNode->setNext(n);
	n->setPrev(headNode);
	tailNode = new DoubleLinkedNode<type>();
	n->setNext(tailNode);
	tailNode->setPrev(n);
	curSize = 1;
}

template<typename type>
DoubleLinkedList<type>::~DoubleLinkedList(){
	if (headNode){
		headNode->~DoubleLinkedNode<type>();
		headNode = nullptr;
	}
}

//Iterator functions

//Creates an iterator to the dummy head node
template<typename type>
iterator<type> DoubleLinkedList<type>::before_begin(){
	return iterator<type>(headNode);
}

//Creates an iterator to the first data node
template<typename type>
iterator<type> DoubleLinkedList<type>::begin(){
	iterator<type> it = iterator<type>(headNode);
	it++;
	return it;
}

//Creates an iterator to the dummy tail node
template<typename type>
iterator<type> DoubleLinkedList<type>::end(){
	return iterator<type>(tailNode);
}

//Creates an iterator to the dummy tail node
template<typename type>
iterator<type> DoubleLinkedList<type>::rbefore_begin(){
	return iterator<type>(tailNode);
}

//Creates an iterator to the last data node
template<typename type>
iterator<type> DoubleLinkedList<type>::rbegin(){
	iterator<type> it = iterator<type>(tailNode);
	it--;
	return it;
}

//Creates an iterator to the dummy head node
template<typename type>
iterator<type> DoubleLinkedList<type>::rend(){
	return iterator<type>(headNode);
}

//Capacity functions

//Returns the size of the list
template<typename type>
int DoubleLinkedList<type>::size(){
	return curSize;
}

//Returns true if list is empty
template<typename type>
bool DoubleLinkedList<type>::empty(){
	return curSize == 0;
}

//Element access
template<typename type>
DoubleLinkedNode<type>* DoubleLinkedList<type>::head(){
	return headNode->next();
}

//Returns a pointer to the tail data node
template<typename type>
DoubleLinkedNode<type>* DoubleLinkedList<type>::tail(){
	return tailNode->prev();
}

//Returns a pointer to the data node at the provided position
//it = iterator to desired data node
template<typename type>
DoubleLinkedNode<type>* DoubleLinkedList<type>::at(iterator<type> it){
	if (it == end()) throw std::out_of_range("position larger than list size");
	return it->next();
}

//Returns a pointer to the data node at the provided position
//pos = index of the desired data node
template<typename type>
DoubleLinkedNode<type>* DoubleLinkedList<type>::at(std::size_t pos){
	iiterator<type> it;
	if (pos > (curSize / 2)) {
		it = rbegin();
		it -= (curSize - pos);
	}
	else {
		it = before_begin();
		it += pos;
	}
	return at(it);
}

//Modifiers

//Inserts the given node after the iterator position.
//it	= iterator to desired insert position
//node	= node to be inserted
//returns incremented iterator, now referencing the inserted node
template<typename type>
iterator<type> DoubleLinkedList<type>::insert(iterator<type> it, DoubleLinkedNode<type>* n){
	if (it == end()) throw std::out_of_range("position larger than list size"); //FUUUUCK
	n->setNext(it->next());
	n->setPrev(it.operator->());
	n->prev()->setNext(n);
	n->next()->setPrev(n);
	it++;
	curSize++;
	return it;
}

//Removes the node after the iterator position.
//it	= iterator to the desired remove position
//Returns the removed node, iterator is unchanged
template<typename type>
DoubleLinkedNode<type>* DoubleLinkedList<type>::remove(iterator<type> it){
	if (it == end() || (it + 1) == end()) throw std::out_of_range("position larger than list size");
	DoubleLinkedNode<type>* rem = it->next();
	it->setNext(rem->next());
	it->next()->setPrev(it.operator->());
	rem->setNext(nullptr);
	rem->setPrev(nullptr);
	curSize--;
	return rem;
}

//Erases the node after the iterator position.
//it	= iterator to the desired erase position
//Returns unchanged iterator, erased node is deconstructed.
template<typename type>
iterator<type> DoubleLinkedList<type>::erase(iterator<type> it){
	if (it == end() || (it + 1) == end()) throw std::out_of_range("position larger than list size");
	DoubleLinkedNode<type>* era = it->next();
	it->setNext(era->next());
	it->next()->setPrev(it.operator->());
	era->setNext(nullptr);
	era->setPrev(nullptr);
	era->~DoubleLinkedNode();
	curSize--;
	return;
}

//Helper method for insert. Inserts node at indicated position.
//n		= node to be inserted
//pos	= position to be inserted at
template<typename type>
void DoubleLinkedList<type>::insert(DoubleLinkedNode<type>* n, std::size_t pos){
	iterator<type> it;
	if (pos > (curSize / 2)) {
		it = rbegin();
		it -= (curSize - pos);
	}
	else {
		it = before_begin();
		it += pos;
	}
	insert(it, n);
}

//Helper method for insert. Creates a new node from the provided data and inserts it at the indicated position.
//d		= data to turn into the node to be inserted
//pos	= position to be inserted at
template<typename type>
void DoubleLinkedList<type>::insert(type d, std::size_t pos){
	DoubleLinkedNode<type>* ins = new DoubleLinkedNode<type>(d);
	insert(ins, pos);
}

//Helper method for remove. Removes the node at the indicated position.
//pos	= position of node to be removed
//Returns the removed node
template<typename type>
DoubleLinkedNode<type>* DoubleLinkedList<type>::remove(std::size_t pos){
	iterator<type> it;
	if (pos > (curSize / 2)) {
		it = rbegin();
		it -= (curSize - pos);
	}
	else {
		it = before_begin();
		it += pos;
	}
	return remove(it);
}

//Helper method for erase. Erases the node at the indicated position. Erased node is deconstructed.
//pos	= position of node to be removed
template<typename type>
void DoubleLinkedList<type>::erase(std::size_t pos){
	iterator<type> it;
	if (pos > (curSize / 2)) {
		it = rbegin();
		it -= (curSize - pos);
	}
	else {
		it = before_begin();
		it += pos;
	}
	return remove(it);
}

//Inserts the provided node at the front of the list, making it the head data node.
//n		= node to be inserted
template<typename type>
void DoubleLinkedList<type>::push_head(DoubleLinkedNode<type>* n){
	insert(n, 0);
}

//Helper method for push_head. Creates a new node from the provided data and inserts it at the front of the list, making it the new head data node.
//d		= data to turn into the node to be inserted
template<typename type>
void DoubleLinkedList<type>::push_head(type d){
	insert(d, 0);
}

//Removes the node at the front of the list, or the head data node.
//Returns the removed node
template<typename type>
DoubleLinkedNode<type>* DoubleLinkedList<type>::pop_head(){
	return remove(0);
}

//Inserts the provided node at the end of the list, making it the tail data node.
//n		= node to be inserted
template<typename type>
void DoubleLinkedList<type>::push_tail(DoubleLinkedNode<type>* n){
	insert(n, curSize);
}

//Helper method for push_tail. Creates a new node from the provided data and inserts it at the end of the list, making it the new tail data node.
//d		= data to turn into the node to be inserted
template<typename type>
void DoubleLinkedList<type>::push_tail(type d){
	insert(d, curSize);
}

//Removes the node at the end of the list, or the tail data node.
//Returns the removed node
template<typename type>
DoubleLinkedNode<type>* DoubleLinkedList<type>::pop_tail(){
	return remove(curSize - 1);
}

template<typename type>
void DoubleLinkedList<type>::copy(DoubleLinkedList<type>* o){
	if (headNode->next()) headNode->next()->~LinkedNode(); //TODO fix this
	iterator<type> it = o->before_begin();
	headNode->setNext(it->next());
}

//Removes any duplicate nodes from a sorted list.
template<typename type>
void DoubleLinkedList<type>::unique(){
	iterator<type> it = before_begin();
	while (++it){
		if ((it + 1) == it) remove(it);
	}
}

//Merges the contents of the provided list
template<typename type>
void DoubleLinkedList<type>::merge(DoubleLinkedList<type>& o){
	iterator<type> it = before_begin();
	iterator<type> o_it = o.before_begin();
	while ((o_it + 1) != o.end()){
		if ((o_it + 1) < (it + 1)) insert(it, o.remove(o_it));
		else it++;
	}
}

//List Operations

//Splices the list at the iterator position, placing nodes from after the splice at the end of the provided list.
//it	= iterator to splice location
//o		= list to store the spliced nodes
template<typename type>
void DoubleLinkedList<type>::splice(iterator<type> it, DoubleLinkedList<type>& o){ //TODO improve
	while ((it + 1) != end()) o.push_tail(remove(it));
}

//Helper function for splice. Splices the list at the provided position, placing nodes from after the splice at the end of the provided list.
//pos	= index position of the splice location
//o		= list to store the spliced nodes
template<typename type>
void DoubleLinkedList<type>::splice(std::size_t pos, DoubleLinkedList<type>& o){
	iterator<type> it;
	if (pos > (curSize / 2)) {
		it = rbegin();
		it -= (curSize - pos);
	}
	else {
		it = before_begin();
		it += pos;
	}
	splice(it, o);
}

//Reversed the contents of the list.
template<typename type>
void DoubleLinkedList<type>::reverse(){
	if (empty()) return;
	DoubleLinkedNode<type>* newHead = pop_tail(); //TODO refactor with operator= function
	DoubleLinkedNode<type>* cur = newHead;
	while (!empty()){
		cur->setNext(pop_tail());
		cur = cur->next();
	}
	cur->setNext(headNode->next());
	headNode->next()->setPrev(cur);
	headNode->setNext(newHead);
	headNode->next()->setPrev(headNode);
}

//Sorts the list in ascending order through a merge sort
template<typename type>
void DoubleLinkedList<type>::sort(){
	if (curSize < 2) return;
	DoubleLinkedList<type> o = DoubleLinkedList<type>();
	splice(curSize / 2, o);
	sort();
	o.sort();
	merge(o);
}

//Swaps the contents of the list and the provided list
//o		= list to swap contents with
template<typename type>
void DoubleLinkedList<type>::swap(DoubleLinkedList<type>& o){
	iterator<type> it = before_begin();
	iterator<type> o_it = o.before_begin();
	headNode->setNext(o_it->next());
	o.setHead(it->next()) //TODO refactor with operator=
}

template<typename type>
void DoubleLinkedList<type>::setHead(DoubleLinkedNode<type>* n){ //TODO Remodel operator=
	if (headNode) headNode->~DoubleLinkedNode(); //Should I do this? Yes, except it breaks swap().
	headNode = n;
	curSize = 1;
	DoubleLinkedNode<type> temp = headNode;
	while (temp->next()){
		temp = temp->next();
		curSize++;
	}
}

template<typename type>
DoubleLinkedNode<type>* DoubleLinkedList<type>::prune(int pos){
	if (pos > curSize) return nullptr; //Throw error?
	DoubleLinkedNode<type>* ret = headNode;
	while (pos-- > 1){
		ret = ret->next();
	}
	DoubleLinkedNode<type> temp = ret;
	ret = ret->next();
	temp->setNext(nullptr);
	curSize = pos;
	return ret;
}



