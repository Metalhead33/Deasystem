/* 
 * File:   FsSystem.cpp
 * Author: metalhead33
 * 
 * Created on 2017. február 23., 22:56
 */

#include "FsSystem.hpp"
#include <cstdlib>
#include <cstring>
std::vector<std::string> StringSplit( std::string str, char sep) // Written by JLBorges
{
	std::vector<std::string> ret ;
	char* temp_str = (char*)malloc(str.size() + 1);
	strcpy(temp_str,str.c_str());
	char *tempp1=temp_str;
	if(*tempp1 == sep) ++tempp1;
	char *tempp2=tempp1;
	for(;*tempp1;++tempp1)
	{
		if(*tempp1 == sep)
		{
			*tempp1 = 0;
			ret.push_back(tempp2);
			tempp2 = tempp1 + 1;
		}
		else if( !(*(tempp1+1)) )
		{
			ret.push_back(tempp2);
		}
	}
	//std::istringstream stm(str) ;
	//std::string token ;
	//while( std::getline( stm, token, sep ) ) ret.push_back(token) ;
	free(temp_str);
	IF_DEBUG(
	std::cout << "Tokenized the string \"" << str <<"\" with the tokenizer \'" << sep << "\', producing " << ret.size() << " tokens.\n";
	)
	return ret ;
}

std::vector<std::string> StringSplit( char* str, char sep)
{
	return StringSplit(std::string(str),sep);
}

namespace Dea {

FsSystem::FsSystem()
{
	ROOT = new Directory(0,"ROOT",true);
}

FsSystem::~FsSystem() {
	delete ROOT;
}

Directory* FsSystem::GetRoot()
{
	return ROOT;
}

Element* FsSystem::SeekElement(std::vector<std::string> path)
{
	std::vector<std::string>::iterator it;
	std::vector<std::string>::iterator end = path.end();
	Element* elem = ROOT;
	for(it = path.begin();it != end;++it)
	{
		IF_DEBUG(
		std::cout << "FSYSTEM: Currently at parent [" << elem << "], token \"" << *it << "\".\n";
		)
		if(!elem) break;
		if(elem->IsDirectory())
		{
			elem = ((Directory*)elem)->PGetByName(*it);
		}
		else break;
	}
	IF_DEBUG(
	std::cout << "FSYSTEM: Iteration over.\n";
	)
	if(!elem) return 0;
	
	if(elem->GetName() == *(path.rbegin()) ) return elem;
	else return 0;
}
Element* FsSystem::SeekElement(std::string path)
{
	return SeekElement(StringSplit(path,'/'));
}
Directory* FsSystem::Mkdir(std::vector<std::string> path)
{
	std::vector<std::string>::iterator it = path.begin();
	std::vector<std::string>::iterator end = path.end();
	Element* elem = ROOT;
	Element* prev;
	for(;it != end;++it)
	{
		prev = elem;
		if(elem->IsDirectory()) elem = ((Directory*)elem)->PGetByName(*it);
		if(elem)
		{
			if(elem->IsData()) return 0;
		}
		else elem = new Directory((Directory*)prev,*it);
	}
	return (Directory*)elem;
}
Directory* FsSystem::Mkdir(std::string path)
{
	return Mkdir(StringSplit(path,'/'));
}

Element* FsSystem::SeekElement(char* path)
{
	if(!path) return 0;
	else return SeekElement( std::string(path) );
}
Directory* FsSystem::Mkdir(char* path)
{
	if(!path) return 0;
	else return Mkdir( std::string(path) );
}
	
bool FsSystem::Unserialize(AbstractFread* file_handle)
{
	IF_DEBUG(
	std::cout << "DESERIALIZATION BEGINNING.\n";
	)
	char* buf = 0;
	bool eof_signal = false;
	char eof_sampler[4];
	while(!eof_signal)
	{
		if(buf) free(buf);
		buf = 0;
		// Preparations
		char tmp;
		int i = 0;
		uint16_t name_size;
		int8_t type;
		Element* temp_elem;
		Directory* parent;
		
		// Figure out how large is the path of the file
		file_handle->read(&name_size,sizeof(uint16_t));
		// Read the actual path of the file and create its parent directory.
		buf = (char*)malloc(sizeof(char) * name_size);
		file_handle->read(buf,sizeof(char) * name_size);
		IF_DEBUG(
		std::cout << "Creating the file \"" << std::string(buf) << "\".\n";
		)
		
		temp_elem = SeekElement(buf); // Make sure the file doesn't exist already.
		if(temp_elem)
		{
			delete temp_elem;
			temp_elem = 0;
		}
		std::vector<std::string> path = StringSplit(buf,'/');
		
		std::string elem_name = *(path.rbegin());
		if(path.size() >= 2)
		{
			path.pop_back();
			parent = Mkdir(path);
		}
		else parent = ROOT; // Determining the parent
		// Read the filetype
		file_handle->read(&type,sizeof(int8_t));
		if(type < 0) temp_elem = new Directory(parent,elem_name);
				else switch((Filetype)type)
				{
					case raw:
					{
						uint32_t raw_sizeof;
						file_handle->read(&raw_sizeof,sizeof(uint32_t));
						temp_elem = new RawFile(parent,elem_name,raw_sizeof);
						file_handle->read(((RawFile*)temp_elem)->GetPointer(),raw_sizeof);
						IF_DEBUG(
						std::cout << "[" << temp_elem << "]: Deserialized raw file with size " << raw_sizeof << ".\n";
						)
						break;
					}
					case boolean:
					{
						bool tmp_bool;
						file_handle->read(&tmp_bool,sizeof(bool));
						temp_elem = new BoolFile(parent,elem_name,tmp_bool);
						IF_DEBUG(
						std::cout << "[" << temp_elem << "]: Deserialized bool file with value " << tmp_bool << ".\n";
						)
						break;
					}
					case int8:
					{
						int8_t tmp_int8;
						file_handle->read(&tmp_int8,sizeof(int8_t));
						temp_elem = new Int8File(parent,elem_name,tmp_int8);
						IF_DEBUG(
						std::cout << "[" << temp_elem << "]: Deserialized Int8 file with value " << tmp_int8 << ".\n";
						)
						break;
					}
					case int16:
					{
						int16_t tmp_int16;
						file_handle->read(&tmp_int16,sizeof(int16_t));
						temp_elem = new Int16File(parent,elem_name,tmp_int16);
						IF_DEBUG(
						std::cout << "[" << temp_elem << "]: Deserialized Int16 file with value " << tmp_int16 << ".\n";
						)
						break;
					}
					case int32:
					{
						int32_t tmp_int32;
						file_handle->read(&tmp_int32,sizeof(int32_t));
						temp_elem = new Int32File(parent,elem_name,tmp_int32);
						IF_DEBUG(
						std::cout << "[" << temp_elem << "]: Deserialized Int32 file with value " << tmp_int32 << ".\n";
						)
						break;
					}
					case int64:
					{
						int64_t tmp_int64;
						file_handle->read(&tmp_int64,sizeof(int64_t));
						temp_elem = new Int64File(parent,elem_name,tmp_int64);
						IF_DEBUG(
						std::cout << "[" << temp_elem << "]: Deserialized Int64 file with value " << tmp_int64 << ".\n";
						)
						break;
					}
					case uint8:
					{
						uint8_t tmp_uint8;
						file_handle->read(&tmp_uint8,sizeof(uint8_t));
						temp_elem = new Uint8File(parent,elem_name,tmp_uint8);
						IF_DEBUG(
						std::cout << "[" << temp_elem << "]: Deserialized Uint8 file with value " << tmp_uint8 << ".\n";
						)
						break;
					}
					case uint16:
					{
						uint16_t tmp_uint16;
						file_handle->read(&tmp_uint16,sizeof(uint16_t));
						temp_elem = new Uint16File(parent,elem_name,tmp_uint16);
						IF_DEBUG(
						std::cout << "[" << temp_elem << "]: Deserialized Uint16 file with value " << tmp_uint16 << ".\n";
						)
						break;
					}
					case uint32:
					{
						uint32_t tmp_uint32;
						file_handle->read(&tmp_uint32,sizeof(uint32_t));
						temp_elem = new Uint32File(parent,elem_name,tmp_uint32);
						IF_DEBUG(
						std::cout << "[" << temp_elem << "]: Deserialized Uint32 file with value " << tmp_uint32 << ".\n";
						)
						break;
					}
					case uint64:
					{
						uint64_t tmp_uint64;
						file_handle->read(&tmp_uint64,sizeof(uint64_t));
						temp_elem = new Uint64File(parent,elem_name,tmp_uint64);
						IF_DEBUG(
						std::cout << "[" << temp_elem << "]: Deserialized Uint64 file with value " << tmp_uint64 << ".\n";
						)
						break;
					}
					case float32:
					{
						float tmp_float;
						file_handle->read(&tmp_float,sizeof(float));
						temp_elem = new FloatFile(parent,elem_name,tmp_float);
						IF_DEBUG(
						std::cout << "[" << temp_elem << "]: Deserialized Float file with value " << tmp_float << ".\n";
						)
						break;
					}
					case float64:
					{
						double tmp_double;
						file_handle->read(&tmp_double,sizeof(double));
						temp_elem = new DoubleFile(parent,elem_name,tmp_double);
						IF_DEBUG(
						std::cout << "[" << temp_elem << "]: Deserialized Double file with value " << tmp_double << ".\n";
						)
						break;
					}
					case string8:
					{
						uint32_t raw_stringsize;
						file_handle->read(&raw_stringsize,sizeof(uint32_t));
						char* stringer = (char*)malloc(sizeof(char) * raw_stringsize);
						file_handle->read(stringer,sizeof(char) * raw_stringsize);
						temp_elem = new String8File(parent,elem_name,std::string(stringer));
						free(stringer);
						IF_DEBUG(
						std::cout << "[" << temp_elem << "]: Deserialized String8 file with length " << raw_stringsize << ".\n";
						)
						break;
					}
					case string16:
					{
						uint32_t raw_stringsize;
						file_handle->read(&raw_stringsize,sizeof(uint32_t));
						char16_t* stringer = (char16_t*)malloc(sizeof(char16_t) * raw_stringsize);
						file_handle->read(stringer,sizeof(char16_t) * raw_stringsize);
						temp_elem = new String16File(parent,elem_name,std::u16string(stringer));
						free(stringer);
						IF_DEBUG(
						std::cout << "[" << temp_elem << "]: Deserialized String16 file with length " << raw_stringsize << ".\n";
						)
						break;
					}
					case string32:
					{
						uint32_t raw_stringsize;
						file_handle->read(&raw_stringsize,sizeof(uint32_t));
						char32_t* stringer = (char32_t*)malloc(sizeof(char32_t) * raw_stringsize);
						file_handle->read(stringer,sizeof(char32_t) * raw_stringsize);
						temp_elem = new String32File(parent,elem_name,std::u32string(stringer));
						free(stringer);
						IF_DEBUG(
						std::cout << "[" << temp_elem << "]: Deserialized String32 file with length " << raw_stringsize << ".\n";
						)
						break;
					}
					default:
						break;
				}
			IF_DEBUG(
			std::cout << "Deserialized \"" << temp_elem->GetPath() << "\".\nNow checking if EOF or not.\n";
			)
			file_handle->read(eof_sampler,4);
			eof_sampler[3] = 0;
			if(!strcmp(eof_sampler,"EOF"))
			{
				eof_signal = true;
				IF_DEBUG(
				std::cout << "This is the end of the file.\n";
				)
			}
			else
			{
				file_handle->seek(file_handle->tell()-4);
				eof_signal = false;
			}
	}
	file_handle->seek(0);
	IF_DEBUG(
	std::cout << "DESERIALIZATION OVER.\n";
	)
}

void FsSystem::Serialize(AbstractFwrite* file_handle)
{
	IF_DEBUG(
	std::cout << "SERIALIZATION BEGINNING.\n";
	)
	ROOT->Serialize(file_handle);
	char* eof = "EOF";
	file_handle->write(eof,4);
	IF_DEBUG(
	std::cout << "SERIALIZATION OVER.\n";
	)
}

}