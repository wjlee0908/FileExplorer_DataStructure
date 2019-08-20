#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <iostream>
#include <exception>

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
	LinkedList() :
		head_(nullptr),
		iterator_(nullptr),
		length_(0)
	{}

	/**
	*    copy constructor
	*/
	LinkedList(const LinkedList<T>& copied_object) :
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
	*	@post	Found item's reference is returned. Otherwise, throws exception.
	*	@return	Found item's reference
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
	*	@post	Found item's reference is returned. Otherwise, throws exception.
	*	@return	Found item's reference
	*/
	const T& Get(const T& key) const;

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
	*	@brief	Get the next element in list. (for const object)
	*	@pre	Current pointer is assigned. Element at current pointer is not last in list.
	*	@post	Current pointer is updated to next position.
	*	@return	1 if this function works well, otherwise 0.
	*/
	T& GetNextItem() {
		// call const version of function and cast return value to non const
		return const_cast<T&>(
			static_cast<const LinkedList<T>&>(*this).GetNextItem()
			);
	}

	/**
	*	@brief	Get the next element in list. (for const object)
	*	@pre	Current pointer is assigned. Element at current pointer is not last in list.
	*	@post	Current pointer is updated to next position. 
	*	@return	1 if this function works well, otherwise 0.
	*/
	const T& GetNextItem() const;

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
	// ����Ʈ�� ��� node �޸� ����
	MakeEmpty();
}


// Initialize list to empty state.
template <typename T>
void LinkedList<T>::MakeEmpty()
{
	ListNode<T>* deleted_node;

	// �̹� ��������� �������� ����
	if (IsEmpty()) {
		return;
	}

	// head �Űܰ��� head ����
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

	// special case: ����Ʈ�� ������� ���� new�� head�� ����
	if (IsEmpty()) {
		head_ = new_node;
	}
	else {
		// �� ������ ��� �ڿ� �� ��� ����
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
template<typename T>
const T& LinkedList<T>::Get(const T& key) const
{
	bool more_to_search, is_found;
	ListNode<T>* location;	//���� ����

	// �� ����Ʈ������ �׻� �� ã��
	if (IsEmpty()) {
		throw std::out_of_range("Get(): list is empty");
	}

	location = head_;
	is_found = false;
	more_to_search = (location != nullptr);	//���� �ʱ�ȭ

	while (more_to_search && !is_found)	//����Ʈ�� ���� �ƴϸ鼭 ���� ã�� �ʾ����� �ݺ��Ѵ�.
	{
		if (key == location->data)
		{
			is_found = true;
			return location->data;
		}	//��ġ�ϴ� �׸��� ã���� �� found�� ���� �������ְ� �ش� �������� ����
		else
		{
			location = location->next;
			more_to_search = (location != nullptr);
		}	//ã�� ������ �� ���� �׸����� location�� �ű�� �� ���� NULL�̸� ����Ʈ�� ���̹Ƿ� moreToSearch�� ���� �������ش�.
	}

	if (!is_found) {
		throw std::invalid_argument("Get(): key is not found");
	}

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
const T& LinkedList<T>::GetNextItem() const
{
	WalkIterator();

	if (iterator_ != nullptr) {
		// �ϳ� ������ ����� data�� ��ȯ
		return iterator_->data;
	}
	else {
		// ������ ��忡�� walk ���� ���
		throw std::out_of_range("GetNextItem(): out of range");
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

	// �� ����Ʈ�� ���� ����� ������ ��� ����
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

	// Ȥ�� ���� �⺻
	return NULL;
}



#endif	// LINKED_LIST

