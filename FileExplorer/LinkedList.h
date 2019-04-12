#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H


/**
*	Structure for node to use in Unsortec Linked list.
*/
template <typename T>
struct ListNode
{
	T data;	///< A data for each node.
	ListNode* next;	///< A node pointer to point succeed node.
};


/**
*	Unsorted list class for managing items.
*/
template <typename T>
class LinkedList
{
public:
	/**
	*	default constructor.
	*/
	LinkedList();

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
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Add(T item);

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
	*	@post	none.
	*	@return	address of found item. if not found, returns NULL
	*/
	T* GetItemAddress(const T item);

	/**
	*	@brief	Initialize current pointer for an iteration through the list.
	*	@pre	None.
	*	@post	current pointer is prior to list. current pointer has been initialized.
	*/
	void ResetIterator();

	/**
	*	@brief	Move iterator to next list node.
	*	@pre	element at current pointer is not last in list.
	*	@post	iterator is updated to next position.
	*   @return current iterating node pointer.
	*/
	ListNode<T>* WalkIterator();

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
	*	@brief	Copy parameter list and assign to this list.
	*	@pre	copide_data is set.
	*	@post	list record is set.
	*   @param  copied_data    data to assign
	*   @return retrun this after assigning parameter.
	*/
	LinkedList<T>& operator= (const LinkedList<T>& copied_data);

protected:
	ListNode<T>* head_;	///< Pointer for pointing a first node.
	ListNode<T>* iterator_;	///< Node pointer for pointing current iterating node.
	int length_;	///< Number of node in the list.
};


// Class constructor
template <typename T>
LinkedList<T>::LinkedList()
{
	length_ = 0;
	head_ = NULL;
	iterator_ = NULL;
}


// Class destructor
template <typename T>
LinkedList<T>::~LinkedList()
{
	// ����Ʈ�� ��� node �޸� ����
	MakeEmpty();
}


// Initialize list to empty state.
template <typename T>
void LinkedList<T>::MakeEmpty()
{
	// head�� �ϳ��� �ű�� head�� ���ʷ� �����Ѵ�. 

	ListNode<T>* deleted_node;

	while (head_ != NULL) {
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
int LinkedList<T>::Add(T item)
{
	ListNode<T>* new_node = new ListNode<T>;

	new_node->data = item;
	new_node->next = NULL;

	// special case: ����Ʈ�� ������� ���� new�� head�� ����
	if (IsEmpty()) {
		head_ = new_node;
	}
	else {
		// �� ������ ��� �ڿ� �� ��� ����
		GetTail()->next = new_node;
	}

	length_++;

	return 1;
}

//Delete item from this list.
template <typename T>
int LinkedList<T>::Delete(T item)
{
	bool moreToSearch, found;
	ListNode<T>* pre = NULL;	//���� ����

	iterator_ = head_;
	found = false;
	moreToSearch = (iterator_ != NULL);	//���� �ʱ�ȭ

	while (moreToSearch && !found)	//����Ʈ�� ���� �ƴϸ鼭 ���� ã�� �ʾ����� �ݺ��Ѵ�.
	{
		if (item == iterator_->data)	//���� ����Ű�� ������ ���� item�� ���� ��ġ�� ��
		{
			found = true;	//ã�����Ƿ� found �� ����
			if (pre == NULL)
				head_ = iterator_->next;	//�׸� ������ �ٸ� ���Ұ� ���� �� �׸��� ���� ���Ҹ� ù��° ���ҷ� �Ѵ�.
			else
			{
				pre->next = iterator_->next;
				delete iterator_;
			}	//������ ������ ���� ���Ҹ� '����Ű�� �׸��� ���� ����'�� �ٲ۴�.
			length_--;	//����Ʈ�� ���̸� 1 �ٿ��ش�.
		}
		else
		{
			pre = iterator_;
			iterator_ = iterator_->next;
			moreToSearch = (iterator_ != NULL);
		}	//��ġ���� ���� �� ���� ���Ҹ� ����Ų��. ��, pre�� ������ ���Ҹ� ����Ų��.
	}

	if (found)
		return 1;
	else
		return 0;	//������ �����ϸ� 1, �ƴϸ� 0�� �����Ѵ�.
}

//Change value of item which is in this list.
template <typename T>
int LinkedList<T>::Replace(T item)
{
	bool moreToSearch, found;
	ListNode<T>* location;	//���� ����

	location = head_;
	found = false;
	moreToSearch = (location != NULL);	//���� �ʱ�ȭ

	while (moreToSearch && !found)	//����Ʈ�� ���� �ƴϸ鼭 ���� ã�� �ʾ����� �ݺ��Ѵ�.
	{
		if (item == location->data)
		{
			found = true;
			location->data = item;
		}	//��ġ�ϴ� �׸��� ã���� �� found�� ���� �������ְ� ����Ʈ�� �׸� item�� �������ش�.
		else
		{
			location = location->next;
			moreToSearch = (location != NULL);
		}	//ã�� ������ �� ���� �׸����� location�� �ű�� �� ���� NULL�̸� ����Ʈ�� ���̹Ƿ� moreToSearch�� ���� �������ش�.
	}

	if (found)
		return 1;
	else
		return 0;	//������ �����ϸ� 1, �׷��� ���ϸ� 0�� �����Ѵ�.
}

// Retrieve list element whose key matches item's key (if present).
template <typename T>
int LinkedList<T>::Get(T& item)
{
	bool moreToSearch, found;
	ListNode<T>* location;	//���� ����

	location = head_;
	found = false;
	moreToSearch = (location != NULL);	//���� �ʱ�ȭ

	while (moreToSearch && !found)	//����Ʈ�� ���� �ƴϸ鼭 ���� ã�� �ʾ����� �ݺ��Ѵ�.
	{
		if (item == location->data)
		{
			found = true;
			item = location->data;
		}	//��ġ�ϴ� �׸��� ã���� �� found�� ���� �������ְ� item�� �ش� �׸��� �������ش�.
		else
		{
			location = location->next;
			moreToSearch = (location != NULL);
		}	//ã�� ������ �� ���� �׸����� location�� �ű�� �� ���� NULL�̸� ����Ʈ�� ���̹Ƿ� moreToSearch�� ���� �������ش�.
	}

	if (found)
		return 1;
	else
		return 0;	//ã���� 1, �׷��� ���ϸ� 0�� �����Ѵ�.
}

// Retrieve list element whose key matches item's key (if present).
template<typename T>
T * LinkedList<T>::GetItemAddress(const T item)
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

	return NULL;
}

// Initializes iterator pointer to NULL
template <typename T>
void LinkedList<T>::ResetIterator()
{
	iterator_ = NULL;
}

template<typename T>
ListNode<T>* LinkedList<T>::WalkIterator()
{
	// current pointer�� �ʱ�ȭ�� ���¸� head ����Ŵ.
	if (iterator_ == NULL) {
		iterator_ = head_;
	}
	else {
		// iterator�� ���� ���� �̵�
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
		// �ϳ� ������ ����� data�� ���۷����� ����
		item = iterator_->data;
		return 1;
	}
	else {
		// ������ ��忡�� walk ���� ���
		return 0;
	}
}

// Copy parameter list and assign to this list.
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& copied_data)
{
	ListNode* node = copied_data.head_;
	T copied_item;

	// �� ����Ʈ�� ���� ����� ������ ��� ����
	MakeEmpty();
	while (node != NULL) {
		copied_item = node->item;
		this->Add(copied_item);
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
}



#endif	// LINKED_LIST

