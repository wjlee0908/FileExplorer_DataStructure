#ifndef _CIRCULAR_QUEUE_H
#define _CIRCULAR_QUEUE_H

#include <iostream>
using namespace std;

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
	CircularQueue() :
		CircularQueue(kDefaultMaxSize) {
		InitializeQueue();
	}

	/**
	*	@brief	Constructs circular queue whose size is parameter.
	*	@pre	none.
	*	@post	Member of items points the allocated array.
	*   @param  size    size of constructing queue.
	*/
	CircularQueue(int size) :
		items_(nullptr),
		size_(size),
		front_(size_ - 1),
		rear_(size_ - 1) {
		InitializeQueue();
	}

	/**
    *    copy constructor.
	*/
	CircularQueue(const CircularQueue<T>& copied_object) :
		items_(nullptr),
		size_(copied_object.size_),
		front_(copied_object.front_),
		rear_(copied_object.rear_) {
		InitializeQueue(copied_object.items_);
	}

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
	*	@post	front와 rear is set same value as Constructer.
	*/
	void MakeEmpty();

	/**
	*	@brief	Adds new item to the last of the queue.
	*	@pre	Queue has been initialized.
	*	@post	item is inserted as last element.
	*   @param  item    item to insert.
	*/
	void EnQueue(const T& item);

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
	*	@brief	Initialize queue to size member.
	*	@pre	none.
	*	@post	queue item is initialized.
	*/
	void InitializeQueue();

	/**
	*	@brief	Initialize queue item and copy array parameter.
	*	@pre	none.
	*	@post	queue item is initialized.
	*   @param  copied_items    item array to copy item
	*   @param  arr_size    size of item array.
	*/
	void InitializeQueue(T* copied_items, int arr_size);


	/**
	*	@brief	Circulate circular queue index.
	*	@pre	index is initialized.
	*	@post	index is converted to circular index.
	*   @param  changed index.
	*/
	int CirculateIndex(int& index);

	static const int kDefaultMaxSize = 10;    ///< default max size of queue

	T* items_;	///< dynamically allocated item array.
	int size_;	///< size of the queue.
	int front_;	///< index of the first-1 element.
	int rear_;	///< index of the last element.
};

// destructor.
template <typename T>
CircularQueue<T>::~CircularQueue()
{
	delete[] items_;	// 동적 할당된 배열 메모리 해제
}

// Returns whether the queue is full.
template <typename T>
bool CircularQueue<T>::IsFull() const
{
	// insert할 때 front가 순환하며 증가하다 rear 바로 앞에 도달하면 full.
	// front가 0일 때는, rear가 가장 끝 인덱스 도달하면 full.
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
	// pop하다가 rear가 front에 도달하면 empty.
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
	// front, rear index 초기화하여 기존 데이터 덮어쓰기
	front_ = size_ - 1;
	rear_ = size_ - 1;
}

// Adds new item to the last of the queue.
template <typename T>
void CircularQueue<T>::EnQueue(const T& item)
{
	// full일 때는 추가로 삽입하지 않음.
	if (IsFull()) {
		throw ExceptionFullQueue();
	}

	// rear를 증가시키고 item값을 넣어준다.
	CirculateIndex(++rear_);
	items_[rear_] = item;
}

// Removes first item from the queue.
template <typename T>
T CircularQueue<T>::DeQueue()
{
	// Empty일 때는 제거할 수 없음.
	if (IsEmpty()) {
		throw ExceptionEmptyQueue();
	}

	//front를 1 증가시켜주고 삭제될 값을 item에 복사해준다.
	CirculateIndex(++front_);
	return items_[front_];	
}

// Copy parameter queue and assign to this queue.
template<typename T>
CircularQueue<T>& CircularQueue<T>::operator=(const CircularQueue<T>& copied_object)
{
	// size 더 큰 큐 복사할 수도 있으므로 동적 할당 해제하고 다시 할당함.
	if (this != nullptr) {
		delete[] this->items_;
	}
	
	// 속성 복사
	this->size_ = copied_object.size_;
	this->front_ = copied_object.front_;
	this->rear_ = copied_object.rear_;

	// 배열 할당 후 내용 복사
	this->InitializeQueue(copied_object.items_, copied_object.size_);

	return *this;
}

// Print all the items in the queue on output stream.
template <typename T>
ostream& operator<<(ostream& output_stream, const CircularQueue<T>& queue_object)
{
	// 비어있는 큐에서는 수행하지 않음
	if (IsEmpty()) {
		return output_stream;
	}

	if (front_ > rear_) {   // front+1 ~ 0 ~ rear 순으로 데이터 저장된 경우
		for (int i = queue_object.front_ + 1; i < queue_object.size_; i++) {
			output_stream << queue_object.items_[i] << " ";
		}
		for (int i = 0; i <= queue_object.rear_; i++) {
			output_stream << queue_object.items_[i] << " ";
		}
	}
	else	// 선형처럼 front가 rear보다 작은 경우
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
	// size 더 큰 큐 복사할 수도 있으므로 동적 할당 해제하고 다시 할당함.
	delete[] this->items_;
	this->InitializeQueue(copied_object.size_);

	// 속성 복사
	this->front_ = copied_object.front_;
	this->rear_ = copied_object.rear_;

	// 데이터 array 내용 복사
	// 비어있는 큐에서는 수행하지 않음
	if (!copied_object.IsEmpty()) {
		if (front_ > rear_) {   // front+1 ~ 0 ~ rear 순으로 데이터 저장된 경우
			for (int i = this->front_ + 1; i < this->size_; i++) {
				this->items_[i] = copied_object.items_[i];
			}
			for (int i = 0; i <= this->rear_; i++) {
				this->items_[i] = copied_object.items_[i];
			}
		}
		else	// 선형처럼 front가 rear보다 작은 경우
		{
			for (int i = this->front_ + 1; i <= this->rear_; i++) {
				this->items_[i] = copied_object.items_[i];
			}
		}
	}
}

// Initialize queue to size parameter.
template<typename T>
void CircularQueue<T>::InitializeQueue()
{
	items_ = new T[size_];	// items 배열 동적 할당
}

// Initialize queue item and copy array parameter.
template<typename T>
void CircularQueue<T>::InitializeQueue(T* copied_items, int arr_size)
{
	items_ = new T[arr_size];    // items 배열 동적 할당
	// 데이터 array 내용 복사
	// 비어있는 큐에서는 수행하지 않음
	if (copied_items != nullptr) {
		if (front_ > rear_) {   // front+1 ~ 0 ~ rear 순으로 데이터 저장된 경우
			for (int i = this->front_ + 1; i < this->size_; i++) {
				this->items_[i] = copied_items[i];
			}
			for (int i = 0; i <= this->rear_; i++) {
				this->items_[i] = copied_items[i];
			}
		}
		else	// 선형처럼 front가 rear보다 작은 경우
		{
			for (int i = this->front_ + 1; i <= this->rear_; i++) {
				this->items_[i] = copied_items[i];
			}
		}
	}
}

// Circulate circular queue index.
template<typename T>
int CircularQueue<T>::CirculateIndex(int & index)
{
	index = index % size_;
	return index;
}

#endif    // CIRCULAR_QUEUE