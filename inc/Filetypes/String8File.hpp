/* 
 * File:   String8File.hpp
 * Author: metalhead33
 *
 * Created on 2017. február 24., 17:28
 */

#ifndef STRING8FILE_HPP
#define STRING8FILE_HPP
#include "File.hpp"
namespace Dea {
class String8File : public File {
public:
	String8File(Directory* parent, std::string name, std::string content="");
	virtual ~String8File();
	std::string* GetContent();
	void SetContent(std::string new_content);
	void Serialize(AbstractFwrite* file_handle);
	Filetype GetFiletype();
private:
	std::string m_content;

};
}
#endif /* STRING8FILE_HPP */

