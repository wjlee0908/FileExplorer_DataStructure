#include "FolderType.h"

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
	
	CopySubFolderList(copied_object.sub_folder_list_);
	CopyFileList(copied_object.file_list_);

}

// Copy sub folder list (deep copy)
void FolderType::CopySubFolderList(const BinarySearchTree<FolderType>* copied_list)
{
	if (copied_list == nullptr) {
		this->sub_folder_list_ = nullptr;
	}
	else {
		// 공간 생성하고 데이터 deep copy.
		this->sub_folder_list_ = new BinarySearchTree<FolderType>;
		*(this->sub_folder_list_) = *copied_list;
	}
}

// Copy file list (deep copy)
void FolderType::CopyFileList(const BinarySearchTree<FileType>* copied_list)
{
	if (copied_list == nullptr) {
		this->file_list_ = nullptr;
	}
	else {
		this->file_list_ = new BinarySearchTree<FileType>;
		*(this->file_list_) = *(copied_list);
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
	FolderType new_folder(this);    // parent folder를 this로 설정
	FolderType* created_folder;

	if (num_sub_folder_ == 0) {
		sub_folder_list_ = new BinarySearchTree<FolderType>;
	}

	new_folder.SetAttributesFromKeyboard();

	// 이름이 중복된 폴더면 생성 불가
	if (IsDupliactedSubFolderExists(new_folder)) {
		cout << "\tExisting folder name" << endl;
		return 0;
	}

	sub_folder_list_->Insert(new_folder);

	// 리스트 안에 들어있는 생성한 폴더의 원본에 Path 설정
	created_folder = sub_folder_list_->GetItemAdderess(new_folder);
	num_sub_folder_++;
	created_folder->SetPath();

	return 1;
}

// Add file in this folder
int FolderType::AddFile()
{
	FileType new_file;
	FileType* created_file;
	string new_file_path;

	if (file_list_->GetLength() == 0) {
		file_list_ = new BinarySearchTree<FileType>;
	}

	// new_file->SetAttributesFromKeyboard();

	// 이름이 중복된 파일이면 생성 불가
	/*
	if (IsDupliactedSubFolderExists(*new_folder)) {
		cout << "\tExisting folder name" << endl;
		return 0;
	}
	*/

	file_list_->Insert(new_file);

	// 리스트 안에 들어있는 생성한 폴더의 원본에 Path 설정
	created_file = file_list_->GetItemAdderess(new_file);
	created_file->SetPath();

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

	FolderType find_result = folder_find;

	// 중복 검사
	if (sub_folder_list_ != NULL) {
		if (sub_folder_list_->Search(folder_find) == true) {
			return true;
		}
	}

	return false;
}

// 하위 폴더 제거
int FolderType::DeleteSubFolder() {
	FolderType deleting_folder;
	bool is_folder_exist = false;

	deleting_folder.SetNameFromKeyboard();
	// 삭제할 폴더 있는지 탐색
	is_folder_exist = sub_folder_list_->Search(deleting_folder);

	if (sub_folder_list_->Search(deleting_folder) == true) {
		sub_folder_list_->Remove(deleting_folder);
		cout << "<========DELETE SUCCESS !===========>" << endl;
		num_sub_folder_--;
		return 1;
	}
	else {
		cout << "<========DELETE FAIL !=======>" << endl;
	}

	return 0;
}

// Change sub folder name and rearrange it in the list
int FolderType::ChangeSubFolderName()
{
	try {
		FolderType folder_change;
		bool is_found = false;    // 이름 바꿀 폴더를 찾았는지 저장

		// 바꿀 폴더 찾기
		cout << "\tinput name of folder to change" << endl;
		folder_change.SetNameFromKeyboard();

		if (sub_folder_list_ == nullptr) {
			throw std::invalid_argument("ChangeFolderName(): sub folder list is NULL");
		}

		is_found = sub_folder_list_->Search(folder_change);

		// 바꿀 폴더 없으면 에러 메세지 출력하고 종료
		if (!is_found) {
			throw std::invalid_argument("ChangeFolderName(): folder doesn't exist");
		}

		// 바꿀 폴더 이름 바꾸기
		folder_change = sub_folder_list_->Get(folder_change);    // 실제 바꿀 폴더 데이터를 Get
		sub_folder_list_->Remove(folder_change);    // 정렬을 위해 리스트에서 제거하고
		cout << "\tinput name to change" << endl;
		folder_change.SetNameFromKeyboard();
		sub_folder_list_->Insert(folder_change);	// 다시 삽입

		return 1;
	}
	catch (std::invalid_argument e) {
		cout << "\tfolder not found!" << endl;
		return 0;
	}
} 

// Get sub folder by name
FolderType* FolderType::GetSubFolder() const{
	FolderType finding_folder;
	FolderType* sub_folder;
	bool is_found;

	finding_folder.SetNameFromKeyboard();
	is_found = sub_folder_list_->Search(finding_folder);

	if (!is_found) {
		return nullptr;    // 찾는 서브 폴더 없음
	}

	sub_folder = sub_folder_list_->GetItemAdderess(finding_folder);

	return sub_folder;
}

// Retrieve folders containing finding name
int FolderType::RetrieveFolderByName() const {
	try {
		FolderType retrieving_folder;
		bool is_found = false;

		retrieving_folder.SetNameFromKeyboard(); //name을 입력받는다.

		// if sub folder list isn't valid
		if (sub_folder_list_ == nullptr) {
			throw std::invalid_argument("RetrieveFolderByName(): sub folder list is NULL");
		}

		// 리스트 순차 탐색
		TreeIterator<FolderType> iter((*sub_folder_list_));    // 서브 폴더들 탐색할 iterator
		for (iter.First(); !iter.IsNull(); iter.Next()) {
			// 이름 확인
			if ((*iter).GetName().find(retrieving_folder.GetName()) != string::npos) {
				(*iter).DisplayNameOnScreen();
				is_found = true;
			}
		}

		if (!is_found) {
			throw std::invalid_argument("RetrieveFolderByName(): finding folder doesn't exist");
		}

		return 0;
	}
	catch (invalid_argument e) {
		// 못 찾으면 에러 메세지 출력하고 종료
		cout << "\tFolder not found" << endl;
		return 1;
	}
}

// Display all sub folders of this folder
void FolderType::DisplayAllSubFolders() const {
	FolderType displayed_folder;

	cout << "\n\tSub Folder list" << endl;
	sub_folder_list_->Print(cout, INORDER);
}
