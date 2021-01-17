#ifndef __BASEDEF_HPP__
#define __BASEDEF_HPP__

#include <iostream>

#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

typedef char								*pchar;
typedef unsigned char				uchar,	*puchar;
typedef short								*pshort;
typedef unsigned short				ushort,	*pushort;
typedef int									*pint;
typedef unsigned int				uint,	*puint;
typedef long								*plong;
typedef unsigned long				ulong,	*pulong;
typedef long long							*pllong;
typedef unsigned long long			ullong,	*pullong;
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
#define __DEPRECATED

#endif // !__BASEDEF_HPP__
