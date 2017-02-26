/* 
 * File:   Element.hpp
 * Author: metalhead33
 *
 * Created on 2017. február 23., 18:25
 */

#ifndef ELEMENT_HPP
#define ELEMENT_HPP
#include <string>
#include "AbstractFwrite.hpp"
namespace Dea {
	
class Directory;
	
class Element {
	friend class Directory;
public:
	//Element();
	Element(Directory* parent, std::string name);
	virtual ~Element();
	std::string GetName() const;
	void SetName(std::string new_name);
	std::string GetPath(); //Total path.
	Directory* GetParent() const;
	void SetParent(Directory* new_parent); //Also removes from previous parent + adds to list of new parent. Safe, but shouldn't be ever called by the parent's functions.
	
	virtual bool IsDirectory() = 0;
	virtual bool IsData() = 0;
	virtual void Serialize(AbstractFwrite* file_handle);
private:
	Directory* m_parent; //Containing directory
	std::string m_name; //Name
	void __SetParent(Directory* new_parent); //Unsafe, and should only be used from within the parent's functions. Only removes parent from the element itself, doesn't notify the parent.
};
}
#endif /* ELEMENT_HPP */

