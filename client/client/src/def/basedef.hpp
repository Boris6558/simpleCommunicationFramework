#ifndef __BASEDEF_HPP__
#define __BASEDEF_HPP__

#include <iostream>

#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>



typedef unsigned char				uchar;
typedef unsigned short				ushort;
typedef unsigned int				uint;
typedef unsigned long				ulong;
typedef unsigned long long			ullong;
typedef char						CString[64];

#define TO_STRING(v) #v
#define CastTo(type,value) boost::lexical_cast<type>((value))

#define _F(format_str,...)		\
  (boost::format(format_str)	\
  __VA_ARGS__					\
  ).str()

#define __ARG_OUT
#define __ARG_IN
#define __ARG_OUT_AND_IN

#endif // !__BASEDEF_HPP__
