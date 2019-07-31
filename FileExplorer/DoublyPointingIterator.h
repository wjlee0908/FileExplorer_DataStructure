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
	bool IsNull() const;

	/**
	*	@brief	Returns whether pointer of next node is null.
	*	@pre	Iterator has been initialized.
	*	@post	None.
	*	@return	nullptr true, otherwise false.
	*/
	bool IsNextNull() const;

	/**
	*	@brief	Get first data of the list. For const iterator.
	*	@pre	Iterator has been initialized.
	*	@post	Current pointer is moved to the first node.
	*	@return	Return first data of the list.
	*/
	T& First();

	/**
	*	@brief	Get next data of the current pointer. For const iterator.
	*	@pre	Iterator has been initialized.
	*	@post	Current pointer is moved to the next node.
	*	@return	Return next data of the list. if next is null, return current data.
	*/
	T& Next();

	/**
	*	@brief	Get current node of the list
	*	@pre	Iterator has been initialized.
	*	@post	out_node is assigned to current_node reference.
	*	@return	true if current node exist, otherwise false.
	*/
	DoublyPointingNode<T>* GetCurrentNode() {
		// call const version of GetCurrentNode() and cast return value to non-const
		return const_cast<DoublyPointingNode<T>*>(
			static_cast<const DoublyPointingIterator<T>&>(*this).GetCurrentNode()
			);
	}

	/**
	*	@brief	Get current node of the list.
	*	@pre	Iterator has been initialized.
	*	@post	out_node is assigned to current_node reference.
	*	@return	true if current node exist, otherwise false.
	*/
	const DoublyPointingNode<T>* GetCurrentNode() const;


	/**
	*	@brief	Get current item of the list
	*	@pre	Iterator has been initialized.
	*	@post	None
	*	@return	current item reference. 
	*/
	T& operator*() {
		// call const version of operator*() and cast return value to non-const
		return const_cast<T&>(
			static_cast<const DoublyPointingIterator<T>&>*(*this)
			);
	}

	/**
	*	@brief	Get current item of the list. For const iterator.
	*	@pre	Iterator has been initialized.
	*	@post	None
	*	@return	current item reference.
	*/
	const T& operator*() const;

	/**
	*	@brief	Reference current item of the list
	*	@pre	Iterator has been initialized.
	*	@post	None
	*	@return	current item reference.
	*/
	T& operator->() {
		// call const version of operator->() and cast return value to non-const
		return const_cast<T&>(
			static_cast<const DoublyPointingIterator<T>&>(*this).operator->()
			);
	}

	/**
	*	@brief	Reference current item of the list
	*	@pre	Iterator has been initialized.
	*	@post	None
	*	@return	current item reference.
	*/
	const T& operator->() const;

private:
	const DoublyLinkedList<T>& list_;	///< list for iterating
	DoublyPointingNode<T>* current_node_;	///< Node pointer for pointing current node to iterate.
};


// Returns whether pointer of current node is null.
template <typename T>
bool DoublyPointingIterator<T>::IsNull() const{
	if (current_node_ == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

// Returns whether pointer of next node is null.
template <typename T>
bool DoublyPointingIterator<T>::IsNextNull() const{
	if (current_node_ == nullptr || current_node_->next == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

// Get first data of the list.
template <typename T>
T& DoublyPointingIterator<T>::First(){
	current_node_ = list_.head_;
	if (list_.IsEmpty()) {
		throw std::out_of_range("Head(): list is empty");
		//return T(); // return dummy
	}

	return current_node_->data;
}

// Get next data of the current pointer.
template <typename T>
T& DoublyPointingIterator<T>::Next(){
	if (IsNull()) {
		throw std::out_of_range("Next() : current node is NULL");
	}

	DoublyPointingNode<T> original_node = (*current_node_);
	current_node_ = current_node_->next;
	if (IsNull()) {
		return original_node.data;    // return original node if next is null.
	}
	return current_node_->data;
}

// Get current node of the list
template <typename T>
const DoublyPointingNode<T>* DoublyPointingIterator<T>::GetCurrentNode() const {
	if (IsNull()) {
		throw std::invalid_argument("GetCurrentNode(): current node is null");
		return nullptr;
	}
	else {
		return current_node_;
	}
}

template<typename T>
const T & DoublyPointingIterator<T>::operator*() const
{
	if (IsNull()) {
		throw invalid_argument("iterating item is null");
	}
	return current_node_->data;
}

template<typename T>
const T & DoublyPointingIterator<T>::operator->() const
{
	if (IsNull()) {
		throw invalid_argument("iterating item is null");
	}
	return current_node_->data;
}

#endif // !_DOUBLY_POINTING_ITERATOR_H
