#ifndef _CIRCULAR_QUEUE_H
#define _CIRCULAR_QUEUE_H

#include <iostream>
using namespace std;

#define MAX_SIZE 10

/**
*	@brief	Exception class thrown by Enqueue when queue is full.
*/
class ExceptionFullQueue
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
class ExceptionEmptyQueue
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
	*	@brief	Constructs circular queue whose size is parameter.
	*	@pre	none.
	*	@post	Member of items points the allocated array.
	*   @param  size    size of constructing queue.
	*/
	CircularQueue(int size);

	/**
    *    copy constructor.
	*/
	CircularQueue(const CircularQueue<T>& copied_object);

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
	bool IsFull() const;

	/**
	*	@brief  Returns whether the queue is empty.
	*	@pre	Queue is initialized.
	*	@post	none.
	*   @return bool that expresses whether queue is empty.
	*/
	bool IsEmpty() const;

	/**
	*	@brief	Makes the queue empty.
	*	@pre	Queue has been initialized.
	*	@post	front�� rear is set same value as Constructer.
	*/
	void MakeEmpty();

	/**
	*	@brief	Adds new item to the last of the queue.
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
	*	@brief	Copy parameter queue and assign to this queue.
	*	@pre	copied_data is set.
	*	@post	queue is set.
	*   @param  copied_data    data to assign
	*   @return retrun this after assigning parameter.
	*/
	CircularQueue<T>& operator= (const CircularQueue<T>& copied_data);

	/**
	*	@brief	Print all the items in the queue on output stream.
	*	@pre	Queue is initialized.
	*	@post	None.
	*/
	friend ostream& operator<<(ostream& output_stream, const CircularQueue<T>& queue_object);

private:
	/**
	*	@brief	Copy parameter queue and assign to this queue. (deep copy)
	*	@pre	copied_object is set.
	*	@post	queue is set.
	*   @param  copied_object    object to assign
	*/
	void AssignCopy(const CircularQueue<T> & copied_object);

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

	int front_;	///< index of the first-1 element.
	int rear_;	///< index of the last element.
	int size_;	///< size of the queue.
	T* items_;	///< dynamically allocated item array.
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

// copy constructor. (deep copy)
template<typename T>
CircularQueue<T>::CircularQueue(const CircularQueue<T>& copied_object)
{
	AssignCopy(copied_object);
}

// destructor.
template <typename T>
CircularQueue<T>::~CircularQueue()
{
	delete[] items_;	// ���� �Ҵ�� �迭 �޸� ����
}

// Returns whether the queue is full.
template <typename T>
bool CircularQueue<T>::IsFull() const
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
bool CircularQueue<T>::IsEmpty() const
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
		throw ExceptionFullQueue();
	}

	// rear�� ������Ű�� item���� �־��ش�.
	CirculateIndex(++rear_);
	items_[rear_] = item;
}

// Removes first item from the queue.
template <typename T>
T CircularQueue<T>::DeQueue()
{
	// Empty�� ���� ������ �� ����.
	if (IsEmpty()) {
		throw ExceptionEmptyQueue();
	}

	//front�� 1 ���������ְ� ������ ���� item�� �������ش�.
	CirculateIndex(++front_);
	return items_[front_];	
}

// Copy parameter queue and assign to this queue.
template<typename T>
CircularQueue<T>& CircularQueue<T>::operator=(const CircularQueue<T>& copied_data)
{
	AssignCopy(copied_data);

	return *this;
}

// Print all the items in the queue on output stream.
template <typename T>
ostream& operator<<(ostream& output_stream, const CircularQueue<T>& queue_object)
{
	// ����ִ� ť������ �������� ����
	if (IsEmpty()) {
		return output_stream;
	}

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

// Copy parameter queue and assign to this queue. (deep copy)
template<typename T>
void CircularQueue<T>::AssignCopy(const CircularQueue<T> & copied_object)
{
	// size �� ū ť ������ ���� �����Ƿ� ���� �Ҵ� �����ϰ� �ٽ� �Ҵ���.
	delete[] this->items_;
	this->InitializeQueue(copied_object.size_);

	// �Ӽ� ����
	this->front_ = copied_object.front_;
	this->rear_ = copied_object.rear_;

	// ������ array ���� ����
	// ����ִ� ť������ �������� ����
	if (!copied_object.IsEmpty()) {
		if (front_ > rear_) {   // front+1 ~ 0 ~ rear ������ ������ ����� ���
			for (int i = this->front_ + 1; i < this->size_; i++) {
				this->items_[i] = copied_object.items_[i];
			}
			for (int i = 0; i <= this->rear_; i++) {
				this->items_[i] = copied_object.items_[i];
			}
		}
		else	// ����ó�� front�� rear���� ���� ���
		{
			for (int i = this->front_ + 1; i <= this->rear_; i++) {
				this->items_[i] = copied_object.items_[i];
			}
		}
	}
}

// Initialize queue to size parameter.
template<typename T>
void CircularQueue<T>::InitializeQueue(int size)
{
	size_ = size;
	items_ = new T[size_];	// items �迭 ���� �Ҵ�
	front_ = size_ - 1;
	rear_ = size_ - 1;
}

// Circulate circular queue index.
template<typename T>
int CircularQueue<T>::CirculateIndex(int & index)
{
	index = index % size_;
	return index;
}

#endif    // CIRCULAR_QUEUE