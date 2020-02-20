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
		// ���� �����ϰ� ������ deep copy.
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

	// �ڿ� ���� ���� ���̱�
	path_.Add(this);
}

// add sub folder into sub folder list.
int FolderType::AddSubFolder() {
	FolderType new_folder(this);    // parent folder�� this�� ����
	FolderType* created_folder;

	if (num_sub_folder_ == 0) {
		sub_folder_list_ = new BinarySearchTree<FolderType>;
	}

	new_folder.SetAttributesFromKeyboard();

	// �̸��� �ߺ��� ������ ���� �Ұ�
	if (IsDupliactedSubFolderExists(new_folder)) {
		cout << "\tExisting folder name" << endl;
		return 0;
	}

	sub_folder_list_->Insert(new_folder);

	// ����Ʈ �ȿ� ����ִ� ������ ������ ������ Path ����
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

	// �̸��� �ߺ��� �����̸� ���� �Ұ�
	/*
	if (IsDupliactedSubFolderExists(*new_folder)) {
		cout << "\tExisting folder name" << endl;
		return 0;
	}
	*/

	file_list_->Insert(new_file);

	// ����Ʈ �ȿ� ����ִ� ������ ������ ������ Path ����
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

	// �ߺ� �˻�
	if (sub_folder_list_ != NULL) {
		if (sub_folder_list_->Search(folder_find) == true) {
			return true;
		}
	}

	return false;
}

// ���� ���� ����
int FolderType::DeleteSubFolder() {
	FolderType deleting_folder;
	bool is_folder_exist = false;

	deleting_folder.SetNameFromKeyboard();
	// ������ ���� �ִ��� Ž��
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
		bool is_found = false;    // �̸� �ٲ� ������ ã�Ҵ��� ����

		// �ٲ� ���� ã��
		cout << "\tinput name of folder to change" << endl;
		folder_change.SetNameFromKeyboard();

		if (sub_folder_list_ == nullptr) {
			throw std::invalid_argument("ChangeFolderName(): sub folder list is NULL");
		}

		is_found = sub_folder_list_->Search(folder_change);

		// �ٲ� ���� ������ ���� �޼��� ����ϰ� ����
		if (!is_found) {
			throw std::invalid_argument("ChangeFolderName(): folder doesn't exist");
		}

		// �ٲ� ���� �̸� �ٲٱ�
		folder_change = sub_folder_list_->Get(folder_change);    // ���� �ٲ� ���� �����͸� Get
		sub_folder_list_->Remove(folder_change);    // ������ ���� ����Ʈ���� �����ϰ�
		cout << "\tinput name to change" << endl;
		folder_change.SetNameFromKeyboard();
		sub_folder_list_->Insert(folder_change);	// �ٽ� ����

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
		return nullptr;    // ã�� ���� ���� ����
	}

	sub_folder = sub_folder_list_->GetItemAdderess(finding_folder);

	return sub_folder;
}

// Retrieve folders containing finding name
int FolderType::RetrieveFolderByName() const {
	try {
		FolderType retrieving_folder;
		bool is_found = false;

		retrieving_folder.SetNameFromKeyboard(); //name�� �Է¹޴´�.

		// if sub folder list isn't valid
		if (sub_folder_list_ == nullptr) {
			throw std::invalid_argument("RetrieveFolderByName(): sub folder list is NULL");
		}

		// ����Ʈ ���� Ž��
		TreeIterator<FolderType> iter((*sub_folder_list_));    // ���� ������ Ž���� iterator
		for (iter.First(); !iter.IsNull(); iter.Next()) {
			// �̸� Ȯ��
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
		// �� ã���� ���� �޼��� ����ϰ� ����
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
