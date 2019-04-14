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
	*	@return	retrun address of created item if works well, oterwise return NULL;
	*/
	T* Add(T item);

	/**
	*	@brief	Change value of item which is in this list.
	*	@pre	List is not empty. the item exists in list.
	*	@post	Item's value is changed.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Replace(T item_changed, T item_to_change);

private:
	/**
	*	@brief	Insert node in sorted location
	*	@pre	List is sorted.
	*	@post	Node is inserted in sorted location.
	*   @param  address of node to insert.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int InsertNodeSorted(ListNode<T>* node);
};

// Add item into this list.
template <typename T>
T* SortedLinkedList<T>::Add(T item)
{
	ListNode<T>* new_node = new ListNode<T>;
	ListNode<T>* previous;	// ��� �� ����� next�� add�ϱ� ���� ����
	bool is_inserted = false;

	new_node->data = item;
	new_node->next = NULL;

	if (InsertNodeSorted(new_node) == 1) {
		length_++;
	}

	return &(new_node->data);
}

// Change value of item which is in this list.
template<typename T>
int SortedLinkedList<T>::Replace(T item_changed, T item_to_change)
{
	ListNode<T>* previous = NULL;
	ListNode<T>* replaced_node = NULL;

	ResetIterator();
	while (WalkIterator() != NULL) {
		if (iterator_ == item_changed) {
			iterator_->data = item_to_change;
			// ��� �յ� ���� ����
			if (previous != NULL) {
				previous->next = iterator_->next;
			}
			iterator_->next = NULL;
			replaced_node = iterator_;
			break;
		}
		previous = iterator_;
	}

	// �� ã������ ����
	if (replaced_node == NULL) {
		return 1;
	}

	// �ٲ� ��� ������
	InsertNodeSorted(replaced_node);

	return 0;
}

// Insert node in sorted location
template<typename T>
int SortedLinkedList<T>::InsertNodeSorted(ListNode<T>* node)
{
	ListNode<T>* previous;	// ��� �� ����� next�� �����ϱ� ���� ����
	bool is_inserted = false;

	// special case: ����Ʈ�� ������� ���� new�� head�� ����
	if (IsEmpty()) {
		head_ = node;
		is_inserted = true;
	}
	else {
		// item���� �� ū ��� ������ ����
		ResetIterator();
		while (!IsEmpty()) {
			previous = iterator_;
			WalkIterator();

			if (node->data < iterator_->data) {
				if (previous != NULL) {
					previous->next = node;
				}
				else {
					// new node�� ù ��庸�� ������ head�� ����
					head_ = node;
				}
				node->next = iterator_;

				is_inserted = true;
				break;
			}

			if (iterator_->next == NULL) {	// ���� �� ��� ����
				break;
			}
		}

		// �������̶�� iterator next = new
		if (is_inserted == false) {
			iterator_->next = node;
		}
	}
	return 1;
}


#endif	// SORTED_LINKED_LIST