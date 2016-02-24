
#include <iostream>

template <typename T>
struct Node{
	T item;
	Node<T> * next;
};

template <typename T> 
class LinkedList
{
private:
	Node<T> * first;
	int N;

public:
	LinkedList(){ head = NULL;}
	void insert(T item);
	void delete(T item);
	void print();
	void getHead();
	void getNodeCnt();

};

