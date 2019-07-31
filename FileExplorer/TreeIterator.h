#pragma once
#ifndef _TREE_ITERATOR_H
#define _TREE_ITERATOR_H

#include "BinarySearchTree.h"
#include "Stack.h"
#include <stdexcept>

/**
*	template 참조 에러 방지
*/
template <typename T>
class BinarySearchTree;

/**
*	template 참조 에러 방지
*/
template <typename T>
struct Node;

/**
*	Iterator class for BinarySearchTree.
*/
template <typename T>
class TreeIterator {
	friend class BinarySearchTree<T>;
public:
	/**
	*	Initialize tree_ and current_node_. (constructor overloading)
	*/
	TreeIterator(const BinarySearchTree<T>& tree) : tree_(tree), current_node_(tree.root_) {}

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
	*	@brief	Get first data of the tree.
	*	@pre	Iterator has been initialized.
	*	@post	Current pointer is moved to the first node.
	*	@return	Return first data of the tree.
	*/
	T& First();

	/**
	*	@brief	Get next data of the current pointer.
	*	@pre	Iterator has been initialized.
	*	@post	Current pointer is moved to the next node.
	*	@return	Return next data of the tree. if next is null, return current data.
	*/
	T& Next();

	/**
	*	@brief	Get current node of the tree
	*	@pre	Iterator has been initialized.
	*	@post	out_node is assigned to current_node reference.
	*	@return	true if current node exist, otherwise false.
	*/
	Node<T>* GetCurrentNode() {
		// call const version of GetCurrentNode and cast return value to non-const
		return const_cast<Node<T>*>(
			static_cast<const TreeIterator<T>&>(*this).GetCurrentNode()
			);
	}

	/**
	*	@brief	Get current node of the tree. For const iterator.
	*	@pre	Iterator has been initialized.
	*	@post	out_node is assigned to current_node reference.
	*	@return	true if current node exist, otherwise false.
	*/
	const Node<T>* GetCurrentNode() const;

	/**
	*	@brief	Get current item of the tree
	*	@pre	Iterator has been initialized.
	*	@post	None
	*	@return	current item reference.
	*/
	T& operator*() {
		// call const version of GetCurrentNode and cast return value to non-const
		return const_cast<T&>(
			static_cast<const TreeIterator<T>&>(*this).operator*()
			);
	}

	/**
	*	@brief	Get current item of the tree. For const iteator
	*	@pre	Iterator has been initialized.
	*	@post	None
	*	@return	current item reference.
	*/
	const T& operator*() const;

	/**
	*	@brief	Reference current item of the tree
	*	@pre	Iterator has been initialized.
	*	@post	None
	*	@return	current item reference.
	*/
	T& operator->() {
		// call const version of GetCurrentNode and cast return value to non-const
		return const_cast<T&>(
			static_cast<const TreeIterator<T>&>(*this).operator->()
			);
	}

	/**
	*	@brief	Reference current item of the tree
	*	@pre	Iterator has been initialized.
	*	@post	None
	*	@return	current item reference.
	*/
	const T& operator->() const;

private:
	/**
	*	@brief  Push all left nodes into stack
	*	@pre	node has been initialized
	*	@post	left nodes are stored in stack.
	*/
	void PushAll(Node<T>* node);

	const BinarySearchTree<T>& tree_;	///< tree for iterating
	Node<T>* current_node_;	///< Node pointer for pointing current node to iterate.
	Stack<Node<T>*> stack_;   ///< stack for store next node to traversal
};


// Returns whether pointer of current node is null.
template <typename T>
bool TreeIterator<T>::IsNull() const {
	if (current_node_ == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

// Returns whether pointer of next node is null.
template <typename T>
bool TreeIterator<T>::IsNextNull() const{
	if (!stack_.IsEmpty()) {	// pop할 노드 없으면 next null
		return true;
	}
	else {
		return false;
	}
}

// Get first data of the tree.
template <typename T>
T& TreeIterator<T>::First() {
	current_node_ = tree_.root_;
	if (tree_.IsEmpty()) {
		// throw std::out_of_range("Head(): tree is empty");
		return T(); // return dummy
	}

	return current_node_->data;
}

// Get next data of the current pointer.
template <typename T>
T& TreeIterator<T>::Next() {
	if (IsNull()) {
		throw std::out_of_range("Next() : current node is NULL");
	}

	Node<T> original_node = (*current_node_);
	Node<T>* next_node = stack_.Pop();
	PushAll(next_node->right);

	current_node_ = next_node;
	if (IsNull()) {
		return original_node.data;    // return original node if next is null.
	}
	return current_node_->data;
}

// Get current node of the tree
template <typename T>
const Node<T>* TreeIterator<T>::GetCurrentNode() const {
	if (IsNull()) {
		throw std::invalid_argument("GetCurrentNode(): current node is null");
		return nullptr;
	}
	else {
		return current_node_;
	}
}

template<typename T>
const T & TreeIterator<T>::operator*() const
{
	if (IsNull()) {
		throw invalid_argument("iterating item is null");
	}
	return current_node_->data;
}

template<typename T>
const T & TreeIterator<T>::operator->() const
{
	if (IsNull()) {
		throw invalid_argument("iterating item is null");
	}
	return current_node_->data;
}

#endif // !_TREE_ITERATOR_H

// Push all left nodes into stack
template<typename T>
void TreeIterator<T>::PushAll(Node<T>* node)
{
	while (node != nullptr) {
		stack_.Push(node);
		node = node->left;
	}
}
