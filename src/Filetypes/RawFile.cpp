/* 
 * File:   RawFile.cpp
 * Author: metalhead33
 * 
 * Created on 2017. február 24., 17:03
 */

#include "RawFile.hpp"
#include "Global.hpp"

namespace Dea {
RawFile::RawFile(Directory* parent, std::string name,void* ptr,size_t size)
	: File(parent,name)
{
	raw_data = ptr;
	data_size = size;
	cactivated = false;
}
RawFile::RawFile(Directory* parent, std::string name,size_t size)
	: File(parent,name)
{
	raw_data = malloc(size);
	data_size = size;
	cactivated = true;
}

RawFile::~RawFile() {
	Free();
}

bool RawFile::IsCactivated()
{
	return cactivated;
}
void* RawFile::GetPointer()
{
	return raw_data;
}
size_t RawFile::GetSize()
{
	return data_size;
}

void RawFile::Malloc(size_t new_size)
{
	raw_data = malloc(new_size);
	data_size = new_size;
	cactivated = true;
}

void RawFile::Free()
{
	if(cactivated)
	{
		free(raw_data);
		data_size = 0;
		cactivated = false;
	}
}

void RawFile::SetPointer(void* new_ptr,size_t new_size)
{
	if(cactivated) Free();
	raw_data = new_ptr;
	data_size = new_size;
}

void RawFile::Serialize(AbstractFwrite* file_handle)
{
	uint32_t sizeoff = data_size;
	IF_DEBUG(
	std::cout << "[" << this << "]: Serializing raw file with size" << sizeoff << ".\n";
	)
	File::Serialize(file_handle);
	file_handle->write(&sizeoff,sizeof(int32_t));
	file_handle->write(raw_data,data_size);
}

Filetype RawFile::GetFiletype()
{
	return raw;
}

}