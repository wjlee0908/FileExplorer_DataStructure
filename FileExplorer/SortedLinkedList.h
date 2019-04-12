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
	ListNode<T>* previous;	// ��� �� ����� next�� add�ϱ� ���� ����
	bool is_inserted = false;

	new_node->data = item;
	new_node->next = NULL;

	// special case: ����Ʈ�� ������� ���� new�� head�� ����
	if (IsEmpty()) {
		head_ = new_node;
		is_inserted = true;
	}

	// item���� �� ū ��� ������ ����
	ResetIterator();
	while (!IsEmpty()) {
		previous = iterator_;
		WalkIterator();

		if (new_node->data < iterator_->data) {
			if (previous != NULL) {
				previous->next = new_node;
			}
			else {
				// new node�� ù ��庸�� ������ head�� ����
				head_ = new_node;
			}
			new_node->next = iterator_;

			is_inserted = true;
			break;
		}

		if (iterator_->next == NULL) {	// ���� �� ��� ����
			break;
		}
	}

	// �������̶�� iterator next = new
	if (is_inserted == false) {
		iterator_->next = new_node;
	}

	length_++;

	return 1;
}


#endif	// SORTED_LINKED_LIST