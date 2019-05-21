#include "FolderType.h"

// copy constructor for deep copy.
FolderType::FolderType(const FolderType & copied_data)
{
	AssignCopy(copied_data);
}

// copy and assgin parameter to this folder
FolderType & FolderType::operator=(const FolderType & copied_data)
{
	AssignCopy(copied_data);
	return *this;
}

// Assign copy of parameter
void FolderType::AssignCopy(const FolderType & copied_object)
{
	ItemType::AssignCopy(copied_object);

	this->num_sub_folder_ = copied_object.num_sub_folder_;

	if (copied_object.num_sub_folder_ != 0) {
		// 공간 생성하고 데이터 deep copy.
		this->sub_folder_list_ = new SortedDoublyLinkedList<FolderType>;
		*(this->sub_folder_list_) = *(copied_object.sub_folder_list_);
	}

}

// Set folder path using item name and parent folders
void FolderType::SetPath()
{
	ItemType::SetPath();

	// 뒤에 현재 폴더 붙이기
	path_.Add(this);
}

// add sub folder into sub folder list.
int FolderType::AddSubFolder() {
	FolderType new_folder;
	FolderType* created_folder;
	string new_folder_path;

	if (num_sub_folder_ == 0) {
		sub_folder_list_ = new SortedDoublyLinkedList<FolderType>;
	}

	//new_folder.SetRecordFromKeyboard();
	new_folder.SetAttributesFromKeyboard();

	// 이름이 중복된 폴더면 생성 불가
	if (IsDupliactedSubFolderExists(new_folder)) {
		cout << "\tExisting folder name" << endl;
		return 0;
	}


	new_folder.parent_folder_ = this;  
	
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

// Change sub folder name and rearrange it in the list
int FolderType::ChangeSubFolderName()
{
	FolderType* folder_change;    // folder to change name
	FolderType changed_folder;    // folder that its name changed.

	// 바꿀 폴더 찾기
	cout << "\tinput name of folder to change" << endl;
	folder_change = GetSubFolder();

	if (folder_change == NULL) {
		cout << "\tfolder not found" << endl;
		return 0;
	}

	// 바꿀 폴더 이름 바꾸기
	changed_folder = (*folder_change);
	cout << "\tinput name to change" << endl;
	changed_folder.SetNameFromKeyboard();

	sub_folder_list_->ChangeItemKey(*folder_change, changed_folder);

	return 0;
}

// Get sub folder by name
FolderType* FolderType::GetSubFolder() {
	FolderType finding_folder;
	bool is_found;

	finding_folder.SetNameFromKeyboard();
	is_found = sub_folder_list_->Get(finding_folder);

	if (!is_found) {
		return nullptr;
	}

	return &finding_folder;
}

// Retrieve folders containing finding name
int FolderType::RetrieveFolderByName() {
	FolderType retrieving_folder;
	bool is_found = false;

	retrieving_folder.SetNameFromKeyboard(); //name을 입력받는다.

	// 리스트 순차 탐색
	DoublyPointingIterator<FolderType> iter(*sub_folder_list_);    // 서브 폴더들 탐색할 iterator
	for (iter.First(); !iter.IsNull(); iter.Next()) {
		// 이름 확인
		if ((*iter).GetName().find(retrieving_folder.GetName()) != string::npos) {
			(*iter).DisplayNameOnScreen();
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
	// 리스트의 끝까지 displayed_folder에 할당
	DoublyPointingIterator<FolderType> iter(*sub_folder_list_);
	for (iter.First(); !iter.IsNull(); iter.Next()) {
		(*iter).DisplayNameOnScreen();
	}

}
