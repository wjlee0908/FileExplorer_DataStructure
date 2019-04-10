#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H


/**
*	Structure for node to use in Linked list.
*/
template <typename T>
struct ListNode
{
	T data;	///< A data for each node.
	ListNode* next;	///< A node pointer to point succeed node.
};


/**
*	Sorted list class for managing items.
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
	*	@brief	Add item into appropriate spot of this list.
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
	*/
	void GetNextItem(T& item);

private:
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


// Add item into this list.
template <typename T>
int LinkedList<T>::Add(T item)
{
	ResetIterator();

	// ����Ʈ�� �߰��� ���ο� node ��ü�� ���� ��带 ����ų ������ ����
	ListNode<T> *node = new ListNode<T>;
	ListNode<T> *pre;
	T dummy;
	bool bFound = false;

	// node ��ü�� �Է¹��� ������ ���� �� �ʱ�ȭ
	node->data = item;
	node->next = NULL;

	// list �� node �� �������� �ʴ� ���
	if (!length_)
	{
		head_ = node;
	}
	// list �� node �� �ϳ� �̻� �����ϴ� ���
	else
	{
		// ���� ������ node �� �̵� �� ����
		while (1)
		{
			// ���� ��带 ����Ű�� ������ ����
			pre = iterator_;

			// iteration �� �̿��� node ������ ����.
			GetNextItem(dummy);

			if (iterator_->data > node->data)
			{
				if (pre == NULL)
				{
					node->next = iterator_;
					head_ = node;
					break;
				}	//���� �ڸ� �� ���Ұ� �������� ���� �� ù��° ���ҷ� ����.
				node->next = iterator_;
				pre->next = node;
				break;
			}	//���� ����Ű�� ������ data���� node�� data������ Ŭ ��� pre ���ڸ��� ����.

			// node �����Ͱ� ������ node �� ����Ű�� �� �ڿ� ���ο� node ����.
			if (iterator_->next == NULL)
			{
				// ������ node �� ���ο� node ����
				iterator_->next = node;
				break;
			}
		}
	}

	length_++;

	return 1;

	////////////////////////////////

	ListNode<T>* new_node = new ListNode<T>;
	ListNode<T>* previous;	// ��� �� ����� next�� add�ϱ� ���� ����

	new_node->data = item;
	new_node->next = NULL;

	while (WalkIterator() != NULL) {
		previous = iterator_;
		// iteartor walk
		WalkIterator();

		// iterator �� new node ��
		// iterator �� ũ�ٸ�
		if (new_node->data < iterator_->data) {
			// prev next = new node, new node next = iterator, length ++
			// new node�� ù ��庸�� ������ ���� �� ��
			if (previous == NULL) {
				head_ = new_node;
			}
			previous->next = new_node;
			new_node->next = iterator_;

		}
		
		// special case : length == 0, head = new
		// �������̶�� iterator next = new

	}
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


// Initializes iterator pointer to NULL
template <typename T>
void LinkedList<T>::ResetIterator()
{
	iterator_ = NULL;
}

template<typename T>
inline ListNode<T>* LinkedList<T>::WalkIterator()
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
void LinkedList<T>::GetNextItem(T& item)
{
	// �ϳ� ������ ����� data�� ���۷����� ����
	item = WalkIterator()->data;
}


#endif	// LINKED_LIST