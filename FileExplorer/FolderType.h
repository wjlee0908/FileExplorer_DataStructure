#ifndef _FOLDERTYPE_H
#define _FOLDERTYPE_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <time.h>
#include <iomanip>
#include "SortedLinkedList.h"
#include "SortedDoublyLinkedList.h"


using namespace std;

/**
*	Relation between two items.
*/
enum RelationType {LESS, GREATER, EQUAL};


/**
*	item information class.
*/
class FolderType
{
public:
	/**
	*	default constructor.
	*/
	FolderType()
	{
		size_ = 0;
		sub_folder_list_ = NULL;
		num_sub_folder_ = 0;
		name_ = "";
		path_ = new LinkedList<FolderType*>;
		GenerateCreatedDate();
		parent_folder_ = NULL;
	}

	/**
	*	destructor.
	*/
	~FolderType()	
	{
		if (num_sub_folder_ != 0) {
			delete sub_folder_list_;
		}
		// delete path_;
	}

	/**
	*    copy constructor
	*/
	FolderType(const FolderType &copied_data);

	/**
	*	@brief	Get folder size.
	*	@pre	folder size is set.
	*	@post	none.
	*	@return	folder size.
	*/
	int GetSize() 
	{
		return size_;
	}

	/**
	*	@brief	Get number of sub folders.
	*	@pre	number of sub folder is set
	*	@post	none.
	*	@return	number of sub folders.
	*/
	int GetNumSubFolder() {
		return num_sub_folder_;
	}

	/**
	*	@brief	Get parent folder.
	*	@pre	parent folder is set.
	*	@post	none.
	*	@return	adderss of parent folder.
	*/
	FolderType* GetParentFolder() {
		return parent_folder_;
	}

	/**
	*	@brief	Get copy of sub folders list.
	*	@pre	sub folders are set
	*	@post	none.
	*	@return	address of sub folders list.
	*/
	const SortedDoublyLinkedList<FolderType>* GetSubFolders() {
		return sub_folder_list_;
	}

	/**
	*	@brief	Get folder name.
	*	@pre	folder name is set.
	*	@post	none.
	*	@return	folder name.
	*/
	string GetName()
	{
		return name_;
	}

	/**
	*	@brief	Get folder path
	*	@pre	folder path is set.
	*	@post	none.
	*	@return	folder path.
	*/
	LinkedList<FolderType*>* GetPath()
	{
		// return path_string_;
		return path_;
	}

	/**
	*	@brief	Get folder path to string type.
	*	@pre	folder path is set.
	*	@post	none.
	*	@return	folder path string.
	*/
	string GetPathString();

	/**
	*	@brief	Get created date.
	*	@pre	folder path is set.
	*	@post	none.
	*	@return	folder path.
	*/
	string GetCreatedDate() {
		return created_date_;
	}

	/**
	*	@brief	Returns wheter this folder is root folder.
	*	@pre	parent folder is set.
	*	@post	none.
	*	@return	boolean that expresses whether this is root folder.
	*/
	bool IsRootFolder() {
		return (parent_folder_ == NULL);
	}

	/**
	*	@brief	Set folder name.
	*	@pre	none.
	*	@post	folder name is set.
	*           name's position is sorted
	*	@param	input_name	folder name.
	*   @return return 1 if this function works well, otherwise 0.
	*/
	int SetName(string input_name);

	/**
	*	@brief	Set folder path using folder name and parent folder
	*	@pre	parent folder is set.
	*	@post	folder path is set.
	*/
	void SetPath();
	
	/**
	*	@brief	Generate folder's created date.
	*	@pre	none.
	*	@post	folder's created date is set.
	*/
	void GenerateCreatedDate();

	/**
	*	@brief	Set folder record.
	*	@pre	none.
	*	@post	folder record is set.
	*	@param	input_name	folder name.
	*   @param  input_parent    input parent folder
	*/
	void SetRecord(string input_name, FolderType* input_parent)
	{
		SetName(input_name);
		parent_folder_ = input_parent;
		SetPath();
		GenerateCreatedDate();
	}

	/**
	*	@brief	Display folder size on screen.
	*	@pre	folder size is set.
	*	@post	folder size is on screen.
	*/
	void DisplaySizeOnScreen() {
		cout << "\tFolder Size : " << size_ << endl;
	}

	/**
	*	@brief	Display number of sub folders on screen.
	*	@pre	num_sub_folder is set.
	*	@post	number of sub folders is on screen.
	*/
	void DisplayNumOfSubFoldersOnScreen() {
		cout << "\tNumber of Sub folders : " << size_ << endl;
	}

	/**
	*	@brief	Display folder name on screen.
	*	@pre	folder name is set.
	*	@post	folder name is on screen.
	*/
	void DisplayNameOnScreen() 
	{
		cout << "\tName : " << name_ << endl; 
	}

	/**
	*	@brief	Display folder path on screen.
	*	@pre	folder path is set.
	*	@post	folder path is on screen.
	*/
	void DisplayPathOnScreen() 
	{
		// cout << "\tPath : " << path_string_ << endl; 
		cout << "\tPath : " << GetPathString() << endl;
	}

	/**
	*	@brief	Display folder's created date on screen
	*	@pre	folder's created time is set.
	*	@post	folder's  is on screen.
	*/
	void DisplayCreatedDateOnScreen() {
		cout << "\tCreated date : " << created_date_ << endl;
	}

	/**
	*	@brief	Display an folder record on screen.
	*	@pre	folder record is set.
	*	@post	folder record is on screen.
	*/
	void DisplayInformationOnScreen()
	{
		DisplayNameOnScreen();
		DisplayPathOnScreen();
		DisplayCreatedDateOnScreen();
	}

	/**
	*	@brief	Set folder name from keyboard.
	*	@pre	none.
	*	@post	folder name is set.
	*/
	void SetNameFromKeyboard();
	
	/**
	*	@brief	Set folder record from keyboard.
	*	@pre	none.
	*	@post	folder record is set.
	*/
	void SetRecordFromKeyboard();

	/**
	*	@brief	Copy parameter folder and assign to this folder.
	*	@pre	copied_data is set.
	*	@post	folder record is set.
	*   @param  copied_data    data to assign
	*   @return retrun this after assigning parameter.
	*/
	FolderType& operator= (const FolderType& copied_data);
	
	/**
	*	@brief	Returns whether this is less than comparing data.
	*            primary key is name.
	*	@pre	comparing_data is set.
	*	@post	folder record is set.
	*   @param  comparing_data    data to compare
	*   @return retruns boolean expresses whether this is less than comparing data.
	*/
	bool operator< (const FolderType& comparing_data);

	/**
	*	@brief	Returns whether this is equal to comparing data
	*			primary key is name.
	*	@pre	comparing_data is set.
	*	@post	folder record is set.
	*   @param  comparing_data    data to compare
	*   @return retruns boolean expresses whether whether this is equal to comparing data.
	*/
	bool operator== (const FolderType& comparing_data);

	/**
	*	@brief	Returns whether this is greater than comparing data.
	*			primary key is name.
	*	@pre	comparing_data is set.
	*	@post	folder record is set.
	*   @param  comparing_data    data to compare
	*   @return retruns boolean expresses whether this is greater than comparing data.
	*/
	bool operator> (const FolderType& comparing_data);

	/**
	*	@brief	Add sub folder of this folder.
	*	@pre	none.
	*	@post	new sub folder is added.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int AddSubFolder();

	/**
	*	@brief  Delete sub folder by name
	*	@pre	sub folder list is set.
	*	@post	none.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int DeleteSubFolder();

	/**
	*	@brief  Change one sub folder's name
	*	@pre	sub folder list is set.
	*	@post	none.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int ChangeSubFolderName();

	/**
	*	@brief  Get sub folder by name
	*	@pre	sub folder list is set.
	*	@post	reference prameter is set.
	*   @param  folder    folder reference that user tried to find.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	FolderType* GetSubFolder();

	/**
	*	@brief  Retrieve folder by folder name.
	*	@pre	sub folder list is set.
	*	@post	none.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int RetrieveFolderByName();

	/**
	*	@brief  Display all sub folders information on screen.
	*	@pre	sub folder list is set.
	*	@post	sub folder list is diaplyed on screen.
	*/
	void DisplayAllSubFolders();

	/**
	*	@brief	Read a record from file.
	*	@pre	the target file is opened.
	*	@post	folder record is set.
	*	@param	fin	file descriptor.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int ReadDataFromFile(ifstream& fin);

	/**
	*	@brief	Write a record into file.
	*	@pre	the target file is opened. And the list should be initialized.
	*	@post	the target file is included the new folder record.
	*	@param	fout	file descriptor.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int WriteDataToFile(ofstream& fout);

protected:
	string name_;		///< folder name.

	int size_;          ///< folder size.
	int num_sub_folder_;    ///< number of sub folders.
	LinkedList<FolderType*>* path_;    ///< folder path list.
	string created_date_;    ///< date that folder created.
	SortedDoublyLinkedList<FolderType>* sub_folder_list_;   ///< sorted sub folder list
	FolderType* parent_folder_;    ///< address of parent folder

private:
	/**
	*	@brief	Copy parameter folder and assign to this folder. (deep copy)
	*	@pre	copide_object is set.
	*	@post	folder record is set.
	*   @param  copied_object    object to assign
	*/
	void AssignCopy(const FolderType& copied_object);

	/**
	*	@brief	Finds the folder that its name duplicates and return its result.
	*	@pre	sub folder name is set.
	*	@post	none.
	*   @param  folder_find    folder to find.
	*   @return retruns boolean expresses whether duplicated folder is exist.
	*/
	bool IsDupliactedSubFolderExists(FolderType folder_find);

	/**
	*	@brief	Compare two folders by folder name.
	*	@pre	two folders should be initialized.
	*	@post	none.
	*	@param	data	target folder for comparing.
	*	@return	return LESS if this.name < data.name,
	*			return GREATER if this.name > data.name then,
	*			otherwise return EQUAL.
	*/
	RelationType CompareByName(const FolderType &data);
};

#endif	// _FOLDERTYPE_H
