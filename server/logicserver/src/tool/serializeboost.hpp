#ifndef __SERIALIZE_BOOST_HPP__
#define __SERIALIZE_BOOST_HPP__

#include <boost/archive/binary_iarchive.hpp> 
#include <boost/archive/binary_oarchive.hpp> 

#include <string>
#include <cstring>

#include "stockstruct/userstock.hpp"
#include "serializememory.hpp"

#define SERIALIAZER_OBJ(class_name,...)														\
template<class Archive>																		\
void serialize(Archive &_ar, class_name &m_##class_name, const unsigned int _version)		\
{																							\
	__VA_ARGS__																				\
}

#define SERIALIAZER_FUN(class_name,serillizer_str)												\
void Serillazer##class_name(class_name &_m_class,std::string &serillizer_str)					\
{																								\
	std::ostringstream os;																		\
	boost::archive::binary_oarchive oa(os);														\
	oa << _m_class;																				\
	serillizer_str = os.str();																	\
	serillizer_str = StrToHex(serillizer_str);													\
}

#define UNSERIALIAZER_FUN(class_name,serillizer_str)											\
void UnSerillazer##class_name(class_name &_m_class,std::string &serillizer_str)					\
{																								\
	serillizer_str = HexToStr(serillizer_str);													\
	std::istringstream is(serillizer_str);														\
	boost::archive::binary_iarchive ia(is);														\
	ia >> _m_class;																				\
}

#define DEF_SERIALIZER_INTERFACE(class_name)									\
	std::string g_seri_str_##class_name = "";									\
	SERIALIAZER_FUN(class_name, g_seri_str_##class_name)						\
	UNSERIALIAZER_FUN(class_name, g_seri_str_##class_name)						
	


namespace boost{namespace serialization
{
	// 序列化对象

}}


// 提供序列化接口 调用DEF_SERIALIZER_INTERFACE宏即可

#endif // !__SERIALIZE_BOOST_HPP__
