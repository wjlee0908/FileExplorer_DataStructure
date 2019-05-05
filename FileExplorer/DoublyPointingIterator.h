#ifndef _DOUBLY_POINTING_ITERATOR_H
#define _DOUBLY_POINTING_ITERATOR_H

#include "DoublyLinkedList.h"

/**
*	template 참조 에러 방지
*/
template <typename T>
class DoublySortedLinkedList;

/**
*	template 참조 에러 방지
*/
template <typename T>
struct DoublyNodeType;

/**
*	Iterator class for DoublySortedLinkedList.  (not using header and trailer nodes).
*/
template <typename T>
class DoublyIterator {
	friend class DoublySortedLinkedList<T>;
public:
	/**
	*	Initialize list_ and current_node_. (constructor overloading)
	*/
	DoublyIterator(const DoublySortedLinkedList<T>& list) : list_(list), current_node_(list.head_) {}

	/**
	*	@brief	Returns whether pointer of current node is null.
	*	@pre	Iterator has been initialized.
	*	@post	None.
	*	@return	nullptr true, otherwise false.
	*/
	bool IsNull();

	/**
	*	@brief	Returns whether pointer of next node is null.
	*	@pre	Iterator has been initialized.
	*	@post	None.
	*	@return	nullptr true, otherwise false.
	*/
	bool IsNextNull();

	/**
	*	@brief	Get first data of the list.
	*	@pre	Iterator has been initialized.
	*	@post	Current pointer is moved to the first node.
	*	@return	Return first data of the list.
	*/
	T Head();

	/**
	*	@brief	Get next data of the current pointer.
	*	@pre	Iterator has been initialized.
	*	@post	Current pointer is moved to the next node.
	*	@return	Return next data of the list.
	*/
	T Next();

	/**
	*	@brief	Get current data of the list and go to the next node. 
	*	@pre	Iterator has been initialized.
	*	@post	Current pointer is moved to next node.
	*	@return	Return current data of the list.
	*/
	DoublyNodeType<T> GetCurrentNode();




private:
	const DoublySortedLinkedList<T>& list_;	///< list for iterating
	DoublyNodeType<T>* current_node_;	///< Node pointer for pointing current node to iterate.
};


// Returns whether pointer of current node is null.
template <typename T>
bool DoublyIterator<T>::IsNull() {
	if (current_node_ == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

// Returns whether pointer of next node is null.
template <typename T>
bool DoublyIterator<T>::IsNextNull() {
	if (current_node_->next == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

// Get first data of the list.
template <typename T>
T DoublyIterator<T>::Head() {
	if (!(list_.IsEmpty())) {
		current_node_ = list_.head_;
		return current_node_->data;
	}
}

// 다음 node로 이동 후 item을 return.
template <typename T>
T DoublyIterator<T>::Next() {
	T output = current_node_->data;
	if (!IsNull()) {
		current_node_ = current_node_->next;
	}
	return output;
}

// 현재 node를 return
template <typename T>
DoublyNodeType<T> DoublyIterator<T>::GetCurrentNode() {
	if (current_node_ != nullptr) {
		return *current_node_;
	}
}




#endif // !_DOUBLY_POINTING_ITERATOR_H
