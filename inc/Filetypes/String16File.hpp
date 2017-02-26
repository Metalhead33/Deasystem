/* 
 * File:   String16File.hpp
 * Author: metalhead33
 *
 * Created on 2017. február 24., 17:47
 */

#ifndef STRING16FILE_HPP
#define STRING16FILE_HPP
#include "File.hpp"
#include <string>
namespace Dea {
class String16File : public File {
public:
	String16File(Directory* parent, std::string name, std::u16string content=u"");
	virtual ~String16File();
	std::u16string* GetContent();
	void SetContent(std::u16string new_content);
	void Serialize(AbstractFwrite* file_handle);
	Filetype GetFiletype();
private:
	std::u16string m_content;

};
}
#endif /* STRING16FILE_HPP */

