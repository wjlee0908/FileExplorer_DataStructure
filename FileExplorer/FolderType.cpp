#include "FolderType.h"

int FolderType::SetName(string input_name) {
	FolderType folder_find;    // folder to find duplicated folder
	string old_name = name_;

	// 중복 검사
	folder_find.SetName(input_name);
	if (sub_folder_list_->Get(folder_find) == 0) {
		cout << "\tExisting folder name" << endl;
		return 0;
	}

	// 이름 재설정
	name_ = input_name;
	// path 재설정

	// 위치 재설정


}

void FolderType::GenerateCreatedDate() {
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

// Set folder name from keyboard.
void FolderType::SetNameFromKeyboard()
{
	cout << "\tName : ";
	cin >> name_;
}


// Set folder path from keyboard.
void FolderType::SetPathFromKeyboard()
{
	cout << "\tPath : ";
	cin >> path_;
}


// Set folder record from keyboard.
void FolderType::SetRecordFromKeyboard()
{
	SetNameFromKeyboard();
}

// copy and assgin parameter to this folder
FolderType & FolderType::operator=(const FolderType & copied_data)
{
	this->name_ = copied_data.name_;
	this->path_ = copied_data.path_;
	this->created_date_ = copied_data.created_date_;
	this->num_sub_folder_ = copied_data.num_sub_folder_;

	if (num_sub_folder_ != 0) {
		this->sub_folder_list_ = copied_data.sub_folder_list_;
	}

	return *this;
}

// Returns whether this is less than comparing data.
bool FolderType::operator<(const FolderType & comparing_data)
{
	return (CompareByName(comparing_data) == LESS);
}

// Returns whether this is equal to comparing data.
bool FolderType::operator==(const FolderType & comparing_data)
{
	return (CompareByName(comparing_data) == EQUAL);
}

// Returns whether this is greater than comparing data.
bool FolderType::operator>(const FolderType & comparing_data)
{
	return (CompareByName(comparing_data) == GREATER);
}

// add sub folder into sub folder list.
int FolderType::AddSubFolder() {
	FolderType new_folder;
	string new_folder_path;

	if (num_sub_folder_ == 0) {
		sub_folder_list_ = new SortedLinkedList<FolderType>;
	}

	new_folder.SetRecordFromKeyboard();

	// 서브 폴더 경로명 설정
	// 루트 폴더 자식이면 앞에 또 / 안붙임
	if (path_.compare("/") == 0) {
		new_folder_path = path_ + new_folder.name_;
	}
	else {
		new_folder_path = path_ + "/" + new_folder.name_;
	}

	new_folder.SetPath(new_folder_path);    
	new_folder.GenerateCreatedDate();

	if (sub_folder_list_->Add(new_folder)) {
		num_sub_folder_++;
	}

	return 1;
}


// Read a record from file.
int FolderType::ReadDataFromFile(ifstream& fin)
{
	fin >> name_;
	fin >> path_;

	return 1;
};


// Write a record into file.
int FolderType::WriteDataToFile(ofstream& fout)
{
	fout << endl;
	fout << name_ << " ";
	fout << path_;

	return 1;
}


// Compare two folder types.
RelationType FolderType::CompareByName(const FolderType &data)
{
	if(this->name_.compare(data.name_) > 0)
		return GREATER;
	else if(this->name_.compare(data.name_) < 0)
		return LESS;
	else
		return EQUAL;
}

int FolderType::DeleteSubFolder() {
	FolderType deleting_folder;
	int is_delete_suceed = 0;

	deleting_folder.SetNameFromKeyboard();
	is_delete_suceed = sub_folder_list_->Delete(deleting_folder);

	if (is_delete_suceed != 0)
	{
		cout << "<========DELETE SUCCESS !===========>" << endl;
		num_sub_folder_--;
		return 1;
	}

	cout << "<========DELETE FAIL !=======>" << endl;

	return 0;
}

// Get sub folder by name
FolderType* FolderType::GetSubFolder() {
	FolderType finding_folder;

	finding_folder.SetNameFromKeyboard();
	return sub_folder_list_->GetItemAddress(finding_folder);
}

// Retrieve folders containing finding name
int FolderType::RetrieveFolderByName() {
	FolderType retrieving_folder;
	FolderType iterator;    // 리스트 탐색할 item
	bool is_found = false;

	retrieving_folder.SetNameFromKeyboard(); //name을 입력받는다.

	sub_folder_list_->ResetIterator();
	// 리스트 순차 탐색
	while (sub_folder_list_->GetNextItem(iterator) != 0) {
		// 이름 확인
		if (iterator.GetName().find(retrieving_folder.GetName()) != string::npos) {
			iterator.DisplayInformationOnScreen();
			is_found = true;
		}
	}

	if (!is_found) {
		cout << "\tFolder not found" << endl;
		return 1;
	}

	return 0;
}

// Display all sub folders of this folder
void FolderType::DisplayAllSubFolders() {
	FolderType displayed_folder;

	cout << "\n\tSub Folder list" << endl;

	sub_folder_list_->ResetIterator();

	// 리스트의 끝까지 displaye_folder에 할당
	while (sub_folder_list_->GetNextItem(displayed_folder) != 0) {
		displayed_folder.DisplayInformationOnScreen();
	}
}
