#include "FolderType.h"
#include "SortedArrayList.h"

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

// Set folder id from keyboard.
void FolderType::SetIdFromKeyboard()
{
	cout << "\tID : ";
	cin >> id_;
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
	SetIdFromKeyboard();
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

// add sub folder into sub folder list.
int FolderType::AddSubFolder() {
	FolderType new_folder;
	string new_folder_path;

	if (num_sub_folder_ == 0) {
		sub_folder_list_ = new SortedArrayList;
	}
	// 리스트 차면 폴더 추가 실패
	else if(sub_folder_list_->IsFull()) {
		return 0;
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

	if (sub_folder_list_->Add(&new_folder)) {
		num_sub_folder_++;
	}

	return 1;
}


// Read a record from file.
int FolderType::ReadDataFromFile(ifstream& fin)
{
	fin >> id_;
	fin >> name_;
	fin >> path_;

	return 1;
};


// Write a record into file.
int FolderType::WriteDataToFile(ofstream& fout)
{
	fout << endl;
	fout << id_ << " ";
	fout << name_ << " ";
	fout << path_;

	return 1;
}


// Compare two folder types.
RelationType FolderType::CompareByID(const FolderType &data)
{
	if(this->id_ > data.id_)
		return GREATER;
	else if(this->id_ < data.id_)
		return LESS;
	else
		return EQUAL;
}

int FolderType::DeleteFolder() {
	FolderType deleting_folder;
	int is_delete_suceed = 0;

	deleting_folder.SetIdFromKeyboard();
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

// Retrieve folders containing finding name
int FolderType::RetrieveFolderByName() {
	FolderType retrieving_folder;
	FolderType iterator;    // 리스트 탐색할 item
	bool is_found = false;

	retrieving_folder.SetNameFromKeyboard(); //name을 입력받는다.

	sub_folder_list_->ResetList();
	// 리스트 순차 탐색
	while (sub_folder_list_->GetNextItem(iterator) != -1) {
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

	// list의 모든 데이터를 화면에 출력
	sub_folder_list_->ResetList();
	int current_index = sub_folder_list_->GetNextItem(displayed_folder);
	while (current_index < num_sub_folder_ && current_index != -1) {
		displayed_folder.DisplayInformationOnScreen();
		current_index = sub_folder_list_->GetNextItem(displayed_folder);
	}
}
