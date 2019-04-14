#include "FolderType.h"

// return path to string type
string FolderType::GetPathString()
{
	string path_string = "";
	FolderType* iterated_folder;	// while문에서 현재 탐색 중인 폴더

	// path 결정되지 않으면 빈 스트링 리턴
	if (path_->IsEmpty()) {
		return path_string;
	}

	// path 끝까지 iterating
	path_->ResetIterator();
	while (path_->GetNextItem(iterated_folder)) {

		// 루트 폴더는 이름만 append
		if (iterated_folder->parent_folder_ == NULL) {
			path_string.append(iterated_folder->name_);
		}
		// 루트 폴더 자식은 이름만 append. 앞에 또 / 안붙임
		else if (iterated_folder->parent_folder_->name_.compare("/") == 0) {
			path_string.append(iterated_folder->name_);
		}
		// 나머지는 '/' + 이름 append
		else {
			path_string.append("/");
			path_string.append(iterated_folder->name_);
		}
	}

	return path_string;
}

int FolderType::SetName(string input_name) {
	FolderType folder_find;    // folder to find duplicated folder
	SortedLinkedList<FolderType>* current_list;   // folder list that this folder is included.
	string new_path = "";

	/*
	// 중복 검사
	if (parent_folder_ != NULL) {
		current_list = parent_folder_->sub_folder_list_;
		if (current_list != NULL) {
			folder_find.name_ = input_name;
			if (current_list->Get(folder_find) == 0) {
				cout << "\tExisting folder name" << endl;
				return 0;
			}
		}
	}
	*/

	// 중복 검사
	folder_find.name_ = input_name;
	if ((parent_folder_ != NULL) && (parent_folder_->IsDupliactedSubFolderExists(folder_find))) {
		cout << "\tExisting folder name" << endl;
		return 0;
	}

	// 이름 재설정
	name_ = input_name;

	return 1;

}

// Set folder path using folder name and parent folder
void FolderType::SetPath() {
	/*
	string parent_path = "";

	// 상위 폴더 지정 안 되어있으면 실행하지 않음
	if (parent_folder_ == NULL) {
		return;
	}

	parent_path = parent_folder_->GetPath();

	// 루트 폴더 자식이면 앞에 또 / 안붙임
	if (parent_path.compare("/") == 0) {
		path_string_ = parent_path + name_;
	}
	else {
		path_string_ = parent_path + "/" + name_;
	}
	*/

	// 부모 폴더 있으면 부모 폴더의 경로 복사
	if (parent_folder_ != NULL) {
		*path_ = *(parent_folder_->path_);
	}
	// 뒤에 현재 폴더 붙이기
	path_->Add(this);
	
	
	cout << endl;
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
	cin >> path_string_;
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
	this->path_string_ = copied_data.path_string_;
	this->created_date_ = copied_data.created_date_;
	this->num_sub_folder_ = copied_data.num_sub_folder_;
	this->parent_folder_ = copied_data.parent_folder_;

	if (copied_data.num_sub_folder_ != 0) {
		this->sub_folder_list_ = copied_data.sub_folder_list_;
	}
	this->path_ = copied_data.path_;	// copy
	

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
	FolderType* created_folder;
	string new_folder_path;

	if (num_sub_folder_ == 0) {
		sub_folder_list_ = new SortedLinkedList<FolderType>;
	}

	new_folder.SetRecordFromKeyboard();
	// 이름이 중복된 폴더면 생성 불가
	if (IsDupliactedSubFolderExists(new_folder)) {
		cout << "\tExisting folder name" << endl;
		return 0;
	}


	new_folder.parent_folder_ = this;  
	new_folder.GenerateCreatedDate();
	
	// 리스트 안에 들어있는 생성한 폴더의 원본에 Path 설정
	created_folder = sub_folder_list_->Add(new_folder);
	if (created_folder != NULL) {
		num_sub_folder_++;
		created_folder->SetPath();
	}

	return 1;
}


// Read a record from file.
int FolderType::ReadDataFromFile(ifstream& fin)
{
	fin >> name_;
	// fin >> path_string_;
	fin >> GetPathString();

	return 1;
};


// Write a record into file.
int FolderType::WriteDataToFile(ofstream& fout)
{
	fout << endl;
	fout << name_ << " ";
	// fout << path_string_;
	fout << GetPathString();

	return 1;
}

// Finds the folder that its name duplicates and return its result.
bool FolderType::IsDupliactedSubFolderExists(FolderType folder_find)
{
	// 중복 검사
	if (sub_folder_list_ != NULL) {
		if (sub_folder_list_->Get(folder_find) == 1) {
			return true;
		}
	}

	return false;
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

	// 리스트의 끝까지 displayed_folder에 할당
	while (sub_folder_list_->GetNextItem(displayed_folder) != 0) {
		displayed_folder.DisplayInformationOnScreen();
	}
}
