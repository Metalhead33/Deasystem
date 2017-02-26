/* 
 * File:   Directory.cpp
 * Author: metalhead33
 * 
 * Created on 2017. február 23., 18:48
 */

#include "Directory.hpp"
#include <exception>
#include "Global.hpp"
namespace Dea {

Directory::Directory(Directory* parent, std::string name,bool _isroot)
	: Element(parent,name)
{
	root = _isroot;
}

Directory::~Directory() {
	for(ElementIterator it=m_container.begin();it != m_container.end();++it)
	{
		(*it)->__SetParent(0);
		delete *it;
	}
}
bool Directory::IsDirectory()
{
	return true;
}
bool Directory::IsData()
{
	return false;
}
bool Directory::IsRoot()
{
	return root;
}
void Directory::SetRoot(bool set_root)
{
	root = set_root;
	IF_DEBUG(
	if(set_root) std::cout << "DIRECTORY-[" << this << "]: Set to ROOT - true.\n";
	else std::cout << "DIRECTORY-[" << this << "]: Set to ROOT - false.\n";
	)
}
void Directory::Serialize(AbstractFwrite* file_handle)
{
	if(!root){
	int8_t type = -1;
	Element::Serialize(file_handle);
	file_handle->write(&type,sizeof(int8_t));}
	for(ElementIterator it=m_container.begin();it != m_container.end();++it)
	{
		(*it)->Serialize(file_handle);
	}
	
}

ElementIterator Directory::IGetByRowSafe(int row)
{
	if(m_container.size() < row) throw -1;
	int i;
	ElementIterator it;
	for(it=m_container.begin(),i = 1;it != m_container.end() && i <= row;++it,++i);
	return it;
}
/*ElementIterator Directory::IGetByRowUnsafe(int row)
{
	if(m_container.size() < row) throw -2;
	ElementIterator it=m_container.begin() + (size_t)row;
	return it;
}*/
ElementIterator Directory::IGetByName(std::string name)
{
	for(ElementIterator it=m_container.begin();it != m_container.end();++it)
	{
		if((*it)->GetName() == name) return it;
	}
	throw -3;
}
ElementIterator Directory::IGetByPointer(Element* elem)
{
	for(ElementIterator it=m_container.begin();it != m_container.end();++it)
	{
		if((*it) == elem) return it;
	}
	throw -4;
}


Element* Directory::PGetByRowSafe(int row)
{
	try {
	return (*IGetByRowSafe(row));
	} catch(int e)
	{
		IF_DEBUG(
		std::cout << "DIRECTORY-[" << this << "]: Did not find row " << row <<".\n";
		)
		return 0;
	}
}

/*Element* Directory::PGetByRowUnsafe(int row)
{
	try {
	return (*IGetByRowUnsafe(row));
	} catch(int e)
	{
		return 0;
	}
}*/

Element* Directory::PGetByName(std::string name)
{
	try {
	return (*IGetByName(name));
	} catch(int e)
	{
		IF_DEBUG(
		std::cout << "DIRECTORY-[" << this << "]: Did not find the element " << name <<".\n";
		)
		return 0;
	}
}

Element* Directory::PGetByPointer(Element* elem)
{
	try {
	return (*IGetByPointer(elem));
	} catch(int e)
	{
		IF_DEBUG(
		std::cout << "DIRECTORY-[" << this << "]: Did not find the element [" << elem <<"].\n";
		)
		return 0;
	}
}

void Directory::__AddElement(Element* elem)
{
	IF_DEBUG(
	std::cout << "DIRECTORY-[" << this << "]: Adding element [" << elem <<"] to the list of children.\n";
	)
	m_container.push_back(elem);
}
void Directory::__RemoveElement(ElementIterator elem)
{
	m_container.erase(elem);
}
void Directory::__RemoveElement(Element* elem)
{
	IF_DEBUG(
	std::cout << "DIRECTORY-[" << this << "]: Removing element [" << elem <<"] from the list of children.\n";
	)
	__RemoveElement(IGetByPointer(elem));
}


void Directory::AddElement(Element* elem)
{
	elem->__SetParent(this);
	__AddElement(elem);
}

void Directory::RemoveElement(ElementIterator elem)
{
	(*elem)->__SetParent(0);
	__RemoveElement(elem);
}

void Directory::RemoveElement(Element* elem)
{
	elem->__SetParent(0);
	__RemoveElement(elem);
}

std::string Directory::GetPath()
{
	if(root) return "";
	else return Element::GetPath();
}

ElementContainer* Directory::GetContainer()
{
	return &m_container;
}

}
