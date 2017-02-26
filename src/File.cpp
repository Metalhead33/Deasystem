/* 
 * File:   File.cpp
 * Author: metalhead33
 * 
 * Created on 2017. február 24., 16:37
 */

#include "File.hpp"

namespace Dea {
File::File(Directory* parent, std::string name)
	: Element(parent,name)
{
}

bool File::IsDirectory()
{
	return false;
}

bool File::IsData()
{
	return true;
}

File::~File() {
}

void File::Serialize(AbstractFwrite* file_handle)
{
	int8_t type = GetFiletype();
	Element::Serialize(file_handle);
	file_handle->write(&type,sizeof(int8_t));
}

}