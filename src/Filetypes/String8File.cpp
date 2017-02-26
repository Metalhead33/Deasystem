/* 
 * File:   String8File.cpp
 * Author: metalhead33
 * 
 * Created on 2017. február 24., 17:28
 */

#include "String8File.hpp"
#include "Global.hpp"
namespace Dea {

String8File::String8File(Directory* parent, std::string name, std::string content)
	: File(parent,name)
{
	m_content = content;
}

std::string* String8File::GetContent()
{
	return &m_content;
}

void String8File::SetContent(std::string new_content)
{
	m_content = new_content;
}
	
String8File::~String8File() {
}

void String8File::Serialize(AbstractFwrite* file_handle)
{
	File::Serialize(file_handle);
	uint32_t size = m_content.size()+1;
	IF_DEBUG(
	std::cout << "[" << this << "]: Serializing String8 file with size" << size << ".\n";
	)
	file_handle->write(&size,sizeof(uint32_t));
	file_handle->write((void*)m_content.c_str(),m_content.size()+1);
}
Filetype String8File::GetFiletype()
{
	return string8;
}

}