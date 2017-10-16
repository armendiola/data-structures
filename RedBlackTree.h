#pragma once
#include "RedBlackTreeNode.h"
#include <queue>
#include <stack>

template<typename type>
class iterator{
public:
	iterator(RedBlackTreeNode<type>* n){
		node = n;
	}
	~iterator(){
		node = nullptr;
	}
	iterator<type> operator--(){ //pre-increment
		if (!node) return *this;
		parents.push(node);
		node = node->left();
		return *this;
	}
	iterator<type> operator++(){ //pre-increment
		if (!node) return *this;
		parents.push(node);
		node = node->right();
		return *this;
	}
	iterator<type> operator~(){
		if (parents.empty()) return false;
		node = parents.top();
		parents.pop();
		return *this;
	}
	iterator<type> operator--(int){ //post-increment
		return operator--();
	}
	iterator<type> operator++(int){ //post-increment
		return operator++();
	}
	bool operator+= (std::size_t i){
		while (i-- > 0) if (!(operator++().node)) return false;
		return true;
	}
	bool operator-= (std::size_t i){
		while (i-- > 0) if (!(operator--().node)) return false;
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
	bool operator== (const Color& o) const{
		if (!node) return false;
		return node->color() == o;
	}
	bool operator< (const iterator<type>& o) const{
		if (!o.operator->() || !node) return !o.operator->() && node;
		return *(node) < *(o);
	}
	bool operator> (const iterator<type>& o){ return o.operator<(*this); }
	bool operator<= (const iterator<type>& o){ return !(operator>(o)); }
	bool operator>= (const iterator<type>& o){ return !(operator<(o)); }
	RedBlackTreeNode<type>* operator->() const{
		return node;
	}
	RedBlackTreeNode<type>& operator*() const{
		return *node;
	}
	friend std::ostream& operator<< (std::ostream& out, iterator<type>& o){
		out << '[';
		if (o->left()) out << o - 1 << "";
		out << o->getData();
		if (o->right()) out << "" << o + 1;
		out << ']';
		return out;
	};
protected:
	RedBlackTreeNode<type>* node;
	std::stack<RedBlackTreeNode<type>*> parents = std::stack<RedBlackTreeNode<type>*>();
};

template<typename type>
class RedBlackTree
{
public:
	//Constructors & Destructor
	RedBlackTree();
	RedBlackTree(type);
	RedBlackTree(RedBlackTreeNode<type>*);
	~RedBlackTree();

	//Iterator functions
	iterator<type> before_begin();
	iterator<type> begin();
	iterator<type> end();

	//Capacity functions
	std::size_t height(iterator<type>);
	std::size_t height();
	std::size_t count(iterator<type>);
	std::size_t count();
	bool empty();

	//Element access
	RedBlackTreeNode<type>* root();
	RedBlackTreeNode<type>* at(iterator<type>);

	//Modifiers
	void clear();
	RedBlackTreeNode<type>* insert(iterator<type>, RedBlackTreeNode<type>*);
	//iterator<type> emplace(iterator<type>, RedBlackTreeNode<type>*);
	RedBlackTreeNode<type>* remove(iterator<type>, RedBlackTreeNode<type>*);
	void insert(RedBlackTreeNode<type>*);
	void insert(type);
	void remove(RedBlackTreeNode<type>*);
	void remove(type);
	RedBlackTreeNode<type>* pop_root();
	RedBlackTreeNode<type>* rotateRight(iterator<type>);
	RedBlackTreeNode<type>* rotateLeft(iterator<type>);
	RedBlackTreeNode<type>* doubleBlackLeft(iterator<type>);
	RedBlackTreeNode<type>* doubleBlackRight(iterator<type>);
	void copy(RedBlackTree<type>*);
	void unique(iterator<type>);
	void unique();
	void merge(RedBlackTree<type>&);

	//List Operations
	void swap(RedBlackTree<type>&);

	//Lookup
	RedBlackTreeNode<type>* find(type);

	//Operator Overloads
	bool operator+= (RedBlackTreeNode<type>* n){
		insert(n);
		return true;
	}
	friend std::ostream& operator<< (std::ostream& out, RedBlackTree& o){
		out << o.begin();
		return out;
	};

protected:
	RedBlackTreeNode<type>* rootNode;
};

template<typename type>
RedBlackTree<type>::RedBlackTree(){
	rootNode = new RedBlackTreeNode<type>();
}

template<typename type>
RedBlackTree<type>::~RedBlackTree(){
	if (rootNode) rootNode->~RedBlackTreeNode();
	rootNode = nullptr;
}

//Creates an iterator to the root data node
template<typename type>
iterator<type> RedBlackTree<type>::before_begin(){
	return iterator<type>(rootNode);
}

//Creates an iterator to the root data node
template<typename type>
iterator<type> RedBlackTree<type>::begin(){
	iterator<type> it = iterator<type>(rootNode);
	it++;
	return it;
}

//Creates an iterator to a nullptr, which represents the tail
template<typename type>
iterator<type> RedBlackTree<type>::end(){
	return iterator<type>(nullptr);
}

template<typename type>
RedBlackTreeNode<type>* RedBlackTree<type>::root(){
	return rootNode->right();
}

template<typename type>
RedBlackTreeNode<type>* RedBlackTree<type>::at(iterator<type> it){
	return it.operator->();
}

template<typename type>
std::size_t RedBlackTree<type>::height(){
	return height(begin());
}

template<typename type>
std::size_t RedBlackTree<type>::height(iterator<type> it){
	if (it == end()) return 0;
	std::size_t ret = height(it--);
	~it;
	std::size_t comp = height(it++);
	~it;
	if (comp > ret) return comp + 1;
	return ret + 1;
}

template <typename type>
bool RedBlackTree<type>::empty(){
	return rootNode->right() == nullptr;
}

template <typename type>
RedBlackTreeNode<type>* RedBlackTree<type>::rotateRight(iterator<type> it){
	RedBlackTreeNode<type>* ret = it->left();
	it->setLeft(ret->right());
	ret->setRight(it.operator->());
	return ret;
}

template <typename type>
RedBlackTreeNode<type>* RedBlackTree<type>::rotateLeft(iterator<type> it){
	RedBlackTreeNode<type>* ret = it->right();
	it->setRight(ret->left());
	ret->setLeft(it.operator->());
	return ret;
}

template <typename type>
RedBlackTreeNode<type>* RedBlackTree<type>::insert(iterator<type> it, RedBlackTreeNode<type>* n){
	if (it == end()) return n;
	if (*n < *it){
		(~it)->setLeft(insert(it--, n));
		if ((it - 1) == DOUBLE_RED){ //Double Red Violation Cases
			it->left()->setColor(BLACK);
			it->setColor(RED);
			if ((it + 1) == RED) it->right()->setColor(BLACK); //Color Flip Cases
			else{
				if (!(*n < *(it->left()))){ //Double Rotation Case
					it->left()->setColor(RED);
					it->left()->right()->setColor(BLACK);
					(~it)->setLeft(rotateLeft(it--));
				}
				return rotateRight(it); //Rotation Cases
			}
		}
		else if (it->color() && it->left()->color()) it->setColor(DOUBLE_RED); //Double Red Violation Trigger
	}
	else{
		(~it)->setRight(insert(it++, n));
		if ((it + 1) == DOUBLE_RED){ //Double Red Violation Cases
			it->right()->setColor(BLACK);
			it->setColor(RED);
			if ((it - 1) == RED) it->left()->setColor(BLACK); //Color Flip Case
			else{
				if (*n < *(it->right())){ //Double Rotation Case
					it->right()->setColor(RED);
					it->right()->left()->setColor(BLACK);
					(~it)->setRight(rotateRight(it++));
				}
				return rotateLeft(it); //Rotation Cases
			}
		}
		else if (it->color() && it->right()->color()) it->setColor(DOUBLE_RED); //Double Red Violation Trigger
	}
	return it.operator->();
}

template <typename type>
RedBlackTreeNode<type>* RedBlackTree<type>::remove(iterator<type> it, RedBlackTreeNode<type>* n){ //TODO improve simplicity, make more elagant if possible
	if (it == end()) return nullptr;
	if (*n == *it){
		if (!(it->left())){
			if (it == RED || (it + 1) == RED){ //Half Node and Red Leaf Node Cases
				if(it->right()) it->right()->setColor(BLACK);
				return it->right();
			}
			else{ //Black Leaf Node Case
				RedBlackTreeNode<type>* ret = new RedBlackTreeNode<type>();
				ret->setColor(DOUBLE_BLACK);
				return ret;
			}
		}
		if (!(it->right())){
			if (it == RED || (it - 1) == RED){ //Half Node Case
				it->left()->setColor(BLACK);
				return it->left();
			}
		}
		RedBlackTreeNode<type>* ret = it->right();
		while (ret->left()) ret = ret->left();
		(~it)->setRight(remove(it++, ret)); //Case 3, 4, 5
		ret->setLeft(it->left());
		ret->setRight(it->right());
		ret->setColor(it->color());
		return ret;
	}
	if (*n < *it){
		(~it)->setLeft(remove(it--, n));
		if ((it - 1) == DOUBLE_BLACK) return doubleBlackLeft(it);
	}
	else{
		(~it)->setRight(remove(it++, n));
		if ((it + 1) == DOUBLE_BLACK) return doubleBlackRight(it);
	}
	return it.operator->();
}

template <typename type>
RedBlackTreeNode<type>* RedBlackTree<type>::doubleBlackLeft(iterator<type> it){
	RedBlackTreeNode<type>* ret = it.operator->();
	if ((it + 1) == RED){ //Red Sibling Case
		it->right()->setColor(BLACK);
		it->setColor(RED);
		ret = rotateLeft(it);
		ret->setLeft(doubleBlackLeft(it)); //Search for better way to down propogate
	}
	else{
		it++;
		if ((it + 1) == RED || (it - 1) == RED){ //Black Sibling with Red Child Cases
			if ((it + 1) == BLACK) (~it)->setRight(rotateRight(it));
			else{
				it->right()->setColor(BLACK);
				~it;
			}
			it->right()->setColor(it->color());
			it->setColor(BLACK);
			ret = rotateLeft(it);
		}
		else{ //Black Sibling without Red Child Case
			~it;
			it->right()->setColor(RED);
			if (it == RED) it->setColor(BLACK);
			else it->setColor(DOUBLE_BLACK);
		}
		it->left()->setColor(BLACK);
		if (*(it->left()) == RedBlackTreeNode<type>()) it->setLeft(nullptr);
	}
	return ret;
}

template <typename type>
RedBlackTreeNode<type>* RedBlackTree<type>::doubleBlackRight(iterator<type> it){
	RedBlackTreeNode<type>* ret = it.operator->();
	if ((it - 1) == RED){ //Red Sibling Case
		it->left()->setColor(BLACK);
		it->setColor(RED);
		ret = rotateRight(it);
		ret->setRight(doubleBlackRight(it)); //Search for better way to down propogate
	}
	else{
		it--;
		if ((it - 1) == RED || (it + 1) == RED){ //Black Sibling with Red Child Case
			if ((it - 1) == BLACK) (~it)->setLeft(rotateLeft(it));
			else{
				it->left()->setColor(BLACK);
				~it;
			}
			it->left()->setColor(it->color());
			it->setColor(BLACK);
			ret = rotateRight(it);
		}
		else{ //Black Sibling without Red Child Case
			~it;
			it->left()->setColor(RED);
			if (it == RED) it->setColor(BLACK);
			else it->setColor(DOUBLE_BLACK);
		}
		it->right()->setColor(BLACK);
		if (*(it->right()) == RedBlackTreeNode<type>()) it->setRight(nullptr);
	}
	return ret;
}

template <typename type>
void RedBlackTree<type>::insert(RedBlackTreeNode<type>* n){
	rootNode->setRight(insert(begin(), n));
	rootNode->right()->setColor(BLACK);
}

template <typename type>
void RedBlackTree<type>::insert(type d){
	insert(new RedBlackTreeNode<type>(d));
}

template <typename type>
void RedBlackTree<type>::remove(RedBlackTreeNode<type>* n){
	rootNode->setRight(remove(begin(), n));
	rootNode->right()->setColor(BLACK);
}

template <typename type>
void RedBlackTree<type>::remove(type d){
	remove(new RedBlackTreeNode<type>(d));
}

template <typename type>
RedBlackTreeNode<type>* RedBlackTree<type>::pop_root(){
	RedBlackTreeNode<type>* ret = remove(begin(), at(begin()));
	//TODO
	return ret;
}

template <typename type>
void RedBlackTree<type>::unique(iterator<type> it){
	if (it == end() || (it + 1 == end())) return;
	(~it)->setRight(remove(it++, it.operator->()));
	unique(it++);
	~it;
	unique(it--);
	~it;
}

template <typename type>
void RedBlackTree<type>::unique(){
	return unique(begin());
}

template <typename type>
void RedBlackTree<type>::swap(RedBlackTree<type>& o){
	RedBlackTreeNode<type>* n = rootNode->right();
	iterator<type> o_it = o.before_begin();
	rootNode->setRight(o_it->right());
	o_it->setRight(n);
}

template <typename type>
std::size_t RedBlackTree<type>::count(iterator<type> it){
	if (it == end()) return 0;
	std::size_t ret = count(it++);
	~it;
	ret += count(it--);
	~it;
	return ret + 1;
}

template <typename type>
std::size_t RedBlackTree<type>::count(){
	return count(begin())
}

template<typename type>
RedBlackTreeNode<type>* RedBlackTree<type>::find(type d){
	iterator<type> it = begin();
	RedBlackTreeNode<type>* n = new RedBlackTreeNode<type>(d);
	while (!(it == end() || *it == *n)){
		if (*n < *it) it--;
		else it++;
	}
	return at(it);
}