#ifndef _STACK_H
#define _STACK_H

#include <iostream>
using namespace std;

/**
*	@brief	Exception class thrown by Push when stack is full.
*/
class ExceptionFullStack
{
public:
	/**
	*	@brief	Display a message for full stack on screen.
	*/
	void print()
	{
		cout << "FullStack exception thrown." << endl;
	}
};


/**
*	@brief	Exception class thrown by Pop and Top when stack is empty.
*/
class ExceptionEmptyStack
{
public:
	/**
	*	@brief	Display a message for full stack on screen.
	*/
	void print()
	{
		cout << "EmptyStack exception thrown." << endl;
	}
};


/**
*	Stack class template for managing T type elements.
*	Internally implemented as dynamically allocated array.
*/
template <typename T>
class Stack
{
public:
	/**
	*	default constructor.
	*/
	Stack();

	/**
	*	@brief	Constructs stack whose size is parameter size.
	*	@pre	none.
	*	@post	Member of items points the allocated array.
	*   @param  size    size of constructing stack.
	*/
	Stack(int size);

	/**
	*    copy constructor.
	*/
	Stack(const Stack<T>& copied_object);

	/**
	*	destructor.
	*/
	~Stack();

	/**
	*	@brief	Returns whether the stack is full.
	*	@pre	Stack is initialized.
	*	@post	none.
	*   @return bool that expresses whether stack is full.
	*/
	bool IsFull() const;

	/**
	*	@brief  Returns whether the stack is empty.
	*	@pre	Stack is initialized.
	*	@post	none.
	*   @return bool that expresses whether stack is empty.
	*/
	bool IsEmpty() const;

	/**
	*	@brief	Makes the stack empty.
	*	@pre	Stack has been initialized.
	*	@post	top is initialized
	*/
	void MakeEmpty();

	/**
	*	@brief	Adds newItem to the top of the stack.
	*	@pre	Stack has been initialized.
	*	@post	If (stack is full), FullStack exception is thrown; otherwise, newItem is at the top of the stack.
	*/
	void Push(T item);

	/**
	*	@brief	Removes top item from the stack.
	*	@pre	Stack has been initialized.
	*	@post	If (stack is empty), EmptyStack exception is thrown; otherwise, top element has been removed from stack.
	*/
	T Pop();

	/**
	*	@brief	Returns a top item on the stack.
	*	@pre	Stack has been initialized.
	*	@post	If (stack is empty), EmptyStack exception is thrown; oterwise none.
	*/
	T& GetTopElement();

	/**
	*	@brief	Returns a top item on the stack. for the const stack.
	*	@pre	Stack has been initialized.
	*	@post	If (stack is empty), EmptyStack exception is thrown; otherwise none.
	*/
	const T& GetTopElement() const;

	/**
	*	@brief	Print all the items in the stack on output stream.
	*	@pre	Stack is initialized.
	*	@post	None.
	*/
	friend ostream& operator<<(ostream& output_stream, const Stack<T>& stack_object);

private:
	/**
	*	@brief	Initialize stack to size parameter.
	*	@pre	none.
	*	@post	stack is initialized.
	*   @param  size of stack.
	*/
	void InitializeStack(int size);

	static const int kDefaultMaxSize = 10;    ///< default max size of stack 

	int top_;	///< Number of elements in current array.
	int size_;	///< size of the stack.
	T* items_;	///< dynamically allocated item array.
};

// default constructor
template<typename T>
Stack<T>::Stack()
{
	InitializeStack(kDefaultMaxSize);
}

//Constructs stack whose size is parameter size.
template<typename T>
inline Stack<T>::Stack(int size)
{
	InitializeStack(size);
}

// copy constructor
template<typename T>
Stack<T>::Stack(const Stack<T>& copied_object)
{
	// size 더 큰 스택 복사할 수도 있으므로 동적 할당 해제하고 다시 할당함.
	delete[] this->items_;
	this->InitializeStack(copied_object.size_);

	// 속성 복사
	this->top_ = copied_object.top_;

	// 데이터 array 복사
	// 비어 있는 큐에서는 수행하지 않음.
	if (!copied_object.IsEmpty()) {
		for (int i = 0; i <= top; i++)
		{
			this->items_[i] = copied_object.items_[i];
		}
	}
 }


// destructor.
template<typename T>
Stack<T>::~Stack()
{
	delete[] items_;	// 동적 할당된 배열 메모리 해제
}


// Determines whether the stack is full.
template<typename T>
bool Stack<T>::IsEmpty() const
{
	if (top_ <= -1) {
		return true;
	}
	else {
		return false;
	}
}

// Makes the stack empty.
template<typename T>
void Stack<T>::MakeEmpty()
{
	top_ = -1;
}


// Returns whether the stack is full.
template<typename T>
bool Stack<T>::IsFull() const
{
	if (top_ >= size_ - 1)
		return true;
	else
		return false;
}


// Adds new item to the top of the stack.
template<typename T>
void Stack<T>::Push(T item)
{
	if (IsFull())
		throw ExceptionFullStack();
	else
	{
		top_++;
		items_[top_] = item;
	}
}


// Removes top item from the stack.
template<typename T>
T Stack<T>::Pop()
{
	T popped_element;

	if (IsEmpty()) {
		throw ExceptionEmptyStack();
	}
	else
	{
		popped_element = GetTopElement();
		top_--;
		return popped_element;
	}
}


// Returns a copy of top item on the stack.
template<typename T>
T& Stack<T>::GetTopElement()
{
	// cast return type to non-const reference
	return const_cast<T&>(
		// calls const version of GetTopElement
		static_cast<const Stack<T>&>(*this).GetTopElement()
		);
}

template<typename T>
const T& Stack<T>::GetTopElement() const
{
	if (IsEmpty())
		throw ExceptionEmptyStack();
	else
		return items_[top_];
}

// Print all the items in the stack on output stream.
template<typename T>
ostream& operator<<(ostream& output_stream, const Stack<T>& stack_object) {
	// Stack 내의 모든 element 출력.
	for (int i = 0; i <= top; i++)
	{
		output_stream << items[i] << " ";
	}

	return output_stream;
}

// Initialize stack to size parameter.
template<typename T>
void Stack<T>::InitializeStack(int size)
{
	size_ = size;
	items_ = new T[size_];    // dynamically allocate items array
	top_ = -1;
}

#endif // _STACK_H