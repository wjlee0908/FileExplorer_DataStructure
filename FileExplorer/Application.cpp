#include "Application.h"


void Application::InitializeRootFolder() {
	root_folder_.SetRecord("/", NULL);
	current_folder_ = &root_folder_;
}

// Program driver.
void Application::Run()
{
	while(1)
	{
		menu_command_ = GetCommand();

		switch(menu_command_)
		{
		case 1:		// make new folder
			MakeNewFolder();
			break;
		case 2:    // open sub folder
			OpenFolder();
			break;
		case 3:		// Open parent folder
			OpenParentFolder();
			break;
		case 4:		//delete sub folder
			DeleteFolder();
			break;
		case 5:    //search sub folder by name.
			RetriveFolderByName();
			break;
		case 6:   // change folder name
			ChangeFolderName();
			break;
		case 7:		//display property of current folder
			DisplayProperty();
			break;
		case 8:   // make new file
			// MakeNewFile();
			break;
		case 9:   // open file
			// OpenFile();
			break;
		case 10:		// display properties of all folders
			DisplayAllSubFolders();
			break;
		case :
			return;
		default:
			cout << "\tIllegal selection...\n";
			break;
		}
	}
}


// Display command on screen and get a input from keyboard.
int Application::GetCommand()
{
	int command;
	cout << endl << endl;
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : Make new folder" << endl;
	cout << "\t   2 : Open folder" << endl;
	cout << "\t   3 : Open parent folder" << endl;
	cout << "\t   4 : Delete sub folder" << endl;
	cout << "\t   5 : Retrieve folder by name" << endl;
	cout << "\t   6 : Change folder name" << endl;
	cout << "\t   7 : Print folder property" << endl;
	cout << "\t   8 : Make new file" << endl;
	cout << "\t   9 : Open file" << endl;
	cout << "\t   10 : Print all sub folders on screen" << endl;
	cout << "\t   11 : Quit" << endl; 

	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}

// Add new folder into current folder.
int Application::MakeNewFolder()
{
	int is_add_suceed = 0;

	is_add_suceed = current_folder_->AddSubFolder();

	DisplayAllSubFolders();

	return is_add_suceed;

}

// change current folder
int Application::OpenFolder()
{
	// current folder address = found folder address
	FolderType* folder_open;	// address of folder to open

	folder_open = current_folder_->GetSubFolder();

	if (folder_open != NULL) {
		current_folder_ = folder_open;
		return 1;
	}
	else {
		cout << "\tfolder not found" << endl;
		return 0;
	}
}

int Application::OpenParentFolder()
{
	FolderType* parent_folder;
	parent_folder = current_folder_->GetParentFolder();

	if (parent_folder == NULL) {
		cout << "\tparent folder doesn't exist" << endl;
		return 0;
	}
	else {
		current_folder_ = parent_folder;
		return 1;
	}

}

void Application::DisplayProperty() {
	current_folder_->DisplayInformationOnScreen();
}

//이름을 입력받은 item으로 리스트에서 item을 찾아서 출력한다.
int Application::RetriveFolderByName()
{

	return current_folder_->RetrieveFolderByName();
}

// Change Folder name
int Application::ChangeFolderName()
{
	
	FolderType* folder_change;	// address of folder to change name

	cout << "\t input name of folder to change" << endl;
	folder_change = current_folder_->GetSubFolder();

	if (folder_change == NULL) {
		cout << "\tfolder not found" << endl;
		return 0;
	}
	
	folder_change->SetNameFromKeyboard();
	return 1;

}

//id로 item을 찾아서 제거한다.
int Application::DeleteFolder()
{
	int result = current_folder_->DeleteSubFolder();
	current_folder_->DisplayAllSubFolders();

	return result;
}

// Display all sub folders of current folder on screen.
void Application::DisplayAllSubFolders()
{
	current_folder_->DisplayAllSubFolders();
}


// Open a file by file descriptor as an input file.
int Application::OpenInFile(char *fileName)
{
	input_file_.open(fileName);	// file open for reading.
	
	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if(!input_file_)	return 0;
	else	return 1;
}


// Open a file by file descriptor as an output file.
int Application::OpenOutFile(char *fileName)
{
	output_file_.open(fileName);	// file open for writing.

	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if(!output_file_)	return 0;
	else	return 1;
}

/*
// Open a file as a read mode, read all data on the file, and set list by the data.
int Application::ReadDataFromFile()
{
	int index = 0;
	FolderType data;	// 읽기용 임시 변수
	
	char filename[FILENAMESIZE];
	cout << "\n\tEnter Input file Name : ";
	cin >> filename;

	// file open, open error가 발생하면 0을 리턴
	if(!OpenInFile(filename))
		return 0;

	// 파일의 모든 내용을 읽어 list에 추가
	while(!input_file_.eof())
	{
		// array에 학생들의 정보가 들어있는 structure 저장
		data.ReadDataFromFile(input_file_);
	}

	input_file_.close();	// file close

	// 현재 list 출력
	DisplayAllSubFolders();

	return 1;
}
*/

/*
// Open a file as a write mode, and write all data into the file,
int Application::WriteDataToFile()
{
	
	SortedArrayList* data;	// 쓰기용 임시 변수

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Output file Name : ";
	cin >> filename;

	// file open, open error가 발생하면 0을 리턴
	if(!OpenOutFile(filename))
		return 0;

	// list 포인터를 초기화
	data->ResetList();

	// list의 모든 데이터를 파일에 쓰기
	int length = data->GetLength();
	int curIndex = data->GetNextItem();
	while(curIndex < length && curIndex != -1)
	{
		data.WriteDataToFile(output_file_);
		curIndex = folder_list_.GetNextItem(data);
	}

	output_file_.close();	// file close
	
	return 1;
}
*/