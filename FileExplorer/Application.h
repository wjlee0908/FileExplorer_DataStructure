#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "FolderType.h"

#define FILENAMESIZE 1024

/**
*	application class for item management simply.
*/
class Application
{
public:
	/**
	*	default constructor.
	*/
	Application()
	{
		menu_command_ = 0;
		InitializeRootFolder();
	}
	
	/**
	*	destructor.
	*/
	~Application()	{}

	/**
	*	@brief	Initialize root folder.
	*	@pre	none.
	*	@post	root folder is initialized.
	*/
	void InitializeRootFolder();

	/**
	*	@brief	Program driver.
	*	@pre	program is started.
	*	@post	program is finished.
	*/
	void Run();

	/**
	*	@brief	Display command on screen and get a input from keyboard.
	*	@pre	none.
	*	@post	none.
	*	@return	user's command.
	*/
	int GetCommand();

	/**
	*	@brief	make new folder.
	*	@pre	current folder should be initialized.
	*	@post	new folder is added into the current folder.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int MakeNewFolder();

	/**
	*	@brief	open sub folder.
	*	@pre	sub folders should be initialized.
	*	@post	current folder is changed to selected folder.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int OpenFolder();

	/**
	*	@brief	delete folder that matches input id
	*	@pre	current folder should be initialized
	*	@post	found item is deleted from folder
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int DeleteFolder();

	/**
	*	@brief	display current folder's property
	*	@pre	folder should be initialized.
	*	@post	folder property is displayed on screen.
	*/
	void DisplayProperty();

	/**
	*	@brief	Display all sub folders of current folder on screen.
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayAllSubFolders();

	/**
	*	@brief	Open a file by file descriptor as an input file.
	*	@pre	a file for reading is exist.
	*	@post	open the file for reading.
	*	@param	fileName	a filename to open for reading.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int OpenInFile(char *fileName);

	/**
	*	@brief	Open a file by file descriptor as an output file.
	*	@pre	current folder should be initialized.
	*	@post	open the file for writing.
	*	@param	fileName	a filename to open for writing.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int OpenOutFile(char *fileName);

	/**
	*	@brief	Retrieve folder by folder name.
	*	@pre	none.
	*	@post	prints all folders that contain input word.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int RetriveFolderByName();

	/**
	*	@brief	Change Folder name.
	*	@pre	folder to change name is set.
	*	@post	selected folder name is changed.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int ChangeFolderName();

	/**
	*	@brief	Open a file as a read mode, read all data on the file, and set current folder by the data.
	*	@pre	The file is not opened.
	*	@post	current folder holds all records from the file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	// int ReadDataFromFile();

	/**
	*	@brief	Open a file as a write mode, and write all data into the file,
	*	@pre	The file is not opened.
	*	@post	the current folder is stored in the output file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	// int WriteDataToFile();

private:
	ifstream input_file_;		///< input file descriptor.
	ofstream output_file_;		///< output file descriptor.
	FolderType root_folder_;    ///< default root folder
	FolderType* current_folder_;   ///< current working folder.
	int menu_command_;			///< current command number.
};

#endif	// _APPLICATION_H