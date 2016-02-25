
#include <iostream>

template <typename T>
struct Node{
	T item;
	Node<T> * next;
};

template <typename T> 
class Queue
{
private:
	Node<T> * head;
	Node<T> * tail;
	int N;

public:
	Queue():head(NULL),tail(NULL),N(0){};
	bool isEmpty(){return N==0;};
	int size(){return N;};
	void enqueue( T item);
	T dequeue();

	~Queue(){
		if (! isEmpty())
		{
			while(dequeue());
		}
	}


	void print();

};

template <typename T> 
void Queue<T>::enqueue(T item)
{
	Node<T> * pNew = new Node<T>();
	pNew->item = item;
	pNew->next = NULL;

	
	if (!isEmpty())
	{
		tail-> next = pNew;
		tail = pNew;
	}
	else 

	{
		tail = pNew;
		head = tail;
	}
	N++;

}
template <typename T>
T Queue<T>:: dequeue()
{
	Node<T> * pPop = head;
	head = head->next;
	N--;
	if (isEmpty()) tail = NULL;
	
	T tmp = pPop->item;
	delete pPop;
	return tmp;
}