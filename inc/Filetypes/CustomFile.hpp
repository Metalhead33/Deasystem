/* 
 * File:   CustomFile.hpp
 * Author: metalhead33
 *
 * Created on 2017. február 24., 19:07
 */

#ifndef CUSTOMFILE_HPP
#define CUSTOMFILE_HPP
#include "../File.hpp"
#include "../Global.hpp"
#include <cstdint>
namespace Dea {
	
template <typename type,Filetype typemod> class CustomFile : public File {
	private:
		type m_content;
	public:
		CustomFile(Directory* parent, std::string name,type new_content)
			: File(parent,name)
		{
			m_content = new_content;
		}
		virtual ~CustomFile() {;}
		Filetype GetFiletype() { return typemod; }
		void Serialize(AbstractFwrite* file_handle)
		{
			File::Serialize(file_handle);
			IF_DEBUG(
			std::cout << "[" << this << "]: Serializing custom file with size" << sizeof(type) << ".\n";
			)
			file_handle->write(&m_content,sizeof(type));
		}
		void SetContent(type new_content) { m_content = new_content; }
		type GetContent() { return m_content; }
};

typedef CustomFile<bool,boolean> BoolFile; 
typedef CustomFile<int8_t,int8> Int8File; 
typedef CustomFile<int16_t,int16> Int16File; 
typedef CustomFile<int32_t,int32> Int32File; 
typedef CustomFile<int64_t,int64> Int64File; 
typedef CustomFile<uint8_t,uint8> Uint8File; 
typedef CustomFile<uint16_t,uint16> Uint16File; 
typedef CustomFile<uint32_t,uint32> Uint32File; 
typedef CustomFile<uint64_t,uint64> Uint64File; 
typedef CustomFile<float,float32> FloatFile; 
typedef CustomFile<double,float64> DoubleFile; 

}


#endif /* CUSTOMFILE_HPP */

