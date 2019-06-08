#ifndef _FOLDERTYPE_H
#define _FOLDERTYPE_H

#include "ItemType.h"
#include "BinarySearchTree.h"
#include "FileType.h"

using namespace std;

class FileType;

/**
*	folder information class.
*/
class FolderType : public ItemType
{
public:
	/**
	*	default constructor.
	*/
	FolderType()
	{
		ItemType::ItemType();
		sub_folder_list_ = nullptr;
		file_list_ = nullptr;
		num_sub_folder_ = 0;
	}

	/**
	*	destructor.
	*/
	~FolderType()	
	{
		ItemType::~ItemType();
		if (num_sub_folder_ != 0) {
			delete sub_folder_list_;
		}
	}

	/**
	*    copy constructor
	*/
	FolderType(const FolderType &copied_data);

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
	const BinarySearchTree<FolderType>* GetSubFolders() {
		return sub_folder_list_;
	}

	/**
	*	@brief	Set folder path using item name and parent folders
	*	@pre	parent folder is set.
	*	@post	folder path is set.
	*/
	virtual void SetPath() override;

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
	*	@brief	Display number of sub folders on screen.
	*	@pre	num_sub_folder is set.
	*	@post	number of sub folders is on screen.
	*/
	void DisplayNumOfSubFoldersOnScreen() {
		cout << "\tNumber of Sub folders : " << num_sub_folder_ << endl;
	}

	/**
	*	@brief	Add sub folder of this folder.
	*	@pre	none.
	*	@post	new sub folder is added.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int AddSubFolder();

	/**
	*	@brief	Add file in this folder.
	*	@pre	none.
	*	@post	new file is added.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int AddFile();

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

	/**
	*	@brief	Copy parameter folder and assign to this folder.
	*	@pre	copied_data is set.
	*	@post	folder record is set.
	*   @param  copied_data    data to assign
	*   @return retrun this after assigning parameter.
	*/
	FolderType& operator= (const FolderType& copied_data);

protected:
	int num_sub_folder_;    ///< number of sub folders.
	BinarySearchTree<FolderType>* sub_folder_list_;   ///< sorted sub folder list
	BinarySearchTree<FileType>* file_list_;    ///< sorted file list

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
};

#endif	// _FOLDERTYPE_H
