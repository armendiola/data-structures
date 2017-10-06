#pragma once
#include "TreeNode.h"
#include <queue>
#include <stack>

template<typename type>
class iterator{
public:
	iterator(TreeNode<type>* n){
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
	bool operator< (const iterator<type>& o) const{
		if (!o.operator->() || !node) return !o.operator->() && node;
		return *(node) < *(o);
	}
	bool operator> (const iterator<type>& o){ return o.operator<(*this); }
	bool operator<= (const iterator<type>& o){ return !(operator>(o)); }
	bool operator>= (const iterator<type>& o){ return !(operator<(o)); }
	TreeNode<type>* operator->() const{
		return node;
	}
	TreeNode<type>& operator*() const{
		return *node;
	}
	friend std::ostream& operator<< (std::ostream& out, iterator<type>& o){
		if (o->left()) out << o - 1 << "<-";
		out << *o;
		if (o->right()) out << "->" << o + 1;
		return out;
	};
protected:
	TreeNode<type>* node;
	std::stack<TreeNode<type>*> parents = std::stack<TreeNode<type>*>();
};

template<typename type>
class BinaryTree
{
public:
	//Constructors & Destructor
	BinaryTree();
	BinaryTree(type);
	BinaryTree(TreeNode<type>*);
	~BinaryTree();

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
	TreeNode<type>* root();
	TreeNode<type>* at(iterator<type>);

	//Modifiers
	void clear();
	TreeNode<type>* insert(iterator<type>, TreeNode<type>*);
	//iterator<type> emplace(iterator<type>, TreeNode<type>*);
	TreeNode<type>* remove(iterator<type>, TreeNode<type>*);
	void insert(TreeNode<type>*);
	void insert(type);
	TreeNode<type>* remove(TreeNode<type>*);
	TreeNode<type>* remove(type);
	TreeNode<type>* pop_root();
	void copy(BinaryTree<type>*);
	void unique(iterator<type>);
	void unique();
	void merge(BinaryTree<type>&);

	//List Operations
	void swap(BinaryTree<type>&);

	//Lookup
	TreeNode<type>* find(type);

	//Operator Overloads
	bool operator+= (TreeNode<type>* n){
		insert(n);
		return true;
	}
	friend std::ostream& operator<< (std::ostream& out, BinaryTree& o){
		out << o.begin();
		return out;
	};

protected:
	TreeNode<type>* rootNode;
};

template<typename type>
BinaryTree<type>::BinaryTree(){
	rootNode = new TreeNode<type>();
}

template<typename type>
BinaryTree<type>::~BinaryTree(){
	if (rootNode) rootNode->~TreeNode();
	rootNode = nullptr;
}

//Creates an iterator to the root data node
template<typename type>
iterator<type> BinaryTree<type>::before_begin(){
	return iterator<type>(rootNode);
}

//Creates an iterator to the root data node
template<typename type>
iterator<type> BinaryTree<type>::begin(){
	iterator<type> it = iterator<type>(rootNode);
	it++;
	return it;
}

//Creates an iterator to a nullptr, which represents the tail
template<typename type>
iterator<type> BinaryTree<type>::end(){
	return iterator<type>(nullptr);
}

template<typename type>
TreeNode<type>* BinaryTree<type>::root(){
	return rootNode->right();
}

template<typename type>
TreeNode<type>* BinaryTree<type>::at(iterator<type> it){
	return it.operator->();
}

template<typename type>
std::size_t BinaryTree<type>::height(){
	return height(begin());
}

template<typename type>
std::size_t BinaryTree<type>::height(iterator<type> it){
	if (it == end()) return 0;
	std::size_t ret = height(it--);
	~it;
	std::size_t comp = height(it++);
	~it;
	if (comp > ret) return comp + 1;
	return ret + 1;
}

template <typename type>
bool BinaryTree<type>::empty(){
	return rootNode->right() == nullptr;
}

template <typename type>
TreeNode<type>* BinaryTree<type>::insert(iterator<type> it, TreeNode<type>* n){
	if (it == end()) return n;
	if (*n < *it) (~it)->setLeft(insert(it--, n));
	else (~it)->setRight(insert(it++, n));
	return it.operator->();
}

template <typename type>
TreeNode<type>* BinaryTree<type>::remove(iterator<type> it, TreeNode<type>* n){ //TODO improve simplicity, make more elagant if possible
	if (it == end()) return nullptr;
	if (*n == *it){
		if (!(it->left())) return it->right(); //Case 1, 2
		if (!(it->right())) return it->left(); //Case 2
		iterator<type> rep = it + 1;
		if (!(rep->left())){ //Case 3, 4
			rep->setLeft(it->left());
			return rep.operator->();
		}
		while (rep->left()) rep--; //Case 5
		~rep;
		TreeNode<type>* ret = rep->left();
		rep->setLeft(ret->right());
		ret->setLeft(it->left());
		ret->setRight(it->right());
		return ret;
	}
	if (*n < *it) (~it)->setLeft(remove(it--, n));
	else (~it)->setRight(remove(it++, n));
	return it.operator->();
}

template <typename type>
void BinaryTree<type>::insert(TreeNode<type>* n){
	insert(before_begin(), n);
}

template <typename type>
void BinaryTree<type>::insert(type d){
	insert(new TreeNode<type>(d));
}

template <typename type>
TreeNode<type>* BinaryTree<type>::remove(TreeNode<type>* n){
	return remove(before_begin(), n);
}

template <typename type>
TreeNode<type>* BinaryTree<type>::remove(type d){
	return remove(new TreeNode<type>(d));
}

template <typename type>
TreeNode<type>* BinaryTree<type>::pop_root(){
	return remove(before_begin(), at(begin()));
}

template <typename type>
void BinaryTree<type>::unique(iterator<type> it){
	if (it == end() || (it + 1 == end())) return;
	(~it)->setRight(remove(it++, it.operator->()));
	unique(it++);
	~it;
	unique(it--);
	~it;
}

template <typename type>
void BinaryTree<type>::unique(){
	return unique(begin());
}

template <typename type>
void BinaryTree<type>::swap(BinaryTree<type>& o){
	TreeNode<type>* n = rootNode->right();
	iterator<type> o_it = o.before_begin();
	rootNode->setRight(o_it->right());
	o_it->setRight(n);
}

template <typename type>
std::size_t BinaryTree<type>::count(iterator<type> it){
	if (it == end()) return 0;
	std::size_t ret = count(it++);
	~it;
	ret += count(it--);
	~it;
	return ret + 1;
}

template <typename type>
std::size_t BinaryTree<type>::count(){
	return count(begin())
}

template<typename type>
TreeNode<type>* BinaryTree<type>::find(type d){
	iterator<type> it = begin();
	TreeNode<type>* n = new TreeNode<type>(d);
	while (!(it == end() || *it == *n)){
		if (*n < *it) it--;
		else it++;
	}
	return at(it);
}