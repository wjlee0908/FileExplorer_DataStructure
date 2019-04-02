#include "SortedArrayList.h"

// Make list empty.
void SortedArrayList::MakeEmpty()
{
	length_ = 0;
}


// Get a number of records in current list.
int SortedArrayList::GetLength()
{
	return length_;
}


// Check capacity of list is full.
bool SortedArrayList::IsFull()
{
	if(length_ > MAXSIZE - 1)
		return true;
	else
		return false;
}

SortedArrayList & SortedArrayList::operator=(const SortedArrayList & copied_list)
{
	for (int i = 0; i < length_; i++) {
		this->data_array_[i] = copied_list.data_array_[i];
	}

	return *this;
}

// add a new data into list.
int SortedArrayList::Add(const FolderType* in_data)
{
	// TODO: ���� �������� �þ�� �ٲٱ�
	
	if (!IsFull()) {
		FolderType current_item;

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
void SortedArrayList::ResetList()
{
	current_iterator_ = -1;
}


// move list iterator to the next item in list and get that item.
int SortedArrayList::GetNextItem(FolderType& data)
{
	current_iterator_++;	// list pointer ����
	if(current_iterator_ == MAXSIZE)	// end of list�̸� -1�� ����
		return -1;
	data = data_array_[current_iterator_];	// ���� list pointer�� ���ڵ带 ����

	return current_iterator_;
}

//id�� ��ġ�ϴ� item�� ã�Ƽ� ��ȯ��
int SortedArrayList::Get(FolderType& data)
{
	FolderType CurItem;
	
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
int SortedArrayList::Delete(FolderType data)
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
int SortedArrayList::Replace(FolderType data)
{
	FolderType tmp(data);	//�Է¹��� item�� ���

	if(Get(data))	//��ġ�ϴ� �������� ã�� ���
	{
		data_array_[current_iterator_]=tmp;	//�迭���� ���������Ͱ� ����Ű�� ���� ����ߴ� ���������� ��ü��Ŵ
		return 1;	//����(1)�� ����
	}
	return 0;	//id��ġ�ϴ� item�� ã�� ���Ѵٸ� ����(0)�� ����
}

//id�� ��ġ�ϴ� item�� ����Ž������ �˻��ؼ� ��ȯ�Ѵ�.
int SortedArrayList::GetBinarySearch( FolderType& data )
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
