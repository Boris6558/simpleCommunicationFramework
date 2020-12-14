#ifndef __STRING_OP_HPP__
#define __STRING_OP_HPP__

#include <cstring>
#include <string>
#include <stdlib.h>

#include "def/tooldef.hpp"
#include "def/basedef.hpp"

void SplitString(std::string &read_data,std::string split_symb, ProtocolPack &out_sp __ARG_OUT)
{
	std::string split_ = "";
	std::string split[2];	// 对应SplitPack里的成员
	int param_index = 0;
	int symbo_count = 1;
	for (int i = 0; i < read_data.size(); i++)
	{
		char s1 = read_data[i];
		if (s1 == split_symb[0])
		{
			symbo_count++;
			split_ += CastTo(std::string,s1);

			if (symbo_count % 2 == 0)
			{
				param_index++;
				symbo_count = 0;
			}

			continue;
		}

		split[param_index] += CastTo(std::string, s1);
	}

	if (split_.compare(split_symb) != 0) // 说明不是协议的内容
	{
		return;
	}
	out_sp.msg_type = CastTo(int, split[0]);
	out_sp.msg_content = CastTo(std::string, split[1]);
}


#endif // !__STRING_OP_HPP__
