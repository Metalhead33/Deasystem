/* 
 * File:   String32File.hpp
 * Author: metalhead33
 *
 * Created on 2017. február 24., 18:04
 */

#ifndef STRING32FILE_HPP
#define STRING32FILE_HPP
#include "File.hpp"
#include <string>
namespace Dea {
class String32File : public File {
public:
	String32File(Directory* parent, std::string name, std::u32string content=U"");
	virtual ~String32File();
	std::u32string* GetContent();
	void SetContent(std::u32string new_content);
	void Serialize(AbstractFwrite* file_handle);
	Filetype GetFiletype();
private:
	std::u32string m_content;

};
}
#endif /* STRING32FILE_HPP */

