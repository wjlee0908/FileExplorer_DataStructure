#ifndef _DOUBLY_POINTING_ITERATOR_H
#define _DOUBLY_POINTING_ITERATOR_H

#include "DoublyLinkedList.h"
#include <stdexcept>

/**
*	template 참조 에러 방지
*/
template <typename T>
class DoublyLinkedList;

/**
*	template 참조 에러 방지
*/
template <typename T>
struct DoublyPointingNode;

/**
*	Iterator class for DoublyLinkedList.  (not using header and trailer nodes).
*/
template <typename T>
class DoublyPointingIterator {
	friend class DoublyLinkedList<T>;
public:
	/**
	*	Initialize list_ and current_node_. (constructor overloading)
	*/
	DoublyPointingIterator(const DoublyLinkedList<T>& list) : list_(list), current_node_(list.head_) {}

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
	*	@brief	Get current node of the list
	*	@pre	Iterator has been initialized.
	*	@post	out_node is assigned to current_node reference.
	*	@return	true if current node exist, otherwise false.
	*/
	bool GetCurrentNode(DoublyPointingNode<T>& out_node);

private:
	const DoublyLinkedList<T>& list_;	///< list for iterating
	DoublyPointingNode<T>* current_node_;	///< Node pointer for pointing current node to iterate.
};


// Returns whether pointer of current node is null.
template <typename T>
bool DoublyPointingIterator<T>::IsNull() {
	if (current_node_ == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

// Returns whether pointer of next node is null.
template <typename T>
bool DoublyPointingIterator<T>::IsNextNull() {
	if (current_node_ == nullptr || current_node_->next == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

// Get first data of the list.
template <typename T>
T DoublyPointingIterator<T>::Head() {
	if (list_.IsEmpty()) {
		throw std::out_of_range("Head(): list is empty");
	}
	else {
		current_node_ = list_.head_;
		return current_node_->data;
	}
}

// Get next data of the current pointer.
template <typename T>
T DoublyPointingIterator<T>::Next() {
	if (!IsNextNull()) {
		current_node_ = current_node_->next;
	}
	return current_node_->data;
}

// Get current node of the list
template <typename T>
bool DoublyPointingIterator<T>::GetCurrentNode(DoublyPointingNode<T>& out_node) {
	if (IsNull()) {
		throw std::invalid_argument("GetCurrentNode(): current node is null");
		return false;
	}
	else {
		out_node = *current_node_;
		return true;
	}
}

#endif // !_DOUBLY_POINTING_ITERATOR_H
