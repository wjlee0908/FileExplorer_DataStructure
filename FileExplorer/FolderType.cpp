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
		// ���� �����ϰ� ������ deep copy.
		this->sub_folder_list_ = new BinarySearchTree<FolderType>;
		*(this->sub_folder_list_) = *(copied_object.sub_folder_list_);
	}
	if (copied_object.file_list_ != nullptr) {
		this->file_list_ = new BinarySearchTree<FileType>;
		*(this->file_list_) = *(copied_object.file_list_);
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
	FolderType* new_folder = new FolderType;
	FolderType created_folder;
	string new_folder_path;

	if (num_sub_folder_ == 0) {
		sub_folder_list_ = new BinarySearchTree<FolderType>;
	}

	//new_folder.SetRecordFromKeyboard();
	new_folder->SetAttributesFromKeyboard();

	// �̸��� �ߺ��� ������ ���� �Ұ�
	if (IsDupliactedSubFolderExists(*new_folder)) {
		cout << "\tExisting folder name" << endl;
		return 0;
	}


	new_folder->parent_folder_ = this;  
	
	// ����Ʈ �ȿ� ����ִ� ������ ������ ������ Path ����
	sub_folder_list_->Insert(*new_folder);
	bool is_found = sub_folder_list_->Search(created_folder);
	if (is_found) {
		num_sub_folder_++;
		created_folder.SetPath();
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
	FolderType folder_change;
	bool is_found = false;    // �̸� �ٲ� ������ ã�Ҵ��� ����

	// �ٲ� ���� ã��
	cout << "\tinput name of folder to change" << endl;
	folder_change.SetNameFromKeyboard();
	is_found = sub_folder_list_->Search(folder_change);

	// �ٲ� ���� ������ ���� �޼��� ����ϰ� ����
	if (!is_found) {
		cout << "\tfolder not found!" << endl;
		return 0;
	}
	 
	// �ٲ� ���� �̸� �ٲٱ�
	folder_change = sub_folder_list_->Get(folder_change);    // ���� �ٲ� ���� �����͸� Get
	sub_folder_list_->Remove(folder_change);    // ������ ���� ����Ʈ���� �����ϰ�
	cout << "\tinput name to change" << endl;
	folder_change.SetNameFromKeyboard();
	sub_folder_list_->Insert(folder_change);	// �ٽ� ����

	return 1;
} 

// Get sub folder by name
FolderType* FolderType::GetSubFolder() {
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
int FolderType::RetrieveFolderByName() {
	FolderType retrieving_folder;
	bool is_found = false;

	retrieving_folder.SetNameFromKeyboard(); //name�� �Է¹޴´�.

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
		cout << "\tFolder not found" << endl;
		return 1;
	}

	return 0;
}

// Display all sub folders of this folder
void FolderType::DisplayAllSubFolders() {
	FolderType displayed_folder;

	cout << "\n\tSub Folder list" << endl;
	sub_folder_list_->Print(cout, INORDER);
}
