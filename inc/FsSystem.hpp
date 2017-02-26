/* 
 * File:   FsSystem.hpp
 * Author: metalhead33
 *
 * Created on 2017. február 23., 22:56
 */

#ifndef FSSYSTEM_HPP
#define FSSYSTEM_HPP
#include "Directory.hpp"
#include "AbstractFread.hpp"
#include "Global.hpp"
#include "RawFile.hpp"
#include "CustomFile.hpp"
#include "String8File.hpp"
#include "String16File.hpp"
#include "String32File.hpp"
#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> StringSplit( std::string str, char sep = ' ' );
std::vector<std::string> StringSplit( char* str, char sep = ' ' );

namespace Dea {
class FsSystem {
public:
	FsSystem();
	virtual ~FsSystem();
	
	Element* SeekElement(std::vector<std::string> path);
	Element* SeekElement(std::string path);
	Element* SeekElement(char* path);
	Directory* GetRoot();
	Directory* Mkdir(std::vector<std::string> path);
	Directory* Mkdir(std::string path);
	Directory* Mkdir(char* path);
	bool Unserialize(AbstractFread* file_handle);
	void Serialize(AbstractFwrite* file_handle);
private:
	Directory* ROOT;
};
}

#endif /* FSSYSTEM_HPP */

