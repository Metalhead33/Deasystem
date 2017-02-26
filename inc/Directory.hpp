/* 
 * File:   Directory.hpp
 * Author: metalhead33
 *
 * Created on 2017. február 23., 18:48
 */

#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP
#include "Element.hpp"
#include <list>
namespace Dea {
	
typedef std::list<Element*> ElementContainer;
typedef std::list<Element*>::iterator ElementIterator;
	
class Directory : public Element {
	friend class Element;
public:
	Directory(Directory* parent, std::string name, bool _isroot = false);
	virtual ~Directory();
	bool IsDirectory();
	bool IsData();
	void Serialize(AbstractFwrite* file_handle);
	bool IsRoot();
	void SetRoot(bool set_root);
	std::string GetPath(); //Total path.
	
	ElementIterator IGetByRowSafe(int row); //Slower but safer
	//ElementIterator IGetByRowUnsafe(int row); //Faster but not-so-safe
	ElementIterator IGetByName(std::string name);
	ElementIterator IGetByPointer(Element* elem);
	
	Element* PGetByRowSafe(int row); //Slower but safer
	//Element* PGetByRowUnsafe(int row); //Faster but not-so-safe
	Element* PGetByName(std::string name);
	Element* PGetByPointer(Element* elem);
	
	void AddElement(Element* elem); // Calls back in the given element
	void RemoveElement(ElementIterator elem); // Calls back in the given element
	void RemoveElement(Element* elem); // Calls back in the given element
private:
	ElementContainer m_container;
	bool root;
	void __AddElement(Element* elem); // Unsafe, doesn't call back in the given element. Should be only used in Element's functions.
	void __RemoveElement(ElementIterator elem); // Unsafe, doesn't call back in the given element. Should be only used in Element's functions.
	void __RemoveElement(Element* elem); // Unsafe, doesn't call back in the given element. Should be only used in Element's functions.
};
}
#endif /* DIRECTORY_HPP */

