#include "ItemType.h"
#include "FolderType.h"

ItemType::~ItemType()
{
}

ItemType::ItemType(const ItemType & coplied_data)
{
}

// Get item path by string type
string ItemType::GetPathString()
{
	string path_string = "";

	// path 결정되지 않으면 빈 스트링 리턴
	if (path_.IsEmpty()) {
		return path_string;
	}

	DoublyPointingIterator<FolderType*> iter(path_);    // path 탐색할 iterator
	for (iter.First(); !iter.IsNull(); iter.Next()) {
		// 루트 폴더는 이름만 append
		if (iter->parent_folder_ == NULL) {
			path_string.append(iter->name_);
		}
		// 루트 폴더 자식은 이름만 append. 앞에 또 / 안붙임
		else if (iter->parent_folder_->name_.compare("/") == 0) {
			path_string.append(iter->name_);
		}
		// 나머지는 '/' + 이름 append
		else {
			path_string.append("/");
			path_string.append(iter->name_);
		}
	}

	return path_string;
}

// Set item path using item name and parent folders
void ItemType::SetPath()
{
	// 부모 폴더 있으면 부모 폴더의 경로 복사
	if (parent_folder_ != NULL) {
		path_ = parent_folder_->path_;
	}
}

// Assign copy of parameter
void ItemType::AssignCopy(const ItemType & copied_object)
{
	this->name_ = copied_object.name_;
	this->created_date_ = copied_object.created_date_;
	this->size_ = copied_object.size_;
	this->path_ = copied_object.path_;    // path list deep copy
	
}

RelationType ItemType::CompareByName(const FolderType & data)
{
	if (this->name_.compare(data.name_) > 0)
		return GREATER;
	else if (this->name_.compare(data.name_) < 0)
		return LESS;
	else
		return EQUAL;
}

void ItemType::SetNameFromKeyboard()
{
	cout << "\tName : ";
	cin >> name_;
}

// Set item attributes from keyboard.
void ItemType::SetAttributesFromKeyboard()
{
	SetNameFromKeyboard();
}

ItemType & ItemType::operator=(const ItemType & copied_item)
{
	AssignCopy(copied_item);
	return *this;
}

// Generate item's created date.
void ItemType::GenerateCreatedDate()
{
	// Declaring argument for time() 
	time_t current_time;

	// Declaring variable to store return value of 
	// localtime() 
	struct tm * current_tm;

	// Applying time() 
	time(&current_time);

	// Using localtime() 
	current_tm = localtime(&current_time);

	// stream output
	stringstream ss;
	ss << setw(4) << current_tm->tm_year + 1900 << setfill('0') << setw(2)
		<< current_tm->tm_mon + 1 << setfill('0') << setw(2) << current_tm->tm_mday << setfill('0') << setw(2) << current_tm->tm_hour << setfill('0') << setw(2)
		<< current_tm->tm_min << setfill('0') << setw(2) << current_tm->tm_sec << "\0";
	created_date_ = ss.str();  // copy the stream buffer to name 
}
