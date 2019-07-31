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
	virtual T* Add(const T& item) override;

	/**
	*	@brief	Change key of item which is in this list.
	*	@pre	List is not empty. the item exists in list.
	*	@post	Item's key is changed. item is rearranged.
	*   @param  original_item    item to change name
	*   @param  changed_item    item that its key is changed
	*	@return	1 if this function works well, otherwise 0.
	*/
	int ChangeItemKey(const T& original_item, const T& changed_item);

private:
	/**
	*	@brief	Insert node in sorted location
	*	@pre	List is sorted.
	*	@post	Node is inserted in sorted location.
	*   @param  address of node to insert.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int InsertNodeSorted(ListNode<T>* node);
	/**
	*	@brief	Finds the item that its key duplicates in the list and return its result.
	*	@pre	items key is set.
	*	@post	none.
	*   @param  item_check    item to check duplication.
	*   @return retruns boolean expresses whether duplicated item is exist.
	*/
	bool IsDupliactedItemExists(T item_check) const;
};

// Add item into this list.
template <typename T>
T* SortedLinkedList<T>::Add(const T& item)
{
	ListNode<T>* new_node = new ListNode<T>;

	new_node->data = item;
	new_node->next = NULL;
	
	// 노드 순서 맞는 위치에 삽입
	if (InsertNodeSorted(new_node) == 1) {
		length_++;
	}

	return &(new_node->data);
}

// Change value of item which is in this list.
template<typename T>
int SortedLinkedList<T>::ChangeItemKey(const T& original_item, const T& changed_item)
{
	ListNode<T>* previous = NULL;
	ListNode<T>* replaced_node = NULL;

	// 중복 검사
	if (IsDupliactedItemExists(changed_item)) {
		return 1;
	}

	ResetIterator();
	while (WalkIterator() != NULL) {
		if (iterator_->data == original_item) {
			iterator_->data = changed_item;

			// head일 경우 head값도 조정.
			if (iterator_ == head_) {
				head_ = iterator_->next;
			}

			// 노드 앞뒤 연결 해제
			if (previous != NULL) {
				previous->next = iterator_->next;
			}
			iterator_->next = NULL;
			replaced_node = iterator_;
			// 연결 해제했으니 length 낮춤. 나중에 다시 insert 위해.
			length_--;
			break;
		}
		previous = iterator_;
	}

	// 바꿀 아이템 못 찾았으면 종료
	if (replaced_node == NULL) {
		return 1;
	}

	// 바꾼 노드 재정렬
	InsertNodeSorted(replaced_node);

	return 0;
}

// Insert node in sorted location
template<typename T>
int SortedLinkedList<T>::InsertNodeSorted(ListNode<T>* node)
{
	ListNode<T>* previous;	// 대상 전 노드의 next에 삽입하기 위해 생성
	bool is_inserted = false;

	// special case: 리스트가 비어있을 때는 입력받은 node를 head로 지정
	if (IsEmpty()) {
		head_ = node;
		is_inserted = true;
	}
	else {
		// item보다 더 큰 노드 직전에 삽입
		ResetIterator();
		while (!IsEmpty()) {
			previous = iterator_;
			WalkIterator();

			if (node->data < iterator_->data) {
				if (previous != NULL) {
					previous->next = node;
				}
				else {
					// new node가 첫 노드보다 작으면 head로 지정
					head_ = node;
				}
				node->next = iterator_;

				is_inserted = true;
				break;
			}

			if (iterator_->next == NULL) {	// 가장 끝 노드 도달
				break;
			}
		}

		// 마지막이라면 iterator next = new
		if (is_inserted == false) {
			iterator_->next = node;
		}
	}
	return 1;
}

template<typename T>
bool SortedLinkedList<T>::IsDupliactedItemExists(T item_check) const
{
	if (Get(item_check) == 1) {
		return true;
	}

	return false;
}


#endif	// SORTED_LINKED_LIST