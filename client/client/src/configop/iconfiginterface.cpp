#include "iconfiginterface.hpp"

IConfigInterface::IConfigInterface()
{
}

IConfigInterface::~IConfigInterface()
{
}

bool IConfigInterface::Load(std::string path)
{
	LOAD_XML(CONFIG_BASE_DIR + path, pt);

	if (pt.empty())
	{
		return false;
	}
	return true;
}

void IConfigInterface::SetNode(std::string node, PTree *node_pt __ARG_OUT)
{
	*node_pt = pt.get_child(node);

	if (node_pt == NULL)
	{
		printf("(%s: %d)error[%s]: node_pt is NULL\n",__FILE__, __LINE__, __FUNCTION__);
		BOOST_ASSERT(node_pt != NULL);
	}

}
