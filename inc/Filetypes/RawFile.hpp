/* 
 * File:   RawFile.hpp
 * Author: metalhead33
 *
 * Created on 2017. február 24., 17:03
 */

#ifndef RAWFILE_HPP
#define RAWFILE_HPP
#include "../File.hpp"
#include <cstdlib>
namespace Dea {
class RawFile : public File {
public:
	RawFile(Directory* parent, std::string name,void* ptr,size_t size);
	RawFile(Directory* parent, std::string name,size_t size);
	virtual ~RawFile();
	bool IsCactivated(); // Returns whether this raw file's data was allocated C-style, or just got pointed at randomly
	void* GetPointer();
	size_t GetSize();
	void Serialize(AbstractFwrite* file_handle);
	
	void Malloc(size_t new_size);
	void Free();
	void SetPointer(void* new_ptr,size_t new_size);
	
	Filetype GetFiletype();
private:
	bool cactivated;
	void* raw_data;
	size_t data_size;
};
}
#endif /* RAWFILE_HPP */

