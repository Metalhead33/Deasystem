/* 
 * File:   String32File.cpp
 * Author: metalhead33
 * 
 * Created on 2017. február 24., 18:04
 */

#include "String32File.hpp"
#include "Global.hpp"
namespace Dea {

String32File::String32File(Directory* parent, std::string name, std::u32string content)
	: File(parent,name)
{
	m_content = content;
}

std::u32string* String32File::GetContent()
{
	return &m_content;
}

void String32File::SetContent(std::u32string new_content)
{
	m_content = new_content;
}
	
String32File::~String32File() {
}

void String32File::Serialize(AbstractFwrite* file_handle)
{
	File::Serialize(file_handle);
	uint32_t size = m_content.size()+1;
	IF_DEBUG(
	std::cout << "[" << this << "]: Serializing String32 file with size" << size << ".\n";
	)
	file_handle->write(&size,sizeof(uint32_t));
	file_handle->write((void*)m_content.c_str(),(m_content.size()+1)*sizeof(char32_t));
}
Filetype String32File::GetFiletype()
{
	return string32;
}
}