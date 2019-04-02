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
	// TODO: 폴더 동적으로 늘어나게 바꾸기
	
	if (!IsFull()) {
		FolderType current_item;

		// 첫 번째 item get
		ResetList();
		GetNextItem(current_item);

		// current_item보다 큰 원소 바로 뒤나 제일 뒤에 삽입
		while (current_iterator_ <= length_) {
			if (current_item.CompareByID(*in_data) == GREATER || current_iterator_ == length_) {	// 큰 원소 찾거나 끝에 도달했을 때
				// 맨 뒤 요소부터 한 칸씩 뒤로
				for (int i = length_ - 1; i >= current_iterator_; i--) {
					data_array_[i + 1] = data_array_[i];
				}
				data_array_[current_iterator_] = *in_data;
				length_++;
				break;
			}
			GetNextItem(current_item);    // 찾을 때 까지 다음 아이템으로
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
	current_iterator_++;	// list pointer 증가
	if(current_iterator_ == MAXSIZE)	// end of list이면 -1을 리턴
		return -1;
	data = data_array_[current_iterator_];	// 현재 list pointer의 레코드를 복사

	return current_iterator_;
}

//id가 일치하는 item을 찾아서 반환함
int SortedArrayList::Get(FolderType& data)
{
	FolderType CurItem;
	
	ResetList();	//iterator 초기화
	GetNextItem(CurItem);	//첫아이템 가져옴
	while(current_iterator_<length_)	//처음부터 끝까지
	{
		switch(CurItem.CompareByID(data))	//입력 아이템과 현재 아이템을 비교
		{
		case EQUAL:	//일치하면
			data=CurItem;	//data에 현재 아이템을 반환
			return 1;	//성공(1)을 리턴
			break;
		case GREATER:	//현재 아이템의 id가 더 크면(정렬되있으므로 나머지에 찾는게 없다)
			return 0;	//실패(0)을 리턴
			break;
		default:	//현재 아이템의 id가 더 작으면
			GetNextItem(CurItem);	//다음 아이템을 가져온다.(계속 탐색)
			break;
		}
	}
	return 0; //실패시0
}

//id가 일치하는 item을 찾아서 제거함
int SortedArrayList::Delete(FolderType data)
{
	if(Get(data))	//id가 일치하는 item을 발견한다면(1)
	{
		for(int i=current_iterator_;i<length_;i++)	//현재 포인터부터 입력된 배열 끝까지 반복
			data_array_[i]=data_array_[i+1];	//배열 뒤에걸 앞으로 하나씩 땡김
		length_--;	//아이템 개수를 하나 줄임
		return 1;	//성공(1)을 리턴
	}
	return 0;	//id일치하는 item을 찾지 못한다면 실패(0)을 리턴
}

//id가 일치하는 item의 내용을 교체시킴
int SortedArrayList::Replace(FolderType data)
{
	FolderType tmp(data);	//입력받은 item을 백업

	if(Get(data))	//일치하는 아이템을 찾은 경우
	{
		data_array_[current_iterator_]=tmp;	//배열에서 현재포인터가 가르키는 것을 백업했던 아이템으로 교체시킴
		return 1;	//성공(1)을 리턴
	}
	return 0;	//id일치하는 item을 찾지 못한다면 실패(0)을 리턴
}

//id가 일치하는 item을 이진탐색으로 검색해서 반환한다.
int SortedArrayList::GetBinarySearch( FolderType& data )
{
	if(length_==0)	//만약 배열이 비었다면
		return 0;	//실패(0)을 리턴
	int currentPos=length_/2;	//배열의 중간부터 시작
	while(1)
	{
		switch(data_array_[currentPos].CompareByID(data))
		{
		case EQUAL:	//현재 아이템과 입력 아이템의 id가 일치한다면
			data=data_array_[currentPos];	//data에 발견한 값을 리턴
			return 1;	//성공(1)을 리턴
			break;
		case GREATER:	//현재 아이템의 id가 입력 아이템의 id보다 크다면
			if(currentPos==0)	//처음 배열의 값보다 작은경우
				return 0;	//실패(0)을 리턴
			currentPos/=2;	//더 작은쪽 인덱스의 절반로 이동
			break;
		case LESS:	//현재 아이템의 id가 입력 아이템의 id보다 작다면
			if(currentPos==length_-1)	//마지막 배열의 값보다 큰경우
				return 0;	//실패(0)을 리턴
			currentPos=(currentPos+length_)/2;	//더 큰쪽 인덱스의 절반으로 이동
			break;
		}
	}
	return 0;	//호출될 일 없는 리턴(WARNING 방지용)
}
