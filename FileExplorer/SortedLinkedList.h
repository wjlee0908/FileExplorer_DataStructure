#ifndef _SORTED_LINKED_LIST_H
#define _SORTED_LINKED_LIST_H

#include "LinkedList.h"

/**
*	Sorted list class for managing items.
*/
template <typename T>
class SortedLinkedList : public LinkedList<T>
{
	public:
	/**
	*	@brief	Add item into appropriate spot of this list.
	*	@pre	List is not full. item is not in list.
	*	@post	Item is inserted in this list.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Add(T item);
};

// Add item into this list.
template <typename T>
int SortedLinkedList<T>::Add(T item)
{
	ListNode<T>* new_node = new ListNode<T>;
	ListNode<T>* previous;	// 대상 전 노드의 next에 add하기 위해 생성
	bool is_inserted = false;

	new_node->data = item;
	new_node->next = NULL;

	// special case: 리스트가 비어있을 때는 new를 head로 지정
	if (IsEmpty()) {
		head_ = new_node;
		is_inserted = true;
	}

	// item보다 더 큰 노드 직전에 삽입
	ResetIterator();
	while (!IsEmpty()) {
		previous = iterator_;
		WalkIterator();

		if (new_node->data < iterator_->data) {
			if (previous != NULL) {
				previous->next = new_node;
			}
			else {
				// new node가 첫 노드보다 작으면 head로 지정
				head_ = new_node;
			}
			new_node->next = iterator_;

			is_inserted = true;
			break;
		}

		if (iterator_->next == NULL) {	// 가장 끝 노드 도달
			break;
		}
	}

	// 마지막이라면 iterator next = new
	if (is_inserted == false) {
		iterator_->next = new_node;
	}

	length_++;

	return 1;
}


#endif	// SORTED_LINKED_LIST