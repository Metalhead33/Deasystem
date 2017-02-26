/* 
 * File:   String16File.cpp
 * Author: metalhead33
 * 
 * Created on 2017. február 24., 17:47
 */

#include "String16File.hpp"
#include "Global.hpp"

namespace Dea {

String16File::String16File(Directory* parent, std::string name, std::u16string content)
	: File(parent,name)
{
	m_content = content;
}

std::u16string* String16File::GetContent()
{
	return &m_content;
}

void String16File::SetContent(std::u16string new_content)
{
	m_content = new_content;
}
	
String16File::~String16File() {
}

void String16File::Serialize(AbstractFwrite* file_handle)
{
	File::Serialize(file_handle);
	uint32_t size = m_content.size()+1;
	IF_DEBUG(
	std::cout << "[" << this << "]: Serializing String16 file with size" << size << ".\n";
	)
	file_handle->write(&size,sizeof(uint32_t));
	file_handle->write((void*)m_content.c_str(),(m_content.size()+1)*sizeof(char16_t));
}
Filetype String16File::GetFiletype()
{
	return string16;
}
}