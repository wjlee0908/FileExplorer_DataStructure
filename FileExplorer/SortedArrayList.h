#ifndef _SORTEDARRAYLIST_H
#define _SORTEDARRAYLIST_H

#include <iostream>
#include <fstream>	
#include <string>

using namespace std;

#define MAXSIZE 5

/**
*	array based simple sorted list.
*/
template <typename T>
class SortedArrayList
{
public:
	/**
	*	default constructor.
	*/
	SortedArrayList()
	{
		length_ = 0;
		ResetList();
	}

	/**
	*	destructor.
	*/
	~SortedArrayList()	{}

	/**
	*	@brief	Make list empty.
	*	@pre	none.
	*	@post	clear list.
	*/
	void MakeEmpty();

	/**
	*	@brief	Get a number of records in current list.
	*	@pre	none.
	*	@post	none.
	*	@return	number of records in current list.
	*/
	int GetLength();

	/**
	*	@brief	Check capacity of list is full.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if list capacity reached to the upper bound, otherwise return false.
	*/
	bool IsFull();

	/**
	*	@brief	Copy parameter list and assign to this list.
	*	@pre	copied_list is set.
	*	@post	this list is set.
	*	@return	return this after assining parameter.
	*/
	SortedArrayList& operator= (const SortedArrayList& copied_list);

	/**
	*	@brief	add a new data into list.
	*	@pre	list should be initialized.
	*	@post	added the new record into the list.
	*	@param	data	new data.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int Add(const T* in_data);

	/**
	*	@brief	Initialize list iterator.
	*	@pre	list should be initialized.
	*	@post	iterator is reset.
	*/
	void ResetList();

	/**
	*	@brief	move list iterator to the next item in list and get that item.
	*	@pre	list and list iterator should not be initialized. 
	*	@post	iterator is moved to next item.
	*	@param	data	get current iterator's item. it does not need to be initialized.
	*	@return	index of current iterator's item if is not end of list, oterwise return -1.
	*/
	int GetNextItem(T& data);

	/**
	*	@brief	item�� ã�Ƽ� �ش� item�� ��ȯ�Ѵ�.
	*	@pre	�μ� data�� �ִ� id�� list ���� �����ϴ� ���̾�� �Ѵ�.
	*	@post	list ������ ã�� item�� data�� �Էµȴ�.
	*	@param	data	ã���� �ϴ� id�� �Էµ� ItemType��. �߰��� item�� ���ϵȴ�.
	*	@return	����(�߰�)�� 1, ���н� 0�� �����Ѵ�.
	*/
	int Get(T& data);

	/**
	*	@brief	id�� ��ġ�ϴ� item�� ã�Ƽ� �ش� item�� �����Ѵ�.
	*	@pre	�μ� data�� �ִ� id�� list ���� �����ϴ� ���̾�� �Ѵ�.
	*	@post	list ���� �ش� item�� ���ŵȴ�.
	*	@param	data	�����ϰ��� �ϴ� id�� �Էµ� ItemType��. 
	*	@return	������ 1, ���н� 0�� �����Ѵ�.
	*/
	int Delete(T data);

	/**
	*	@brief	id�� ��ġ�ϴ� list�� item�� ã�Ƽ� �����Ѵ�.
	*	@pre	�μ� data�� �ִ� id�� list ���� �����ϴ� ���̾�� �Ѵ�.
	*	@post	�迭 ���� �Ѱܹ��� item�� id�� ��ġ�ϴ� ���� �Ѱܹ��� item�� �������� ����ȴ�.
	*	@param	data	��ü�ϰ��� �ϴ� id�� ���ڵ带 ���� ItemType��.
	*	@return	������ 1, ���н� 0�� �����Ѵ�.
	*/
	int Replace(T data);

	/**
	*	@brief	����Ž���� ���� id�� ��ġ�ϴ� list�� item�� ã�Ƽ� ��ȯ�Ѵ�.
	*	@pre	����.
	*	@post	�迭 ���� �Ѱܹ��� item�� id�� ��ġ�ϴ� ���� ã�Ƽ� data�� ��ȯ�ȴ�.
	*	@param	data	ã���� �ϴ� id�� �Էµ� ItemType��.
	*	@return	����(�߰�)�� 1, ���н� 0�� �����Ѵ�.
	*/
	int GetBinarySearch(T& data);
private:
	T data_array_[MAXSIZE];  ///< list array.
	int length_;				///< number of elements in list.
	int current_iterator_;			///< iterator pointer.
};

// Make list empty.
template <typename T>
void SortedArrayList<T>::MakeEmpty()
{
	length_ = 0;
}


// Get a number of records in current list.
template <typename T>
int SortedArrayList<T>::GetLength()
{
	return length_;
}


// Check capacity of list is full.
template <typename T>
bool SortedArrayList<T>::IsFull()
{
	if(length_ > MAXSIZE - 1)
		return true;
	else
		return false;
}

// Copy parameter list and assign to this list.
template <typename T>
SortedArrayList<T> & SortedArrayList<T>::operator=(const SortedArrayList & copied_list)
{
	for (int i = 0; i < length_; i++) {
		this->data_array_[i] = copied_list.data_array_[i];
	}

	return *this;
}

// add a new data into list.
template <typename T>
int SortedArrayList<T>::Add(const T* in_data)
{
	// TODO: ���� �������� �þ�� �ٲٱ�
	
	if (!IsFull()) {
		T current_item;

		// ù ��° item get
		ResetList();
		GetNextItem(current_item);

		// current_item���� ū ���� �ٷ� �ڳ� ���� �ڿ� ����
		while (current_iterator_ <= length_) {
			if (current_item.CompareByID(*in_data) == GREATER || current_iterator_ == length_) {	// ū ���� ã�ų� ���� �������� ��
				// �� �� ��Һ��� �� ĭ�� �ڷ�
				for (int i = length_ - 1; i >= current_iterator_; i--) {
					data_array_[i + 1] = data_array_[i];
				}
				data_array_[current_iterator_] = *in_data;
				length_++;
				break;
			}
			GetNextItem(current_item);    // ã�� �� ���� ���� ����������
		}
	}
	else {
		return 0;
	}

	return 1;
}

// Initialize list iterator.
template <typename T>
void SortedArrayList<T>::ResetList()
{
	current_iterator_ = -1;
}


// move list iterator to the next item in list and get that item.
template <typename T>
int SortedArrayList<T>::GetNextItem(T& data)
{
	current_iterator_++;	// list pointer ����
	if(current_iterator_ == MAXSIZE)	// end of list�̸� -1�� ����
		return -1;
	data = data_array_[current_iterator_];	// ���� list pointer�� ���ڵ带 ����

	return current_iterator_;
}

//id�� ��ġ�ϴ� item�� ã�Ƽ� ��ȯ��
template <typename T>
int SortedArrayList<T>::Get(T& data)
{
	T CurItem;
	
	ResetList();	//iterator �ʱ�ȭ
	GetNextItem(CurItem);	//ù������ ������
	while(current_iterator_<length_)	//ó������ ������
	{
		switch(CurItem.CompareByID(data))	//�Է� �����۰� ���� �������� ��
		{
		case EQUAL:	//��ġ�ϸ�
			data=CurItem;	//data�� ���� �������� ��ȯ
			return 1;	//����(1)�� ����
			break;
		case GREATER:	//���� �������� id�� �� ũ��(���ĵ������Ƿ� �������� ã�°� ����)
			return 0;	//����(0)�� ����
			break;
		default:	//���� �������� id�� �� ������
			GetNextItem(CurItem);	//���� �������� �����´�.(��� Ž��)
			break;
		}
	}
	return 0; //���н�0
}

//id�� ��ġ�ϴ� item�� ã�Ƽ� ������
template <typename T>
int SortedArrayList<T>::Delete(T data)
{
	if(Get(data))	//id�� ��ġ�ϴ� item�� �߰��Ѵٸ�(1)
	{
		for(int i=current_iterator_;i<length_;i++)	//���� �����ͺ��� �Էµ� �迭 ������ �ݺ�
			data_array_[i]=data_array_[i+1];	//�迭 �ڿ��� ������ �ϳ��� ����
		length_--;	//������ ������ �ϳ� ����
		return 1;	//����(1)�� ����
	}
	return 0;	//id��ġ�ϴ� item�� ã�� ���Ѵٸ� ����(0)�� ����
}

//id�� ��ġ�ϴ� item�� ������ ��ü��Ŵ
template <typename T>
int SortedArrayList<T>::Replace(T data)
{
	T tmp(data);	//�Է¹��� item�� ���

	if(Get(data))	//��ġ�ϴ� �������� ã�� ���
	{
		data_array_[current_iterator_]=tmp;	//�迭���� ���������Ͱ� ����Ű�� ���� ����ߴ� ���������� ��ü��Ŵ
		return 1;	//����(1)�� ����
	}
	return 0;	//id��ġ�ϴ� item�� ã�� ���Ѵٸ� ����(0)�� ����
}

//id�� ��ġ�ϴ� item�� ����Ž������ �˻��ؼ� ��ȯ�Ѵ�.
template <typename T>
int SortedArrayList<T>::GetBinarySearch( T& data )
{
	if(length_==0)	//���� �迭�� ����ٸ�
		return 0;	//����(0)�� ����
	int currentPos=length_/2;	//�迭�� �߰����� ����
	while(1)
	{
		switch(data_array_[currentPos].CompareByID(data))
		{
		case EQUAL:	//���� �����۰� �Է� �������� id�� ��ġ�Ѵٸ�
			data=data_array_[currentPos];	//data�� �߰��� ���� ����
			return 1;	//����(1)�� ����
			break;
		case GREATER:	//���� �������� id�� �Է� �������� id���� ũ�ٸ�
			if(currentPos==0)	//ó�� �迭�� ������ �������
				return 0;	//����(0)�� ����
			currentPos/=2;	//�� ������ �ε����� ���ݷ� �̵�
			break;
		case LESS:	//���� �������� id�� �Է� �������� id���� �۴ٸ�
			if(currentPos==length_-1)	//������ �迭�� ������ ū���
				return 0;	//����(0)�� ����
			currentPos=(currentPos+length_)/2;	//�� ū�� �ε����� �������� �̵�
			break;
		}
	}
	return 0;	//ȣ��� �� ���� ����(WARNING ������)
}

#endif	// _SORTEDARRAYLIST_H