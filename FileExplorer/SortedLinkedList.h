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
	// 리스트의 모든 node 메모리 해제
	MakeEmpty();
}


// Initialize list to empty state.
template <typename T>
void LinkedList<T>::MakeEmpty()
{
	// head를 하나씩 옮기며 head를 차례로 제거한다. 

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

	// 리스트에 추가할 새로운 node 객체와 이전 노드를 가리킬 포인터 선언
	ListNode<T> *node = new ListNode<T>;
	ListNode<T> *pre;
	T dummy;
	bool bFound = false;

	// node 객체에 입력받은 데이터 설정 및 초기화
	node->data = item;
	node->next = NULL;

	// list 에 node 가 존재하지 않는 경우
	if (!length_)
	{
		head_ = node;
	}
	// list 에 node 가 하나 이상 존재하는 경우
	else
	{
		// 가장 마지막 node 로 이동 후 삽입
		while (1)
		{
			// 이전 노드를 가리키는 포인터 갱신
			pre = iterator_;

			// iteration 을 이용해 node 포인터 갱신.
			GetNextItem(dummy);

			if (iterator_->data > node->data)
			{
				if (pre == NULL)
				{
					node->next = iterator_;
					head_ = node;
					break;
				}	//넣을 자리 앞 원소가 존재하지 않을 때 첫번째 원소로 삽입.
				node->next = iterator_;
				pre->next = node;
				break;
			}	//지금 가리키는 원소의 data값이 node의 data값보다 클 경우 pre 뒷자리에 삽입.

			// node 포인터가 마지막 node 를 가리키면 그 뒤에 새로운 node 삽입.
			if (iterator_->next == NULL)
			{
				// 마지막 node 와 새로운 node 연결
				iterator_->next = node;
				break;
			}
		}
	}

	length_++;

	return 1;

	////////////////////////////////

	ListNode<T>* new_node = new ListNode<T>;
	ListNode<T>* previous;	// 대상 전 노드의 next에 add하기 위해 생성

	new_node->data = item;
	new_node->next = NULL;

	while (WalkIterator() != NULL) {
		previous = iterator_;
		// iteartor walk
		WalkIterator();

		// iterator 와 new node 비교
		// iterator 더 크다면
		if (new_node->data < iterator_->data) {
			// prev next = new node, new node next = iterator, length ++
			// new node가 첫 노드보다 작으면 수행 안 함
			if (previous == NULL) {
				head_ = new_node;
			}
			previous->next = new_node;
			new_node->next = iterator_;

		}
		
		// special case : length == 0, head = new
		// 마지막이라면 iterator next = new

	}
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
			item = location->data;
		}	//일치하는 항목을 찾았을 때 found의 값을 변경해주고 item에 해당 항목을 복사해준다.
		else
		{
			location = location->next;
			moreToSearch = (location != NULL);
		}	//찾지 못했을 때 다음 항목으로 location을 옮기고 그 값이 NULL이면 리스트의 끝이므로 moreToSearch의 값을 변경해준다.
	}

	if (found)
		return 1;
	else
		return 0;	//찾으면 1, 그렇지 못하면 0을 리턴한다.
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
void LinkedList<T>::GetNextItem(T& item)
{
	// 하나 증가한 노드의 data를 레퍼런스로 전달
	item = WalkIterator()->data;
}


#endif	// LINKED_LIST