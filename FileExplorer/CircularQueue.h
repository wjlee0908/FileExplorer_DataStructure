#ifndef _CIRCULAR_QUEUE_H
#define _CIRCULAR_QUEUE_H

#define MAX_SIZE 10

#include <iostream>
using namespace std;


/**
*	@brief	Exception class thrown by Enqueue when queue is full.
*/
class FullQueue
{
public:
	/**
	*	@brief	Display a message for full queue on screen.
	*/
	void print()
	{
		cout << "FullQueue exception thrown." << endl;
	}
};


/**
*	@brief	Exception class thrown by Dequeue when queue is empty.
*/
class EmptyQueue
{
public:
	/**
	*	@brief	Display a message for empty queue on screen.
	*/
	void print()
	{
		cout << "EmtpyQueue exception thrown." << endl;
	}
};

/**
*	Queue class template for managing T type elements.
*   Internally implemented as a circular queue.
*/
template <typename T>
class CircularQueue
{
public:
	/**
	*	default constructor.
	*/
	CircularQueue();

	/**
	*	@brief	Constructs circular queue whose size is max.
	*	@pre	none.
	*	@post	Member of items points the allocated array.
	*   @param  size    size of constructing queue.
	*/
	CircularQueue(int size);

	/**
    *    copy constructor.
	*/
	//CircularQueue(const CircularQueue<T>& copied_object);

	/**
	*	destructor
	*/
	~CircularQueue();
	
	/**
	*	@brief	Returns whether the queue is full.
	*	@pre	Queue is initialized.
	*	@post	none.
	*   @return bool that expresses whether queue is full.
	*/
	bool IsFull();

	/**
	*	@brief  Returns whether the queue is empty.
	*	@pre	Queue is initialized.
	*	@post	none.
	*   @return bool that expresses whether queue is empty.
	*/
	bool IsEmpty();

	/**
	*	@brief	Makes the queue empty.
	*	@pre	Queue has been initialized.
	*	@post	front�� rear is set same value as Constructer.
	*/
	void MakeEmpty();

	/**
	*	@brief	Adds newItem to the last of the queue.
	*	@pre	Queue has been initialized.
	*	@post	item is inserted as last element.
	*   @param  item    item to insert.
	*/
	void EnQueue(T item);

	/**
	*	@brief	Pop first item from the queue.
	*	@pre	Queue has been initialized.
	*	@post	first element has been removed from queue.
	*   @return removed item.
	*/
	T DeQueue();

	/**
	*	@brief	Print all the items in the queue on output stream.
	*	@pre	Queue is initialized.
	*	@post	None.
	*/
	friend ostream& operator<<(ostream& output_stream, const CircularQueue<T>& queue_object);

private:
	int front_;	///< index of the first-1 element.
	int rear_;	///< index of the last element.
	int size_;	///< size of the queue.
	T* items_;	///< dynamically allocated item array.

	/**
	*	@brief	Initialize queue to size parameter.
	*	@pre	none.
	*	@post	queue is initialized.
	*   @param  size of queue.
	*/
	void InitializeQueue(int size);

	/**
	*	@brief	Circulate circular queue index.
	*	@pre	index is initialized.
	*	@post	index is converted to circular index.
	*   @param  changed index.
	*/
	int CirculateIndex(int& index);
};

// default constructor.
template <typename T>
CircularQueue<T>::CircularQueue()
{
	InitializeQueue(MAX_SIZE);   // set queue to max size.
}

// Allocate queue whose size is parameter
template <typename T>
CircularQueue<T>::CircularQueue(int size)
{
	InitializeQueue(size);
}

// destructor.
template <typename T>
CircularQueue<T>::~CircularQueue()
{
	delete[] items_;	// ���� �Ҵ�� �迭 �޸� ����
}

// Returns whether the queue is full.
template <typename T>
bool CircularQueue<T>::IsFull()
{
	// insert�� �� front�� ��ȯ�ϸ� �����ϴ� rear �ٷ� �տ� �����ϸ� full.
	// front�� 0�� ����, rear�� ���� �� �ε��� �����ϸ� full.
	if (front_ == rear_ - 1 || (front_ == 0) & (rear_ >= size_ - 1)) {
		return true;
	}
	else {
		return false;
	}
}

// Returns whether the queue is empty.
template <typename T>
bool CircularQueue<T>::IsEmpty()
{
	// pop�ϴٰ� rear�� front�� �����ϸ� empty.
	if (front_ == rear_) {
		return true;	
	}
	else {
		return false;
	}
}

// Makes the queue empty.
template <typename T>
void CircularQueue<T>::MakeEmpty()
{
	// front, rear index �ʱ�ȭ�Ͽ� ���� ������ �����
	front_ = size_ - 1;
	rear_ = size_ - 1;
}

// Adds new item to the last of the queue.
template <typename T>
void CircularQueue<T>::EnQueue(T item)
{
	// full�� ���� �߰��� �������� ����.
	if (IsFull()) {
		throw FullQueue();
	}

	// rear�� ������Ű�� item���� �־��ش�.
	CirculateIndex(++rear);
	items_[rear_] = item;
}

// Removes first item from the queue.
template <typename T>
T CircularQueue<T>::DeQueue()
{
	// Empty�� ���� ������ �� ����.
	if (IsEmpty()) {
		throw EmptyQueue();
	}

	//front�� 1 ���������ְ� ������ ���� item�� �������ش�.
	CirculateIndex(++front);
	return items_[front_];	
}

// Print all the items in the queue on output stream.
template <typename T>
ostream& operator<<(ostream& output_stream, const CircularQueue<T>& queue_object)
{
	if (front_ > rear_) {   // front+1 ~ 0 ~ rear ������ ������ ����� ���
		for (int i = queue_object.front_ + 1; i < queue_object.size_; i++) {
			output_stream << queue_object.items_[i] << " ";
		}
		for (int i = 0; i <= queue_object.rear_; i++) {
			output_stream << queue_object.items_[i] << " ";
		}
	}
	else	// ����ó�� front�� rear���� ���� ���
	{
		for (int i = queue_object.front_ + 1; i <= queue_object.rear_; i++) {
			output_stream << queue_object.items_[i] << " ";
		}	
	}

	return output_stream;
}

template<typename T>
void CircularQueue<T>::InitializeQueue(int size)
{
	items_ = new T[size];	// items �迭 ���� �Ҵ�
	size_ = size;
	front_ = size_ - 1;
	rear_ = size_ - 1;
}

template<typename T>
int CircularQueue<T>::CirculateIndex(int & index)
{
	index = index % size_;
	return index;
}

#endif    // CIRCULAR_QUEUE