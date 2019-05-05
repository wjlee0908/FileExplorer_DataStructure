#pragma once
#ifndef _DOUBLY_LINKED_LIST_H
#define _DOUBLY_LINKED_LIST_H

/**
*	Structure for NodeType to use in Linked structure.
*/

template <typename T>
class DoublyPointingIterator;

template <typename T>
struct DoublyPointingNode
{
	T data;    ///< A data for each node.
	DoublyPointingNode* previous;	///< A node pointer of previous node.
	DoublyPointingNode* next;	///< A node pointer of next node.
};


/**
*	Single sorted list class for managing items.
*/
template <typename T>
class DoublyLinkedList
{
	friend class DoublyPointingIterator<T>;
public:
	/**
	*	default constructor.
	*/
	DoublyLinkedList();

	/**
	*	destructor.
	*/
	~DoublyLinkedList();

	/**
	*    copy constructor
	*/
	DoublyLinkedList(const DoublyLinkedList<T>& copied_object)
	{
		AssignCopy();
	}

	/**
	*	@brief	Initialize list to empty state.
	*	@pre	None
	*	@post	List is empty. All nodes are deallocated.
	*/
	void MakeEmpty();

	/**
	*	@brief	Get number of elements in the list.
	*	@pre	None.
	*	@post	Function value = number of elements in list.
	*	@return	Number of elements in this list.
	*/
	int GetLength() const;

	/**
     *	@brief	Returns whether the list is full.
     *	@pre	List has been initialized.
     *	@post	None.
     *	@return	If there is not memory left, throws bad_alloc exception and return true
	 *          otherwise false.
     */
	bool IsFull() const;

	/**
	*	@brief	Returns whether the list is empty.
	*	@pre	None.
	*	@post	None.
	*	@return	boolean that expresses whether the list is empty.
	*/
	bool IsEmpty() const;

	/**
	*	@brief	Add item into last of this list.
	*	@pre	List is not full. item is not in list.
	*	@post	Item is inserted in this list.
	*	@return	retrun address of created item if works well, oterwise return NULL;
	*/
	virtual T* Add(T item);

	/**
	*	@brief	Delete item from this list.
	*	@pre	List is not empty. the item exists in list.
	*	@post	Item is deleted from this list.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Delete(T item);

	/**
	*	@brief	Change value of item which is in this list.
	*	@pre	List is not empty. the item exists in list.
	*	@post	Item's value is changed.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Replace(T item);

	/**
	*	@brief	Returns list element whose key matches item's key (if present).
	*	@pre	Key member of item is initialized.
	*	@post	If there is an element whose key matches with item's key then the element's record is assigned to the item.
	*	@return	1 if any element's primary key matches with item's, otherwise 0.
	*/
	bool Get(T& item);

	/**
	*	@brief	Returns list node whose key matches item's key (if present).
	*	@pre	Key member of item is initialized.
	*	@post	If there is an element whose key matches with item's key then found node is assgined to found_node.
	*	@return	true if any element's primary key matches with item's, otherwise false.
	*/
	bool GetNode(T& item, DoublyPointingNode<T>& found_node);

	/**
	*	@brief	Retrieve list element whose key matches item's key (if present).
	*	@pre	Key member of item is initialized.
	*	@post	none.
	*	@return	address of found item. if not found, returns NULL
	*/
	T* GetItemAddress(const T item);

	/**
	*	@brief	Get last element of list
	*	@pre	list elements are set.
	*	@post	none.
	*   @return last element of this list
	*/
	DoublyPointingNode<T>* GetTail();

	/**
	*	@brief	Get address of last item of list
	*	@pre	list elements are set.
	*	@post	none.
	*   @return address  of last item of this list
	*/
	T* GetTailItemAddress() {
		if (tail_ == NULL) {
			return NULL;
		}
		else {
			return &(tail_->data)
		}
	};

	/**
	*	@brief	Copy parameter list and assign to this list.
	*	@pre	copide_data is set.
	*	@post	list record is set.
	*   @param  copied_data    data to assign
	*   @return retrun this after assigning parameter.
	*/
	DoublyLinkedList<T>& operator= (const DoublyLinkedList<T>& copied_data);

protected:
	DoublyPointingNode<T>* head_;	///< Pointer for pointing a first node.
	DoublyPointingNode<T>* tail_;   ///< Pointer for pointing a last node.
	int length_;	///< Number of node in the list.

private:
	/**
	*	@brief	Copy parameter list and assign to this list. (deep copy)
	*	@pre	copide_object is set.
	*	@post	list is set.
	*   @param  copied_object    object to assign
	*/
	void AssignCopy(const DoublyLinkedList<T>& copied_object);
};



// Class constructor
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
	length_ = 0;
	head_ = nullptr;
	tail_ = nullptr;
}


// Class destructor
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	// 리스트의 모든 node 메모리 해제
	MakeEmpty();
}


// Initialize list to empty state.
template <typename T>
void DoublyLinkedList<T>::MakeEmpty()
{
	DoublyPointingIterator<T> iterator(*this);
	DoublyPointingNode<T>* deleted_node;

	// 이미 비어있으면 수행하지 않음
	if (IsEmpty()) {
		return;
	}

	// head 옮겨가며 head 삭제
	while (length_ > 0) {
		deleted_node = iterator.current_node_;
		iterator.Next();
		delete deleted_node;

		length_--;
	}
}


// Get number of elements in the list.
template <typename T>
int DoublyLinkedList<T>::GetLength() const
{
	return length_;
}

// Returns whether the list is full.
template<typename T>
bool DoublyLinkedList<T>::IsFull() const
{
	// 메모리 할당 시도 후 실패하면 true 반환
	try {
		DoublyPointingNode<T>* temp = nullptr;	// if there is not memory left, temp would not be initialized as NULL
		delete temp;					// deleting temp(pointer) could not be executed.
		return false;
	}
	catch (bad_alloc& e_ba) {
		cerr << "bad_alloc exception caught : " << e_ba.what() << endl;
		return true;
	}
}

// Returns whether the list is empty
template<typename T>
inline bool DoublyLinkedList<T>::IsEmpty() const
{
	return (length_ == 0);
}


// Add item into this list.
template <typename T>
T* DoublyLinkedList<T>::Add(T item)
{
	DoublyPointingNode<T>* new_node = new DoublyPointingNode<T>;
	DoublyPointingIterator iterator(*this);

	new_node->data = item;
	new_node->previous = NULL:
	new_node->next = NULL;

	// special case: 리스트가 비어있을 때는 new를 head, tail로 지정
	if (IsEmpty()) {
		head_ = new_node;
		tail_ = new_node;
	}
	else {
		// 맨 마지막 노드 뒤에 새 노드 붙임
		tail_->next = new_node;
		new_node->previous = tail_;
		tail_ = new_node;
	}

	length_++;

	return &(new_node->data);
}

// Delete item from this list.
template <typename T>
int DoublyLinkedList<T>::Delete(T item)
{
	DoublyPointingNode<T> deleted_node;
	bool is_found = false;

	// item과 일치하는 노드 탐색해서 일치하는 노드 deleted_node에 할당
	is_found = GetNode(item, deleted_node);

	// item과 일치하는 노드 찾으면
	if (is_found) {
		// 현재 노드 앞뒤 노드의 next, previous가 현재 노드 건너뛰고 가리키게
		if (deleted_node.previous != nullptr) {
			deleted_node.previous->next = deleted_node.next;
		}
		if (deleted_node.next != nullptr) {
			deleted_node.next->previous = deleted_node.previous;
		}
		// 노드 메모리 해제
		delete deleted_node;
		length_--;
	}

	// 삭제가 성공하면 1, 아니면 0을 리턴한다.
	if (is_found)
		return 1;
	else
		return 0;	
}

// Change value of item which is in this list.
template <typename T>
int DoublyLinkedList<T>::Replace(T item)
{
	bool is_found;
	DoublyPointingNode<T> target_node;

	is_found = GetNode(item, target_node);

	if (is_found) {
		// 찾은 노드의 데이터를 대상 아이템으로 바꿈
		target_node.data = item;
		return 1;
	}
	else {
		return 0;
	}
}

// Retrieve list element whose key matches item's key (if present).
template <typename T>
bool DoublyLinkedList<T>::Get(T& item)
{
	DoublyPointingNode<T> found_node;    // 일치하는 아이템을 찾은 노드
	bool is_found;

	is_found = GetNode(item, found_node);

	if (is_found) {
		return true;
	}
	else {
		return false;
	}
}

// Returns list node whose key matches item's key (if present).
template<typename T>
bool DoublyLinkedList<T>::GetNode(T & item, DoublyPointingNode<T> & found_node)
{
	DoublyPointingIterator<T> iterator(this*);
	DoublyPointingNode<T> current_node;
	bool is_found = false;

	// 리스트 끝까지 탐색
	while (!iterator.IsNull()) {
		iterator.GetCurrentNode(current_node);
		// item과 일치하는 노드 찾음
		if (current_node.data == item) {
			// returns current node reference
			iterator.GetCurrentNode(found_node);
			is_found = true;
		}
		else {
			// 다음 노드 탐색
			iterator.Next();
		}
	}

	return is_found;
}

// Retrieve list element whose key matches item's key (if present).
// TODO: Get으로 대체
template<typename T>
T * DoublyLinkedList<T>::GetItemAddress(const T item)
{
	T found_item;
	Get(found_item);
	
	return &found_item;
}

// Copy parameter list and assign to this list when using = operator.
template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& copied_data)
{
	AssignCopy(copied_data);

	return *this;
}

// Copy parameter list and assign to this list. (deep copy)
template<typename T>
void DoublyLinkedList<T>::AssignCopy(const DoublyLinkedList<T> & copied_object)
{
	DoublyPointingNode<T>* node = copied_object.head_;	// node for iteration
	T copied_item;

	// 빈 리스트에 복사 대상의 아이템 모두 삽입
	MakeEmpty();
	while (node != NULL) {
		copied_item = node->data;
		this->Add(copied_item);
		node = node->next;
	}
}

// Get last element of list
template<typename T>
DoublyPointingNode<T>* DoublyLinkedList<T>::GetTail() {
	return tail_;
}

#endif	// DOUBLY_LINKED_LIST