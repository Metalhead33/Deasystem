/* 
 * File:   File.hpp
 * Author: metalhead33
 *
 * Created on 2017. február 24., 16:37
 */

#ifndef FILE_HPP
#define FILE_HPP
#include "Element.hpp"

namespace Dea {
	
enum Filetype {
	dummy,
	raw,
	custom,
	boolean,
	int8,
	int16,
	int32,
	int64,
	uint8,
	uint16,
	uint32,
	uint64,
	float32,
	float64,
	string8,
	string16,
	string32
};
	
class File : public Element {
public:
	File(Directory* parent, std::string name);
	virtual ~File();
	virtual Filetype GetFiletype() = 0;
	
	bool IsDirectory();
	bool IsData();
	virtual void Serialize(AbstractFwrite* file_handle);
private:

};
}
#endif /* FILE_HPP */

