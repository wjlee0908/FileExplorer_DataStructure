#pragma once
#ifndef _ITEMTYPE_H
#define _ITEMTYPE_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <time.h>
#include <iomanip>

#include "DoublyLinkedList.h"

using namespace std;

class FolderType;

/**
*	Relation between two items.
*/
enum RelationType { LESS, GREATER, EQUAL };

/**
*   item that included in file explorer
*/
class ItemType
{
public:
	/**
	*	default constructor.
	*/
	ItemType() : ItemType("", 0, nullptr) {}

	ItemType(string name, int size, FolderType* parent_folder)
		: name_(name), size_(size), parent_folder_(parent_folder_) {
		GenerateCreatedTime();
	}

	/**
	*	destructor.
	*/
	~ItemType();

	/**
	*    copy constructor
	**/
	ItemType(const ItemType &copied_data);

	/**
	*	@brief	Get Item name.
	*	@pre	Item name is set.
	*	@post	none.
	*	@return	Item name.
	*/
	string GetName() const { return this->name_; }


	/**
	*	@brief	Get size.
	*	@pre	item size is set.
	*	@post	none.
	*	@return	size.
	*/
	int GetSize() const { return this->size_; }

	/**
	*	@brief	Get Item path list.
	*	@pre	Item path is set.
	*	@post	none.
	*	@return	Item path.
	*/
	DoublyLinkedList<FolderType*> GetPath() { return this->path_; }

	/**
	*	@brief	Get item path by string type.
	*	@pre	item path is set.
	*	@post	none.
	*	@return	item path string.
	*/
	string GetPathString() const;

	/**
	*	@brief	Get Created time.
	*	@pre	Created time is set.
	*	@post	none.
	*	@return	Created time.
	*/
	string GetCreatedTime() const { return this->created_time_; }

	/**
	*	@brief	Set Item Name.
	*	@pre	none.
	*	@post	Item Name is set.
	*	@param	name	Item name to set.
	*/
	void SetName(string name) { this->name_ = name; };

	/**
	*	@brief	Set Item Size.
	*	@pre	none.
	*	@post	Item size is set.
	*	@param	size	Item size to set.
	*/
	void SetSize(int size) { this->size_ = size; };

	/**
	*	@brief	Set item path using item name and parent folders
	*	@pre	parent folder is set.
	*	@post	item path is set.
	*/
	virtual void SetPath();

	/**
	*	@brief	Set item attributes.
	*	@pre	none.
	*	@post	item attributes are set.
	*	@param	name	item name.
	*   @param  parent_folder    input parent folder
	*/
	virtual void SetAttributes(string name, FolderType* parent_folder) {
		SetName(name);
		parent_folder_ = parent_folder;
		SetPath();
		GenerateCreatedTime();
	}

	/**
	*	@brief	Display item name on screen.
	*	@pre	item name is set.
	*	@post	item name is on screen.
	*/
	void DisplayNameOnScreen() const
	{
		cout << "\tName : " << name_ << endl;
	}


	/**
	*	@brief	Display item size on screen.
	*	@pre	item size is set.
	*	@post	item size is on screen.
	*/
	void DisplaySizeOnScreen() const {
		cout << "\tSize : " << size_ << endl;
	}

	/**
	*	@brief	Display item path on screen.
	*	@pre	item path is set.
	*	@post	item path is on screen.
	*/
	void DisplayPathOnScreen() const
	{
		cout << "\tPath : " << GetPathString() << endl;
	}

	/**
	*	@brief	Display item's created time on screen
	*	@pre	item's created time is set.
	*	@post	item's  is on screen.
	*/
	void DisplayCreatedTimeOnScreen() const {
		cout << "\tCreated time : " << created_time_ << endl;
	}

	/**
	*	@brief	Display an item information on screen.
	*	@pre	item information is set.
	*	@post	item information is on screen.
	*/
	virtual void DisplayInformationOnScreen() const
	{
		DisplayNameOnScreen();
		DisplayPathOnScreen();
		DisplaySizeOnScreen();
		DisplayCreatedTimeOnScreen();
	}

	/**
	*	@brief	Set item name from keyboard.
	*	@pre	none.
	*	@post	item name is set.
	*/
	void SetNameFromKeyboard();

	/**
	*	@brief	Set item attributes from keyboard.
	*	@pre	none.
	*	@post	item attributes are set.
	*/
	virtual void SetAttributesFromKeyboard();

	/**
	*	@brief	Doing Deep copy by assignment operator.
	*	@pre	copied item is set
	*	@post	this is set.
	*	@param	copied_item that you want to copy
	*	@return	return self-reference after copy
	*/
	ItemType& operator= (const ItemType& copied_item);

	/**
	*	@brief	Returns whether this is greater than comparing data.
	*            primary key is name.
	*	@pre	comparing_data is set.
	*	@post	none.
	*   @param  comparing_data    data to compare
	*   @return retruns boolean expresses whether this is greater than comparing data.
	*/
	bool operator> (const ItemType& comparing_data) const { return (CompareByName(comparing_data) == GREATER); }

	/**
	*	@brief	Returns whether this is less than comparing data.
	*            primary key is name.
	*	@pre	comparing_data is set.
	*	@post	none.
	*   @param  comparing_data    data to compare
	*   @return retruns boolean expresses whether this is less than comparing data.
	*/
	bool operator< (const ItemType& comparing_data) const { return (CompareByName(comparing_data) == LESS); }

	/**
	*	@brief	Returns whether this is equal to comparing data
	*			primary key is name.
	*	@pre	comparing_data is set.
	*	@post	none.
	*   @param  comparing_data    data to compare
	*   @return retruns boolean expresses whether whether this is equal to comparing data.
	*/
	bool operator== (const ItemType& comparing_data) const { return (CompareByName(comparing_data) == EQUAL); }

	/**
	*	@brief	output stream 출력 함수 오버로딩
	*	@pre	item is set.
	*	@post	item name is printed in stream.
	*   @param  os    output stream
	*   @param  item  item to print
	*   @return retruns output stream
	*/
	friend ostream& operator<<(ostream& os, const ItemType& item);

protected:
	/**
	*	@brief	Copy parameter item and assign to this item. (deep copy)
	*	@pre	copide_object is set.
	*	@post	item record is set.
	*   @param  copied_object    object to assign
	*/
	virtual void AssignCopy(const ItemType& copied_object);

	/**
	*	@brief	Compare two folders by folder name.
	*	@pre	two folders should be initialized.
	*	@post	none.
	*	@param	data	target folder for comparing.
	*	@return	return LESS if this.name < data.name,
	*			return GREATER if this.name > data.name then,
	*			otherwise return EQUAL.
	*/
	RelationType CompareByName(const ItemType &data) const;

	string name_;		///< item name.
	int size_;          ///< item size.
	DoublyLinkedList<FolderType*> path_;    ///< folder path list.
	string created_time_;    ///< time that item created.
	FolderType* parent_folder_;    ///< adderess of folder that includes this item

private:
	/**
	*	@brief	Generate item's created time.
	*	@pre	none.
	*	@post	item's created time is set.
	*/
	void GenerateCreatedTime();
};

#endif	// _ITEMTYPE_H