#pragma once
#include "ItemType.h"
class FileType : public ItemType
{
public:
	FileType();
	FileType(string name, FolderType* parent_folder);
	~FileType();
};

