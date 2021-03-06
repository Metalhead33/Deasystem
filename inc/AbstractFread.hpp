/* 
 * File:   AbstractFread.hpp
 * Author: metalhead33
 *
 * Created on 2017. február 23., 17:17
 */

#ifndef ABSTRACTFREAD_HPP
#define ABSTRACTFREAD_HPP
#include <cstdint>
namespace Dea {

class AbstractFread {
public:
	virtual ~AbstractFread() {;}
	virtual int64_t read(void* data, int64_t size) = 0;
	virtual int64_t seek(int64_t position) = 0;
	virtual int64_t tell() = 0;
	virtual int64_t size() = 0;
	virtual char getc() = 0;
private:

};

}

#endif /* ABSTRACTFREAD_HPP */

