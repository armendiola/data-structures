#include <iostream>
//#include "DoubleLinkedList.h"
#include "AVLTree.h"

int main(){
	AVLTree<int> tester = AVLTree<int>();
	std::cout << tester.height() << std::endl;
	tester.insert(4);
	std::cout << tester.height() << ": " << tester << std::endl;
	tester.insert(10);
	std::cout << tester.height() << ": " << tester << std::endl;
	tester.insert(9);
	std::cout << tester.height() << ": " << tester << std::endl;
	tester.insert(8);
	std::cout << tester.height() << ": " << tester << std::endl;
	tester.insert(6);
	std::cout << tester.height() << ": " << tester << std::endl;
	tester.insert(5);
	std::cout << tester.height() << ": " << tester << std::endl;
	tester.insert(7);
	std::cout << tester.height() << ": " << tester << std::endl;
	tester.insert(11);
	std::cout << tester.height() << ": " << tester << std::endl;
	tester.insert(2);
	std::cout << tester.height() << std::endl;
	std::cout << tester << std::endl;
	tester.remove(4);
	std::cout << tester << std::endl;
	tester.remove(5);
	std::cout << tester << std::endl;
	tester.remove(11);
	std::cout << tester << std::endl;
	tester.remove(8);
	std::cout << tester << std::endl;

	/*
	DoubleLinkedList<int> list = DoubleLinkedList<int>();
	list.push_head(3);
	std::cout << "List 1:\t" << list;
	list.push_tail(4);
	std::cout << "List 1:\t" << list;
	list.push_tail(6);
	std::cout << "List 1:\t" << list;
	list.push_tail(7);
	std::cout << "List 1:\t" << list;
	list.push_head(1);
	std::cout << "List 1:\t" << list;
	list.push_tail(2);
	std::cout << "List 1:\t" << list;
	list.push_tail(5);
	std::cout << "List 1:\t" << list;
	list.push_tail(8);
	std::cout << "List 1:\t" << list;
	list.push_tail(9);
	std::cout << "List 1:\t" << list;
	list.sort();
	list.reverse();
	std::cout << "List 1:\t" << list;
	*/

	return 0;
}