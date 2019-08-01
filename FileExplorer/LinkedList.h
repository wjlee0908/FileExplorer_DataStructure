#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H


/**
*	Structure for node to use in Unsorted Linked list.
*/
template <typename T>
struct ListNode
{
	T data;	///< A data for each node.
	ListNode* next;	///< A node pointer to point succeed node.
};


/**
*	Unsorted list class template for managing T type elements.
*/
template <typename T>
class LinkedList
{
public:
	/**
	*	default constructor.
	*/
	LinkedList(): 
		head_(nullptr), 
		iterator_(nullptr), 
		length_(0)
	{}

	/**
	*    copy constructor
	*/
	LinkedList(const LinkedList<T>& copied_object):
		LinkedList() {
		AssignCopy();
	}

	/**
	*	destructor.
	*/
	~LinkedList();

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
	virtual T* Add(const T& item);

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
	*	@brief	Retrieve list element whose key matches item's key (if present).
	*	@pre	Key member of item is initialized.
	*	@post	If there is an element whose key matches with item's key then the element's record is copied to the item.
	*	@return	1 if any element's primary key matches with item's, otherwise 0.
	*/
	int Get(T& item);

	/**
	*	@brief	Retrieve list element whose key matches item's key (if present).
	*	@pre	Key member of item is initialized.
	*	@post	found item's reference is returned
	*	@return	1 if any element's primary key matches with item's, otherwise 0.
	*/
	T& Get(const T& key) {
		// call const version and cast return value to non-const
		return const_cast<T&>(
			static_cast<const LinkedList<T>&>(*this).Get()
			);
	}

	/**
	*	@brief	Retrieve list element whose key matches item's key (if present, for const object).
	*	@pre	Key member of item is initialized.
	*	@post	found item's reference is returned
	*	@return	1 if any element's primary key matches with item's, otherwise 0.
	*/
	const T& Get(const T& key) const;

	/**
	*	@brief	Retrieve list element whose key matches item's key (if present).
	*	@pre	Key member of item is initialized.
	*	@post	none.
	*	@return	address of found item. if not found, returns NULL
	*/
	T* GetItemAddress(const T& item);

	/**
	*	@brief	Retrieve list element whose key matches item's key (if present). For const list.
	*	@pre	Key member of item is initialized.
	*	@post	none.
	*	@return	address of found item. if not found, returns NULL.
	*/
	const T* GetItemAddress(const T& item) const;

	/**
	*	@brief	Initialize current pointer for an iteration through the list.
	*	@pre	None.
	*	@post	current pointer is prior to list. current pointer has been initialized.
	*/
	void ResetIterator() const;

	/**
	*	@brief	Move iterator to next list node.
	*	@pre	element at current pointer is not last in list.
	*	@post	iterator is updated to next position.
	*   @return current iterating node pointer.
	*/
	ListNode<T>* WalkIterator() const;

	/**
	*	@brief	Get the next element in list.
	*	@pre	current pointer is defined. Element at current pointer is not last in list.
	*	@post	current pointer is updated to next position. item is a copy of element at current pointer.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int GetNextItem(T& item);

	/**
	*	@brief	Get last element of list
	*	@pre	list elements are set.
	*	@post	none.
	*   @return last element of this list
	*/
	ListNode<T>* GetTail();

	/**
	*	@brief	Get address of last item of list
	*	@pre	list elements are set.
	*	@post	none.
	*   @return address  of last item of this list
	*/
	T* GetTailItemAddress() {
		// cast const T* to non-const T*
		return const_cast<T*>(
			// call const version of GetTailItemAddress
			static_cast<const LinkedList<T>&>(*this).GetTailItemAddress()
		);
	}

	/**
	*	@brief	Get address of last item of list. For const object.
	*	@pre	list elements are set.
	*	@post	none.
	*   @return address  of last item of this list
	*/
	const T* GetTailItemAddress() const {
		if (GetTail() == nullptr) {
			return nullptr;
		}
		else {
			return &(GetTail()->data);
		}
	}

	/**
	*	@brief	Copy parameter list and assign to this list.
	*	@pre	copide_data is set.
	*	@post	list record is set.
	*   @param  copied_data    data to assign
	*   @return retrun this after assigning parameter.
	*/
	LinkedList<T>& operator= (const LinkedList<T>& copied_data);

protected:
	ListNode<T>* head_;	///< Pointer for pointing a first node.
	mutable ListNode<T>* iterator_;	///< Node pointer for pointing current iterating node.
	int length_;	///< Number of node in the list.

private:
	/**
	*	@brief	Copy parameter list and assign to this list. (deep copy)
	*	@pre	copide_object is set.
	*	@post	list is set.
	*   @param  copied_object    object to assign
	*/
	void AssignCopy(const LinkedList<T>& copied_object);
};

// Class destructor
template <typename T>
LinkedList<T>::~LinkedList()
{
	// 리스트의 모든 node 메모리 해제
	MakeEmpty();
}


// Initialize list to empty state.
template <typename T>
void LinkedList<T>::MakeEmpty()
{
	ListNode<T>* deleted_node;

	// 이미 비어있으면 수행하지 않음
	if (IsEmpty()) {
		return;
	}

	// head 옮겨가며 head 삭제
	while (length_ > 0) {
		deleted_node = head_;
		head_ = head_->next;
		delete deleted_node;

		length_--;
	}
}


// Get number of elements in the list.
template <typename T>
int LinkedList<T>::GetLength() const
{
	return length_;
}

// Returns whether the list is empty
template<typename T>
inline bool LinkedList<T>::IsEmpty() const
{
	return (length_ == 0);
}


// Add item into this list.
template <typename T>
T* LinkedList<T>::Add(const T& item)
{
	ListNode<T>* new_node = new ListNode<T>;

	new_node->data = item;
	new_node->next = NULL;

	// special case: 리스트가 비어있을 때는 new를 head로 지정
	if (IsEmpty()) {
		head_ = new_node;
	}
	else {
		// 맨 마지막 노드 뒤에 새 노드 붙임
		GetTail()->next = new_node;
	}

	length_++;

	return &(new_node->data);
}

//Delete item from this list.
template <typename T>
int LinkedList<T>::Delete(T item)
{
	bool moreToSearch, found;
	ListNode<T>* pre = NULL;	//변수 선언

	iterator_ = head_;
	found = false;
	moreToSearch = (iterator_ != NULL);	//변수 초기화

	while (moreToSearch && !found)	//리스트의 끝이 아니면서 아직 찾지 않았으면 반복한다.
	{
		if (item == iterator_->data)	//현재 가리키는 원소의 값과 item의 값이 일치할 때
		{
			found = true;	//찾았으므로 found 값 변경
			if (pre == NULL)
				head_ = iterator_->next;	//항목 이전에 다른 원소가 없을 때 항목의 다음 원소를 첫번째 원소로 한다.
			else
			{
				pre->next = iterator_->next;
				delete iterator_;
			}	//이전의 원소의 다음 원소를 '가리키는 항목의 다음 원소'로 바꾼다.
			length_--;	//리스트의 길이를 1 줄여준다.
		}
		else
		{
			pre = iterator_;
			iterator_ = iterator_->next;
			moreToSearch = (iterator_ != NULL);
		}	//일치하지 않을 때 다음 원소를 가리킨다. 단, pre는 지금의 원소를 가리킨다.
	}

	if (found)
		return 1;
	else
		return 0;	//삭제가 성공하면 1, 아니면 0을 리턴한다.
}

//Change value of item which is in this list.
template <typename T>
int LinkedList<T>::Replace(T item)
{
	bool moreToSearch, found;
	ListNode<T>* location;	//변수 선언

	location = head_;
	found = false;
	moreToSearch = (location != NULL);	//변수 초기화

	while (moreToSearch && !found)	//리스트의 끝이 아니면서 아직 찾지 않았으면 반복한다.
	{
		if (item == location->data)
		{
			found = true;
			location->data = item;
		}	//일치하는 항목을 찾았을 때 found의 값을 변경해주고 리스트의 항목에 item을 복사해준다.
		else
		{
			location = location->next;
			moreToSearch = (location != NULL);
		}	//찾지 못했을 때 다음 항목으로 location을 옮기고 그 값이 NULL이면 리스트의 끝이므로 moreToSearch의 값을 변경해준다.
	}

	if (found)
		return 1;
	else
		return 0;	//수정에 성공하면 1, 그렇지 못하면 0을 리턴한다.
}

// Retrieve list element whose key matches item's key (if present).
template <typename T>
int LinkedList<T>::Get(T& item)
{
	bool moreToSearch, is_found;
	ListNode<T>* location;	//변수 선언

	// 빈 리스트에서는 항상 못 찾음
	if (IsEmpty()) {
		return 0;
	}

	location = head_;
	is_found = false;
	moreToSearch = (location != NULL);	//변수 초기화

	while (moreToSearch && !is_found)	//리스트의 끝이 아니면서 아직 찾지 않았으면 반복한다.
	{
		if (item == location->data)
		{
			is_found = true;
			item = location->data;
		}	//일치하는 항목을 찾았을 때 found의 값을 변경해주고 item에 해당 항목을 복사해준다.
		else
		{
			location = location->next;
			moreToSearch = (location != NULL);
		}	//찾지 못했을 때 다음 항목으로 location을 옮기고 그 값이 NULL이면 리스트의 끝이므로 moreToSearch의 값을 변경해준다.
	}

	if (is_found)
		return 1;
	else
		return 0;	//찾으면 1, 그렇지 못하면 0을 리턴한다.
}

template<typename T>
const T& LinkedList<T>::Get(const T& key) const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
}

// Retrieve list element whose key matches item's key (if present).
template<typename T>
T* LinkedList<T>::GetItemAddress(const T& item)
{
	// cast const pointer to not-const pointer
	return const_cast<T*>(
		// call const version of GetItemAddress
		static_cast<const LinkedList<T>&>(*this).GetItemAddress(item);
	)
}

// const list version of GetItemAddress
template<typename T>
const T* LinkedList<T>::GetItemAddress(const T& item) const
{
	ResetIterator();

	if (IsEmpty()) {
		return NULL;
	}
	while (WalkIterator() != NULL) {
		if (iterator_->data == item) {
			return &(iterator_->data);
		}
	}

	return nullptr;
}

// Initializes iterator pointer to NULL
template <typename T>
void LinkedList<T>::ResetIterator() const
{
	iterator_ = NULL;
}

template<typename T>
ListNode<T>* LinkedList<T>::WalkIterator() const
{
	// current pointer가 초기화된 상태면 head 가리킴.
	if (iterator_ == NULL) {
		iterator_ = head_;
	}
	else {
		// iterator를 다음 노드로 이동
		iterator_ = iterator_->next;
	}

	return iterator_;
}


// Gets the next element in list.
template <typename T>
int LinkedList<T>::GetNextItem(T& item)
{
	WalkIterator();

	if (iterator_ != NULL) {
		// 하나 증가한 노드의 data를 레퍼런스로 전달
		item = iterator_->data;
		return 1;
	}
	else {
		// 마지막 노드에서 walk 했을 경우
		return 0;
	}
}

// Copy parameter list and assign to this list when using = operator.
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& copied_data)
{
	AssignCopy(copied_data);

	return *this;
}

// Copy parameter list and assign to this list. (deep copy)
template<typename T>
void LinkedList<T>::AssignCopy(const LinkedList<T> & copied_object)
{
	ListNode<T>* node = copied_object.head_;	// node for iteration

	// 빈 리스트에 복사 대상의 아이템 모두 삽입
	MakeEmpty();
	while (node != nullptr) {
		this->Add(node->data);
		node = node->next;
	}
}

// Get last element of list
template<typename T>
ListNode<T>* LinkedList<T>::GetTail() {
	ResetIterator();
	while (WalkIterator()) {
		if (iterator_->next == NULL) {
			return iterator_;
		}
	}

	// 혹시 몰라서 기본
	return NULL;
}



#endif	// LINKED_LIST

