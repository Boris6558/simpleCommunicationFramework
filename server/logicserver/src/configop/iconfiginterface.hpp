#ifndef __XMLOP_HPP__
#define __XMLOP_HPP__

#include "def/iconfiginterfacedef.hpp"

#define LOAD_NODE(node_,fun)																						\
do																													\
{																													\
	if (this->Load(path))																							\
	{																												\
		PTree node;																									\
		this->SetNode(node_, &node);																				\
		int ret = this->fun(node);																					\
		if (ret != 0)																								\
		{																											\
			printf("(%s: %d)error[%s]: config init fail! function[%s],return error value[%d]\n",					\
				__FILE__, __LINE__,__FUNCTION__ ,#fun, ret);														\
			return ret;																								\
		}																											\
	}																												\
} while (0);

class IConfigInterface
{
public:
	IConfigInterface();
	virtual ~IConfigInterface();

	virtual int Init(std::string path) = 0;
	bool Load(std::string path);
	void SetNode(std::string node, PTree *node_pt __ARG_OUT);

private:
	PTree pt;

};

#endif // !__XMLOP_HPP__
