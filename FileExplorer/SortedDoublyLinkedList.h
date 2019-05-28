#ifndef _SORTED_DOUBLY_LINKED_LIST_H
#define _SORTED_DOUBLY_LINKED_LIST_H

#include "DoublyLinkedList.h"

/**
*	Sorted list class for managing items.
*/
template <typename T>
class SortedDoublyLinkedList : public DoublyLinkedList<T>
{
public:
	/**
	*	@brief	Add item into appropriate spot of this list.
	*	@pre	List is not full. item is not in list.
	*	@post	Item is inserted in this list.
	*	@return	retrun address of created item if works well, oterwise return NULL;
	*/
	virtual T* Add(T item) override;

	/**
	*	@brief	Change key of item which is in this list.
	*	@pre	List is not empty. the item exists in list.
	*	@post	Item's key is changed. item is rearranged.
	*   @param  original_item    item to change name
	*   @param  changed_item    item that its key is changed
	*	@return	true if this function works well, otherwise false.
	*/
	bool ChangeItemKey(T original_item, T changed_item);

private:
	/**
	*	@brief	Insert node in sorted location
	*	@pre	List is sorted.
	*	@post	Node is inserted in sorted location.
	*   @param  address of node to insert.
	*	@return	true if this function works well, otherwise false.
	*/
	bool InsertNodeSorted(DoublyPointingNode<T>* node);
	/**
	*	@brief	Finds the item that its key duplicates in the list and return its result.
	*	@pre	items key is set.
	*	@post	none.
	*   @param  item_check    item to check duplication.
	*   @return retruns boolean expresses whether duplicated item is exist.
	*/
	bool IsDupliactedItemExists(T item_check);
};

// Add item into this list.
template <typename T>
T* SortedDoublyLinkedList<T>::Add(T item)
{
	DoublyPointingNode<T>* new_node = new DoublyPointingNode<T>;

	new_node->data = item;
	new_node->previous = nullptr;
	new_node->next = nullptr;

	// 노드 순서 맞는 위치에 삽입
	InsertNodeSorted(new_node);

	return &(new_node->data);
}

// Change value of item which is in this list.
template<typename T>
bool SortedDoublyLinkedList<T>::ChangeItemKey(T original_item, T changed_item)
{
	// DoublyPointingIterator<T> iter(this*);
	DoublyPointingNode<T>* replaced_node;
	bool is_found = false;

	// 중복 검사
	if (IsDupliactedItemExists(changed_item)) {
		return false;
	}

	// original이랑 같은 노드를 찾음
	replaced_node = GetNode(original_item);

	// 실패하면 종료
	if (replaced_node == nullptr) {
		return false;
	}

	// 그 노드의 데이터를 changed_item으로 바꿈
	replaced_node->data = changed_item;

	// 리스트 연결 해제
	replaced_node->previous->next = replaced_node->next;
	replaced_node->next->previous = replaced_node->previous;
	length_--;

	// 재정렬
	InsertNodeSorted(replaced_node);

	return true;
}

// Insert node in sorted location
template<typename T>
bool SortedDoublyLinkedList<T>::InsertNodeSorted(DoublyPointingNode<T>* node)
{
	TreeIterator<T> iterator(*this);
	DoublyPointingNode<T>* current_node;
	bool is_inserted = false;

	// special case: 리스트가 비어있을 때는 입력받은 node를 head로 지정
	if (IsEmpty()) {
		head_ = node;
		tail_ = node;
		node->previous = nullptr;
		node->next = nullptr;
		is_inserted = true;
	}
	else {
		// 리스트 끝까지 탐색
		while (!iterator.IsNull()) {
			current_node = iterator.GetCurrentNode();
			// item보다 더 큰 노드 직전에 삽입
			if (node->data < current_node->data) {
				if (current_node == head_) {
					// new node가 첫 노드보다 작으면 head로 지정
					head_ = node;
					node->previous = nullptr;
				}
				else {
					current_node->previous->next = node;
					node->previous = current_node->previous;
				}
				node->next = current_node;
				current_node->previous = node;

				is_inserted = true;
				break;
			}
			else {
				// 다음 노드 탐색
				iterator.Next();
			}
		}

		// 마지막이라면 tail next = new
		if (is_inserted == false) {
			tail_->next = node;
			node->previous = tail_;
			node->next = nullptr;
			tail_ = node;
		}
	}

	length_++;

	return true;
}

template<typename T>
bool SortedDoublyLinkedList<T>::IsDupliactedItemExists(T item_check)
{
	if (Get(item_check)) {
		return true;
	}

	return false;
}


#endif	// SORTED_LINKED_LIST