/* 
 * File:   Element.cpp
 * Author: metalhead33
 * 
 * Created on 2017. február 23., 18:25
 */

#include "Element.hpp"
#include "Directory.hpp"
#include "Global.hpp"
namespace Dea {

/*Element::Element()
{
	;
}*/

Element::Element(Directory* parent, std::string name)
{
	m_parent = 0;
	SetParent(parent);
	m_name = name;
	IF_DEBUG(
	std::cout << "ELEMENT-[" << this << "]: Created element with the name " << name << " and parent [" << parent << "].\n";
	)
}

Element::~Element()
{
	SetParent(0);
	IF_DEBUG(
	std::cout << "ELEMENT-[" << this << "]: Deallocating.\n";
	)
}

std::string Element::GetName() const
{
	return m_name;
}

void Element::SetName(std::string new_name)
{
	IF_DEBUG(
	std::cout << "ELEMENT-[" << this << "]: Name set from " << m_name << " to " << new_name << ".\n";
	)
	m_name = new_name;
}

std::string Element::GetPath()
{
	if(m_parent) return m_parent->GetPath() + "/" + m_name;
	else return m_name;
}

Directory* Element::GetParent() const
{
	return m_parent;
}

void Element::SetParent(Directory* new_parent)
{
	if(m_parent)
	{
		m_parent->__RemoveElement(this);
	}
	if(new_parent)
	{
		new_parent->__AddElement(this);
	}
	__SetParent(new_parent);
}

	
void Element::__SetParent(Directory* new_parent)
{
	IF_DEBUG(
	std::cout << "ELEMENT-[" << this << "]: Parent changed from " << m_parent << " to " << new_parent << ".\n";
	)
	m_parent = new_parent;
}
void Element::Serialize(AbstractFwrite* file_handle)
{
	IF_DEBUG(
	std::cout << "ELEMENT-[" << this << "]: Serializing.\n";
	)
	std::string temp = GetPath();
	uint16_t size = temp.size()+1;
	file_handle->write(&size,sizeof(uint16_t));
	file_handle->write((void*)temp.c_str(),temp.size()+1);
}

}
