#ifndef _SORTEDARRAYLIST_H
#define _SORTEDARRAYLIST_H

#include <iostream>
#include <fstream>	
#include <string>
#include "FolderType.h"

using namespace std;

#define MAXSIZE 5

// ���� include �ϸ鼭 �� ã�� ���� ���� ���� �̸� ���
class FolderType;

/**
*	array based simple unsorted list.
*/
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
	int Add(const FolderType* in_data);

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
	int GetNextItem(FolderType& data);

	/**
	*	@brief	item�� ã�Ƽ� �ش� item�� ��ȯ�Ѵ�.
	*	@pre	�μ� data�� �ִ� id�� list ���� �����ϴ� ���̾�� �Ѵ�.
	*	@post	list ������ ã�� item�� data�� �Էµȴ�.
	*	@param	data	ã���� �ϴ� id�� �Էµ� ItemType��. �߰��� item�� ���ϵȴ�.
	*	@return	����(�߰�)�� 1, ���н� 0�� �����Ѵ�.
	*/
	int Get(FolderType& data);

	/**
	*	@brief	id�� ��ġ�ϴ� item�� ã�Ƽ� �ش� item�� �����Ѵ�.
	*	@pre	�μ� data�� �ִ� id�� list ���� �����ϴ� ���̾�� �Ѵ�.
	*	@post	list ���� �ش� item�� ���ŵȴ�.
	*	@param	data	�����ϰ��� �ϴ� id�� �Էµ� ItemType��. 
	*	@return	������ 1, ���н� 0�� �����Ѵ�.
	*/
	int Delete(FolderType data);

	/**
	*	@brief	id�� ��ġ�ϴ� list�� item�� ã�Ƽ� �����Ѵ�.
	*	@pre	�μ� data�� �ִ� id�� list ���� �����ϴ� ���̾�� �Ѵ�.
	*	@post	�迭 ���� �Ѱܹ��� item�� id�� ��ġ�ϴ� ���� �Ѱܹ��� item�� �������� ����ȴ�.
	*	@param	data	��ü�ϰ��� �ϴ� id�� ���ڵ带 ���� ItemType��.
	*	@return	������ 1, ���н� 0�� �����Ѵ�.
	*/
	int Replace(FolderType data);

	/**
	*	@brief	����Ž���� ���� id�� ��ġ�ϴ� list�� item�� ã�Ƽ� ��ȯ�Ѵ�.
	*	@pre	����.
	*	@post	�迭 ���� �Ѱܹ��� item�� id�� ��ġ�ϴ� ���� ã�Ƽ� data�� ��ȯ�ȴ�.
	*	@param	data	ã���� �ϴ� id�� �Էµ� ItemType��.
	*	@return	����(�߰�)�� 1, ���н� 0�� �����Ѵ�.
	*/
	int GetBinarySearch(FolderType& data);
private:
	FolderType data_array_[MAXSIZE];  ///< list array.
	int length_;				///< number of elements in list.
	int current_iterator_;			///< iterator pointer.
};

#endif	// _SORTEDARRAYLIST_H