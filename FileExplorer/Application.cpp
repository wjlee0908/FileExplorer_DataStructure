#include "Application.h"


void Application::InitializeRootFolder() {
	root_folder_.SetAttributes("/", NULL);
	current_folder_ = &root_folder_;
}

// Program driver.
void Application::Run()
{
	while(1)
	{
		cout << endl << endl;
		DisplayWoringDirectory();
		menu_command_ = GetCommand();

		switch(menu_command_)
		{
		case 1:		// make new folder
			MakeNewFolder();
			break;
		case 2:    // open sub folder
			OpenSubFolder();
			break;
		case 3:		// Open parent folder
			OpenParentFolder();
			break;
		case 4:    // Go to previous folder in history
			GoToPreviousFolder();
			break;
		case 5:    // Go to next folder in history
			// GoToNextFolder();
			break;
		case 6:		//delete sub folder
			DeleteFolder();
			break;
		case 7:   // change folder name
			ChangeFolderName();
			break;
		case 8:		//display property of current folder
			DisplayProperty();
			break;
		case 9:    //search sub folder by name.
			RetriveFolderByName();
			break;
		case 10:   // make new file
			// MakeNewFile();
			break;
		case 11:   // open file
			// OpenFile();
			break;
		case 12:		// display properties of all folders
			DisplayAllSubFolders();
			break;
		case 13:    // display name of all recent folders.
			DisplayRecentFolders();
			break;
		case 0:
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
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : Make new folder" << endl;
	cout << "\t   2 : Open folder" << endl;
	cout << "\t   3 : Open parent folder" << endl;
	cout << "\t   4 : Go to previous folder" << endl;
	cout << "\t   5 : Go to next folder" << endl;
	cout << "\t   6 : Delete sub folder" << endl;
	cout << "\t   7 : Change folder name" << endl;
	cout << "\t   8 : Print folder property" << endl;
	cout << "\t   9 : Retrieve folder by name" << endl;
	cout << "\t   10 : Make new file" << endl;
	cout << "\t   11 : Open file" << endl;
	cout << "\t   12 : Print all sub folders on screen" << endl;
	cout << "\t   13 : Print recent folders" << endl;
	cout << "\t   0 : Quit" << endl; 

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
int Application::OpenSubFolder()
{
	FolderType* folder_open;	// address of folder to open

	// 1. find folder to open
	folder_open = current_folder_->GetSubFolder();

	// 2. current folder <- found folder
	if (folder_open != NULL) {
		OpenFolder(folder_open);
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

	if (parent_folder != NULL) {
		current_folder_ = parent_folder;	// change current folder to parent folder.
		return 1;
	}
	else {
		cout << "\tparent folder doesn't exist" << endl;
		return 0;
	}

}

// open previous folder in folder history.
int Application::GoToPreviousFolder()
{
	try {
		// ���� �ڷ� ���⸦ ���� �ڷ� �� folder�� history�� �������� ����.
		// ���� open folder �޼ҵ� ��� �� ��.
		current_folder_ = folder_history_.Pop();
	}
	catch(ExceptionEmptyStack exception) {
		cout << "\terror: no folders in history" << endl;
		return 0;
	}
	return 1;
}

void Application::DisplayProperty() const {
	current_folder_->DisplayInformationOnScreen();
}

// displays current working directory.
void Application::DisplayWoringDirectory() const
{
	cout << "\tWorking Directory" << endl;
	current_folder_->DisplayPathOnScreen();
}

//�̸��� �Է¹��� item���� ����Ʈ���� item�� ã�Ƽ� ����Ѵ�.
int Application::RetriveFolderByName() const
{
	return current_folder_->RetrieveFolderByName();
}

// Change Folder name
int Application::ChangeFolderName()
{
	current_folder_->ChangeSubFolderName();
	current_folder_->DisplayAllSubFolders();
	return 1;

}

// Open folder
void Application::OpenFolder(FolderType * folder_to_open)
{
	folder_history_.Push(current_folder_);	// ���� ���� �ִ� ������ �����丮�� ����
	current_folder_ = folder_to_open;
	AddToRecentFolders(current_folder_);   // �� ������ �ֱ� ��� ������ �߰�
}

// Add folder to Recent folder queue
void Application::AddToRecentFolders(FolderType * folder)
{
	// �� á���� ���� ������ �������� dequeue.
	if (recent_folders_.IsFull()) {
		recent_folders_.DeQueue();
	}
	recent_folders_.EnQueue(folder);
}

//id�� item�� ã�Ƽ� �����Ѵ�.
int Application::DeleteFolder()
{
	int result = current_folder_->DeleteSubFolder();
	current_folder_->DisplayAllSubFolders();

	return result;
}

// Display all sub folders of current folder on screen.
void Application::DisplayAllSubFolders() const
{
	current_folder_->DisplayAllSubFolders();
}

// Display all recent folders on screen.
void Application::DisplayRecentFolders() const
{
	CircularQueue<FolderType*> folders;    // folders to display
	string folder_name;    // folder name to display.
	
	folders = recent_folders_;    // dequeue�ϸ鼭 print�ϱ� ���� ����
	
	cout << "\t";
	while (!folders.IsEmpty()) {
		folder_name = folders.DeQueue()->GetName();
		cout << folder_name << " ";
	}
	cout << endl;

}


// Open a file by file descriptor as an input file.
int Application::OpenInFile(char *fileName)
{
	input_file_.open(fileName);	// file open for reading.
	
	// ���� ���¿� �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	if(!input_file_)	return 0;
	else	return 1;
}


// Open a file by file descriptor as an output file.
int Application::OpenOutFile(char *fileName)
{
	output_file_.open(fileName);	// file open for writing.

	// ���� ���¿� �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	if(!output_file_)	return 0;
	else	return 1;
}

/*
// Open a file as a read mode, read all data on the file, and set list by the data.
int Application::ReadDataFromFile()
{
	int index = 0;
	FolderType data;	// �б�� �ӽ� ����
	
	char filename[FILENAMESIZE];
	cout << "\n\tEnter Input file Name : ";
	cin >> filename;

	// file open, open error�� �߻��ϸ� 0�� ����
	if(!OpenInFile(filename))
		return 0;

	// ������ ��� ������ �о� list�� �߰�
	while(!input_file_.eof())
	{
		// array�� �л����� ������ ����ִ� structure ����
		data.ReadDataFromFile(input_file_);
	}

	input_file_.close();	// file close

	// ���� list ���
	DisplayAllSubFolders();

	return 1;
}
*/

/*
// Open a file as a write mode, and write all data into the file,
int Application::WriteDataToFile()
{
	
	SortedArrayList* data;	// ����� �ӽ� ����

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Output file Name : ";
	cin >> filename;

	// file open, open error�� �߻��ϸ� 0�� ����
	if(!OpenOutFile(filename))
		return 0;

	// list �����͸� �ʱ�ȭ
	data->ResetList();

	// list�� ��� �����͸� ���Ͽ� ����
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