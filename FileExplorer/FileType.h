#pragma once
#include "ItemType.h"
class FileType : public ItemType
{
public:
	FileType() : ItemType::ItemType() {}

	FileType(string name, FolderType* parent_folder)
		: ItemType::ItemType(name, 0, parent_folder) {}

	~FileType() {}
};

